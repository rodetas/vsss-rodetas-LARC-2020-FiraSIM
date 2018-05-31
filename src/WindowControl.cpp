//
// Created by manoel on 30/05/18.
//

#include "WindowControl.h"

void WindowControl::start() {

    *isPlaying = false;
    *isTestingTransmission = false;

    int option;

    while(true){

        cout << "1 - Play/Pause" << endl;
        cout << "2 - Test Transmission" << endl;

        cin >> option;

        switch (option){

            case 1:{
                *isPlaying = !*isPlaying;
            } break;

            case 2:{
                *isTestingTransmission = !*isTestingTransmission;
            } break;

            default: break;
        }

    }

}

void WindowControl::setPlayingVariable(bool* isPlaying){
    this->isPlaying = isPlaying;
}

void WindowControl::setTestingVariable(bool* isTesting){
    this->isTestingTransmission = isTesting;
}