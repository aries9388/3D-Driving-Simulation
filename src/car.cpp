#include "car.hpp"

Car::Car(Object* obj,vector<vector<double> > ivts,vector<vector<double> > ovts,vector<vector<double> > pvts)
: innerverts(ivts),outterverts(ovts)
{
	double leftbound, rightbound, upbound, bottombound,frontbound, rearbound;
	vector<vector<double> > verts = obj->getverts();

	leftbound = verts[0][0];
	rightbound = verts[0][0];
	upbound = verts[0][1];
	bottombound = verts[0][1];
	frontbound = verts[0][2];
	rearbound = verts[0][2];
	for(unsigned int i = 1; i < verts.size(); i++)
	{
		double tmpx = verts[i][0];
		double tmpy = verts[i][1];
		double tmpz = verts[i][2];
		if(tmpx < leftbound)	leftbound = tmpx;
		if(tmpx > rightbound)	rightbound = tmpx;
		if(tmpy < bottombound) bottombound = tmpy;
		if(tmpy > upbound)	upbound = tmpy;
		if(tmpz < rearbound)	rearbound = tmpz;
		if(tmpz > frontbound)	frontbound = tmpz;
	}

	for(unsigned int i = 0; i < pvts.size(); i++)
	{
		// double tmppx,tmppz;
		// if(i == ivts.size()-1)
		// {
		// 	tmppx = outterverts[0][0];
		// 	tmppz = outterverts[0][2];
		// } 	
		// else
		// {
		// 	tmppx = outterverts[i+1][0];
		// 	tmppz = outterverts[i+1][2];
		// } 
		// Point3D tmpmidp = Point3D((innerverts[i][0]+tmppx)/2,0,(innerverts[i][2]+tmppz)/2);
		Point3D tmppp = Point3D(pvts[i][0],pvts[i][1],pvts[i][2]);
		pathpoints.push_back(tmppp);
	}

	center[0] = (leftbound+rightbound)/2;
	center[1] = (upbound+bottombound)/2;
	center[2] = (frontbound+rearbound)/2;

	Point3D tmpp = Point3D(innerverts[0][0],innerverts[0][1],innerverts[0][2]);
	Vector3D tmpv = center - tmpp;
	double dmin = tmpv.length();
	int dmincount = 0;
	for(unsigned int i = 1; i < innerverts.size(); i++)
	{
		tmpp = Point3D(innerverts[i][0],innerverts[i][1],innerverts[i][2]);
		tmpv = center - tmpp;
		if(tmpv.length() < dmin)
		{
			dmin = tmpv.length();
			dmincount = i;
		}	
	}
	int dmincount2;
	if(dmincount == innerverts.size()-1)
	{
		tmpp = Point3D(innerverts[dmincount-1][0],innerverts[dmincount-1][1],innerverts[dmincount-1][2]);
		tmpv = center - tmpp;
		dmin = tmpv.length();
		dmincount2 = dmincount - 1;
		tmpp = Point3D(innerverts[0][0],innerverts[0][1],innerverts[0][2]);
		tmpv = center - tmpp;
		if(tmpv.length() < dmin)	dmincount2 = 0;
	}
	if(dmincount == 0)
	{
		tmpp = Point3D(innerverts[innerverts.size()-1][0],innerverts[innerverts.size()-1][1],innerverts[innerverts.size()-1][2]);
		tmpv = center - tmpp;
		dmin = tmpv.length();
		dmincount2 = innerverts.size() - 1;
		tmpp = Point3D(innerverts[1][0],innerverts[1][1],innerverts[1][2]);
		tmpv = center - tmpp;
		if(tmpv.length() < dmin)	dmincount2 = 1;
	}
	else
	{
		tmpp = Point3D(innerverts[dmincount-1][0],innerverts[dmincount-1][1],innerverts[dmincount-1][2]);
		tmpv = center - tmpp;
		dmin = tmpv.length();
		dmincount2 = dmincount-1;
		tmpp = Point3D(innerverts[dmincount+1][0],innerverts[dmincount+1][1],innerverts[dmincount+1][2]);
		tmpv = center - tmpp;
		if(tmpv.length() < dmin)	dmincount2 = dmincount+1;
	}

	// i_near = dmincount;
	// i_next = dmincount2;
	i_near = 0;
	i_next = 1;
	speed = 0;
	acceleration = 0;
	o_dir = Vector3D(0,0,0.1);
	// camera = Point3D(50,30,25);
	// camerao = camera;
	// steeringangle = 0;
	// center = Point3D(center[0],center[1]-(lrb[1]-innerverts[i_near][1]),center[2]);
	origin = center;
	center = pathpoints[0];
	move_dir = pathpoints[1] - pathpoints[0];
	camera = Point3D(center[0],2.5,center[2])-(7/move_dir.length()*move_dir);
	farcamera = Point3D(50,50,30);
	// cout<<move_dir<<endl;
	rot_angle = acos(move_dir.dot(o_dir)/(move_dir.length()*o_dir.length()))*180/M_PI;
	changevelocity();
	height = bottombound;
	checkpoint = false;
	sdist = 0;
	sdistcount = 0;
	exhaustpos = Point3D(center[0],0.3,center[2]) - (1.5/move_dir.length()*move_dir);
	// SM = SoundManager();
	// SM.SetPosition(soundsrc, 0, 0, 0);
	// SM.SetListenerPosition(-camera[0], -camera[1], -camera[2]);
	// soundbuffer = SM.LoadWav("data/car.wav");
	// soundsrc = SM.MakeSource();
	// SM.QueueBuffer(soundsrc,soundbuffer);
}

Car::~Car()
{
}

void Car::updateCar()
{
	// SM.Play(soundsrc);
	// SM.SetLoop(soundsrc,loop)
	// cout<<"Center: "<<center<<endl;
	if(checkpoint)
	{
		if(i_near == pathpoints.size()-1) i_next = 0;
		else	i_next = i_near + 1;
		// cout<<"rot_angle: "<<rot_angle<<endl;
		// cout<<pathpoints[i_near]<<endl;
		Vector3D tmpv = pathpoints[i_next] - pathpoints[i_near];
		sdist = tmpv.length();
		sdistcount = 0;
		Vector3D normal = move_dir.cross(Vector3D(0,1,0));
		// cout<<"normal: "<<normal<<endl;
		double theta = acos(move_dir.dot(tmpv)/(move_dir.length()*tmpv.length()))*180/M_PI;
		if((-1*tmpv).dot(normal) < 0 ) theta = -theta;
		// cout<<"theta: "<<theta<<endl;
		move_dir = tmpv;
		// cout<<"move_dir: "<<move_dir<<endl;
		rot_angle += theta;
		// cout<<"check rot_angle: "<<angle_acc<<endl;
		changevelocity();
		// cout<<"Velocity: "<<velocity<<endl;	
		// cout<<"Center: "<<center<<endl;
		checkpoint = false;
	}
	else
	{
		sdistcount += velocity.length();
		increcenter();
		emission();
		if(sdistcount >= sdist)
		{
			center = pathpoints[i_next];
			camera = Point3D(center[0],2.5,center[2])-(7/move_dir.length()*move_dir);
			exhaustpos = Point3D(center[0],0.3,center[2])-(1.5/move_dir.length()*move_dir);
			checkpoint = true;
			i_near = (i_near+1)%pathpoints.size();
		}
	}
}

bool Car::lfb_hit()
{
	// Vector3D v_ltor = Point3D(outterverts[i_near][0],outterverts[i_near][1],outterverts[i_near][2]) - 
	// 					Point3D(innerverts[i_near][0],innerverts[i_near][1],innerverts[i_near][2]);
	// Vector3D v_ltolfb = lfb - Point3D(innerverts[i_near][0],innerverts[i_near][1],innerverts[i_near][2]);
	// cout<<"i_near: "<<i_near<<" i_next: "<<i_next<<endl;
	// Vector3D v_ltoln = Point3D(innerverts[i_near][0],innerverts[i_near][1],innerverts[i_near][2]) - 
	// 					Point3D(innerverts[i_next][0],innerverts[i_next][1],innerverts[i_next][2]);
	// double angle1 = v_ltor.dot(v_ltolfb)/(v_ltor.length()*v_ltolfb.length());
	// double angle2 = v_ltor.dot(v_ltoln)/(v_ltor.length()*v_ltoln.length());
	// cout<<"i_next"

	// cout<<"Left front bottom: "<<rfb<<endl;
	// cout<<"innerverts: "<<Point3D(innerverts[i_near][0],innerverts[i_near][1],innerverts[i_near][2])<<endl;
	Vector3D v_ltor = Point3D(outterverts[i_near][0],outterverts[i_near][1],outterverts[i_near][2]) - 
						Point3D(innerverts[i_near][0],innerverts[i_near][1],innerverts[i_near][2]);
	Vector3D v_ltor1 = Point3D(outterverts[i_near-1][0],outterverts[i_near-1][1],outterverts[i_near-1][2]) - 
						Point3D(innerverts[i_near][0],innerverts[i_near][1],innerverts[i_near][2]);
	Vector3D v_ltolfb = rfb - Point3D(outterverts[i_near][0],outterverts[i_near][1],outterverts[i_near][2]);
	Vector3D v_ltolfb1 = rfb - Point3D(outterverts[i_near-1][0],outterverts[i_near-1][1],outterverts[i_near-1][2]);

	if(v_ltolfb.length() >= v_ltor.length() && v_ltolfb1.length() >= v_ltor1.length()) return true;
	return false;
}

bool Car::lrb_hit()
{
	Vector3D v_ltor = Point3D(outterverts[i_near][0],outterverts[i_near][1],outterverts[i_near][2]) - 
						Point3D(innerverts[i_near][0],innerverts[i_near][1],innerverts[i_near][2]);
	Vector3D v_ltolrb = lrb - Point3D(innerverts[i_near][0],innerverts[i_near][1],innerverts[i_near][2]);
	if(v_ltor.dot(v_ltolrb) <= 0)	return true;
	return false;
}


bool Car::rfb_hit()
{
	Vector3D v_rtol = Point3D(innerverts[i_near][0],innerverts[i_near][1],innerverts[i_near][2]) -  
					Point3D(outterverts[i_near][0],outterverts[i_near][1],outterverts[i_near][2]);
	Vector3D v_ltorfb = rfb - Point3D(outterverts[i_near][0],outterverts[i_near][1],outterverts[i_near][2]);
	if(v_rtol.dot(v_ltorfb) <= 0 )	return true;
	return false;
}

bool Car::rrb_hit()
{
	Vector3D v_rtol = Point3D(innerverts[i_near][0],innerverts[i_near][1],innerverts[i_near][2]) -  
					Point3D(outterverts[i_near][0],outterverts[i_near][1],outterverts[i_near][2]);
	Vector3D v_ltorrb = rrb - Point3D(outterverts[i_near][0],outterverts[i_near][1],outterverts[i_near][2]);
	if(v_rtol.dot(v_ltorrb) <= 0 )	return true;
	return false;
}

void Car::increcenter()
{
	// cout<<"Velocity: "<<velocity<<endl;
	// cout<<"steeringangle: "<<steeringangle<<endl;
	// cout<<"acceleration: "<<acceleration<<endl;
	// double r_x,r_z;
	// if(steeringangle >= 0)	// left
	// {
	// 	center = Point3D(center[0]+velocity[0],center[1],center[2]+velocity[2]);		;
	// 	camera = Point3D(center[0],center[1]+1.5,center[2]-5);
	// 	r_x = cos(steeringangle*M_PI/180)*(camera[0]-center[0]) - sin(-steeringangle*M_PI/180)*(camera[2]-center[2]) + center[0];
	// 	r_z = sin(steeringangle*M_PI/180)*(camera[0]-center[0]) + cos(-steeringangle*M_PI/180)*(camera[2]-center[2]) + center[2];
	// 	camera = Point3D(r_x,camera[1],r_z);
	// }
	// else
	// {
	// 	center = Point3D(center[0]+velocity[0],center[1],center[2]+velocity[2]);
	// 	camera = Point3D(center[0],center[1]+1.5,center[2]-5);
	// 	r_x = cos(abs(steeringangle)*M_PI/180)*(camera[0]-center[0]) - sin(abs(steeringangle)*M_PI/180)*(camera[2]-center[2]) + center[0];
	// 	r_z = sin(abs(steeringangle)*M_PI/180)*(camera[0]-center[0]) + cos(abs(steeringangle)*M_PI/180)*(camera[2]-center[2]) + center[2];
	// 	camera = Point3D(r_x,camera[1],r_z);
	// }
	center = center + velocity;
	camera = camera + velocity;
	exhaustpos = exhaustpos + velocity;
	// Vector3D revmovedir = -1/move_dir.length()*move_dir;
	// camera = center + 5*revmovedir;
	// camera[1] = camera[1] + 1.5;

	// camera = Point3D(center[0],center[1]+1.5,center[2]+5);
	// r_x = cos(steeringangle*M_PI/180)*(camera[0]-center[0]) - sin(-steeringangle*M_PI/180)*(camera[2]-center[2]) + center[0];
	// r_z = sin(steeringangle*M_PI/180)*(camera[0]-center[0]) + cos(-steeringangle*M_PI/180)*(camera[2]-center[2]) + center[2];
	// camera = Point3D(r_x,camera[1],r_z);
}

void Car::accelerate()
{
	// if(acceleration <= 0.25) acceleration += 0.00005;
	acceleration = 0.01;
	speed += acceleration;
}

// void Car::speedup()
// {
	
// }
double Car::getSpeed()
{
	return speed;
}

Point3D Car::getcamera()
{
	return camera;

}

Point3D Car::getcenter()
{
	return center;
}


Vector3D Car::getvelocity()
{
	return velocity;
}

Vector3D Car::calcdist()
{
	Vector3D dist = center - origin;
	// dist[1] = center[1] - innerverts[i_near][1];
	// cout<<"Dist: "<<dist<<endl;
	return dist;
}

void Car::setangley(double angley)
{
	steeringangle = angley;
	// changevelocity();

}

double Car::getheight()
{
	return height;
}

void Car::changevelocity()
{
	// cout<<"steeringangle: "<<steeringangle<<endl;
	// double r_x,r_z;
	// r_x = o_dir[0]*cos(rot_angle*M_PI/180)-sin(rot_angle*M_PI/180)*o_dir[2];
	// r_z = o_dir[0]*sin(rot_angle*M_PI/180)-cos(rot_angle*M_PI/180)*o_dir[2];
	// velocity = Vector3D(r_x,0,r_z);

	velocity = 0.5/move_dir.length()*move_dir;

}

double Car::getrotangle()
{
	return rot_angle;
}

Point3D Car::getfarcamera()
{
	return farcamera;
}

void Car::generateexhaust()
{
	// int i = 0;

	// while(i < 50)
	// {
		Particle tmpp = Particle(0,0,0,exhaustpos);
		int j = 0;
		while(j < exhaust.size())
		{
			if(!exhaust[j].isalive())
			{
				exhaust[j] = tmpp;	// replace the old dead one
				break;
			}
			else j++;
		}
		if(j >= exhaust.size() && exhaust.size() < MAX_PARTICLE_SIZE)	exhaust.push_back(tmpp);
		// exhaust.push_back(tmpp);
		// if(exhaust.size() >= MAX_PARTICLE_SIZE)	 exhaust.clear();
		// i ++;
	// }
}

void Car::emission()
{
	generateexhaust();

	for(int i = 0; i < exhaust.size(); i++)
	{
		if(exhaust[i].isalive())	exhaust[i].evolve();
	}
}

vector<Particle> Car::getexhaust()
{
	return exhaust;
}