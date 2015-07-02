#ifndef ASSEMBLY_HPP
#define ASSEMBLY_HPP

#include <string>
#include <vector>
#include <iostream>
#include "algebra.hpp"
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

class Assembly
{
public:
	// Assembly(const string& name, 
	// 	vector<vector<double> > vs, 
	// 	vector<vector<double> > us, 
	// 	vector<vector<double> > ns,
	// 	vector<vector<vector<int> > > fs);
	Assembly(const string& name,
		vector<vector<double> > us, 
		vector<vector<double> > ns,
		vector<vector<vector<int> > > fs,
		const Colour& kd, const Colour& ks, double shininess);
	~Assembly();

string getname();

void set_material(const Colour& kd, const Colour& ks, double shininess);

void drawAssembly(vector<vector<double> > vs);

vector<vector<vector<int> > > getfaces();

Colour getkd();

Colour getks();

double getshininess();

private:
	string partname;
	vector<vector<double> > uvs;
	vector<vector<double> > normals;
	vector<vector<vector<int> > > faces;
	Colour a_kd;
	Colour a_ks;
	double a_shininess;
};

#endif