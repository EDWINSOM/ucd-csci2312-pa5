//
// Created by marisa on 12/13/15.
//

#include "Game.h"
#include "Strategic.h"
#include "Simple.h"
#include "Food.h"
#include "Advantage.h"

using namespace std;

namespace Gaming
{

    Game::NUM_INIT_AGENT_FACTOR = 4;
    Game::NUM_INIT_RESOURCE_FACTOR = 2;
    Game::MIN_WIDTH = 3;
    Game::MIN_HEIGHT = 3;
    Game::STARTING_AGENT_ENERGY = 20;
    Game::STARTING_RESOURCE_CAPACITY = 10;


    Game::Game()
    {
        __width = 3;
        __height = 3;

        populate();

        __status = NOT_STARTED;

        __round = 0;

        cout << *this;      // prints out round #, grid/board, and status

        play(__verbose);    // play game until over

    }

    Game::Game(unsigned width, unsigned height, bool manual)
    {
        __width = width;
        __height= height;

        __status = NOT_STARTED;

        unsigned int x=0 , y=0, z;

        for ( z = 0 ; z < __height ; z++)
        {
            y = 0;

            for (int a = 0; a < __width ; a++)
            {
                addSimple(x, y);
                addStrategic(x, ++y);
                addFood(x,++y);
                addAdvantage(x,++y);
            }
            ++x;
        }

        cout << *this;      // prints out round #, grid/board, and status

        play(__verbose);    // play game until over
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

        cout << *this;      // prints out round #, grid/board, and status

        play(__verbose);    // play game until over

    }

    Game::~Game()
    {
        __grid.clear();
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

        while((result == false) && (i < 9))
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

        while ((result == false) && (i < 9) )
        {
            if( __grid[i] == nullptr)
            {
                Position position(x, y);
                __grid[i] = new Simple(*this, position, Game::STARTING_AGENT_ENERGY);
                result = true;
            }
            ++i;
        }

        return result;
    }

    bool Game::addStrategic(const Position &position, Strategy *s) {

        bool result = false;

        int i = 0;

        while ((result == false) && (i < 9) )
        {
            if( __grid[i] == nullptr)
            {
                __grid[i] = new Strategic(*this, position, Game::STARTING_AGENT_ENERGY, s);
                result = true;
            }
            ++i;
        }

        return result;
    }

    bool Game::addStrategic(unsigned x, unsigned y, Strategy *s) {

        bool result = false;

        int i = 0;

        while ((result == false) && (i < 9) )
        {
            if( __grid[i] == nullptr)
            {
                Position position(x,y);
                __grid[i] = new Strategic(*this, position, Game::STARTING_AGENT_ENERGY, s);
                result = true;
            }
            ++i;
        }

        return result;
    }


    bool Game::addFood(const Position &position) {

        bool result = false;

        int i = 0;

        while ((result == false) && (i < 9) )
        {
            if( __grid[i] == nullptr)
            {
                __grid[i] = new Food(*this, position, Game::STARTING_RESOURCE_CAPACITY);
                result = true;
            }
            ++i;
        }

        return result;
    }


    bool Game::addFood(unsigned x, unsigned y) {

        bool result = false;

        int i = 0;

        while ((result == false) && (i < 9) )
        {
            if( __grid[i] == nullptr)
            {
                Position position(x,y);
                __grid[i] = new Food(*this, position, Game::STARTING_RESOURCE_CAPACITY);
                result = true;
            }
            ++i;
        }

        return result;
    }


    bool Game::addAdvantage(const Position &position) {
        bool result = false;

        int i = 0;

        while ((result == false) && (i < 9) )
        {
            if( __grid[i] == nullptr)
            {
                __grid[i] = new Advantage(*this, position, Game::STARTING_RESOURCE_CAPACITY);
                result = true;
            }
            ++i;
        }

        return result;
    }


    bool Game::addAdvantage(unsigned x, unsigned y) {
        bool result = false;

        int i = 0;

        while ((result == false) && (i < 9) )
        {
            if( __grid[i] == nullptr)
            {
                Position position(x,y);
                __grid[i] = new Advantage(*this, position, Game::STARTING_RESOURCE_CAPACITY);
                result = true;
            }
            ++i;
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

    const Surroundings Game::getSurroundings(const Position &pos) const
    {
        Surroundings * give = new Surroundings<PieceType ,9>;

        (*give).myArray[4] = SELF;

        if ((pos.x == 0) && (pos.y == 0))   // at position (0,0), [0] in __grid
        {
            (*give).myArray[0] = INACCESSIBLE;
            (*give).myArray[1] = INACCESSIBLE;
            (*give).myArray[2] = INACCESSIBLE;
            (*give).myArray[3] = INACCESSIBLE;
            (*give).myArray[6] = INACCESSIBLE;

            (*give).myArray[5] = __grid[1]->getType();
            (*give).myArray[7] = __grid[3]->getType();
            (*give).myArray[8] = __grid[4]->getType();
        }

        if((pos.x == 0) && (pos.y == 1))  // at position (0,1), [1] in __grid
        {
            (*give).myArray[0] = INACCESSIBLE;
            (*give).myArray[1] = INACCESSIBLE;
            (*give).myArray[2] = INACCESSIBLE;

            (*give).myArray[3] = __grid[0]->getType();
            (*give).myArray[5] = __grid[2]->getType();
            (*give).myArray[6] = __grid[3]->getType();
            (*give).myArray[7] = __grid[4]->getType();
            (*give).myArray[8] = __grid[5]->getType();
        }

        if( (pos.x == 0) && (pos.y == 2))   // at position (0.2), [2] in __grid
        {
            (*give).myArray[0] = INACCESSIBLE;
            (*give).myArray[1] = INACCESSIBLE;
            (*give).myArray[2] = INACCESSIBLE;
            (*give).myArray[5] = INACCESSIBLE;
            (*give).myArray[8] = INACCESSIBLE;

            (*give).myArray[3] = __grid[1]->getType();
            (*give).myArray[6] = __grid[4]->getType();
            (*give).myArray[7] = __grid[5]->getType();
        }

        if( (pos.x == 1) && (pos.y == 0))   // at position (1,0), [3] in __grid
        {
            (*give).myArray[0] = INACCESSIBLE;
            (*give).myArray[3] = INACCESSIBLE;
            (*give).myArray[6] = INACCESSIBLE;

            (*give).myArray[1] = __grid[0]->getType();
            (*give).myArray[2] = __grid[1]->getType();
            (*give).myArray[5] = __grid[4]->getType();
            (*give).myArray[7] = __grid[6]->getType();
            (*give).myArray[8] = __grid[7]->getType();
        }

        if( (pos.x == 1) && (pos.y == 1))   // at position (1,1), [4] in __grid
        {
            (*give).myArray[0] = __grid[0]->getType();
            (*give).myArray[1] = __grid[1]->getType();
            (*give).myArray[2] = __grid[2]->getType();
            (*give).myArray[3] = __grid[3]->getType();
            (*give).myArray[5] = __grid[5]->getType();
            (*give).myArray[6] = __grid[6]->getType();
            (*give).myArray[7] = __grid[7]->getType();
            (*give).myArray[8] = __grid[8]->getType();
        }

        if( (pos.x == 1) && (pos.y == 2))   // at position (1,2), [5] in __grid
        {
            (*give).myArray[2] = INACCESSIBLE;
            (*give).myArray[5] = INACCESSIBLE;
            (*give).myArray[8] = INACCESSIBLE;

            (*give).myArray[0] = __grid[1]->getType();
            (*give).myArray[1] = __grid[2]->getType();
            (*give).myArray[3] = __grid[4]->getType();
            (*give).myArray[6] = __grid[7]->getType();
            (*give).myArray[7] = __grid[8]->getType();
        }

        if( (pos.x == 2) && (pos.y == 0))   // at position (2,0), [6] in __grid
        {
            (*give).myArray[0] = INACCESSIBLE;
            (*give).myArray[3] = INACCESSIBLE;
            (*give).myArray[6] = INACCESSIBLE;
            (*give).myArray[7] = INACCESSIBLE;
            (*give).myArray[8] = INACCESSIBLE;

            (*give).myArray[1] = __grid[3]->getType();
            (*give).myArray[2] = __grid[4]->getType();
            (*give).myArray[5] = __grid[7]->getType();
        }

        if( (pos.x == 2) && (pos.y == 1)) // at position (2,1), [7] in __grid
        {
            (*give).myArray[6] = INACCESSIBLE;
            (*give).myArray[7] = INACCESSIBLE;
            (*give).myArray[8] = INACCESSIBLE;

            (*give).myArray[0] = __grid[3]->getType();
            (*give).myArray[1] = __grid[4]->getType();
            (*give).myArray[2] = __grid[5]->getType();
            (*give).myArray[3] = __grid[6]->getType();
            (*give).myArray[5] = __grid[8]->getType();
        }

        if ( (pos.x == 2) && (pos.y == 2)) // at position (2,2), [8] in __grid
        {
            (*give).myArray[2] = INACCESSIBLE;
            (*give).myArray[5] = INACCESSIBLE;
            (*give).myArray[6] = INACCESSIBLE;
            (*give).myArray[7] = INACCESSIBLE;
            (*give).myArray[8] = INACCESSIBLE;

            (*give).myArray[0] = __grid[4]->getType();
            (*give).myArray[1] = __grid[5]->getType();
            (*give).myArray[3] = __grid[7]->getType();
        }

        return *give;

    }

    const ActionType Game::reachSurroundings(const Position &from, const Position &to) {



        return S;
    }

    std::ostream &Gaming::operator<<(std::ostream &os, const Game &game) {

        cout << endl << "Round: " << game.__round << endl;
        int m = 0;
        auto it  = game.__grid.begin();

        for (int j = 0; j < game.__height; j++)
        {
            for (int i = 0; i < game.__width; i++)
            {
                cout << "[";
                if(game.__grid[m] != nullptr)
                {
                    cout << (*(it)[m]) .getType();
                }
                cout << "]";
                m++;
            }
            cout << endl;
        }

        cout << endl << "Status: " << game.__status << endl;
    }

    bool Game::isLegal(const ActionType &ac, const Position &pos) const {

        // game is over
        if (__status == OVER)
        {
            return false;
        }

        if( (pos.x > -1) && (pos.x < 5) )
        {
            if ((pos.y > -1) && (pos.y < 4) )
            {
                return true;
            }
        }


        return false;
    }

    void Game::play(bool verbose)
    {
        __status = PLAYING;
        round();


        __status = OVER;
    }

    void Game::round()
    {
        Surroundings copy;
        ActionType returned;
        bool legal = false;
        Position test(1,1);

        for (int i = 0 ; i < 9 ; i++)
        {
            if( (__grid[i]->getType() != INACCESSIBLE) && (__grid[i]->getType() != EMPTY) )
            {
                copy = getSurroundings(__grid[i]->getPosition());       // returns a Surroundings

                if(__grid[i]->getTurned() != true)
                {
                    __grid[i]->setTurned(true);
                    returned = __grid[i]->takeTurn(copy);      // return ActionType

                    //convert returned value on surroundings to a position on __grid

                    // adding current position by (-1,-1)
                    if (returned == NW)
                    {
                        (*__grid[i])*(*__grid[i-4]);    //interaction
                        test.x += -1;
                        test.y += -1;
                    }

                    // adding current position by (-1,0)
                    else if (returned == N)
                    {
                        (*__grid[i])*(*__grid[i-3]);    //interaction
                        test.x += -1;
                    }

                    // adding current position by (-1,1)
                    else if (returned == NE)
                    {
                        (*__grid[i])*(*__grid[i-2]);    //interaction
                        test.x += -1;
                        test.y += 1;
                    }

                    // adding current position by (0,-1)
                    else if (returned == W)
                    {
                        (*__grid[i])*(*__grid[i-1]);    //interaction
                        test.y += -1;
                    }

                    // adding current position by (0,1)
                    else if (returned == E)
                    {
                        (*__grid[i])*(*__grid[i+1]);    //interaction
                        test.y += 1;
                    }

                    // adding current position by (1,-1)
                    else if (returned == SW)
                    {
                        (*__grid[i])*(*__grid[i+2]);    //interaction
                        test.x += 1;
                        test.y += -1;
                    }

                    // adding current position by (1,0)
                    else if (returned == S)
                    {
                        (*__grid[i])*(*__grid[i+3]);    //interaction
                        test.x += 1;
                    }

                    // adding current position by (1,1)
                    else if (returned == SE)
                    {
                        (*__grid[i])*(*__grid[i+4]);    //interaction
                        test.x += 1;
                        test.y += 1;
                    }

                    legal = isLegal(returned,test);

                    if( legal)
                    {
                        __grid[i]->setPosition(test);       // send in accepted position
                    }



                }
            }

        }
    }
}