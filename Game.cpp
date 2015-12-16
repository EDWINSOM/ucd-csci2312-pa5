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

        populate();

        __status = NOT_STARTED;

        __round = 0;

        cout << *this;
        play();
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

        play();

    }

    Game::~Game()
    {
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

        __grid.reserve(__width*__height);

        // populate Strategic agents
        while (numStrategic > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
                numStrategic --;
            }
        }

        // populate Simple agents
        while (numSimple > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
                numSimple --;
            }
        }

        // populate Food Pieces
        while (numFoods > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numFoods --;
            }
        }

        //populate Advantage Pieces
        while (numAdvantages > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numAdvantages --;
            }
        }


    }

    bool Game::addSimple(const Position &position) {

        bool result = false;

        int i = 0;


        while((result == false) && (i < (__width*__height)))
        {
            if( __grid[i] == nullptr)
            {
                __grid[i] = new Simple(*this, position, Game::STARTING_AGENT_ENERGY);
                 result = true;
            }
            ++i;
        }

        return result;
    }

    bool Game::addSimple(unsigned x, unsigned y) {

        bool result = false;

        int i = 0;

        while ((result == false) && (i < (__width*__height)) )
        {
            if( __grid[i] == nullptr)
            {
                Position position(x, y);
                __grid[i] = new Simple(*this, position, Game::STARTING_AGENT_ENERGY);
                result = true;
            }
            ++i;
        }

        __grid.resize(__grid.size());
        return result;
    }

    bool Game::addStrategic(const Position &position, Strategy *s) {

        bool result = false;

        int i = 0;

        while ((result == false) && (i < (__width*__height)) )
        {
            if( __grid[i] == nullptr)
            {
                __grid[i] = new Strategic(*this, position, Game::STARTING_AGENT_ENERGY, s);
                result = true;
            }
            ++i;
        }

        __grid.resize(__grid.size());
        return result;
    }

    bool Game::addStrategic(unsigned x, unsigned y, Strategy *s) {

        bool result = false;

        int i = 0;

        while ((result == false) && (i < (__width*__height)) )
        {
            if( __grid[i] == nullptr)
            {
                Position position(x,y);
                __grid[i] = new Strategic(*this, position, Game::STARTING_AGENT_ENERGY, s);
                result = true;
            }
            ++i;
        }

        __grid.resize(__grid.size());
        return result;
    }


    bool Game::addFood(const Position &position) {

        bool result = false;

        int i = 0;

        while ((result == false) && (i < (__width*__height)) )
        {
            if( __grid[i] == nullptr)
            {
                __grid[i] = new Food(*this, position, Game::STARTING_RESOURCE_CAPACITY);
                result = true;
            }
            ++i;
        }

        __grid.resize(__grid.size());
        return result;
    }


    bool Game::addFood(unsigned x, unsigned y) {

        bool result = false;

        int i = 0;

        while ((result == false) && (i < (__width*__height)) )
        {
            if( __grid[i] == nullptr)
            {
                Position position(x,y);
                __grid[i] = new Food(*this, position, Game::STARTING_RESOURCE_CAPACITY);
                result = true;
            }
            ++i;
        }

        __grid.resize(__grid.size());
        return result;
    }


    bool Game::addAdvantage(const Position &position) {
        bool result = false;

        int i = 0;

        while ((result == false) && (i < (__width*__height)) )
        {
            if( __grid[i] == nullptr)
            {
                __grid[i] = new Advantage(*this, position, Game::STARTING_RESOURCE_CAPACITY);
                result = true;
            }
            ++i;
        }

        __grid.resize(__grid.size());
        return result;
    }


    bool Game::addAdvantage(unsigned x, unsigned y) {
        bool result = false;

        int i = 0;

        while ((result == false) && (i < (__width*__height)) )
        {
            if( __grid[i] == nullptr)
            {
                Position position(x,y);
                __grid[i] = new Advantage(*this, position, Game::STARTING_RESOURCE_CAPACITY);
                result = true;
            }
            ++i;
        }

        __grid.resize(__grid.size());
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

    const Surroundings Game::getSurroundings(const Position &pos) const
    {
        Surroundings * give = new Surroundings;

        (*give).array[4] = SELF;

        if ((pos.x == 0) && (pos.y == 0))   // at position (0,0), [0] in __grid
        {
            (*give).array[0] = INACCESSIBLE;
            (*give).array[1] = INACCESSIBLE;
            (*give).array[2] = INACCESSIBLE;
            (*give).array[3] = INACCESSIBLE;
            (*give).array[6] = INACCESSIBLE;

            if (__grid[1] == nullptr)
            {
                (*give).array[5] = EMPTY;
            }
            else
                (*give).array[5] = __grid[1]->getType();

            if(__grid[3] == nullptr)
            {
                (*give).array[7] = EMPTY;
            }
            else
                  (*give).array[7] = __grid[3]->getType();

            if(__grid[4] == nullptr)
            {
                (*give).array[8] = EMPTY;
            }
            else
                (*give).array[8] = __grid[4]->getType();
        }

        if((pos.x == 0) && (pos.y == 1))  // at position (0,1), [1] in __grid
        {
            (*give).array[0] = INACCESSIBLE;
            (*give).array[1] = INACCESSIBLE;
            (*give).array[2] = INACCESSIBLE;

            if(__grid[0] == nullptr)
            {
                (*give).array[3] = EMPTY;
            }
            else
                (*give).array[3] = __grid[0]->getType();


            if(__grid[2] == nullptr)
            {
                (*give).array[5] = EMPTY;
            }
            else
            (*give).array[5] = __grid[2]->getType();



            if(__grid[3] == nullptr)
            {
                (*give).array[6] = EMPTY;
            }
            else
            (*give).array[6] = __grid[3]->getType();



            if(__grid[4] == nullptr)
            {
                (*give).array[7] = EMPTY;
            }
            else
            (*give).array[7] = __grid[4]->getType();

            if(__grid[5] == nullptr)
            {
                (*give).array[8] = EMPTY;
            }
            else
            (*give).array[8] = __grid[5]->getType();
        }

        if( (pos.x == 0) && (pos.y == 2))   // at position (0.2), [2] in __grid
        {
            (*give).array[0] = INACCESSIBLE;
            (*give).array[1] = INACCESSIBLE;
            (*give).array[2] = INACCESSIBLE;
            (*give).array[5] = INACCESSIBLE;
            (*give).array[8] = INACCESSIBLE;

            if(__grid[1] == nullptr)
            {
                (*give).array[3] = EMPTY;
            }
            else
            (*give).array[3] = __grid[1]->getType();

            if(__grid[4] == nullptr)
            {
                (*give).array[6] = EMPTY;
            }
            else
            (*give).array[6] = __grid[4]->getType();


            if(__grid[5] == nullptr)
            {
                (*give).array[7] = EMPTY;
            }
            else
            (*give).array[7] = __grid[5]->getType();
        }

        if( (pos.x == 1) && (pos.y == 0))   // at position (1,0), [3] in __grid
        {
            (*give).array[0] = INACCESSIBLE;
            (*give).array[3] = INACCESSIBLE;
            (*give).array[6] = INACCESSIBLE;

            if(__grid[0] == nullptr)
            {
                (*give).array[1] = EMPTY;
            }
            else
            (*give).array[1] = __grid[0]->getType();


            if(__grid[1] == nullptr)
            {
                (*give).array[2] = EMPTY;
            }
            else
            (*give).array[2] = __grid[1]->getType();

            if(__grid[4] == nullptr)
            {
                (*give).array[5] = EMPTY;
            }
            else
            (*give).array[5] = __grid[4]->getType();


            if(__grid[6] == nullptr)
            {
                (*give).array[7] = EMPTY;
            }
            else
            (*give).array[7] = __grid[6]->getType();


            if(__grid[7] == nullptr)
            {
                (*give).array[8] = EMPTY;
            }
            else
            (*give).array[8] = __grid[7]->getType();
        }

        if( (pos.x == 1) && (pos.y == 1))   // at position (1,1), [4] in __grid
        {
            if(__grid[0] == nullptr)
            {
                (*give).array[0] = EMPTY;
            }
            else
            (*give).array[0] = __grid[0]->getType();

            if(__grid[1] == nullptr)
            {
                (*give).array[1] = EMPTY;
            }
            else
            (*give).array[1] = __grid[1]->getType();


            if(__grid[2] == nullptr)
            {
                (*give).array[2] = EMPTY;
            }
            else
            (*give).array[2] = __grid[2]->getType();


            if(__grid[3] == nullptr)
            {
                (*give).array[3] = EMPTY;
            }
            else
            (*give).array[3] = __grid[3]->getType();


            if(__grid[5] == nullptr)
            {
                (*give).array[5] = EMPTY;
            }
            else
            (*give).array[5] = __grid[5]->getType();


            if(__grid[6] == nullptr)
            {
                (*give).array[6] = EMPTY;
            }
            else
            (*give).array[6] = __grid[6]->getType();


            if(__grid[7] == nullptr)
            {
                (*give).array[7] = EMPTY;
            }
            else
            (*give).array[7] = __grid[7]->getType();


            if(__grid[8] == nullptr)
            {
                (*give).array[8] = EMPTY;
            }
            else
            (*give).array[8] = __grid[8]->getType();
        }

        if( (pos.x == 1) && (pos.y == 2))   // at position (1,2), [5] in __grid
        {
            (*give).array[2] = INACCESSIBLE;
            (*give).array[5] = INACCESSIBLE;
            (*give).array[8] = INACCESSIBLE;

            if(__grid[1] == nullptr)
            {
                (*give).array[0] = EMPTY;
            }
            else
            (*give).array[0] = __grid[1]->getType();

            if(__grid[2] == nullptr)
            {
                (*give).array[1] = EMPTY;
            }
            else
            (*give).array[1] = __grid[2]->getType();


            if(__grid[4] == nullptr)
            {
                (*give).array[3] = EMPTY;
            }
            else
            (*give).array[3] = __grid[4]->getType();


            if(__grid[7] == nullptr)
            {
                (*give).array[6] = EMPTY;
            }
            else
            (*give).array[6] = __grid[7]->getType();


            if(__grid[8] == nullptr)
            {
                (*give).array[7] = EMPTY;
            }
            else
            (*give).array[7] = __grid[8]->getType();
        }

        if( (pos.x == 2) && (pos.y == 0))   // at position (2,0), [6] in __grid
        {
            (*give).array[0] = INACCESSIBLE;
            (*give).array[3] = INACCESSIBLE;
            (*give).array[6] = INACCESSIBLE;
            (*give).array[7] = INACCESSIBLE;
            (*give).array[8] = INACCESSIBLE;

            if(__grid[3] == nullptr)
            {
                (*give).array[1] = EMPTY;
            }
            else
            (*give).array[1] = __grid[3]->getType();


            if(__grid[4] == nullptr)
            {
                (*give).array[2] = EMPTY;
            }
            else
            (*give).array[2] = __grid[4]->getType();

            if(__grid[7] == nullptr)
            {
                (*give).array[5] = EMPTY;
            }
            else
            (*give).array[5] = __grid[7]->getType();
        }

        if( (pos.x == 2) && (pos.y == 1)) // at position (2,1), [7] in __grid
        {
            (*give).array[6] = INACCESSIBLE;
            (*give).array[7] = INACCESSIBLE;
            (*give).array[8] = INACCESSIBLE;


            if(__grid[3] == nullptr)
            {
                (*give).array[0] = EMPTY;
            }
            else
            (*give).array[0] = __grid[3]->getType();


            if(__grid[4] == nullptr)
            {
                (*give).array[1] = EMPTY;
            }
            else
            (*give).array[1] = __grid[4]->getType();

            if(__grid[5] == nullptr)
            {
                (*give).array[2] = EMPTY;
            }
            else
            (*give).array[2] = __grid[5]->getType();


            if(__grid[6] == nullptr)
            {
                (*give).array[3] = EMPTY;
            }
            else
            (*give).array[3] = __grid[6]->getType();


            if(__grid[8] == nullptr)
            {
                (*give).array[5] = EMPTY;
            }
            else
            (*give).array[5] = __grid[8]->getType();
        }

        if ( (pos.x == 2) && (pos.y == 2)) // at position (2,2), [8] in __grid
        {
            (*give).array[2] = INACCESSIBLE;
            (*give).array[5] = INACCESSIBLE;
            (*give).array[6] = INACCESSIBLE;
            (*give).array[7] = INACCESSIBLE;
            (*give).array[8] = INACCESSIBLE;


            if(__grid[4] == nullptr)
            {
                (*give).array[0] = EMPTY;
            }
            else
            (*give).array[0] = __grid[4]->getType();


            if(__grid[5] == nullptr)
            {
                (*give).array[1] = EMPTY;
            }
            else
            (*give).array[1] = __grid[5]->getType();


            if(__grid[7] == nullptr)
            {
                (*give).array[3] = EMPTY;
            }
            else
            (*give).array[3] = __grid[7]->getType();
        }

        return *give;

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

        cout << endl << "Round: " << game.__round << endl;
        int m = 0;

        for (int j = 0; j < game.__height; j++)
        {
            for (int i = 0; i < game.__width; i++)
            {
                if(game.__grid[m] != nullptr)
                {
                    cout << "[" << *game.__grid[m] << setw(2) << "]";
                }
                else
                    cout << "[" << setw(6) << "]";
                m++;
            }
            cout << endl;
        }

        cout << "Status: " << status << "...";

        return os;
    }

    bool Game::isLegal(const ActionType &ac, const Position &pos) const {

        if( (pos.x > -1) && (pos.x < 5) )
        {
            if ((pos.y > -1) && (pos.y < 4) )
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
            for (int i = 0; i < 9 ; i++)
            {
                if (__grid[i] != nullptr)
                {
                    viable = __grid[i]->isViable();

                    if (viable) {
                        ++counter;
                        __grid[i]->age();
                        __grid[i]->setTurned(false);

                        // check if Piece has aged to 0
                        viable = __grid[i]->isViable();
                        if (!viable) {
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


        for (int i = 0 ; i < 9 ; i++)
        {
            if( __grid[i] != nullptr ) {

                    if (__grid[i]->getTurned() != true) {
                        copy = getSurroundings(__grid[i]->getPosition());       // returns a Surroundings

                        __grid[i]->setTurned(true);

                        returned = __grid[i]->takeTurn(copy);      // return ActionType

                        //convert returned value on surroundings to a position on __grid

                        // adding current position by (-1,-1)
                        if (returned == NW) {
                            factor = -4;
                            if (__grid[i - 4] != nullptr)        // is new position is not empty
                            {
                                (*__grid[i]) * (*__grid[i - 4]);    //interaction

                                viable1 = (*__grid[i]).isViable();
                                viable2 = (*__grid[i - 4]).isViable();

                                if (viable1 == false) {
                                    __grid[i] = nullptr;
                                }
                                if (viable2 == false) {
                                    __grid[i - 4] = nullptr;

                                    test.x += -1;
                                    test.y += -1;
                                }
                            }

                            else {
                                test.x += -1;
                                test.y += -1;
                            }

                        }

                            // adding current position by (-1,0)
                        else if (returned == N) {
                            factor = -3;
                            if (__grid[i - 3] != nullptr)        // is new position is not empty
                            {
                                (*__grid[i]) * (*__grid[i - 3]);    //interaction

                                viable1 = (*__grid[i]).isViable();
                                viable2 = (*__grid[i - 3]).isViable();

                                if (viable1 == false) {
                                    __grid[i] = nullptr;
                                }
                                if (viable2 == false) {
                                    __grid[i - 3] = nullptr;
                                    test.x += -1;
                                }
                            }
                            else {
                                test.x += -1;
                            }

                        }

                            // adding current position by (-1,1)
                        else if (returned == NE) {
                            factor = -2;
                            if (__grid[i - 2] != nullptr)        // is new position is not empty
                            {
                                (*__grid[i]) * (*__grid[i - 2]);    //interaction

                                viable1 = (*__grid[i]).isViable();
                                viable2 = (*__grid[i - 2]).isViable();

                                if (viable1 == false) {
                                    __grid[i] = nullptr;
                                }
                                if (viable2 == false) {
                                    __grid[i - 2] = nullptr;
                                    test.x += -1;
                                    test.y += 1;
                                }
                            }
                            else {
                                test.x += -1;
                                test.y += 1;
                            }

                        }

                            // adding current position by (0,-1)
                        else if (returned == W) {
                            factor = -1;
                            if (__grid[i - 1] != nullptr)        // is new position is not empty
                            {
                                (*__grid[i]) * (*__grid[i - 1]);    //interaction

                                viable1 = (*__grid[i]).isViable();
                                viable2 = (*__grid[i - 1]).isViable();

                                if (viable1 == false) {
                                    __grid[i] = nullptr;
                                }
                                if (viable2 == false) {
                                    __grid[i - 1] = nullptr;
                                    test.y += -1;
                                }
                            }
                            else {
                                test.y += -1;
                            }

                        }

                            // adding current position by (0,1)
                        else if (returned == E) {
                            factor = 1;
                            if (__grid[i + 1] != nullptr)        // is new position is not empty
                            {
                                (*__grid[i]) * (*__grid[i + 1]);    //interaction

                                viable1 = (*__grid[i]).isViable();
                                viable2 = (*__grid[i + 1]).isViable();

                                if (viable1 == false) {
                                    __grid[i] = nullptr;
                                }
                                if (viable2 == false) {
                                    __grid[i + 1] = nullptr;
                                    test.y += 1;
                                }
                            }
                            else {
                                test.y += 1;
                            }
                        }

                            // adding current position by (1,-1)
                        else if (returned == SW) {
                            factor = 2;
                            if (__grid[i + 2] != nullptr)        // is new position is not empty
                            {
                                (*__grid[i]) * (*__grid[i + 2]);    //interaction

                                viable1 = (*__grid[i]).isViable();
                                viable2 = (*__grid[i + 2]).isViable();

                                if (viable1 == false) {
                                    __grid[i] = nullptr;
                                }
                                if (viable2 == false) {
                                    __grid[i + 2] = nullptr;
                                    test.x += 1;
                                    test.y += -1;
                                }
                            }
                            else {
                                test.x += 1;
                                test.y += -1;
                            }
                        }

                            // adding current position by (1,0)
                        else if (returned == S) {
                            factor = 3;
                            if (__grid[i + 3] != nullptr)        // is new position is not empty
                            {
                                (*__grid[i]) * (*__grid[i + 3]);    //interaction

                                viable1 = (*__grid[i]).isViable();
                                viable2 = (*__grid[i + 3]).isViable();

                                if (viable1 == false) {
                                    __grid[i] = nullptr;
                                }
                                if (viable2 == false) {
                                    __grid[i + 3] = nullptr;
                                    test.x += 1;
                                }
                            }
                            else {
                                test.x += 1;
                            }
                        }

                            // adding current position by (1,1)
                        else if (returned == SE) {
                            factor = 4;
                            if (__grid[i + 4] != nullptr)        // is new position is not empty
                            {
                                (*__grid[i]) * (*__grid[i + 4]);    //interaction

                                viable1 = (*__grid[i]).isViable();
                                viable2 = (*__grid[i + 4]).isViable();

                                if (viable1 == false) {
                                    __grid[i] = nullptr;
                                }
                                if (viable2 == false) {
                                    __grid[i + 4] = nullptr;
                                    test.x += 1;
                                    test.y += 1;
                                }
                            }
                            else {
                                test.x += 1;
                                test.y += 1;
                            }
                        }

                        test = move(test, returned);

                        legal = isLegal(returned, test);

                        if (legal) {
                            if (__grid[i] != nullptr) {
                                __grid[i]->setPosition(test);       // send in accepted position
                                __grid[i + factor] = __grid[i];
                                __grid[i] = nullptr;
                            }
                        }

                    }

            }

        }

    }

    const Position Game::move(const Position &pos, const ActionType &ac) const {

        bool legal = false;

        legal = isLegal(ac,pos);


        if( legal)
        {
           return pos;
        }

        else
            return Position(0,0);
    }

    const ActionType Game::reachSurroundings(const Position &from, const Position &to) {
        return STAY;
    }
}
