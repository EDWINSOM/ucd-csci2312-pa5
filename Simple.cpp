//
// Created by marisa on 12/13/15.
//

#include "Simple.h"

using namespace std;

namespace Gaming
{
    const char Simple::SIMPLE_ID = 'S';

    ActionType Simple::takeTurn(const Surroundings &s) const {


      for (int i = 0; i < 9; i++) {
            if (i == 4)
                ++i;

            if ((s.array[i] == FOOD) | (s.array[i] == ADVANTAGE)) {
                if (i == 0)
                    return NW;

                else if (i == 1)
                    return N;

                else if (i == 2)
                    return NE;

                else if (i == 3)
                    return W;

                else if (i == 5)
                    return E;

                else if (i == 6)
                    return SW;

                else if (i == 7)
                    return S;

                else if (i == 8)
                    return SE;
            }

        }

        for (int j = 0; j < 9; j++) {
            if (j == 4)
                ++j;

            if (s.array[j] == EMPTY) {
                if (j == 0)
                    return NW;

                else if (j == 1)
                    return N;

                else if (j == 2)
                    return NE;

                else if (j == 3)
                    return W;

                else if (j == 5)
                    return E;

                else if (j == 6)
                    return SW;

                else if (j == 7)
                    return S;

                else if (j == 8)
                    return SE;
            }
        }

        return STAY;
    }

    Simple::Simple(const Game &g, const Position &p, double energy): Agent(g,p,energy) {

        __energy = energy;
        __id = idGen();
        return ;
    }

    void Simple::print(std::ostream &os) const {

        if (__id < 10)
        {
            os << SIMPLE_ID << __id << "   ";
            return;
        }
        if (__id < 100)
        {
            os << SIMPLE_ID << __id << "  ";
            return;
        }
        else if (__id < 1000)
        {
            os << SIMPLE_ID << __id << " ";
            return;
        }

        return;

    }
}
