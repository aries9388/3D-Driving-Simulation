#ifndef VIEWER_HPP
#define VIEWER_HPP

#include <gtkmm.h>
#include <gtkglmm.h>
#include "object.hpp"
#include "car.hpp"
#include "mountain.hpp"
#include "particle.hpp"
#include "bmploader.hpp"

#define dl_car 1
#define dl_track 2
#define dl_mountain 3
#define dl_grass 4
#define dl_skybox 5
#define dl_exhaust 6


// const GLint pickBuffSize = 512;

class Viewer : public Gtk::GL::DrawingArea
{
public:
	Viewer();
	virtual ~Viewer();

	void initList();
	void drawdlCar();
	void drawdlTrack();
	void drawdlMountain();
	void drawgrass();
	void drawskybox();
	void drawexhaust();
	void render();
	void invalidate();
	void update();

protected:

	virtual void on_realize();

	virtual bool on_expose_event(GdkEventExpose* event);

	virtual bool on_configure_event(GdkEventConfigure* event);

	virtual bool on_button_press_event(GdkEventButton* event);

	virtual bool on_button_release_event(GdkEventButton* event);

	virtual bool on_motion_notify_event(GdkEventMotion* event);

private:
	double anglex;
	double angley;
	double anglez;
	bool x_move;
	bool y_move;
	bool z_move;
	int init_x,init_y,init_z;
	Car* v_car;
	double v_x;
	Mountain* v_mountain;
	bool aamode,farcameramode;
	GLuint grasstexture;
	GLuint skyboxtexture[6];
	GLuint smoketexture;
	int shadowmapwidth, shadowmapheight;
	GLuint shadowmaptexture;
	Matrix4x4 biasmatrix;
	GLfloat lightprojectmatrix[16];
	GLfloat lightviewmatrix[16];
	GLfloat cameraprojectmatrix[16];
	GLfloat cameraviewmatrix[16];
	BMP* grass_bmp;
	BMP* front_bmp;
	BMP* back_bmp;
	BMP* left_bmp;
	BMP* right_bmp;
	BMP* up_bmp;
	BMP* down_bmp;
	BMP* smoke_bmp;
	SoundManager *sm;
	int soundbuf;
	int soundsrc;
};

#endif