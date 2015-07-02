#ifndef LOAD_OBJ_HPP
#define LOAD_OBJ_HPP

#include <string>
#include <vector>
#include "assembly.hpp"

using namespace std;

class Object
{
public:
	Object(vector<vector<double> > vs);
	~Object();

	void add_assembly(Assembly ab);

	int get_assembly_size();

	void drawObject();

	vector<vector<double> > getverts();
	vector<vector<vector<int> > > getfaceindices(int ind);
	Colour getvkd(int index);
	Colour getvks(int index);
	double getvshininess(int index);
private:
	vector<vector<double> > verts;
	vector<Assembly> v_ab;
	vector<Colour> v_kd;
	vector<Colour> v_ks;
	vector<double> v_shininess;
};



#endif