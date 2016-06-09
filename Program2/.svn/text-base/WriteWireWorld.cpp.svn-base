#include "WriteWireWorld.h"

#include <algorithm>

using appsdk::SDKBitMap;
using appsdk::uchar4;

bool WriteWireWorld(const std::string &fileName,
                    SDKBitMap &image,
                    const std::vector<cl_uchar> &wire_world,
                    size_t rows,
                    size_t cols) {
  // Color map
  static uchar4 colors[] = {
    { 0xff, 0xff, 0xff, 0xff },
    { 0x00, 0xff, 0x00, 0xff },
    { 0xff, 0x00, 0x00, 0xff },
    { 0x00, 0x00, 0x00, 0xff },
    { 0x00, 0x00, 0xff, 0xff }
  };

  // Output image pixels
  uchar4 *pixel = image.getPixels();

  // Convert state array to image
  for (const cl_uchar &state : wire_world) {
    *(pixel++) = colors[std::min(static_cast<unsigned int>(state),4U)];
  }

  // Write image to file
  return image.write(fileName.c_str());
}
