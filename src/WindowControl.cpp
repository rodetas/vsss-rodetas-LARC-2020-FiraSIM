//
// Created by manoel on 30/05/18.
//

#include "WindowControl.h"

void WindowControl::start() {

    initializeWidgets();
    setSignals();

    //Gtk::Main::run(window);
}

void WindowControl::initializeWidgets(){

    auto builder = Gtk::Builder::create();

    try {

        builder->add_from_file("../glade/Vision.glade");

        // inicializar os buttons aqui

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

}

void WindowControl::onPressButtonPlaying(){
    // invocar o signal para atualizar o kernel que houve uma variavel
    //signalUpdatePlaying.emit( valor )
}

void WindowControl::onPressButtonTesting(){
    // invocar o signal para atualizar o kernel que houve uma na variavel
    //signalUpdateTesting.emit ...
}