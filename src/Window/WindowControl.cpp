//
// Created by manoel on 30/05/18.
//

#include "Window/WindowControl.h"

void WindowControl::start() {
    initializeWidgets();
	setSignals();

    Gtk::Main::run(*window);
}

bool WindowControl::onKeyboard(GdkEventKey* event, Gtk::Window* window) {

    return true;
}

void WindowControl::initializeWidgets(){

    auto builder = Gtk::Builder::create();

    try {

        builder->add_from_file("../glade/control-window.glade");

        // inicializar os buttons aqui
		builder->get_widget("window", window);

    	builder->get_widget("buttonPlay", buttonPlay);
		builder->get_widget("buttonTests", buttonTests);


    } catch (const Glib::FileError &ex) {
        std::cerr << "FileError: " << ex.what() << std::endl;
    } catch (const Glib::MarkupError &ex) {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
    } catch (const Gtk::BuilderError &ex) {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
    }

}

void WindowControl::setSignals(){
    // definir os eventos dos botoes
	window->signal_key_press_event().connect(sigc::bind<Gtk::Window*>(sigc::mem_fun(this, &WindowControl::onKeyboard), window) , false);
	buttonPlay->signal_clicked().connect(sigc::bind<Gtk::ToggleButton *>(sigc::mem_fun(this, &WindowControl::onPressButtonPlaying),buttonPlay));
	buttonTests->signal_clicked().connect(sigc::bind<Gtk::ToggleButton *>(sigc::mem_fun(this, &WindowControl::onPressButtonTesting),buttonTests));
}

void WindowControl::onPressButtonPlaying(Gtk::ToggleButton * buttonPlay){
    if(buttonPlay->get_active()) buttonPlay->set_label("Sending");
    else buttonPlay->set_label("Paused");

	signalUpdatePlaying.emit(buttonPlay->get_active());
}

void WindowControl::onPressButtonTesting(Gtk::ToggleButton * buttonTests){
    if(buttonTests->get_active()) buttonTests->set_label("Testing");
    else buttonTests->set_label("Stopped");

	signalUpdateTesting.emit(buttonTests->get_active());
}
