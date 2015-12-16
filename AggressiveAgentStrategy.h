//
// Created by Ivo Georgiev on 12/9/15.
//

#ifndef PA5GAME_AGGRESSIVEAGENTSTRATEGY_H
#define PA5GAME_AGGRESSIVEAGENTSTRATEGY_H

#include "Strategy.h"

namespace Gaming {

    class AggressiveAgentStrategy : public Strategy {
        double __agentEnergy;

    public:
        static const double DEFAULT_AGGRESSION_THRESHOLD;

        AggressiveAgentStrategy(double agentEnergy): __agentEnergy(agentEnergy) {};
        ~AggressiveAgentStrategy() {__agentEnergy = 0;};
      //  ActionType operator()(const Surroundings &s) const override;

    };

}


#endif //PA5GAME_AGGRESSIVEAGENTSTRATEGY_H
