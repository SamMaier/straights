//
// Created by Shiranka Miskin on 7/14/15.
//

#ifndef STRAIGHTS_IMAGEFACTORY_H
#define STRAIGHTS_IMAGEFACTORY_H

#include<gdkmm/pixbuf.h>
#include "Card.h"

class ImageFactory {
public:
    ImageFactory();
    virtual ~ImageFactory();
    Glib::RefPtr<Gdk::Pixbuf> getCardImage(Card);
private:
    std::vector< Glib::RefPtr< Gdk::Pixbuf > > cards_;

};


#endif //STRAIGHTS_IMAGEFACTORY_H
