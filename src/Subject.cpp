//
// Created by Shiranka Miskin on 6/27/15.
//

#include "Subject.h"
void Subject::subscribe(Observer* observer) {
    observers_.insert(observer);
}

void Subject::unsubscribe(Observer* observer) {
    observers_.erase(observer);
}

void Subject::notify() {
    for (Observer* observer : observers_) {
        observer->update();
    }
}