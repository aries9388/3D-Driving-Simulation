#ifndef CAR_HPP
#define CAR_HPP

#include <iostream>
#include "algebra.hpp"
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "object.hpp"
#include "particle.hpp"
#include "SoundManager.h"

#define MAX_PARTICLE_SIZE 1000

class Car
{
public:
	Car(Object* obj,vector<vector<double> > ivts,vector<vector<double> > ovts,vector<vector<double> > pvts);
	virtual ~Car();

	void updateCar();
	void increcenter();
	bool lfb_hit();
	bool lrb_hit();
	bool rfb_hit();
	bool rrb_hit();
	void accelerate();
	double getSpeed();
	Point3D getcamera();
	Point3D getcenter();
	Vector3D getvelocity();	
	Vector3D calcdist();
	void setangley(double angley);
	double getheight();
	void changevelocity();
	double getrotangle();
	Point3D getfarcamera();
	void generateexhaust();
	void emission();
	vector<Particle> getexhaust();

private:
	Point3D lft,lfb,rft,rfb,lrt,lrb,rrt,rrb;
	Point3D lfto,lfbo,rfto,rfbo,lrto,lrbo,rrto,rrbo;
	Point3D center;
	Point3D camera,camerao;
	Point3D origin;
	double rot_angle;
	int i_near,i_next;
	vector<vector<double> > innerverts;
	vector<vector<double> > outterverts;
	vector<Point3D>	pathpoints;
	double speed;
	double acceleration;
	int steeringangle;
	Vector3D velocity;
	Vector3D o_dir;
	Vector3D move_dir;
	double height;
	double sdist,sdistcount;
	bool checkpoint,rotatedone;
	Point3D farcamera;
	Point3D exhaustpos;
	vector<Particle> exhaust;
	// SoundManager SM;
	// int soundbuffer;
	// int soundsrc;
};

#endif