//
// Created by manoel on 30/05/18.
//

#ifndef SDK_RODETAS_WINDOWCONTROL_H
#define SDK_RODETAS_WINDOWCONTROL_H

#include <gtkmm.h>
#include<gtkmm/togglebutton.h>
#include <iostream>
#include <sigc++/sigc++.h>
#include <stdlib.h>

using namespace std;

class WindowControl {

public:

    void start();

    void initializeWidgets();
    void setSignals();

   	void onPressButtonPlaying(Gtk::ToggleButton * );
    void onPressButtonTesting(Gtk::ToggleButton * );

	bool onKeyboard(GdkEventKey*, Gtk::Window*);

	// signals to Kernel
    sigc::signal <void, bool> signalUpdatePlaying;
    sigc::signal <void, bool> signalUpdateTesting;


private:

    bool* isPlaying;
    bool* isTestingTransmission;

	Gtk::Window* window = nullptr;

    Gtk::ToggleButton* buttonPlay = nullptr;
    Gtk::ToggleButton* buttonTests = nullptr;

};

#endif //SDK_RODETAS_WINDOWCONTROL_H
