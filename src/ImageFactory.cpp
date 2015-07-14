//
// Created by Shiranka Miskin on 7/14/15.
//

#include "ImageFactory.h"

const char suits[] = {'0','1','2','3'};
const char ranks[] = {'0','1','2','3','4','5','6','7','8','9','j','q','k'};

Glib::RefPtr<Gdk::Pixbuf> createPixbuf(const std::string &name) {
    return Gdk::Pixbuf::create_from_file(name);
}

ImageFactory::ImageFactory() {

    std::vector<std::string> images;
    for (char suit : suits) {
        for (char rank : ranks) {
            std::string fileName = "res/";
            fileName += suit;
            fileName += "_";
            fileName += rank;
            fileName += ".png";
            images.push_back(fileName);
        }
    }

    images.push_back("res/nothing.png");
    transform(&images[0], &images[images.size() - 1], std::back_inserter(cards_), &createPixbuf);
}

Glib::RefPtr<Gdk::Pixbuf> ImageFactory::getCardImage(Card card) {
    return cards_[card.getSuit() * SUIT_COUNT + card.getRank()];
}

ImageFactory::~ImageFactory() {
}
