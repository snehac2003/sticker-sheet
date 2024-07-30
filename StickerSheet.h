#pragma once

#include "Image.h"

struct stickerImage { // this struct is for each sticker
    Image* sticker;
    unsigned int x;
    unsigned int y;
    unsigned int index;
};

class StickerSheet {
    public:
        StickerSheet(const Image &picture, unsigned max);
        StickerSheet(const StickerSheet &other);
        const StickerSheet& operator=(const StickerSheet &other);
        void changeMaxStickers(unsigned max);
        int addSticker(Image &sticker, int x, int y);
        int setStickerAtLayer(Image &sticker, unsigned layer, int x, int y);
        bool translate(unsigned index, int x, int y);
        void removeSticker(unsigned index);
        Image* getSticker(unsigned index);
        int layers() const;
        Image render() const;
        ~StickerSheet();
    private:
        Image base_image_;
        unsigned int max_;
        //stickerImage sticker_; // do i need this?? -- one sticker
        stickerImage **sticker_array_; // array of stickerImage structs -- each has Image, x, y, index // is it ** or *?
        unsigned int layer_count_; //-- same as index of struct?
};
