//
// Created by manoel on 30/05/18.
//

#ifndef SDK_RODETAS_WINDOWCONTROL_H
#define SDK_RODETAS_WINDOWCONTROL_H

#include <iostream>
#include <sigc++/sigc++.h>
#include <gtkmm.h>

using namespace std;

class WindowControl {

public:

    void start();

    void initializeWidgets();
    void setSignals();

    void onPressButtonPlaying();
    void onPressButtonTesting();

    // signals to Kernel
    sigc::signal <void, bool> signalUpdatePlaying;
    sigc::signal <void, bool> signalUpdateTesting;


private:

    bool* isPlaying;
    bool* isTestingTransmission;

};

#endif //SDK_RODETAS_WINDOWCONTROL_H
