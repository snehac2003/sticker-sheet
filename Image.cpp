#include "Image.h"


Image::Image() {
    PNG();
}

Image::Image(unsigned int width, unsigned int height) : PNG(width, height) {

}

void Image::darken() {
    
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            cs225::HSLAPixel &pixel = getPixel(x,y);
            pixel.l -= 0.1;
            if (pixel.l < 0) { pixel.l = 0; }
            if (pixel.l > 1) { pixel.l = 1; }
        }
    }

}

void Image::darken(double amount) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            cs225::HSLAPixel &pixel = getPixel(x,y);
            pixel.l -= amount;
            if (pixel.l < 0) { pixel.l = 0; }
            if (pixel.l > 1) { pixel.l = 1; }
        }
    }
}

void Image::desaturate() {
    
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            cs225::HSLAPixel &pixel = getPixel(x,y);
            pixel.s -= 0.1;
            if (pixel.s < 0) { pixel.s = 0; }
            if (pixel.s > 1) { pixel.s = 1; }
        }
    }
}

void Image::desaturate(double amount) {
    
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            cs225::HSLAPixel &pixel = getPixel(x,y);
            pixel.s -= amount;
            if (pixel.s < 0) { pixel.s = 0; }
            if (pixel.s > 1) { pixel.s = 1; }
        }
    }
}

void Image::grayscale() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            cs225::HSLAPixel &pixel = getPixel(x,y);
            pixel.s = 0;
        }
    }
}

void Image::illinify() {
     
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            cs225::HSLAPixel &pixel = getPixel(x,y);
            if (pixel.h < 113 | pixel.h > 244) { // finish - do math--fix math??
                pixel.h = 11;
            } else {
                pixel.h = 216;
            }
        }
    }
}

void Image::lighten() {
    // lighten an Image by increasing the luminance of every pixel by 0.1
    // this function ensures that the luminance remains in the range [0,1]
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            cs225::HSLAPixel &pixel = getPixel(x,y);
            pixel.l += 0.1;
            if (pixel.l < 0) { pixel.l = 0; }
            if (pixel.l > 1) { pixel.l = 1; }
        }
    }
}

void Image::lighten(double amount) {
    // lighten an Image by increasing the luminance of every pixel by amount
    // this function ensures that the luminance remains in the range [0,1]
        // amount: the desired increase in luminance
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            cs225::HSLAPixel &pixel = getPixel(x,y);
            pixel.l += amount;
            if (pixel.l < 0) { pixel.l = 0; }
            if (pixel.l > 1) { pixel.l = 1; }
        }
    }
}

void Image::rotateColor(double degrees) {
    // rotates the color wheel by degrees
    // rotating in a positive direction increases the degree of the hue. This function ensures that the hue remains in the range [0, 360]
        // degrees: the desired amount of rotation
    while (degrees < 0) {
        degrees = degrees + 360.0;
    } 
    while (degrees >= 360.0) {
        degrees = degrees - 360.0;
    }
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            cs225::HSLAPixel &pixel = getPixel(x,y);
            pixel.h += degrees;
            if (pixel.h >= 360.0) { // is it > or >=
                pixel.h = pixel.h - 360.0;
            } 
            //else if (pixel.h < 360) {
                //pixel.h = pixel.h + 360;
            //}
        }
    }
}

void Image::saturate() {
    // saturates an Image by increasing the saturation of every pixel by 0.1
    // this function ensures that the saturation remains in the range [0,1]
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            cs225::HSLAPixel &pixel = getPixel(x,y);
            pixel.s += 0.1;
            if (pixel.s < 0) { pixel.s = 0; }
            if (pixel.s > 1) { pixel.s = 1; }
        }
    }
}

void Image::saturate(double amount) {
    // saturates an Image by increasing the saturation of every pixel by amount
    // this function ensures that the saturation remains in the range [0,1]
        // amount: the desired increase in saturation
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            cs225::HSLAPixel &pixel = getPixel(x,y);
            pixel.s += amount;
            if (pixel.s < 0) { pixel.s = 0; }
            if (pixel.s > 1) { pixel.s = 1; }
        }
    }
}

void Image::scale(double factor) {
    // scale the Image by a given factor
        // a factor of 0.1 does not change the image
        // a factor of 0.5 results in an image with half the width and half the height
        // a factor of 2 results in an image with twice the width and twice the height
    // this function both resizes Image and scales the contents
        // factor: Scale factor
    Image *i = new Image((width() * factor), (height() * factor));
    for (unsigned int x = 0; x < (width() * factor); x++) {
        for (unsigned int y = 0; y < (height() * factor); y++) {
            cs225::HSLAPixel &oldpixel = getPixel((x/factor),(y/factor));
            cs225::HSLAPixel &newpixel = i->getPixel(x,y);
            newpixel.h = oldpixel.h;
            newpixel.l = oldpixel.l;
            newpixel.s = oldpixel.s;
            newpixel.a = oldpixel.a;
        }
    }
    //delete i; // am i supposed to delete this here...? or just eventually...
    *this = *i;
    delete i;
} 

void Image::scale(unsigned w, unsigned h) {
    // scales the image to fit within the size (w x h)
    // this function preserves the aspect ratio of the image, so the result will always be an image of width w or of height h (not necessarily both)
    // for example, if the Image is currently (10,20) and we want to scale to (100,100), then this should scale the Image to (50,100). 
        // Note that scaling the image to (100,200) does not fit within the (100,100) dimensions given and is therefore incorrect
    // this fucntion both resizes the Image and scales the contents
        // w: desired width of the scaled Image
        // h: desired height of the scaled Image
    // idea: get the factor back and scale by factor?
    double width_factor = (double) w / (double) width();
    double height_factor = (double) h / (double) height();
    // use the smaller one
    if (width_factor < height_factor) {
        scale(width_factor);
    } else {
        scale(height_factor);
    }

    // have current width, new width
    // have current height, new height
}
