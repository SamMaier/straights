//
// Created by Shiranka Miskin on 7/12/15.
//

#ifndef STRAIGHTS_GTKVIEW_H
#define STRAIGHTS_GTKVIEW_H

#include "Observer.h"
#include "gtkmm.h"
#include <iostream>
#include "Game.h"

class GtkView : public Gtk::Window, public Observer {
public:
    GtkView(Game*);
    virtual ~GtkView() {};
    void update() {};
protected:
    virtual void onButtonClicked();
    Gtk::Button m_button;
    Game* game_;


};


#endif //STRAIGHTS_GTKVIEW_H
