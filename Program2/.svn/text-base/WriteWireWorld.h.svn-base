// WriteWireWorld - write state of WireWorld to image file
//
//   Writes an image file containing the Wire World state to an image
//     The state array is converted to the image as follows:
//       State 3 is black
//       State 2 is red
//       State 1 is green
//       State 0 is white
//       Any other (invalid) cell states are set to blue
//
// @param fileName - name of image file containing the state
// @param image - image object (initialized by ReadWireWorld)
// @param wire_world - vector containing the state
// @param rows - number of rows
// @param cols - number of columns
// @returns true if success, false if failure

#ifndef WRITEWIREWORLD_H
#define WRITEWIREWORLD_H

#include "CLUtil.hpp"
#include "SDKBitMap.hpp"

bool WriteWireWorld(const std::string &fileName,
                    appsdk::SDKBitMap &image,
                    const std::vector<cl_uchar> &wire_world,
                    size_t rows,
                    size_t cols);

#endif  // WRITEWIREWORLD_H
