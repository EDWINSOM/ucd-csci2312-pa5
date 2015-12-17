//
// Created by marisa on 12/13/15.
//

#include <iomanip>
#include "Game.h"
#include "Strategic.h"
#include "Simple.h"
#include "Food.h"
#include "Advantage.h"
#include "Exceptions.h"

using namespace std;

namespace Gaming
{

    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;



    Game::Game()
    {
        __width = 3;
        __height = 3;
        __verbose = true;

        __grid.reserve(__width*__height);

        for (int i = 0; i < __width*__height ; i++)
        {
            __grid[i]= nullptr;
        }


        __numInitResources = 0;
        __numInitAgents=0;

        __status = NOT_STARTED;

        __round = 0;

     //   cout << *this;
    }

    Game::Game(unsigned width, unsigned height, bool manual)
    {
        if ((width < MIN_WIDTH) || (height < MIN_HEIGHT))
        {
            __width = 3;
            __height = 3;
            throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height);
        }

        else
        {
            __width = width;
            __height = height;
        }

        __verbose = true;

        __status = NOT_STARTED;

        __grid.reserve(width*height);

        for (int i = 0; i < __width*__height ; i++)
        {
            __grid[i]= nullptr;
        }

        if (manual == false)
        {
            populate();
        }
        else
        {
            __numInitResources = 0;
            __numInitAgents=0;
        }


    }


    Game::Game(const Game &another)
    {
        __numInitAgents = another.__numInitAgents;

        __numInitResources = another.__numInitResources;

        __width = another.__width;

        __height = another.__height;

        __grid = another.__grid;

        __round = another.__round;

        __status = another.__status;

        __verbose = another.__verbose;

       // play();

    }

    Game::~Game()
    {

        for (int i = 0; i < __grid.size() ; i++)
        {
            __grid[i] = nullptr;
        }
        __grid.clear();
        __status = OVER;
        __verbose = false;
    }


    void Game::populate()
    {
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;

        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents - numStrategic;
        unsigned int numAdvantages = __numInitResources / 4;
        unsigned int numFoods = __numInitResources - numAdvantages;

        // simple pseudo-random number generator
        // sufficient for our casual purposes
        std::default_random_engine gen;
        std::uniform_int_distribution<int> d(0, __width * __height);


        // populate Strategic agents
        while (numStrategic > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
                numStrategic --;
                ++__numInitAgents;
            }
        }

        // populate Simple agents
        while (numSimple > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
                numSimple --;
                ++__numInitAgents;
            }
        }

        // populate Food Pieces
        while (numFoods > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numFoods --;
                ++__numInitResources;
            }
        }

        //populate Advantage Pieces
        while (numAdvantages > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numAdvantages --;
                ++__numInitResources;
            }
        }


    }

    bool Game::addSimple(const Position &position)
    {
        bool result = false;


        if ( (position.x > __width) || (position.y > __height) )
        {
            throw OutOfBoundsEx(__width, __height, position.y, position.x);
        }

        if( __grid[position.x * __width + position.y] == nullptr)
        {
            __grid[position.x * __width + position.y] = new Simple(*this, position, STARTING_AGENT_ENERGY);
            result = true;
            ++__numInitAgents;
        }

        return result;
    }

    bool Game::addSimple(unsigned x, unsigned y)
    {
        bool result = false;
     try {
         Position temp(x, y);


         if (x > __width || y > __height) {
             throw OutOfBoundsEx(__width, __height, y, x);
         }
         if (__grid[x * __width + y] == nullptr)
         {
             __grid[x * __width + y] = new Simple(*this, temp, STARTING_AGENT_ENERGY);
             result =true;
             ++__numInitAgents;

         }
     }
        catch (OutOfBoundsEx ex)
                {
                    cout << ex;
                }

        return result;
    }

    bool Game::addStrategic(const Position &position, Strategy *s) {

        bool result = false;

        if (position.x > __width || position.y > __height)
        {
            throw OutOfBoundsEx(__width, __height, position.y, position.x);
        }

        if(__grid[position.x * __width + position.y] == nullptr)
        {
            __grid[position.x * __width + position.y] = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
            result = true;
            ++__numInitAgents;
        }
        return result;
    }

    bool Game::addStrategic(unsigned x, unsigned y, Strategy *s) {

        bool result = false;
        Position temp(x,y);

        if (x > __width || y > __height)
        {
            throw OutOfBoundsEx(__width, __height, y, x);
        }

        if (__grid[x * __width + y] == nullptr)
        {
            __grid[x * __width + y] = new Strategic(*this, temp, STARTING_AGENT_ENERGY, s);
            result = true;
            ++__numInitAgents;
        }
        return result;
    }


    bool Game::addFood(const Position &position)
    {
        bool result = false;

        if ( (position.x > __width) || (position.y > __height) )
        {
            throw OutOfBoundsEx(__width, __height, position.y, position.x);
        }

        if(__grid[position.x * __width + position.y] == nullptr)
        {
            __grid[position.x * __width + position.y] = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
            result = true;
            ++__numInitResources;
        }
        return result;
    }


    bool Game::addFood(unsigned x, unsigned y)
    {
        bool result = false;
        Position temp(x,y);

        if (x > __width || y > __height)
        {
            throw OutOfBoundsEx(__width, __height, y, x);
        }

        if (__grid[x * __width + y] == nullptr)
        {
            __grid[x * __width + y] = new Food(*this, temp, STARTING_RESOURCE_CAPACITY);
            result = true;
            ++__numInitResources;
        }
        return result;
    }


    bool Game::addAdvantage(const Position &position)
    {
        bool result = false;

        if ( (position.x > __width) || (position.y > __height) )
        {
            throw OutOfBoundsEx(__width, __height, position.y, position.x);
        }

        if(__grid[position.x * __width + position.y] == nullptr)
        {
            __grid[position.x * __width + position.y] = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
            result = true;
            ++__numInitResources;
        }
        return result;
    }


    bool Game::addAdvantage(unsigned x, unsigned y)
    {
        bool result = false;
        Position temp(x,y);

        if (x > __width || y > __height)
        {
            throw OutOfBoundsEx(__width, __height, y, x);
        }

        if (__grid[x * __width + y] == nullptr)
        {
            __grid[x * __width + y] = new Advantage(*this,temp, STARTING_RESOURCE_CAPACITY);
            result = true;
            ++__numInitResources;
        }
        return result;
    }


    unsigned int Game::getNumSimple() const {

        unsigned int numAgents = 0;
        std::vector<Piece *>::const_iterator it = __grid.begin();

        for ( it; it != __grid.end(); ++it)
        {
            Agent *agent = dynamic_cast<Simple*>(*it);
            if (agent) numAgents++;
        }

        return numAgents;
    }

    unsigned int Game::getNumStrategic() const
    {
        unsigned  int numAgents = 0;
        std::vector<Piece *>::const_iterator it = __grid.begin();

        for (it; it != __grid.end(); ++it)
        {
            Agent *agent = dynamic_cast<Strategic *>(*it);
            if (agent) numAgents++;
        }

        return numAgents;
    }


    unsigned int Game::getNumAgents() const {

        return __numInitAgents;
    }

    const Surroundings Game::getSurroundings(const Position &pos) const
    {
        Surroundings give;
        unsigned int index = 0;
        int outBounds = __height-1;
        int outBounds2 = __width-1;

        for (int x = -1; x < 2; x++)
        {
            for (int y = -1; y < 2; y++)
            {
                if ((pos.x + x) < 0 || (pos.y + y) < 0 )
                {
                    give.array[index] = INACCESSIBLE;
                }

                else if ((pos.x + x) > outBounds || (pos.y + y) > outBounds2)
                {
                    give.array[index] = INACCESSIBLE;
                }

                else if (y == 0 && x == 0)
                    give.array[index] = SELF;

                else if (__grid[(pos.x + x) * __width + (pos.y + y)] == nullptr)
                    give.array[index] = EMPTY;

                else
                    give.array[index] = __grid[(pos.x + x) * __width + (pos.y + y)]->getType();
                index++;
            }
        }
        return give;

    }

    std::ostream &operator<<(std::ostream &os, const Game &game) {

        std::string status;
        if (game.__status == 0)
        {
            status = "NOT PLAYING";
        }
        else if (game.__status == 1)
        {
            status = "PLAYING";
        }
        else
            status = "OVER";

        os << endl << "Round: " << game.__round << endl;

        int m = 0;

        for (int j = 0; j < game.__height; j++)
        {
            for (int i = 0; i < game.__width; i++)
            {
                os << "[";
                if(game.__grid[m] != nullptr)
                {
                    os <<  *game.__grid[m];
                }
                else
                    os << "     ";

                os << "]";
                m++;
            }
            os << endl;
        }

        os << "Status: " << status << "...";

        return os;
    }

    bool Game::isLegal(const ActionType &ac, const Position &pos) const

    {   Position test;

        test = move(pos, ac);

        if( (test.x >= 0) && (test.x < __width) )
        {
            if ((test.y >= 0) && (test.y < __height) )
            {
                return true;
            }
        }

        // game is over
        if (__status == OVER)
        {
            return false;
        }


        return false;
    }

    void Game::play(bool verbose)
    {
        __status = PLAYING;
        bool viable;
        unsigned counter;

        while (__status != OVER)
        {
            counter = 0;
            ++__round;
            round();
            for (int i = 0; i < (__width*__height) ; i++)
            {
                if (__grid[i] != nullptr)
                {
                    viable = __grid[i]->isViable();

                    if (viable) {
                        ++counter;
                        __grid[i]->setTurned(false);
                        __grid[i]->age();

                        // check if Piece has aged to 0
                        viable = __grid[i]->isViable();
                        if (!viable) {
                          /*  if ( (__grid[i]->getType() == SIMPLE) || (__grid[i]->getType() == STRATEGIC) )
                            {
                                --__numInitAgents;
                            }
                            if ( (__grid[i]->getType() == FOOD) || (__grid[i]->getType() == ADVANTAGE) )
                            {
                                --__numInitResources;
                            }*/
                            __grid[i] = nullptr;
                        }
                    }
                }
            }

            if(counter <= 1)
            {
                __status = OVER;
            }

            cout << *this << endl;      // prints out game/ grid
        }

    }

    void Game::round()
    {
        Surroundings copy;
        ActionType returned;
        Position test(1,1);
        bool legal = false;
        bool viable1 , viable2;
        int factor = 0;


        for (int i = 0 ; i < (__width*__height) ; i++)
        {
            if( __grid[i] != nullptr )
            {

                if (__grid[i]->getTurned() != true)
                {
                    copy = getSurroundings(__grid[i]->getPosition());       // returns a Surroundings

                    __grid[i]->setTurned(true);

                    returned = __grid[i]->takeTurn(copy);      // return ActionType

                    if (returned == NW)
                        factor = -4;

                    else if (returned == N)
                        factor = -3;

                    else if (returned == NE)
                        factor = -2;

                    else if (returned == W)
                        factor = -1;

                    else if (returned == E)
                        factor = 1;

                    else if (returned == SW)
                        factor = 2;

                    else if (returned == S)
                        factor = 3;

                    else if (returned == SE)
                        factor = 4;
                    else
                        factor = 0;

                    legal = isLegal(returned, __grid[i]->getPosition());
                    if (legal)
                    {
                        __grid[i]->setPosition(test);
                    }
                    if (returned != STAY) {
                        if (__grid[i + factor] != nullptr)        // is new position is not empty
                        {
                            (*__grid[i]) * (*__grid[i + factor]);    //interaction

                            viable1 = (*__grid[i]).isViable();
                            viable2 = (*__grid[i + factor]).isViable();

                            if (viable1 == false) {
                                if ( (__grid[i]->getType() == SIMPLE) || (__grid[i]->getType() == STRATEGIC) )
                                {
                                    --__numInitAgents;
                                }
                                if ( (__grid[i]->getType() == FOOD) || (__grid[i]->getType() == ADVANTAGE) )
                                {
                                    --__numInitResources;
                                }
                                delete __grid[i];
                                __grid[i] = nullptr;
                            }
                            if (viable2 == false) {
                                if ( (__grid[i+factor]->getType() == SIMPLE) || (__grid[i+factor]->getType() == STRATEGIC) )
                                {
                                    --__numInitAgents;
                                }
                                if ( (__grid[i+factor]->getType() == FOOD) || (__grid[i+factor]->getType() == ADVANTAGE) )
                                {
                                    --__numInitResources;
                                }
                                __grid[i + factor] = __grid[i];
                            }
                        }
                    }
                }

            }

        }

    }

    const Position Game::move(const Position &pos, const ActionType &ac) const {
        Position test = pos;
        unsigned int factor;

        // adding current position by (-1,-1)
        if (ac == NW)
        {
            test.x += -1;
            test.y += -1;

        }
        else if (ac == N)
        {
            test.x += -1;
        }

        else if (ac == NE)
        {
            test.x += -1;
            test.y += 1;
        }


        else if (ac == W)
        {
            test.y += -1;
        }


        else if (ac == E)
        {
            test.y += 1;
        }


        else if (ac == SW)
        {
            test.x += 1;
            test.y += -1;
        }


        else if (ac == S)
        {
            test.x += 1;
        }


        else if (ac == SE)
        {
            test.x += 1;
            test.y += 1;
        }

        return test;
    }


    const ActionType Game::reachSurroundings(const Position &from, const Position &to) {
        return STAY;
    }


    unsigned int Game::getNumPieces() const {
        unsigned int pieces = 0;

        pieces += __numInitAgents;
        pieces += __numInitResources;

        return pieces;
    }

    unsigned int Game::getNumResources() const {

        return __numInitResources;
    }

}
