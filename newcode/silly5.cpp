// This code is for dpf-RT

#include "settings.h" // the global variables, the constants, the array size 
#include "misc.cpp" // misc. 
#include "iomanager.h" // read and write pictures.

#include "prediction.h" // the prediction model

#include "arbol1.h" // the declaration of 'BigObject'
#include "tree5.cpp"

#include "timekeeper.h"

TimeKeeper timer;

BigObject left[LEVELS], right[LEVELS];

const int levels = 3;

const char layername[3][2][100] = { 
    { "nl0.pgm", "nr0.pgm"}, 
    { "nl1.pgm", "nr1.pgm"}, 
    { "nl2.pgm", "nr2.pgm"}
};

const char shrinkname[3][2][100] = {
    { "skL0.ppm", "skR0.ppm" },
    { "skL1.ppm", "skR1.ppm" },
    { "skL2.ppm", "skR2.ppm" }
};

int main(int args, char ** argv) {
    misc::process_args(args, argv);
    load_image(file_name[0], left[0].rgb, left[0].H, left[0].W);
    load_image(file_name[1], right[0].rgb, right[0].H, right[0].W);
    if (left[0].H != right[0].H || left[0].W != right[0].W) {
        printf("The size of two pictures differ!! quit....");
        return 0;
    }
    if (left[0].H >= MAX_HEIGHT || right[0].W >= MAX_WIDTH) {
        printf("Input : %d x %d, program : %d %d\n", left[0].H, left[0].W, MAX_HEIGHT, MAX_WIDTH);
        puts("Image too big. change settings.h and re-compile.");
        return 0;
    }

    for (int i = 0; i + 1 < levels; ++i) {
        left[i].shrinkPicture(left[i + 1]);
        right[i].shrinkPicture(right[i + 1]);

        save_image_rgb(shrinkname[i + 1][0], left[i + 1].rgb, left[i+1].H, left[i+1].W);
        save_image_rgb(shrinkname[i + 1][1], right[i + 1].rgb, left[i+1].H, left[i+1].W);
    }

timer.reset();
    misc::process_args(args, argv);
    for (int lvl = levels - 1; lvl >= 0; -- lvl) {

        if (lvl == levels - 1) {
            left[lvl].noPrediction(max_disparity / (1 << lvl));
            right[lvl].noPrediction(max_disparity / (1 << lvl));
        } else {
            // between two layers now, do the prediction
            dpf::getSupportProb(left[lvl].rgb, right[lvl].rgb, 
                                left[lvl].H, left[lvl].W, max_disparity / (1 << lvl));
            dpf::getProbMatrix(lvl, max_disparity / (1 << (lvl + 1)), max_disparity / (1 << lvl));
            dpf::getInterval(0.001 * (1 << lvl));
            // printf("# %d\n", dpf::height);
            // for (int i = 0; i <= dpf::height; ++i) printf("%d %d\n", dpf::interval[i][0], dpf::interval[i][1]);
        
            left[lvl].readPrediction(left[lvl + 1].disparity);
            right[lvl].readPrediction(right[lvl + 1].disparity);
        } 
        // Now use the INTERVAL to find the new disparities.
// timer.check("prediction");
        left[lvl].buildForest(0.95);
        right[lvl].buildForest(0.95);
// timer.check("build forest");
        initDisparity(left[lvl], right[lvl]);
        updateTable(255 * 0.1);
        left[lvl].steroMatch(right[lvl], 1);
        right[lvl].steroMatch(left[lvl], -1);
// timer.check("steromatch");

        misc::median_filter(left[lvl].disparity, left[lvl].H, left[lvl].W);
        misc::median_filter(right[lvl].disparity, right[lvl].H, right[lvl].W); 

        findStablePixels(left[lvl], right[lvl]);
        initDisparity(left[lvl], right[lvl]);
        updateTable(255 * 0.05);
        left[lvl].refinement();
        right[lvl].refinement();

        misc::median_filter(left[lvl].disparity, left[lvl].H, left[lvl].W);
        misc::median_filter(right[lvl].disparity, right[lvl].H, right[lvl].W); 
// timer.check("refine");

        save_image(layername[lvl][0], left[lvl].disparity, left[lvl].H, left[lvl].W, scale * (1 << lvl));
        save_image(layername[lvl][1], right[lvl].disparity, right[lvl].H, right[lvl].W, scale * (1 << lvl));


    } // end of layer iteration.
timer.check("all");
	//save
    save_image(file_name[2], left[0].disparity, left[0].H, left[0].W, scale);
    save_image(file_name[3], right[0].disparity, right[0].H, right[0].W, scale);

    return 0;
}