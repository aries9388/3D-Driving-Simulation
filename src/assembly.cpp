#include "assembly.hpp"
#include <iostream>

using namespace std;

Assembly::Assembly(const string& name,	
	vector<vector<double> > us, 
	vector<vector<double> > ns,
	vector<vector<vector<int> > > fs,
	const Colour& kd, const Colour& ks, double shininess)
	: partname(name),uvs(us),normals(ns),faces(fs),a_kd(kd),a_ks(ks),a_shininess(shininess)
{
}

Assembly::~Assembly()
{
}

string Assembly::getname()
{
	return partname;
}

void Assembly::set_material(const Colour& kd, const Colour& ks, double shininess)
{
	a_kd = kd;
	a_ks = ks;
	a_shininess = shininess;
}

void Assembly::drawAssembly(vector<vector<double> > vs)
{
	// GLfloat diffuse[] = {a_kd.R(),a_kd.G(),a_kd.B(),1.0};
	// GLfloat shininess[] = {a_shininess};
	// GLfloat specular[] = {a_ks.R(),a_ks.G(),a_ks.B(),1.0};
	// glMaterialfv(GL_FRONT, GL_DIFFUSE , diffuse);
	// glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	// glMaterialfv(GL_FRONT, GL_SHININESS,shininess);


	int v_vs1,v_vs2,v_vs3;
	for(unsigned int i = 0; i < faces.size(); i++)
	{
		cerr<<"Triangle "<<i<<endl;
		glBegin(GL_TRIANGLES);
		// for(unsigned int j = 0; j < 3; j++)
		// {
			v_vs1 = faces[i][0][0];
			v_vs2 = faces[i][1][0];
			v_vs3 = faces[i][2][0];
			// v_vn = faces[i][j][2];
			// cerr<<v_vs<<" ";
			// glNormal3d(vs[v_vs1][0],vs[v_vs1][1],vs[v_vs1][2]);
			glVertex3d(vs[v_vs1][0],vs[v_vs1][1],vs[v_vs1][2]);
			// glNormal3d(vs[v_vs2][0],vs[v_vs2][1],vs[v_vs2][2]);
			glVertex3d(vs[v_vs2][0],vs[v_vs2][1],vs[v_vs2][2]);
			// glNormal3d(vs[v_vs3][0],vs[v_vs3][1],vs[v_vs3][2]);
			glVertex3d(vs[v_vs3][0],vs[v_vs3][1],vs[v_vs3][2]);
		// }
		glEnd();
		// cerr<<endl;
	}
}

vector<vector<vector<int> > > Assembly::getfaces()
{
	return faces;
}

Colour Assembly::getkd()
{
	return a_kd;
}

Colour Assembly::getks()
{
	return a_ks;
}

double Assembly::getshininess()
{
	return a_shininess;
}