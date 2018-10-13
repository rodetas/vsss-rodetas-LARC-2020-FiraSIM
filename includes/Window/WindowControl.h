//
// Created by manoel on 30/05/18.
//

#ifndef SDK_RODETAS_WINDOWCONTROL_H
#define SDK_RODETAS_WINDOWCONTROL_H

#include <gtkmm.h>
#include <gtkmm/togglebutton.h>
#include <iostream>
#include <sigc++/sigc++.h>
#include <stdlib.h>
#include <Domain/PositionStatus.h>

using namespace std;

class WindowControl {

public:

    void start();

    void initializeWidgets();
    void setSignals();

   	void onPressButtonPlaying(Gtk::ToggleButton * );
    void onPressButtonTesting(Gtk::ToggleButton * );
	void onPressButtonChange(Gtk::Button * );
	void onPositioningRequired(PositionStatus);
	void onCloseButton();

	bool onKeyboard(GdkEventKey*, Gtk::Window*);

	// signals to Kernel
    sigc::signal <void, bool> signalUpdatePlaying;
    sigc::signal <void, bool> signalUpdateTesting;
	sigc::signal <void, bool> signalChangeFunction;
	sigc::signal <void, PositionStatus> signalPositioning;
	sigc::signal <void> signalCloseWindow;

private:

	Gtk::Window* window = nullptr;

    Gtk::ToggleButton* buttonPlay = nullptr;
    Gtk::ToggleButton* buttonTests = nullptr;
    Gtk::Button* buttonChange = nullptr;
    Gtk::ToggleButton* buttonPenaltyHitPosition = nullptr;
    Gtk::ToggleButton* buttonPenaltyAgainstPosition = nullptr;
    Gtk::ToggleButton* buttonMiddleAttackPosition = nullptr;
    Gtk::ToggleButton* buttonMiddleDefensePosition = nullptr;


};

#endif //SDK_RODETAS_WINDOWCONTROL_H
