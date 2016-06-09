#include "ReadWireWorld.h"

using appsdk::SDKBitMap;
using appsdk::uchar4;

bool ReadWireWorld(const std::string &fileName,
                   SDKBitMap &image,
                   std::vector<cl_uchar> &wire_world,
                   size_t &rows,
                   size_t &cols) {
  // Open the image file
  image.load(fileName.c_str());
  if (!image.isLoaded()) {
    std::cerr << "Unable to open file: " << fileName << std::endl;
    return false;
  }

  // Get the image size
  rows = image.getHeight();
  cols = image.getWidth();

  wire_world.clear();           // discard old data to prevent copying
  wire_world.resize(rows * cols);

  int errors = 0;
  // Convert image to state array
  const uchar4 *src = image.getPixels();  // pointer to pixel buffer
  for (cl_uchar &dst : wire_world) {
    if (src->x == 0 && src->y == 0 && src->z == 0) {
      dst = 3;                  // set to wire
    } else if (src->x != 0 && src->y == 0 && src->z == 0) {
      dst = 2;                  // set to electron tail
    } else if (src->x == 0 && src->y != 0 && src->z == 0) {
      dst = 1;                  // set to electron head
    } else if (src->x == 0xff || src->y == 0xff || src->z == 0xff) {
      dst = 0;                  // set to background
    } else {
      dst = 0;                  // set bad pixels to background
      ++errors;
    }
    ++src;
  }

  if (errors != 0) {
    std::cout << "Warning, " << errors << " invalid pixel values in " << fileName << std::endl;
  }

  return true;
}
