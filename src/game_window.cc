#include "game_window.h"
#include <iostream>

GameWindow::GameWindow() {
    set_default_size(400, 400);
    set_title("Gtk-Tac-Toe");
    
    Gtk::Box* vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
    add(*vbox);
    Gtk::Grid* grid = Gtk::manage(new Gtk::Grid());

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            
            Gtk::Button* btn = Gtk::manage(new Gtk::Button{""});
            btn->set_hexpand(true);
            btn->set_halign(Gtk::ALIGN_FILL);
            btn->set_vexpand(true);
            btn->set_valign(Gtk::ALIGN_FILL);
            btn->signal_clicked().connect([this, y, x] {
                this->on_button_clicked(y, x);
            });
            grid->attach(*btn, y, x);
        }
    }
    grid->set_halign(Gtk::ALIGN_FILL);
    grid->set_valign(Gtk::ALIGN_FILL);

    this->grid = grid; 

    vbox->add(*grid);
    vbox->show_all();
}

GameWindow::~GameWindow() {}

void GameWindow::on_button_clicked(int y, int x) {
    if (!game.set_piece(y, x)) return;
    Gtk::Button* btn = (Gtk::Button*)grid->get_child_at(y, x);
    
    Game::PieceState piece = game.get_piece(y, x);
    if (piece == Game::PieceState::X) btn->set_label("X");
    if (piece == Game::PieceState::O) btn->set_label("O");
    
    Game::Result result = game.get_result();
    if (result != Game::Result::InProgress) {
        lock_buttons();
        Gtk::MessageDialog* dialog = new Gtk::MessageDialog("Result", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);
        switch (result) {
            case Game::Result::XWon:
                dialog->set_secondary_text("X won!");
                break;
            case Game::Result::OWon:
                dialog->set_secondary_text("O won!");
                break;
            case Game::Result::Draw:
                dialog->set_secondary_text("It's a draw!");
                break;
            default: break;
        }
        dialog->set_default_response(Gtk::RESPONSE_OK);
        dialog->run();
        delete dialog;
    }
}

void GameWindow::lock_buttons() {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            Gtk::Button* btn = (Gtk::Button*)grid->get_child_at(y, x);
            btn->set_sensitive(false);
        }
    }
}
