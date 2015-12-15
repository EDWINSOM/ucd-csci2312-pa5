//
// Created by marisa on 12/13/15.
//

#include "Simple.h"

namespace Gaming
{
    Simple::SIMPLE_ID = 'S';

    ActionType Simple::takeTurn(const Surroundings &s) const {


        for (int i = 0; i < 9 ; i++)
        {
            if (i == 4)
                ++i;

            if ( (s.myArray[i] == FOOD) | (s.myArray[i] == ADVANTAGE) )
            {
                if( i == 0)
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

        for (int j = 0 ; j < 9 ; j++)
        {
            if (j == 4)
                ++j;

            if ( s.myArray[j] == EMPTY)
            {
                if( j == 0)
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
}