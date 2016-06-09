// ReadWireWorld - read initial state of WireWorld from image file
//
//   Reads an image file containing the initial state.
//     The image is converted to the state array as follows:
//       Cells with color black (RGB 0,0,0) are set to state 3
//       Cells with color red (red channel non-zero, green and blue 0) are set to state 2
//       Cells with color green (green channel non-zero, red and blue 0) are set to state 1
//       All other cells set to state 0
//
// @param fileName - name of image file containing the state
// @param image - image object (save to write output image)
// @param wire_world - vector to load with state. Will be resized to contain the
//                     state.
// @param rows - returns the number of rows
// @param cols - returns the number of columns
// @returns true if success, false if failure

#ifndef READWIREWORLD_H
#define READWIREWORLD_H

#include "CLUtil.hpp"
#include "SDKBitMap.hpp"

bool ReadWireWorld(const std::string &fileName,
                   appsdk::SDKBitMap &image,
                   std::vector<cl_uchar> &wire_world,
                   size_t &rows,
                   size_t &cols);

#endif  // READWIREWORLD_H
