#ifndef APPWINDOW_HPP
#define APPWINDOW_HPP

#include <gtkmm.h>
#include "viewer.hpp"

class AppWindow : public Gtk::Window {
public:
  AppWindow();
  
  void GameStart();

  // void ViewReset();

  bool update();

  void Level1();

  void Level2();

  void Level3();

  void Level4();

  void Level5();

  void Level6();

  void Level7();

  // bool timecount();
  
protected:
  virtual bool on_key_press_event( GdkEventKey *ev );
  virtual bool on_key_release_event(GdkEventKey *ev );

private:
  // A "vertical box" which holds everything in our window
  Gtk::VBox m_vbox;

  // The menubar, with all the menus at the top of the window
  Gtk::MenuBar m_menubar;
  // Each menu itself
  Gtk::Menu m_menu_app;

  // Gtk::Menu m_menu_draw;

  Gtk::Menu m_menu_speed;

  // The main OpenGL area
  Viewer m_viewer;

};



#endif
