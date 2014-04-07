#ifndef FORESTS_CODE_H_OCT_2013
#define FORESTS_CODE_H_OCT_2013


/**************************************************

Only declarations and single-line functions in this file.
functions are implemented in trunk.cpp and branch.cpp

If you want a new kind of tree, 
create a new branch.cpp and change the silly.cpp includings.

**************************************************/


#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <ctime>
#include <cmath>

#include "memman.h"
#include "mylib.h"

const double sigma_const = 255 * 0.1;

class Edge {
public :
    int a, b; // Node ID
    int weight;
};

class MergeSet {
public :
    int n;  int f[NODES];
    int find(int x); 
    void init(int x);
    bool merge(int a, int b);
};

class TreeNode {
public :
	int x, y, id ; // id = its index in an array
	int ord, up_weight; // the bfs order and the edge weight to parent after direct tree constructed
	TreeNode() {}
	TreeNode(int a, int b) : x(a) , y(b) {}
    int degree, next_node[4], edge_weight[4];
    void add_edge(int node, int weight);
};

class BigObject {
public :

    MergeSet mset; // for buiding the tree
    Edge edges[NODES * 2]; // all candidate edges  1-based
    Edge trees[NODES]; // collected tree edges 1-based
    int n, m; // number of nodes and edges
    int ts; // number of tree edges
    int H, W; // graph info
    //int node_number(int x, int y) { return x * W + y + 1; }
    //void node_location(int p, int &x, int &y) {--p; x = p / W; y = p % W; }

    // next three are in trunck.cpp
    void collect_edges(Picture rgb); // collect all the edges.
	void prepare_visit();  // construct the bfs order for the forest

    // next three are in branch.cpp
    void build_tree(); // build the tree given all the collected edges.
	void compute_cost_on_tree(FloArray cost, double sigma = 255 * 0.1 );

    TreeNode * nodes;
    bool * visited;
	int * order; // the sequence of index, the visiting order of the tree
//Array3<double> backup; // used in calculate cost on tree
	double table[256]; // weight table

};

#endif
