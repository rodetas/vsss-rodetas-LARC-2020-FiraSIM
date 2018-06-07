
#ifndef I_WINDOW_CONTROL_H_
#define I_WINDOW_CONTROL_H_

#include "gtkmm.h"

class IWindowControl {
public:
    virtual int run(int argc, char *argv[]) = 0;

    virtual bool onKeyboard(GdkEventKey*, Gtk::Window*) = 0;

    virtual void onPressButtonPlaying() = 0;
    virtual void onPressButtonTesting() = 0;
};
#endif