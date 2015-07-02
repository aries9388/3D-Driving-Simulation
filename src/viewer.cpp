#include "viewer.hpp"
#include "algebra.hpp"
#include <iostream>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

Object* car;
Object* track;
Object* innertrack;
Object* outtertrack;
Object* pathpoints;

using namespace std;

Viewer::Viewer()
{
	Glib::RefPtr<Gdk::GL::Config> glconfig;

	glconfig = Gdk::GL::Config::create(Gdk::GL::MODE_RGB |
										Gdk::GL::MODE_DEPTH |
										Gdk::GL::MODE_DOUBLE);

	if(glconfig == 0)
	{
		abort();
	}

	set_gl_capability(glconfig);

	add_events(Gdk::VISIBILITY_NOTIFY_MASK |
				Gdk::KEY_PRESS_MASK	|
				Gdk::BUTTON_PRESS_MASK |
				Gdk::BUTTON1_MOTION_MASK |
				Gdk::BUTTON2_MOTION_MASK |
				Gdk::BUTTON3_MOTION_MASK |
				Gdk::BUTTON_RELEASE_MASK);
	anglex = 0;
	angley = 0;
	anglez = 0;
	x_move = false;
	y_move = false;
	z_move = false;
	v_car = new Car(car,innertrack->getverts(),outtertrack->getverts(),pathpoints->getverts());
	v_mountain = new Mountain();
	v_x = 0;
	aamode = false;
	farcameramode = true;
	grass_bmp = new BMP();
	grass_bmp->Load("data/grass.bmp");
	front_bmp = new BMP();
	front_bmp->Load("data/front.bmp");
	back_bmp = new BMP();
	back_bmp->Load("data/back.bmp");
	left_bmp = new BMP();
	left_bmp->Load("data/left.bmp");
	right_bmp = new BMP();
	right_bmp->Load("data/right.bmp");
	up_bmp = new BMP();
	up_bmp->Load("data/up.bmp");
	down_bmp = new BMP();
	down_bmp->Load("data/down.bmp");
	smoke_bmp = new BMP();
	smoke_bmp->Load("data/smoke.bmp");
	sm = new SoundManager();
	soundbuf = sm->LoadWav("data/shifting.wav");
	soundsrc = sm->MakeSource();
	sm->QueueBuffer(soundsrc,soundbuf);
	sm->SetPosition(soundsrc,0,0,0);
	sm->SetListenerPosition(0,0,0);
	sm->Play(soundsrc);
	sm->SetLoop(soundsrc,true);
}

Viewer::~Viewer()
{
}

void Viewer::initList()
{
	glNewList(dl_car,GL_COMPILE);
	drawdlCar();
	glEndList();

	glNewList(dl_track,GL_COMPILE);
	drawdlTrack();
	glEndList();

	glNewList(dl_mountain,GL_COMPILE);
	drawdlMountain();
	glEndList();

	glNewList(dl_grass, GL_COMPILE);
	drawgrass();
	glEndList();

	glNewList(dl_skybox, GL_COMPILE);
	drawskybox();
	glEndList();
}

void Viewer::drawdlCar()
{
	glDisable(GL_TEXTURE_2D);

	vector<vector<double> > vts = car->getverts();

	glBegin(GL_TRIANGLES);

	for(int h = 0; h < car->get_assembly_size(); h++)
	{
		vector<vector<vector<int> > > fs = car->getfaceindices(h);
		Colour tmp_kd = car->getvkd(h);
		Colour tmp_ks = car->getvks(h);
		double tmp_shininess = car->getvshininess(h);
		GLfloat diffuse[] = {tmp_kd.R(),tmp_kd.G(),tmp_kd.B(),1.0};
		GLfloat shininess[] = {tmp_shininess};
		GLfloat specular[] = {tmp_ks.R(),tmp_ks.G(),tmp_ks.B(),1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE , diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,shininess);

		int v_vs1,v_vs2,v_vs3;
		for(int i = 0; i < fs.size(); i++)
		{
			v_vs1 = fs[i][0][0];
			v_vs2 = fs[i][1][0];
			v_vs3 = fs[i][2][0];


			glNormal3d(vts[v_vs1][0],vts[v_vs1][1],vts[v_vs1][2]);
			glVertex3d(vts[v_vs1][0],vts[v_vs1][1],vts[v_vs1][2]);
			glNormal3d(vts[v_vs2][0],vts[v_vs2][1],vts[v_vs2][2]);
			glVertex3d(vts[v_vs2][0],vts[v_vs2][1],vts[v_vs2][2]);
			glNormal3d(vts[v_vs3][0],vts[v_vs3][1],vts[v_vs3][2]);
			glVertex3d(vts[v_vs3][0],vts[v_vs3][1],vts[v_vs3][2]);
		}
	}

	glEnd();
	v_car->setangley(angley);
	v_car->increcenter();
	v_car->updateCar();
}

void Viewer::drawdlTrack()
{
	glDisable(GL_TEXTURE_2D);

	vector<vector<double> > vts = track->getverts();

	glBegin(GL_TRIANGLES);

	for(int h = 0; h < track->get_assembly_size(); h++)
	{
		vector<vector<vector<int> > > fs = track->getfaceindices(h);
		Colour tmp_kd = track->getvkd(h);
		Colour tmp_ks = track->getvks(h);
		double tmp_shininess = track->getvshininess(h);
		GLfloat ambient[] = {tmp_kd.R()*0.1,tmp_kd.G()*0.1,tmp_kd.B()*0.1,1.0};
		GLfloat diffuse[] = {tmp_kd.R(),tmp_kd.G(),tmp_kd.B(),1.0};
		GLfloat shininess[] = {tmp_shininess};
		GLfloat specular[] = {tmp_ks.R(),tmp_ks.G(),tmp_ks.B(),1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT , ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE , diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,shininess);

		int v_vs1,v_vs2,v_vs3;
		for(int i = 0; i < fs.size(); i++)
		{
			v_vs1 = fs[i][0][0];
			v_vs2 = fs[i][1][0];
			v_vs3 = fs[i][2][0];


			glNormal3d(vts[v_vs1][0],vts[v_vs1][1],vts[v_vs1][2]);
			glVertex3d(vts[v_vs1][0],vts[v_vs1][1],vts[v_vs1][2]);
			glNormal3d(vts[v_vs2][0],vts[v_vs2][1],vts[v_vs2][2]);
			glVertex3d(vts[v_vs2][0],vts[v_vs2][1],vts[v_vs2][2]);
			glNormal3d(vts[v_vs3][0],vts[v_vs3][1],vts[v_vs3][2]);
			glVertex3d(vts[v_vs3][0],vts[v_vs3][1],vts[v_vs3][2]);
		}
	}

	glEnd();

}

void Viewer::drawdlMountain()
{
	glDisable(GL_TEXTURE_2D);

	vector<vector<Point3D> > vts = v_mountain->getmountains();

	glBegin(GL_TRIANGLES);

		for(int i = 0; i < vts.size(); i++)
		{
			double height = (vts[i][0][1]+vts[i][1][1]+vts[i][2][1])/3;
			double k_d = 0.27+height/100;
			if(k_d > 1) k_d = 0.937;
			GLfloat ambient[] = {(k_d-0.145)*0.1,k_d*0.1,(k_d+0.063)*0.1,1.0};
			GLfloat diffuse[] = {k_d-0.145,k_d,k_d+0.063,1.0};
			GLfloat shininess[] = {20};
			GLfloat specular[] = {1,1,1,1};
			glMaterialfv(GL_FRONT, GL_AMBIENT , ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE , diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
			glMaterialfv(GL_FRONT, GL_SHININESS,shininess);

			glNormal3d(vts[i][0][0],vts[i][0][1],vts[i][0][2]);
			glVertex3d(vts[i][0][0],vts[i][0][1],vts[i][0][2]);
			glNormal3d(vts[i][1][0],vts[i][1][1],vts[i][1][2]);
			glVertex3d(vts[i][1][0],vts[i][1][1],vts[i][1][2]);
			glNormal3d(vts[i][2][0],vts[i][2][1],vts[i][2][2]);
			glVertex3d(vts[i][2][0],vts[i][2][1],vts[i][2][2]);
		}

	glEnd();
}

void Viewer::drawgrass()
{
	glEnable (GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, grasstexture);

	glBegin(GL_QUADS);

	for(int i = -300 ; i < 300; i += 10)
	{
		for(int j = -200; j < 300; j += 10)
		{
			glTexCoord2f(0.0, 0.0); glVertex3f(j,-0.1,i);
   			glTexCoord2f(0.0, 1.0); glVertex3f(j+10,-0.1,i);
   			glTexCoord2f(1.0, 1.0); glVertex3f(j+10,-0.1,i+10);
   			glTexCoord2f(1.0, 0.0); glVertex3f(j,-0.1,i+10);	
		}

	}

   	glEnd();
}

void Viewer::drawskybox()
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D,skyboxtexture[0]);

	glBegin(GL_QUADS);
	
	glTexCoord2f(0.0, 0.0); glVertex3f(-500,523,530);
   	glTexCoord2f(1.0, 0.0); glVertex3f(548,523,530);
   	glTexCoord2f(1.0, 1.0); glVertex3f(548,-523,530);
   	glTexCoord2f(0.0, 1.0); glVertex3f(-500,-523,530);

   	glEnd();

   	glBindTexture(GL_TEXTURE_2D,skyboxtexture[1]);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0); glVertex3f(548,523,-517);
   	glTexCoord2f(1.0, 0.0); glVertex3f(-500,523,-517);
   	glTexCoord2f(1.0, 1.0); glVertex3f(-500,-523,-517);
   	glTexCoord2f(0.0, 1.0); glVertex3f(548,-523,-517);

   	glEnd();

   	glBindTexture(GL_TEXTURE_2D,skyboxtexture[2]);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0); glVertex3f(548,523,530);
   	glTexCoord2f(1.0, 0.0); glVertex3f(548,523,-517);
   	glTexCoord2f(1.0, 1.0); glVertex3f(548,-523,-517);
   	glTexCoord2f(0.0, 1.0); glVertex3f(548,-523,530);

   	glEnd();

   	glBindTexture(GL_TEXTURE_2D,skyboxtexture[3]);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0); glVertex3f(-500,523,-517);
   	glTexCoord2f(1.0, 0.0); glVertex3f(-500,523,530);
   	glTexCoord2f(1.0, 1.0); glVertex3f(-500,-523,530);
   	glTexCoord2f(0.0, 1.0); glVertex3f(-500,-523,-517);

   	glEnd();

   	glBindTexture(GL_TEXTURE_2D,skyboxtexture[4]);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0); glVertex3f(548,523,-517);
   	glTexCoord2f(1.0, 0.0); glVertex3f(-500,523,-517);
   	glTexCoord2f(1.0, 1.0); glVertex3f(-500,523,530);
   	glTexCoord2f(0.0, 1.0); glVertex3f(548,523,530);

   	glEnd();
}

void Viewer::drawexhaust()
{
	// glEnable (GL_TEXTURE_2D);

	// glBindTexture(GL_TEXTURE_2D, smoketexture);

	vector<Particle> v_exhaust = v_car->getexhaust();

	// cout<<"v_exhaust size: "<<v_exhaust.size()<<endl;

	glBegin(GL_TRIANGLE_STRIP);
	for(int i = 0; i < v_exhaust.size(); i++)
	{
		Particle tmpp = v_exhaust[i];
		if(tmpp.isalive())
		{
			
			// cout<<"Alive one!"<<endl;
			Colour tmpcolour = tmpp.getcolour();
			// glColor3d(tmpcolour.R(),tmpcolour.G(),tmpcolour.B());
			GLfloat diffuse[] = {tmpcolour.R(),tmpcolour.G(),tmpcolour.B(),1.0};
			GLfloat shininess[] = {80};
			GLfloat specular[] = {0.4,0.4,0.4,1};
			glMaterialfv(GL_FRONT, GL_DIFFUSE , diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
			glMaterialfv(GL_FRONT, GL_SHININESS,shininess);
			Point3D tmppos = tmpp.getpos();

			// glTexCoord2f(0.0, 0.0); glVertex3d(tmppos[0]+0.1, tmppos[1]+0.1, tmppos[2]);
   // 			glTexCoord2f(1.0, 0.0); glVertex3d(tmppos[0]-0.1, tmppos[1]+0.1, tmppos[2]);
   // 			glTexCoord2f(1.0, 1.0); glVertex3d(tmppos[0]+0.1, tmppos[1]-0.1, tmppos[2]);
   // 			glTexCoord2f(0.0, 1.0); glVertex3d(tmppos[0]-0.1, tmppos[1]-0.1, tmppos[2]);

   			glVertex3d(tmppos[0]+0.05, tmppos[1]+0.05, tmppos[2]);
			glVertex3d(tmppos[0]-0.05, tmppos[1]+0.05, tmppos[2]);
			glVertex3d(tmppos[0]+0.05, tmppos[1]-0.05, tmppos[2]);
			glVertex3d(tmppos[0]-0.05, tmppos[1]-0.05, tmppos[2]);
			
		}
	}
	glEnd();
}

void Viewer::render()
{
	glPushMatrix();

	Vector3D dist = v_car->calcdist();

	glTranslated(dist[0],-v_car->getheight(),dist[2]);

	// glRotated(-v_car->getverangle(),1,0,0);
	glRotated(v_car->getrotangle(),0,1,0);
	// glRotated(-v_car->gethorangle(),0,0,1);


	
	glCallList(dl_car);
	

  	glPopMatrix();


  	glPushMatrix();

	glCallList(dl_track);

	glCallList(dl_mountain);

	glCallList(dl_grass);

	glCallList(dl_skybox);

	drawexhaust();

	glPopMatrix();
}

void Viewer::update()
{
	v_car->updateCar();
	invalidate();
}

void Viewer::invalidate()
{
	Gtk::Allocation allocation = get_allocation();
	get_window()->invalidate_rect(allocation,false);
}

void Viewer::on_realize()
{
	Gtk::GL::DrawingArea::on_realize();

	Glib::RefPtr<Gdk::GL::Drawable> gldrawable = get_gl_drawable();

	if(!gldrawable) return;

	if(!gldrawable->gl_begin(get_gl_context())) return;

	glGenTextures(1,&grasstexture);

	glBindTexture(GL_TEXTURE_2D, grasstexture);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// glPixelStorei(GL_UNPACK_ALIGNMENT, 4); 

	glTexImage2D(GL_TEXTURE_2D,0,3,grass_bmp->GetWidth(),grass_bmp->GetHeight(),0,GL_BGR_EXT,GL_UNSIGNED_BYTE, grass_bmp->GetImg());

	

	glGenTextures(1, &skyboxtexture[0]);

	glBindTexture(GL_TEXTURE_2D, skyboxtexture[0]);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// glPixelStorei(GL_UNPACK_ALIGNMENT, 4); 

	glTexImage2D(GL_TEXTURE_2D,0,3,front_bmp->GetWidth(),front_bmp->GetHeight(),0,GL_BGR_EXT,GL_UNSIGNED_BYTE, front_bmp->GetImg());

	
	glGenTextures(1, &skyboxtexture[1]);

	glBindTexture(GL_TEXTURE_2D, skyboxtexture[1]);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// glPixelStorei(GL_UNPACK_ALIGNMENT, 4); 

	glTexImage2D(GL_TEXTURE_2D,0,3,back_bmp->GetWidth(),back_bmp->GetHeight(),0,GL_BGR_EXT,GL_UNSIGNED_BYTE, back_bmp->GetImg());

	
	glGenTextures(1, &skyboxtexture[2]);

	glBindTexture(GL_TEXTURE_2D, skyboxtexture[2]);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// glPixelStorei(GL_UNPACK_ALIGNMENT, 4); 

	glTexImage2D(GL_TEXTURE_2D,0,3,left_bmp->GetWidth(),left_bmp->GetHeight(),0,GL_BGR_EXT,GL_UNSIGNED_BYTE, left_bmp->GetImg());

	
	glGenTextures(1, &skyboxtexture[3]);

	glBindTexture(GL_TEXTURE_2D, skyboxtexture[3]);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// glPixelStorei(GL_UNPACK_ALIGNMENT, 4); 

	glTexImage2D(GL_TEXTURE_2D,0,3,right_bmp->GetWidth(),right_bmp->GetHeight(),0,GL_BGR_EXT,GL_UNSIGNED_BYTE, right_bmp->GetImg());

	
	glGenTextures(1, &skyboxtexture[4]);

	glBindTexture(GL_TEXTURE_2D, skyboxtexture[4]);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// glPixelStorei(GL_UNPACK_ALIGNMENT, 4); 

	glTexImage2D(GL_TEXTURE_2D,0,3,up_bmp->GetWidth(),up_bmp->GetHeight(),0,GL_BGR_EXT,GL_UNSIGNED_BYTE, up_bmp->GetImg());

	
	glGenTextures(1, &skyboxtexture[5]);

	glBindTexture(GL_TEXTURE_2D, skyboxtexture[5]);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// glPixelStorei(GL_UNPACK_ALIGNMENT, 4); 

	glTexImage2D(GL_TEXTURE_2D,0,3,down_bmp->GetWidth(),down_bmp->GetHeight(),0,GL_BGR_EXT,GL_UNSIGNED_BYTE, down_bmp->GetImg());



	glGenTextures(1, &smoketexture);

	glBindTexture(GL_TEXTURE_2D, smoketexture);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// glPixelStorei(GL_UNPACK_ALIGNMENT, 4); 

	glTexImage2D(GL_TEXTURE_2D,0,3,smoke_bmp->GetWidth(),smoke_bmp->GetHeight(),0,GL_BGR_EXT,GL_UNSIGNED_BYTE, smoke_bmp->GetImg());


	glShadeModel(GL_SMOOTH);
	// glClearColor(0.4,0.4,0.4,0.0);
	glEnable(GL_DEPTH_TEST);
	// glEnable(GL_BLEND);
	glClearColor(0.7,0.7,1.0,0.0);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	gldrawable->gl_end();

	initList();
}



bool Viewer::on_expose_event(GdkEventExpose* event)
{
	Glib::RefPtr<Gdk::GL::Drawable> gldrawable = get_gl_drawable();

	if(!gldrawable)	return false;
	
	if(!gldrawable->gl_begin(get_gl_context())) return false;

	


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,get_width(),get_height());
	gluPerspective(40.0,(GLfloat)get_width()/(GLfloat)get_height(), 0.1,1000.0);
	// glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Point3D camera = v_car->getcamera();
	Point3D farcamera = v_car->getfarcamera();
	Point3D center = v_car->getcenter();
	if(farcameramode)	gluLookAt(farcamera[0],farcamera[1],farcamera[2],center[0],center[1]+20,center[2],0,1,0);
	else	gluLookAt(camera[0],0.3,camera[2],center[0],center[1]+1,center[2],0,1,0);

	glEnable(GL_NORMALIZE);
	// glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	if(aamode)
	{
		glEnable( GL_LINE_SMOOTH );
    	glEnable( GL_POLYGON_SMOOTH );
    	glEnable( GL_MULTISAMPLE );
    	glEnable( GL_TEXTURE_2D);
	}
	else
	{
		glDisable( GL_LINE_SMOOTH );
    	glDisable( GL_POLYGON_SMOOTH );
    	glDisable( GL_MULTISAMPLE );
    	glDisable(GL_TEXTURE_2D);
	}

	GLfloat ambient[] = {0.2,0.2,0.2,1};
	GLfloat diffuse[] = {1,1,1,1};
	GLfloat specular[] = {1,1,1,1};
	GLfloat shininess[] = {0};
	GLfloat position1[] = {0,200,0,0};
	glLightfv(GL_LIGHT1,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_SHININESS,shininess);
 	glLightfv(GL_LIGHT0,GL_POSITION,position1);
	GLfloat position2[] = {320,200,6,1};
	glLightfv(GL_LIGHT1,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT1, GL_SHININESS,shininess);
 	glLightfv(GL_LIGHT1,GL_POSITION,position2);
	GLfloat position3[] = {-270,200,6,1};
	glLightfv(GL_LIGHT2,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT2,GL_DIFFUSE,diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT2, GL_SHININESS,shininess);
 	glLightfv(GL_LIGHT2,GL_POSITION,position3);
	GLfloat position4[] = {24,200,-280,1};
	glLightfv(GL_LIGHT3,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT3,GL_DIFFUSE,diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT3, GL_SHININESS,shininess);
 	glLightfv(GL_LIGHT3,GL_POSITION,position4);
 	GLfloat position5[] = {24,200,300,1};
 	glLightfv(GL_LIGHT4,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT4,GL_DIFFUSE,diffuse);
	glLightfv(GL_LIGHT4, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT4, GL_SHININESS,shininess);
 	glLightfv(GL_LIGHT4,GL_POSITION,position5);
 	GLfloat position6[] = {200,300,200,0};
 	glLightfv(GL_LIGHT5,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT5,GL_DIFFUSE,diffuse);
	glLightfv(GL_LIGHT5, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT5, GL_SHININESS,shininess);
 	glLightfv(GL_LIGHT5,GL_POSITION,position6);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);

	render();

	vector<vector<double> > ivts = innertrack->getverts();
	vector<vector<double> > ovts = outtertrack->getverts();

	gldrawable->swap_buffers();

	gldrawable->gl_end();

	return true;
}

bool Viewer::on_configure_event(GdkEventConfigure* event)
{
	Glib::RefPtr<Gdk::GL::Drawable> gldrawable = get_gl_drawable();

	if(!gldrawable)	return false;

	if(!gldrawable->gl_begin(get_gl_context()))	return false;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,event->width,event->height);
	gluPerspective(40.0,(GLfloat)event->width/(GLfloat)event->height, 0.1, 1000.0);

	glMatrixMode(GL_MODELVIEW);

	gldrawable->gl_end();

	return true;
}

bool Viewer::on_button_press_event(GdkEventButton* event)
{
	switch(event->button)
	{
		case 1:
		x_move = true;
		// init_x = event->x;
		if(aamode) aamode = false;
		else aamode = true;
		sm->Play(soundsrc);
		break;
		case 2:
		y_move = true;
		init_y = event->x;
		break;
		case 3:
		z_move = true;
		init_z = event->x;
		if(farcameramode) farcameramode = false;
		else farcameramode = true;
		sm->Stop(soundsrc);
		break;
	}
	return  true;
}

bool Viewer::on_button_release_event(GdkEventButton* event)
{
	switch(event->button)
	{
		case 1:
		x_move = false;
		break;
		case 3:
		y_move = false;
		break;
		case 2:
		z_move = false;
		break;
	}
	invalidate();
	return true;
}

bool Viewer::on_motion_notify_event(GdkEventMotion* event)
{
	if(x_move)
	{
		// anglex += (event->x - init_x);
		// init_x = event->x;
		// v_x += 0.1;
		// if(angley != 0)
		// {
		// 	if(angley < 0)	angley += 0.01;
		// 	if(angley > 0)	angley -= 0.01;
		// }
		// if(v_car->lfb_hit()) cout<<"hit: lfb"<<endl;
		// if(v_car->lrb_hit()) cout<<"hit: lrb"<<endl;
		// if(v_car->rfb_hit()) cout<<"hit: rfb"<<endl;
		// if(v_car->rrb_hit()) cout<<"hit: rrb"<<endl;
		// v_car->setangley(angley);
		// v_car->accelerate();
		// v_car->increcenter();
	}
	if(y_move)
	{
		angley += (event->x - init_y)/25;
		cout<<"angley: "<<angley<<endl;
		// v_car->increcenter();
		// v_car->updateCar();
		init_y = event->x;
	}
	if(z_move)
	{
		anglez += (event->x - init_z);
		init_z = event->x;
	}
	// v_car->calcyangle(innertrack->getverts());
	invalidate();
	return true;
}