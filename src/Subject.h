//
// Created by Shiranka Miskin on 6/27/15.
//

#ifndef STRAIGHTS_SUBJECT_H
#define STRAIGHTS_SUBJECT_H


#include <set>
#include "Observer.h"

class Subject {

public:
   void subscribe( Observer*);
   void unsubscribe( Observer*);
protected:
   void notify();

private:
   std::set< Observer* > observers_;
};


#endif
