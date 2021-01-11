#include "game_window.h"
#include <gtkmm.h>
int main() {
    auto app = Gtk::Application::create("com.inxane.gtk-tac-toe");
    GameWindow window;
    return app->run(window);
}
