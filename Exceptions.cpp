//
// Created by marisa on 12/13/15.
//

#include "Exceptions.h"
using namespace std;

namespace Gaming {

    std::ostream &operator<<(std::ostream &os, const GamingException &ex) {
        cout << ex.__name;

        return os;
    }

    DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height) {

        __exp_height = expHeight;
        __exp_width = expWidth;

        __width = width;
        __height = height;

        setName("DimensionEx");

    }

    void InsufficientDimensionsEx::__print_args(std::ostream &os) const {

        cout << "InsufficientDimensionsEx : " << endl;
        cout << "Width: " << __width << endl;
        cout << "Height: " << __height << endl;
        cout << "Exp. Width: " << __exp_width << endl;
        cout << "Exp. Height: " << __exp_height << endl;

    }

    void OutOfBoundsEx::__print_args(std::ostream &os) const {

        cout <<"OutOfBoundsEx : " << endl;
        cout << "Width: " << __width << endl;
        cout << "Height: " << __height << endl;
        cout << "Exp. Width: " << __exp_width << endl;
        cout << "Exp. Height: " << __exp_height << endl;

    }
}

