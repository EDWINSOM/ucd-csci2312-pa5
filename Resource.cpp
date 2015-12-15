//
// Created by marisa on 12/13/15.
//

#include "Resource.h"

namespace Gaming
{

    Resource::RESOURCE_SPOIL_FACTOR = 1.2;

    // Resources always return STAY
    ActionType Resource::takeTurn(const Surroundings &s) const {
        return STAY;
    }
}