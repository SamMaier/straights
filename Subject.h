//
// Created by Shiranka Miskin on 6/27/15.
//

#ifndef STRAIGHTS_SUBJECT_H
#define STRAIGHTS_SUBJECT_H


#include<vector>
#include "View.h"

class Subject {

public:
   void subscribe(View*);
   void unsubscribe(View*);

private:
   std::vector<View*> observers;

};


#endif
