//
// Created by Shiranka Miskin on 7/14/15.
//

#include <iostream>
#include <gtkmm/image.h>
#include "ImageFactory.h"

const char suits[] = {'0','1','2','3'};
const char ranks[] = {'0','1','2','3','4','5','6','7','8','9','j','q','k'};

const char * image_names[] = {
        // Set up NINE of {DIAMOND,CLUB,HEART,SPADE}
        "res/0_0.png", "res/0_1.png", "res/0_2.png", "res/0_3.png",
        // Set up TEN of {DIAMOND,CLUB,HEART,SPADE}
        "res/1_0.png", "res/1_1.png", "res/1_2.png", "res/1_3.png",
        // Set up JACK of {DIAMOND,CLUB,HEART,SPADE}
        "res/2_0.png", "res/2_1.png", "res/2_2.png", "res/2_3.png",
        // Set up QUEEN of {DIAMOND,CLUB,HEART,SPADE}
        "res/3_0.png", "res/3_1.png", "res/3_2.png", "res/3_3.png"
};


Glib::RefPtr<Gdk::Pixbuf> createPixbuf(const std::string &name) {
    return Gdk::Pixbuf::create_from_file(name);
}

ImageFactory::ImageFactory() {

    int numImages = SUIT_COUNT * RANK_COUNT + 1;


    const char* image_names[numImages];
    for (int suit = 0; suit < SUIT_COUNT; suit++) {
        for (int rank = 0; rank < RANK_COUNT; rank++) {
            std::string *fileName = new std::string("res/");
            *fileName += suits[suit];
            *fileName += "_";
            *fileName += ranks[rank];
            *fileName += ".png";
            image_names[suit * RANK_COUNT + rank] = fileName->c_str();
        }
    }
    image_names[numImages - 1] = "res/nothing.png";


    std::transform(&image_names[0], &image_names[G_N_ELEMENTS(image_names)], std::back_inserter(cards_), &createPixbuf);
}

Glib::RefPtr<Gdk::Pixbuf> ImageFactory::getCardImage(Card card) {
    return getCardImage(card.getSuit() * RANK_COUNT + card.getRank());
}

Glib::RefPtr<Gdk::Pixbuf> ImageFactory::getCardImage(int index) {
    return cards_[index];
}


ImageFactory::~ImageFactory() {
}
