#include <iostream>
#include <gtkmm.h>
#include <gtkglmm.h>
#include "appwindow.hpp"
#include "car_obj.hpp"
#include "bmploader.hpp"
#include "SoundManager.h"

extern Object* car;
extern Object* track;
extern Object* innertrack;
extern Object* outtertrack;
extern Object* pathpoints;
extern Object* treeposition;

int main(int argc, char** argv)
{
  // Construct our main loop
  Gtk::Main kit(argc, argv)
;
  // Initialize OpenGL
  Gtk::GL::init(argc, argv);

  std::string filename = "data/car.obj";
  if (argc >= 2) {
    filename = argv[1];
  }

  // This is how you might import a scene.
  car = import_object(filename);
  if (!car) {
    std::cerr << "Could not open " << filename << std::endl;
    return 1;
  }

  track = import_object("data/track.obj");

  if(!track)
  {
    std::cerr<< "Could not open " << filename << std::endl;
    return 1;
  }

  innertrack = import_object("data/innertrack.obj");
  outtertrack = import_object("data/outtertrack.obj");
  pathpoints = import_object("data/path.obj");


  
  // // std::cerr<<"sphere gen: "<<dl_sphere<<std::endl;
  // // Construct our (only) window
  AppWindow window;

  // // And run the application!
  Gtk::Main::run(window);
}

