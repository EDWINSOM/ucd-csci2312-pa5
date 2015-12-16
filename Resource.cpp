//
// Created by marisa on 12/13/15.
//

#include "Resource.h"
#include "Agent.h"

namespace Gaming
{

    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

    // Resources always return STAY
    ActionType Resource::takeTurn(const Surroundings &s) const {
        return STAY;
    }

    Resource::Resource(const Game &g, const Position &p, double __capacity): Piece(g,p), __capacity(__capacity) {
            return;
    }

    Piece &Resource::operator*(Piece &other) {

        if ( (other.getType() == SIMPLE) || (other.getType() == STRATEGIC) )
        {
            return (other.interact(this) );     // 2nd dispatch
        }

        else if ( (other.getType() == FOOD) || (other.getType() == ADVANTAGE))
        {
            return (other.interact(this) );     // 2nd dispatch
        }

        else
            return *this;
    }

    Piece &Resource::interact(Agent *agent) {

        // call Resource consume (), return Agent?

        agent->addEnergy(consume());
    }

    Piece &Resource::interact(Resource *resource) {

        // note: no interaction between resources
        return (*this);
    }

    double Resource::consume() {

         double giveAway = __capacity;

        __capacity = 0;

        finish();

        return giveAway;
    }

    void Resource::age() {

        __capacity /= RESOURCE_SPOIL_FACTOR;

    }
}
