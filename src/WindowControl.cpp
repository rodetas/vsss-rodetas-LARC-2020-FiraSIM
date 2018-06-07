//
// Created by manoel on 30/05/18.
//
#include "IWindowControl.h"
#include "WindowControl.h"

void WindowControl::start() {

    initializeWidgets();
	setSignals();

    //Gtk::Main::run(window);
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
	window->signal_key_press_event().connect(sigc::bind<Gtk::Window*>(sigc::mem_fun(this, &IWindowControl::onKeyboard), window) , false);
	buttonPlay->signal_clicked().connect(sigc::mem_fun(this, &IWindowControl::onPressButtonPlaying));
	buttonTests->signal_clicked().connect(sigc::mem_fun(this, &IWindowControl::onPressButtonTesting));
}

 void WindowControl::onPressButtonPlaying(){
    // invocar o signal para atualizar o kernel que houve uma variavel
    //signalUpdatePlaying.emit( valor )
	//bool state;
	//state=Gtk::ToggleButton::get_active();
	signalUpdatePlaying.emit(true);

}

 void WindowControl::onPressButtonTesting(){
    // invocar o signal para atualizar o kernel que houve uma na variavel
    //signalUpdateTesting.emit ...
	//bool state;
	// state=Gtk::ToggleButton::get_active();
	signalUpdateTesting.emit(true);
}