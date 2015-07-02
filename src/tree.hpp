#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include "algebra.hpp"

using namespace std;

#define MAX_HEIGHT 10

class Tree
{
public:
	Tree();
	~Tree();

	void F();
	double G();

private:
	Point3D t_pos;
	vector<Point3D> braches;
	vector<Point3D> leaves;
	int t_seed;
	Matrix4x4 rot_matrix;
};

#endif