//
// Created by marisa on 12/13/15.
//

#include "Piece.h"
#include "Gaming.h"

using namespace std;

namespace Gaming {

    unsigned int Piece::__idGen = 0;

    Piece::Piece(const Gaming::Game &g, const Gaming::Position &p) : __game(g) {

            __position = p;
            __finished = false;
            __turned = false;
    }

    Piece::~Piece() {

            __id = 0;
            __finished = true;
            __turned = true;

    }

    std::ostream &operator<<(std::ostream &os, const Piece &piece) {

            piece.print(std::cout);


            return os;
    }

    unsigned int Piece::idGen() {
        return ++__idGen;
    }


}

