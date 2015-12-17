//
// Created by marisa on 12/13/15.
//

#include "Agent.h"
#include "Resource.h"
#include "Simple.h"
#include "Strategic.h"
#include "Food.h"
#include "Advantage.h"
#include <vector>

namespace Gaming
{
    const double Agent::AGENT_FATIGUE_RATE = 0.3;

    Agent::Agent(const Game &g, const Position &p, double energy): Piece(g,p) {

        __energy = energy;

    }

    Piece &Agent::operator*(Piece &other) {

        bool valid = false;

        Piece *agent = dynamic_cast<Agent *>(&other);
        if (agent)
        {
            valid = true;
        }

        Piece *resource = dynamic_cast<Resource *>(&other);
        if (resource)
        {
            valid = true;
        }

        if (valid)
        {
            if ((other.getType() == SIMPLE) || (other.getType() == STRATEGIC)) {
                return other.interact(this);
            }

            else if ((other.getType() == FOOD) || (other.getType() == ADVANTAGE)) {
                return (other.interact(this));
            }
        }


            else
                return *this;

    }

    Piece &Agent::interact(Agent *agent) {

        // Agents compete and might either both die, or one dies and the other wins.

        // Both Agents Die
        if (__energy == agent->__energy)
        {
            finish();
            agent->finish();
        }

        // 1st agent wins
        else if (__energy > agent->__energy)
        {
            __energy -= agent->__energy;
            agent->finish();
        }

        else if (__energy < agent->__energy)
        {
            agent->__energy -= __energy;
            finish();
        }

        return *this;
    }

    Piece &Agent::interact(Resource *resource) {

        // call Resource consume (), return Agent?
        addEnergy(resource->consume());

        return *this;
    }

    void Agent::age() {

        __energy -= AGENT_FATIGUE_RATE;

    }
}
