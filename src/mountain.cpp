#include "mountain.hpp"

Mountain::Mountain()
{
	va = Point3D(300,0,300);
	vb = Point3D(300,0,-200);
	vc = Point3D(-200,0,-200);
	vd = Point3D(-300,0,300);
	ve = Point3D(-7.14514,0,200);
	vf = Point3D(200,0,46.94);
	vg = Point3D(96.69362,0,-150);
	vh = Point3D(-100,0,32.14223);
	// vi = Point3D(150,0,-105);

	vector<Point3D> tmparea;
	vector<vector<Point3D> > tmpareas;

	tmparea.push_back(va);
	tmparea.push_back(ve);
	tmparea.push_back(vf);
	tmpareas.push_back(tmparea);
	areas.push_back(tmpareas);
	tmparea.clear();
	tmpareas.clear();

	tmparea.push_back(vf);
	tmparea.push_back(vg);
	tmparea.push_back(vb);
	tmpareas.push_back(tmparea);
	areas.push_back(tmpareas);
	tmparea.clear();
	tmpareas.clear();

	tmparea.push_back(vh);
	tmparea.push_back(vc);
	tmparea.push_back(vg);
	tmpareas.push_back(tmparea);
	areas.push_back(tmpareas);
	tmparea.clear();
	tmpareas.clear();

	tmparea.push_back(ve);
	tmparea.push_back(vd);
	tmparea.push_back(vh);
	tmpareas.push_back(tmparea);
	areas.push_back(tmpareas);
	tmparea.clear();
	tmpareas.clear();

	tmparea.push_back(va);
	tmparea.push_back(vb);
	tmparea.push_back(vf);
	tmpareas.push_back(tmparea);
	areas.push_back(tmpareas);
	tmparea.clear();
	tmpareas.clear();

	tmparea.push_back(vb);
	tmparea.push_back(vc);
	tmparea.push_back(vg);
	tmpareas.push_back(tmparea);
	areas.push_back(tmpareas);
	tmparea.clear();
	tmpareas.clear();

	tmparea.push_back(vc);
	tmparea.push_back(vd);
	tmparea.push_back(vh);
	tmpareas.push_back(tmparea);
	areas.push_back(tmpareas);
	tmparea.clear();
	tmpareas.clear();

	tmparea.push_back(va);
	tmparea.push_back(vd);
	tmparea.push_back(ve);
	tmpareas.push_back(tmparea);
	areas.push_back(tmpareas);
	tmparea.clear();
	tmpareas.clear();


	srand(time(NULL));
	generatemountains();
	generatemountains();
	generatemountains();
	generatemountains();
	for(int i = 0; i < areas.size(); i++)
	{
		vector<vector<Point3D> > tmparea = areas[i];
		for(int j = 0; j < tmparea.size(); j++)
		{
			mountains.push_back(tmparea[j]);
		}
	}

	// mountains = areas[0];
	// cout<<areas[0][0][0]<<endl;
	// cout<<areas[0][0][1]<<endl;
	// cout<<areas[0][0][2]<<endl;
}

vector<vector<Point3D> > Mountain::getmountains()
{
	return mountains;
}

void Mountain::generatemountains()
{
	
	int rand_height = (rand()%20);
	int rand_x,rand_z;
	vector<vector<Point3D> > tmpareas = areas[0];
	vector<vector<Point3D> > areasacc;
	for(int s = 0; s < areas.size();s++)
	{
		vector<vector<Point3D> > tmpareas = areas[s];
		vector<vector<Point3D> > areasacc;
		for(int i = 0; i< tmpareas.size(); i++)
		{
			vector<Point3D> tmparea = tmpareas[i];
			Point3D tmpareav1 = tmparea[0];
			Point3D tmpareav2 = tmparea[1];
			Point3D tmpareav3 = tmparea[2];
			rand_x = (rand()%2)-4;
			rand_z = (rand()%2)-4;
			Point3D tmpv1 = Point3D((tmpareav1[0]+tmpareav2[0])/2+rand_x,(tmpareav1[1]+tmpareav2[1])/2+rand_height,(tmpareav1[2]+tmpareav2[2])/2+rand_z);
			Point3D tmpv2 = Point3D((tmpareav2[0]+tmpareav3[0])/2+rand_x,(tmpareav2[1]+tmpareav3[1])/2+rand_height,(tmpareav2[2]+tmpareav3[2])/2+rand_z);
			Point3D tmpv3 = Point3D((tmpareav1[0]+tmpareav3[0])/2+rand_x,(tmpareav1[1]+tmpareav3[1])/2+rand_height,(tmpareav1[2]+tmpareav3[2])/2+rand_z);

			tmparea.clear();
			tmparea.push_back(tmpv1);
			tmparea.push_back(tmpareav1);
			tmparea.push_back(tmpareav2);
			areasacc.push_back(tmparea);

			tmparea.clear();
			tmparea.push_back(tmpv2);
			tmparea.push_back(tmpareav2);
			tmparea.push_back(tmpareav3);
			areasacc.push_back(tmparea);

			tmparea.clear();
			tmparea.push_back(tmpv3);
			tmparea.push_back(tmpareav1);
			tmparea.push_back(tmpareav3);
			areasacc.push_back(tmparea);

			tmparea.clear();
			tmparea.push_back(tmpv1);
			tmparea.push_back(tmpv2);
			tmparea.push_back(tmpv3);
			areasacc.push_back(tmparea);

			tmparea.clear();
			tmparea.push_back(tmpv1);
			tmparea.push_back(tmpv2);
			tmparea.push_back(tmpareav2);
			areasacc.push_back(tmparea);

			tmparea.clear();
			tmparea.push_back(tmpv2);
			tmparea.push_back(tmpv3);
			tmparea.push_back(tmpareav3);
			areasacc.push_back(tmparea);

			tmparea.clear();
			tmparea.push_back(tmpv3);
			tmparea.push_back(tmpv1);
			tmparea.push_back(tmpareav1);
			areasacc.push_back(tmparea);
		}
		areas[s] = areasacc;
	}

}