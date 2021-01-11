#pragma once

#include <gtkmm.h>
#include "game.h"

class GameWindow : public Gtk::Window {
    public:
        GameWindow();
        virtual ~GameWindow();
    private:
        Gtk::Grid* grid;
        Game game;
        void lock_buttons();
    protected:
        void on_button_clicked(int y, int x);
};
