//
// Created by manoel on 30/05/18.
//

#ifndef SDK_RODETAS_WINDOWCONTROL_H
#define SDK_RODETAS_WINDOWCONTROL_H

#include <iostream>

using namespace std;

class WindowControl {

public:

    void start();

    void setPlayingVariable(bool* isPlaying);
    void setTestingVariable(bool* isTesting);

private:

    bool* isPlaying;
    bool* isTestingTransmission;

};

#endif //SDK_RODETAS_WINDOWCONTROL_H
