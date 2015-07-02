#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <iostream>
#include "algebra.hpp"
#include <cstdlib>
#include <ctime>

using namespace std;

class Particle
{
public:
	Particle(double r,double g, double b, Point3D pos);
	~Particle();

	void evolve();
	bool isalive();
	Colour getcolour();
	Point3D getpos();

private:
	double p_r,p_g,p_b;
	Point3D p_pos;
	Vector3D p_velocity;
	bool p_alive;
	double p_lifetime;
	double p_decay;
};

#endif