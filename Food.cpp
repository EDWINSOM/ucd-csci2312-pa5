//
// Created by marisa on 12/13/15.
//

#include "Food.h"

using namespace std;

namespace Gaming
{
    const char Food::FOOD_ID = 'F';

    Food::Food(const Game &g, const Position &p, double capacity): Resource(g,p,capacity) {

        __capacity = capacity;
        __id = idGen();
        return;
    }

    void Food::print(std::ostream &os) const {

        cout <<  FOOD_ID << __id;

    }
}
