#include "appwindow.hpp"
#include <iostream>

// Game *m_game;
bool gameon = false;
sigc::connection conn;
// sigc::connection timer;

void AppWindow::GameStart()
{
  // m_game = new Game (10,20);
  if(!gameon)
  {
    conn = Glib::signal_timeout().connect(sigc::mem_fun(*this,&AppWindow::update), 1);
    // timer = Glib::signal_timeout().connect(sigc::mem_fun(*this,&AppWindow::timecount), 100);
  }
  gameon = true;
}

// void AppWindow::ViewReset()
// {
//   m_viewer.resetView();
// }

bool AppWindow::update()
{
  
  // m_game->tick();
  m_viewer.update();
  return true;
}

// bool AppWindow::timecount()
// {
//   m_game->game_time_up();
//   return true;
// }

// void AppWindow::Wire_Frame_Mode()
// {
//   m_viewer.setDrawMode(0);
// }

// void AppWindow::Face_Mode()
// {
//   m_viewer.setDrawMode(1);
// }

// void AppWindow::Multicoloured_Mode()
// {
//   m_viewer.setDrawMode(2);
// }
// void AppWindow::Level1()
// {
//   conn.disconnect();
// }

void AppWindow::Level1()
{
  conn.disconnect();
  conn = Glib::signal_timeout().connect(sigc::mem_fun(*this,&AppWindow::update), 1000);
}

void AppWindow::Level2()
{
  conn.disconnect();
  conn = Glib::signal_timeout().connect(sigc::mem_fun(*this,&AppWindow::update), 750);
}

void AppWindow::Level3()
{
  conn.disconnect();
  conn = Glib::signal_timeout().connect(sigc::mem_fun(*this,&AppWindow::update), 500);
}

void AppWindow::Level4()
{
  conn.disconnect();
  conn = Glib::signal_timeout().connect(sigc::mem_fun(*this,&AppWindow::update), 250);
}

void AppWindow::Level5()
{
  conn.disconnect();
  conn = Glib::signal_timeout().connect(sigc::mem_fun(*this,&AppWindow::update), 100);
}

void AppWindow::Level6()
{
  conn.disconnect();
  conn = Glib::signal_timeout().connect(sigc::mem_fun(*this,&AppWindow::update), 10);
}

void AppWindow::Level7()
{
  conn.disconnect();
  conn = Glib::signal_timeout().connect(sigc::mem_fun(*this,&AppWindow::update), 1);
}




AppWindow::AppWindow()
{
  set_title("Driving");

  // A utility class for constructing things that go into menus, which
  // we'll set up next.
  using Gtk::Menu_Helpers::MenuElem;
  using Gtk::Menu_Helpers::RadioMenuElem;

  // Gtk::RadioButtonGroup group1;
  Gtk::RadioButtonGroup group2;
  // Set up the application menu
  // The slot we use here just causes AppWindow::hide() on this,
  // which shuts down the application.
  // m_menu_app.items().push_back(MenuElem("_New Game",Gtk::AccelKey("n"),
  //   sigc::mem_fun(*this, &AppWindow::GameStart)));
  // m_menu_app.items().push_back(MenuElem("_Reset",Gtk::AccelKey("r"),
  //   sigc::mem_fun(*this, &AppWindow::ViewReset)));
  m_menu_app.items().push_back(MenuElem("_Quit", Gtk::AccelKey("q"),
    sigc::mem_fun(*this, &AppWindow::hide)));
  

  // // Set up the menu bar
  m_menubar.items().push_back(Gtk::Menu_Helpers::MenuElem("_Application", m_menu_app));

  // m_menu_draw.items().push_back(RadioMenuElem(group1,"_Wire-frame",Gtk::AccelKey("w"),
  //   sigc::mem_fun(*this,&AppWindow::Wire_Frame_Mode)));
  // m_menu_draw.items().push_back(RadioMenuElem(group1,"_Face",Gtk::AccelKey("f"),
  //   sigc::mem_fun(*this,&AppWindow::Face_Mode)));
  // m_menu_draw.items().push_back(RadioMenuElem(group1,"_Multicoloured",Gtk::AccelKey("m"),
  //   sigc::mem_fun(*this,&AppWindow::Multicoloured_Mode)));

  // m_menubar.items().push_back(Gtk::Menu_Helpers::MenuElem("_Draw Mode",m_menu_draw));
  
  m_menu_speed.items().push_back(RadioMenuElem(group2,"_Very Slow",Gtk::AccelKey("1"),
    sigc::mem_fun(*this,&AppWindow::Level1)));
  m_menu_speed.items().push_back(RadioMenuElem(group2,"_Slow",Gtk::AccelKey("2"),
    sigc::mem_fun(*this,&AppWindow::Level2)));
  m_menu_speed.items().push_back(RadioMenuElem(group2,"_Medium",Gtk::AccelKey("3"),
    sigc::mem_fun(*this,&AppWindow::Level3)));
  m_menu_speed.items().push_back(RadioMenuElem(group2,"_Fast",Gtk::AccelKey("4"),
    sigc::mem_fun(*this,&AppWindow::Level4)));
  m_menu_speed.items().push_back(RadioMenuElem(group2,"_Very Fast",Gtk::AccelKey("5"),
    sigc::mem_fun(*this,&AppWindow::Level5)));
  m_menu_speed.items().push_back(RadioMenuElem(group2,"_Super Fast",Gtk::AccelKey("6"),
    sigc::mem_fun(*this,&AppWindow::Level6)));
  m_menu_speed.items().push_back(RadioMenuElem(group2,"_Overspeed",Gtk::AccelKey("7"),
    sigc::mem_fun(*this,&AppWindow::Level7)));

  m_menubar.items().push_back(Gtk::Menu_Helpers::MenuElem("_Speed",m_menu_speed));


  // Pack in our widgets
  
  // First add the vertical box as our single "top" widget
  add(m_vbox);

  // Put the menubar on the top, and make it as small as possible
  m_vbox.pack_start(m_menubar, Gtk::PACK_SHRINK);

  // Put the viewer below the menubar. pack_start "grows" the widget
  // by default, so it'll take up the rest of the window.
  m_viewer.set_size_request(800, 600);
  m_vbox.pack_start(m_viewer);

  show_all();
  
  GameStart();
}

bool AppWindow::on_key_press_event( GdkEventKey *ev )
{
        // This is a convenient place to handle non-shortcut
        // keys.  You'll want to look at ev->keyval.
  // std::cerr<<"Key: "<<ev->keyval<<std::endl;
	// An example key; delete and replace with the
	// keys you want to process

    //   switch(ev->keyval)
    //   {
    //     // Shift
    //     case 65505:
    //       m_viewer.setScaleMode(true);
    //       return true;
    //     // Up
    //     case 65362:
    //       if(gameon) m_game->rotateCW();
    //       return true;
    //     // Down
    //     case 65364:
    //       if(gameon) m_game->tick();
    //       return true;
    //     // Left
    //     case 65361:
    //       if(gameon) m_game->moveLeft();
    //       return true;
    //     // Right
    //     case 65363:
    //       if(gameon) m_game->moveRight();
    //       return true;
    //     case 32:
    //       if(gameon) m_game->drop();
    //       return true;
    //     default:
    //       return Gtk::Window::on_key_press_event( ev );
    //   }

    return Gtk::Window::on_key_press_event( ev );
    
}

bool AppWindow::on_key_release_event( GdkEventKey *ev )
{
  // std::cerr<<"Key: "<<ev->keyval<<" released"<<std::endl;
  // if(gameon)
  // {
  //   switch(ev->keyval)
  //   {
  //     // Shift
  //     case 65505:
  //       m_viewer.setScaleMode(false);
  //       return true;

  //     default:
  //       return Gtk::Window::on_key_release_event(ev);
  //   }
  // // }

  return Gtk::Window::on_key_release_event(ev);
}

