#ifndef TIMEKEEPER_H_OCT_2013
#define TIMEKEEPER_H_OCT_2013

#include <ctime>
#include <cstdio>

class TimeKeeper {
    clock_t keep, last; // start time, last check point
    int checked;
public :
    void reset() { 
        last = keep = clock();  checked = 0; 
        printf("Timer reset.\n");
    }
    void get_total_time() { 
        double delta = clock() - keep;
        printf("Total time elapsed: %.3fs\n", delta / CLOCKS_PER_SEC);
    }
    void check(const char * a) {
        double now = clock();
        printf("check point #%d - %s: %.3fs\n", ++checked, 
            a, (now - last) / CLOCKS_PER_SEC);
        last = now;
    }

};

#endif
