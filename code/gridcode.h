#ifndef GRID_CODE_H_OCT_2013
#define GRID_CODE_H_OCT_2013
#include <cstdlib>
#include <cstring>
#include <cassert>
// this code is meant for memory management

#define PADDING 10

template <class type>
class Grid {
public :
	type ** grid;
	int height, width;
	Grid<type> () {height = width = -1; }
	Grid<type> (int H, int W) {
		reset(H, W);
	}
/*
	void reset(int H, int W) {
		height = H; width = W;
		grid = (type **) malloc(H * sizeof(type *));
		for (int i = 0; i < H; ++i) 
			grid[i] = (type *) malloc(W * sizeof(type));
	}
*/
	void reset(int H, int W) {
		height = H;
		width = W;
		type *a;
		a = (type*) malloc(sizeof(type) * (height * width + PADDING));
        assert(a != NULL);
        /*if(a == NULL) {
			printf("reset() fail, Memory is too huge, fail.\n"); 
			getchar();
			exit(0);
		} */
		grid = (type**) malloc(sizeof(type*) * height);
		for(int i = 0; i < height; i++)
			grid[i] = &a[i*width];
	}

	Grid<type> (Grid<type> & other) {
		reset(other.height, other.width);
		copy(other);
	}
	void copy(Grid<type> &other) {
		if (other.height != height || other.width != width)
			reset(other.height, other.width);
		for (int i = 0; i < height; ++i) 
			memcpy(grid[i], other.grid[i], width * sizeof(type));
	}
	void zero() {
		//reset(height, width);
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				grid[i][j] = 0;
			}
		}
	}
	type * operator[] (int index) { return grid[index]; }
};

template <class type>
class Array3 {
public :
	int height, width, array;
	Grid<type> ** mat;
	Array3<type> () { array=height=width=-1;  }
	Array3<type> (int arr, int H, int W) {
		reset(arr, H, W);
	}

	void reset(int arr, int H, int W) {
		height = H, width = W, array = arr;
		mat = (Grid<type> **) malloc(array * sizeof(Grid<type> *));
		for (int i = 0; i < array; ++i)
			mat[i] = new Grid<type>(H, W);
	}

	Array3<type>(Array3<type> & other) {
		reset(other.height, other.width, other.array);
		copy(other);
	}
	void copy(Array3<type> & other) {
		if (other.height != height || other.width != width || other.array != array)
			reset(other.array, other.height, other.width);
		for (int i = 0; i < array; ++i)
			mat[i]->copy(other[i]);
	}
	void zero() {
		//reset(array, height, width);
		for (int a = 0; a < array; ++a) {
			mat[a]->zero();
		}
	}
	Grid<type> & operator[] (int index) { return *mat[index]; }
};

#endif
