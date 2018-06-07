//
// Created by manoel on 30/05/18.
//

#ifndef SDK_RODETAS_WINDOWCONTROL_H
#define SDK_RODETAS_WINDOWCONTROL_H

#include <iostream>
#include <sigc++/sigc++.h>
#include <gtkmm.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <IWindowControl.h>
using namespace std;

class WindowControl : public IWindowControl {

public:

    void start();

    void initializeWidgets();
    void setSignals();

   	void onPressButtonPlaying();
    void onPressButtonTesting();

    // signals to Kernel
    sigc::signal <void, bool> signalUpdatePlaying;
    sigc::signal <void, bool> signalUpdateTesting;
	
bool onKeyboard(GdkEventKey*, Gtk::Window*);


private:

    bool* isPlaying;
    bool* isTestingTransmission;
	Gtk::Window* window = nullptr;

		Gtk::Button* buttonPlay = nullptr;
		Gtk::Button* buttonTests = nullptr;

};

#endif //SDK_RODETAS_WINDOWCONTROL_H
