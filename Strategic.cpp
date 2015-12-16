#include "Strategic.h"
#include "AggressiveAgentStrategy.h"

using namespace std;

namespace Gaming
{

    const char Strategic::STRATEGIC_ID = 'T';

    ActionType Strategic::takeTurn(const Surroundings &s) const
    {


            // aggressive Strategic Agent

            if (__energy >= AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD) {
                for (int i = 0; i < 9; i++) {
                    if (i == 4)
                        ++i;

                    if ((s.array[i] == SIMPLE) | (s.array[i] == STRATEGIC)) {
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

                    if (s.array[j] == ADVANTAGE) {
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

                for (int k = 0; k < 9; k++) {
                    if (k == 4)
                        ++k;

                    if (s.array[k] == FOOD) {
                        if (k == 0)
                            return NW;

                        else if (k == 1)
                            return N;

                        else if (k == 2)
                            return NE;

                        else if (k == 3)
                            return W;

                        else if (k == 5)
                            return E;

                        else if (k == 6)
                            return SW;

                        else if (k == 7)
                            return S;

                        else if (k == 8)
                            return SE;
                    }
                }

                for (int m = 0; m < 9; m++) {
                    if (m == 4)
                        ++m;

                    if (s.array[m] == EMPTY) {
                        if (m == 0)
                            return NW;

                        else if (m == 1)
                            return N;

                        else if (m == 2)
                            return NE;

                        else if (m == 3)
                            return W;

                        else if (m == 5)
                            return E;

                        else if (m == 6)
                            return SW;

                        else if (m == 7)
                            return S;

                        else if (m == 8)
                            return SE;
                    }
                }

                return STAY;
            }

                // default Strategic Agent
            else {
                for (int i = 0; i < 9; i++) {
                    if (i == 4)
                        ++i;

                    if ((s.array[i] == ADVANTAGE)) {
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

                    if (s.array[j] == FOOD) {
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

                for (int k = 0; k < 9; k++) {
                    if (k == 4)
                        ++k;

                    if (s.array[k] == EMPTY) {
                        if (k == 0)
                            return NW;

                        else if (k == 1)
                            return N;

                        else if (k == 2)
                            return NE;

                        else if (k == 3)
                            return W;

                        else if (k == 5)
                            return E;

                        else if (k == 6)
                            return SW;

                        else if (k == 7)
                            return S;

                        else if (k == 8)
                            return SE;
                    }
                }

                for (int m = 0; m < 9; m++) {
                    if (m == 4)
                        ++m;

                    if (s.array[m] == SIMPLE) {
                        if (m == 0)
                            return NW;

                        else if (m == 1)
                            return N;

                        else if (m == 2)
                            return NE;

                        else if (m == 3)
                            return W;

                        else if (m == 5)
                            return E;

                        else if (m == 6)
                            return SW;

                        else if (m == 7)
                            return S;

                        else if (m == 8)
                            return SE;
                    }
                }

        }
            return STAY;

    }

    Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s): Agent(g,p,energy) {

        __strategy = s;
        __energy = energy;
        __id = idGen();
    }

    Strategic::~Strategic() {

        __strategy = nullptr;
    }

    void Strategic::print(std::ostream &os) const {

        cout <<  STRATEGIC_ID << __id;

    }
}

