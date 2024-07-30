#pragma once

//using namespace std;
#include "./cs225/PNG.h"

class Image : public cs225::PNG {
    // subclass of PNG class, inherits all member functions

    public:
        Image();
        Image(unsigned int width, unsigned int height);
        void lighten();
        void lighten(double amount);
        void darken();
        void darken(double amount);
        void saturate();
        void saturate(double amount);
        void desaturate();
        void desaturate(double amount);
        void grayscale();
        void rotateColor(double degrees);
        void illinify();
        void scale(double factor);
        void scale(unsigned w, unsigned h);
    private:
        //unsigned int width_;
        //unsigned int height_;
        //double amount_; // ?
        //double degrees_; // ?
        //double factor_; // ?
};
