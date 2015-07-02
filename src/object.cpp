#include "object.hpp"
#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <vector>

Object::Object(vector<vector<double> > vs)
: verts(vs)
{
}

Object::~Object()
{
}

void Object::add_assembly(Assembly ab)
{
	v_ab.push_back(ab);
	v_kd.push_back(ab.getkd());
	v_ks.push_back(ab.getks());
	v_shininess.push_back(ab.getshininess());

}

int Object::get_assembly_size()
{
	return v_ab.size();
}

vector<vector<double> > Object::getverts()
{
	return verts;
}

vector<vector<vector<int> > > Object::getfaceindices(int ind)
{
	return v_ab[ind].getfaces();
}

Colour Object::getvkd(int index)
{
	return v_kd[index];
}

Colour Object::getvks(int index)
{
	return v_ks[index];
}

double Object::getvshininess(int index)
{
	return v_shininess[index];
}