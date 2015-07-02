#include "particle.hpp"

Particle::Particle(double r,double g, double b, Point3D pos)
:p_r(r),p_g(g),p_b(b),p_pos(pos)
{

	double v_x = 0.00002 - (double)(rand()%100-200)/1000000;
	double v_y = 0.0005 - (double)(rand()%100-200)/1000000;
	double v_z = 0.00002 - (double)(rand()%100-200)/1000000;

	// cout<<"v_x: "<<v_x<<" v_y: "<<v_y<<" v_z: "<<v_z<<endl;
	p_velocity = Vector3D(v_x,v_y,v_z);
	p_alive = true;
	p_lifetime = (double)(rand()%10000)/10000;
	// cout<<"life: "<<p_lifetime<<endl;
	p_decay = 0.06;
}

Particle::~Particle()
{
}

void Particle::evolve()
{
	p_lifetime -= p_decay;
	p_pos = p_pos + p_velocity;
	double v_x,v_y,v_z;
	// if(v_x >= 0 ) v_x = p_velocity[0] - 0.000001;
	// if(v_y >= 0 ) v_y = p_velocity[1] - 0.000001;
	// if(v_z >= 0 ) v_z = p_velocity[2] - 0.000001;
	// p_velocity = Vector3D(v_x,v_y,v_z);
	if(p_lifetime <= 0)	p_alive = false;
}

bool Particle::isalive()
{
	return p_alive;
}

Colour Particle::getcolour()
{
	return Colour(p_r, p_g, p_b);
}

Point3D Particle::getpos()
{
	return p_pos;
}

