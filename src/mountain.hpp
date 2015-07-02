#ifndef MOUNTAIN_HPP
#define MOUNTAIN_HPP

#include <string>
#include <vector>
#include <iostream>
#include "algebra.hpp"
#include <cstdlib>
#include <ctime>

using namespace std;

class Mountain
{
public:
	Mountain();
	~Mountain();

	vector<vector<Point3D> > getmountains();
	void generatemountains();

private:
	Point3D va,vb,vc,vd,ve,vf,vg,vh,vi;
	vector<vector<vector<Point3D> > > areas;
	vector<vector<Point3D> > mountains;
};

#endif