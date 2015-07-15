//
// Created by Shiranka Miskin on 7/14/15.
//

#ifndef STRAIGHTS_IMAGEFACTORY_H
#define STRAIGHTS_IMAGEFACTORY_H

#include<gdkmm/pixbuf.h>
#include "Card.h"


#define NIL_CARD 52

class ImageFactory {
public:
    ImageFactory();
    virtual ~ImageFactory();
    Glib::RefPtr<Gdk::Pixbuf> getCardImage(Card);
    Glib::RefPtr<Gdk::Pixbuf> getCardImage(int index);
private:
    std::vector< Glib::RefPtr< Gdk::Pixbuf > > cards_;

};


#endif //STRAIGHTS_IMAGEFACTORY_H
