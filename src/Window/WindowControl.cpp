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
	if (event->keyval == GDK_KEY_space) {
		buttonPlay->clicked();
	} else if (event->keyval == GDK_KEY_Escape){
	    window->hide();
	}

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
		builder->get_widget("buttonChangeFunction", buttonChange);
		builder->get_widget("buttonPenaltyHit", buttonPenaltyHitPosition);
        builder->get_widget("buttonPenaltyAgainst", buttonPenaltyAgainstPosition);
        builder->get_widget("buttonMiddleDefense", buttonMiddleDefensePosition);
        builder->get_widget("buttonMiddleAttack", buttonMiddleAttackPosition);
        builder->get_widget("ButtonFreeBallLeftAttack", buttonFreeBallLeftAttackPosition);
        builder->get_widget("ButtonFreeBallLeftDefense", buttonFreeBallLeftDefensePosition);
        builder->get_widget("ButtonFreeBallRightAttack", buttonFreeBallRightAttackPosition);
        builder->get_widget("ButtonFreeBallRightDefense", buttonFreeBallRightDefensePosition);

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
	window->signal_hide().connect(sigc::mem_fun(this, &WindowControl::onCloseButton));
	buttonPlay->signal_clicked().connect(sigc::bind<Gtk::ToggleButton *>(sigc::mem_fun(this, &WindowControl::onPressButtonPlaying),buttonPlay));
	buttonTests->signal_clicked().connect(sigc::bind<Gtk::ToggleButton *>(sigc::mem_fun(this, &WindowControl::onPressButtonTesting),buttonTests));
	buttonChange->signal_clicked().connect(sigc::bind<Gtk::Button *>(sigc::mem_fun(this, &WindowControl::onPressButtonChange), buttonChange));
	buttonPenaltyHitPosition->signal_clicked().connect(sigc::bind<PositionStatus>(sigc::mem_fun(this, &WindowControl::onPositioningRequired), PositionStatus::PenaltyHit));
	buttonPenaltyAgainstPosition->signal_clicked().connect(sigc::bind<PositionStatus>(sigc::mem_fun(this, &WindowControl::onPositioningRequired), PositionStatus::PenaltyAgainst));
    buttonMiddleDefensePosition->signal_clicked().connect(sigc::bind<PositionStatus>(sigc::mem_fun(this, &WindowControl::onPositioningRequired), PositionStatus::MiddleDefense));
    buttonMiddleAttackPosition->signal_clicked().connect(sigc::bind<PositionStatus>(sigc::mem_fun(this, &WindowControl::onPositioningRequired), PositionStatus::MiddleAttack));
    buttonFreeBallLeftAttackPosition->signal_clicked().connect(sigc::bind<PositionStatus>(sigc::mem_fun(this, &WindowControl::onPositioningRequired), PositionStatus::FreeballLeftAttack));
    buttonFreeBallLeftDefensePosition->signal_clicked().connect(sigc::bind<PositionStatus>(sigc::mem_fun(this, &WindowControl::onPositioningRequired), PositionStatus::FreeballLeftDefense));
    buttonFreeBallRightAttackPosition->signal_clicked().connect(sigc::bind<PositionStatus>(sigc::mem_fun(this, &WindowControl::onPositioningRequired), PositionStatus::FreeballRightAttack));
    buttonFreeBallRightDefensePosition->signal_clicked().connect(sigc::bind<PositionStatus>(sigc::mem_fun(this, &WindowControl::onPositioningRequired), PositionStatus::FreeballRightDefense));
    onPressButtonPlaying(buttonPlay);
}

void WindowControl::onPositioningRequired(PositionStatus positionRequired){
    signalPositioning.emit(positionRequired);
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

void WindowControl::onPressButtonChange(Gtk::Button * buttonChange){
    signalChangeFunction.emit(true);
}

void WindowControl::onCloseButton() {
    signalCloseWindow.emit();
    Gtk::Main::quit();
}