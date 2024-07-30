#include "StickerSheet.h"

#include <iostream>
#include <string>
#include <vector> //???


StickerSheet::StickerSheet(const Image& picture, unsigned max) {
    // initializes StickerSheet with a deep copy of the base picture and the ability to hold a max number of stickers (Images) with indices 0 through max - 1
        // picture: the base picture to use in the StickerSheet
        // max: the maximum number of stickers (Images) on this StickerSheet
    //base_image_ = Image(picture); // sets base image equal to base, is it = picture or = Image(picture)?
    base_image_ = picture;
    max_ = max;
    sticker_array_ = new stickerImage*[max_]; // array of structs of stickers
    layer_count_ = 0; // 0 or max?

    for (unsigned int i = 0; i < max_; i++) {
        sticker_array_[i] = nullptr;
    }
}


StickerSheet::StickerSheet(const StickerSheet& other) {
    // the copy constructor makes this StickerSheet an independent copy of the source
    // hint: code is likely shared between all of the "rule of 3" functions - helper function/2
        // other: the other StickerSheet object to copy data from
    if (this != &other) {
        base_image_ = other.base_image_;
        max_ = other.max_;
        layer_count_ = other.layer_count_;
        sticker_array_ = new stickerImage*[max_];
        for (unsigned int i = 0; i < max_; i++) {
            if (i < other.max_ && other.sticker_array_[i] != nullptr) { 
                sticker_array_[i] = new stickerImage; //?
                sticker_array_[i]->sticker = other.sticker_array_[i]->sticker;
                sticker_array_[i]->x = other.sticker_array_[i]->x;
                sticker_array_[i]->y = other.sticker_array_[i]->y;
                sticker_array_[i]->index = other.sticker_array_[i]->index;
            } else {
                //sticker_array_[i]->sticker = Image(); // is it .sticker or just sticker_array_[i]?
                sticker_array_[i] = nullptr;
            }
        }
    }
}


StickerSheet::~StickerSheet() {
    for (unsigned int i = 0; i < max_; i++) {
        if (sticker_array_[i] != nullptr) {
            delete sticker_array_[i];
        }
    }
    delete[] sticker_array_;
    sticker_array_ = nullptr;
    
}

int StickerSheet::addSticker(Image& sticker, int x, int y) {
    // adds a sticker to the StickerSheet, so that the top left of the sticker's Image is at (x,y) on the StickerSheet
    // the sticker must be added to the lowest possible layer available
    // if all available layers have been filled, a new layer must be added above all existing layers
        // sticker: the Image of the sticker
        // x: the x location of the sticker on the StickerSheet
        // y: the y location of the sticker on the StickerSheet
        // returns: the zero-based layer index the sticker was added to
    if (x < 0 || y < 0) {
        unsigned int new_width = base_image_.width() + (x<0 ? -x : 0);
        unsigned int new_height = base_image_.height() + (y<0 ? -y :0);
        Image new_base(new_width, new_height);
        for (unsigned int i = 0; i < base_image_.width(); i++) {
            for (unsigned int j = 0; j < base_image_.height(); j++) {
                new_base.getPixel(i-(x<0?x:0), j-(y<0?y:0)) = base_image_.getPixel(i,j);
            }
        }
        base_image_ = new_base;
        if (x<0) {
            x=0;
        }
        if (y<0) {
            y=0;
        }
    }
    if (layer_count_ < max_) { // should it be < max_? was != used to be sticker.index != max, <=??
        unsigned int layerIndex = 0;
        while (layerIndex < max_ && sticker_array_[layerIndex] != nullptr) {
            layerIndex++;
        }
        if (layerIndex < max_) {
            sticker_array_[layerIndex] = new stickerImage;
            sticker_array_[layerIndex]->sticker = &sticker;
            sticker_array_[layerIndex]->x = x;
            sticker_array_[layerIndex]->y = y;
            sticker_array_[layerIndex]->index = layerIndex;
            layer_count_++;
        }
    } else { // means all layers are filled??
        
        changeMaxStickers(max_+1);
        sticker_array_[max_-1] = new stickerImage; // was max_
        sticker_array_[max_-1]->sticker = &sticker; // should the index be max instead of layer_count?
        sticker_array_[max_-1]->x = x;
        sticker_array_[max_-1]->y = y;
        sticker_array_[max_-1]->index = max_-1;
        layer_count_++;
    }
    return layer_count_-1; // because it is 0-based?, -1 or without -1
}


void StickerSheet::changeMaxStickers(unsigned max) {
    // modifies the maximum number of stickers that can be stored on this StickerSheet without changing existing stickers' indices
    // if new maximum number of stickers < current number of stickers, the stickers with indices above max-1 will be lost
        // max: the new value for the maximum number of Images in the StickerSheet
    //max_ = max; //??? seems so wrong
    //std::cout << "layer_count_: " << layer_count_ << std::endl;

    // first try
    
    if (max >= layer_count_) {
        // extra stuff added
        stickerImage **temp1 = new stickerImage*[max];
        for (unsigned int i = 0; i < layer_count_; i++) {
            temp1[i] = sticker_array_[i];
        }
        for (unsigned int i = layer_count_; i < max; i++) {
            temp1[i] = nullptr;
        }
        //for (unsigned int i = 0; i < layer_count_; i++) {
            //delete sticker_array_[i];
        //}
        delete[] sticker_array_;
        sticker_array_ = temp1;
        max_ = max;
    } else {
        //max_ = max;
        stickerImage **temp = new stickerImage*[max];
        unsigned int stickercopies = std::min(layer_count_, max);
        for (unsigned int i = 0; i < stickercopies; i++) { // was max_
            temp[i] = sticker_array_[i];
            temp[i]->index = i;
        }
        for (unsigned int i = stickercopies; i < max; i++) {
            temp[i] = nullptr;
        }
        for (unsigned int i = max; i < layer_count_; i++) { // used to be 0
            delete sticker_array_[i];
        }
        delete[] sticker_array_;
        sticker_array_ = temp;
        max_ = max;
        if (layer_count_ >= max_) { // >?
            layer_count_ = max_;
        }
    }
    /* SECOND ATTEMPT
    if (max_ == max) {
        return;
    }
    stickerImage **temp = new stickerImage*[max];
    unsigned int stickercopies = std::min(layer_count_, max);
    for (unsigned int i = 0; i < stickercopies; i++) {
        temp[i] = sticker_array_[i];
        temp[i]->index = i;
    }
    for (unsigned int i = stickercopies; i < max; i++) {
        temp[i] = nullptr;
    }
    for (unsigned int i = 0; i < max_; i++) {
        if (sticker_array_[i] != nullptr) {
            delete sticker_array_[i];
        }
    }
    delete[] sticker_array_;
    sticker_array_ = temp;
    max_ = max;
    if (layer_count_ > max_) {
        layer_count_ = max_;
    }
    */
}


Image* StickerSheet::getSticker(unsigned index) {
    // returns a pointer to the sticker at the specified index, not a copy of it
    // user can modify Image
    // if index is invalid, return NULL
        // index: the layer in which to get the sticker
        // returns: a pointer to a specific Image in the StickerSheet
    if (index >= layer_count_ || sticker_array_[index] == nullptr) { // should it be > max_? should it be layer_count_-1?
        return NULL;
    } else {
        //std::cout << "returning pointer to sticker at index " << index << std::endl;
        return sticker_array_[index]->sticker; // used to be &sticker_array...
    }
}


int StickerSheet::layers() const {
    // returns the total number of layers available on the StickerSheet
        // returns: the total number of layers
    return max_;
}


const StickerSheet& StickerSheet::operator=(const StickerSheet& other) {
    // the assignment operator for the StickerSheet class
    // hint: code likely shared between "rule of 3" functions -- helper function/2?
        // other: the other Scene object to copy data from
        // returns: a constant Scene reference
    if (this != &other) {
        for (unsigned int i = 0; i < max_; i++) {
            delete sticker_array_[i];
        }
        delete[] sticker_array_;
        base_image_ = other.base_image_;
        max_ = other.max_;
        layer_count_ = other.layer_count_;
        sticker_array_ = new stickerImage*[max_];
        
        for (unsigned int i = 0; i < max_; i++) {
            if (i < other.max_ && other.sticker_array_[i] != nullptr) {
                sticker_array_[i] = new stickerImage;
                sticker_array_[i]->sticker = other.sticker_array_[i]->sticker;
                sticker_array_[i]->x = other.sticker_array_[i]->x;
                sticker_array_[i]->y = other.sticker_array_[i]->y;
                sticker_array_[i]->index = other.sticker_array_[i]->index;
            } else {
                sticker_array_[i] = nullptr;
            }
        }
    }
    return *this;
}

void StickerSheet::removeSticker(unsigned index) { // ???? check logic
    // removes the sticker at the given zero-based layer index
    // make sure that the other stickers don't change order
        // index: the layer in which to delete the png

    if (index < layer_count_) {
        delete sticker_array_[index];
        for (unsigned int i = index; i < layer_count_-1; i++) {
            sticker_array_[i] = sticker_array_[i+1];
        }
        sticker_array_[layer_count_-1] = nullptr;
        //sticker_array_[index] = nullptr;
        layer_count_--;
    }
}

Image StickerSheet::render() const {
    // renders the whole StickerSheet on one Image and returns that Image
    // the base picture is drawn first and then each sticker is drawn in order starting with layer 0, then layer 1, and so on
    // if a pixel's alpha channel in a sticker is 0, no pixel is drawn for that sticker at that pixel
    // if the alpha channel is non-zero, a pixel is drawn (alpha blending not required)
    // the returned image always includes the full contents of the picture and all stickers. It should expand in each corresponding direction if stickers go beyond the edge of the picture
        // returns: an Image object representing the drawn scene
    unsigned int width = base_image_.width();
    unsigned int height = base_image_.height();
    unsigned int lp = 0;
    unsigned int tp = 0;
    for (unsigned int i = 0; i < layer_count_; i++) { // < layercount? < max?
        if (sticker_array_[i] != nullptr) {
            // padding for last test case
            if (sticker_array_[i]->x < 0 && (-sticker_array_[i]->x > lp)) {
                lp = -sticker_array_[i]->x;
            }
            if (sticker_array_[i]->y < 0 && (-sticker_array_[i]->y > tp)) {
                tp = -sticker_array_[i]->y;
            }
            // set width and height correctly somehow
            unsigned int stickerWidth = sticker_array_[i]->x + sticker_array_[i]->sticker->width()+tp;
            unsigned int stickerHeight = sticker_array_[i]->y + sticker_array_[i]->sticker->height()+lp;
            /*
            if (stickerWidth > width) {
                width = stickerWidth;
            }
            if (stickerHeight > height) {
                height = stickerHeight;
            }
            */
            width = std::max(width, stickerWidth);
            height = std::max(height, stickerHeight);
        }
    }
    //if (width == 0 && height == 0) {
        //return base_image_;
    //}
    //width += lp;
    //height += tp;
    Image image;
    //image = base_image_; -- what the double for loop does?
    image.resize(width, height);
    //Image image(width, height);

    for (unsigned int x = 0; x < base_image_.width(); x++) {
        for (unsigned int y = 0; y < base_image_.height(); y++) {
            //cs225::HSLAPixel &pixel = i.getPixel(x,y);
            image.getPixel(x+lp,y+tp) = base_image_.getPixel(x,y);
        }
    }
    for (unsigned int i = 0; i < layer_count_; i++) { // layercount or max?
        if (sticker_array_[i] != nullptr) {
            for (unsigned int x = 0; x < sticker_array_[i]->sticker->width(); x++) {
                for (unsigned int y = 0; y < sticker_array_[i]->sticker->height(); y++) {
                    //if (sticker_array_[i]->sticker != nullptr) {
                        //cs225::HSLAPixel &bp = image.getPixel(sticker_array_[i]->x + x, sticker_array_[i]->y + y);
                        cs225::HSLAPixel &sp = sticker_array_[i]->sticker->getPixel(x,y);
                        if (sp.a != 0) {
                            cs225::HSLAPixel &bp = image.getPixel(sticker_array_[i]->x + x+lp, sticker_array_[i]->y + y+tp);
                            bp = sp;
                            //std::cout << "applying sticker at (" << sticker_array_[i]->x + x << ", " << sticker_array_[i]->y+y << ")" << std::endl;
                            //std::cout << "alpha value at sticker pixel (" << x << ", " << y << "): " << sp.a << std::endl;
                        }
                    //}
                }
            }
        }
    }
    //std::cout << "end of render" << std::endl;
    return image;
}


int StickerSheet::setStickerAtLayer(Image& sticker, unsigned layer, int x, int y) {
    // adds a sticker to the StickerSheet at layer layer, so that the top-left of the sticker's Image is at (x,y) on the StickerSheet
        // sticker: the Image of the sticker
        // layer: the layer where the sticker is to be placed
        // x: the x location of the sticker on the StickerSheet
        // y: the y location of the sticker on the StickerSheet
        // returns: the 0-based layer index the sticker was added to, or -1 if the layer DNE
    //return sticker_array_.sticker.index; // didnt work
     // or layer-1
     if (layer >= max_) { // >=?
        return -1;
     }
     if (sticker_array_[layer] == nullptr) { // ALL WERE LAYER-1
        sticker_array_[layer] = new stickerImage;
     }
     sticker_array_[layer]->sticker = &sticker;
     sticker_array_[layer]->x = x;
     sticker_array_[layer]->y = y;
     sticker_array_[layer]->index = layer-1;

     return layer; //-1? or just layer?
 }






bool StickerSheet::translate(unsigned index, int x, int y) {
    // changes the x and y coordinates of the Image in the specified layer
    // if the layer is invalid or does not contain a sticker, this function must return false. otherwise, return true
        // index: 0-based layer index of the sticker
        // x: the new x location of the sticker on the StickerSheet
        // y: the new y location of the sticker on the StickerSheet
        // returns: true if the translate was successful; otherwise false
    if (index < layer_count_) { // should it be < max_???
        sticker_array_[index]->x = x;
        sticker_array_[index]->y = y;
        return true;
    }
    return false;
}
