#include "tree.hpp"

Tree::Tree(Point3D pos,int seed)
:t_pos(pos),t_seed(seed)
{
	rot_matrix = Matrix4x4();
}

Tree:~Tree()
{
}

void Tree::F()
{
	double newheight = G();

	double angle_x = (rand()%20)+10;
	double angle_y = (rand()%20)+10;
	double angle_z = (rand()%20)+10;

	Matrix4x4 rot_x = Matrix4x4(Vector4D(1,0,0,0),Vector4D(0,cos(angle_x),-sin(angle_x),0),Vector4D(0,sin(angle_x),cos(angle_x),0),Vector4D(0,0,0,1));
  	Matrix4x4 rot_y = Matrix4x4(Vector4D(cos(angle_y),0,sin(angle_y),0),Vector4D(0,1,0,0),Vector4D(-sin(angle_y),0,cos(angle_y),0),Vector4D(0,0,0,1));
  	Matrix4x4 rot_z = Matrix4x4(Vector4D(cos(angle_z),-sin(angle_z),0,0),Vector4D(sin(angle_z),cos(angle_z),0,0),Vector4D(0,0,1,0),Vector4D(0,0,0,1));

  	rot_matrix = rot_x*rot_y*rot*z*rot_matrix;

	if(newheight<=10) F();
}

double Tree::G()
{
	double b_height = t_seed + t_seed* (double)((rand()%1)+0.5);


}