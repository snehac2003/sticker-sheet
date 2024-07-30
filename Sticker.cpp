#include "Image.h"
#include "StickerSheet.h"

int main() {


  Image alma;
  alma.readFromFile("../data/alma.png");
  Image a;
  a.readFromFile("../data/penguin.png");
  Image b; 
  b.readFromFile("../data/i.png");
  Image c;
  c.readFromFile("../data/penguin.png");

  StickerSheet sheet_with_stickers(alma, 8);
  sheet_with_stickers.addSticker(a, 40, 30);
  sheet_with_stickers.addSticker(b, 300, 30);
  sheet_with_stickers.addSticker(c, 20, 150);
  //sheet_with_stickers.addSticker(c, -20, -200);
  Image finalImage = sheet_with_stickers.render();

  finalImage.writeToFile("finalImage.png");

  return 0;
}
