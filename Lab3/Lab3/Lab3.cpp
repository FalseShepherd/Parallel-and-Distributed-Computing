// Lab 3
// COMP3705/4705 Spring 2015

// Based on AMD APP SDK HelloWorld:
/**********************************************************************
Copyright ©2013 Advanced Micro Devices, Inc. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

•	Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
•	Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************/

#include "CLUtil.hpp"
#include "SDKBitMap.hpp"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>

#define SUCCESS 0
#define FAILURE 1

using namespace std;
using namespace appsdk;

int main(int argc, char* argv[])
{
  const char inputImage[] = "marmot.bmp";
  const char outputImage[] = "marmot_out.bmp";

  /*Step1: Getting platforms and choose an available one.*/
  cl_uint numPlatforms;	//the NO. of platforms
  cl_platform_id platform = NULL;	//the chosen platform
  cl_int	status = clGetPlatformIDs(0, NULL, &numPlatforms);
  if (status != CL_SUCCESS)
  {
    cerr << "Error: Getting platforms!" << endl;
    return FAILURE;
  }
  
  /*For clarity, choose the first available platform. */
  if (numPlatforms > 0)
  {
    cl_platform_id* platforms = (cl_platform_id*)malloc(numPlatforms* sizeof(cl_platform_id));
    status = clGetPlatformIDs(numPlatforms, platforms, NULL);
    if (status != CL_SUCCESS) {
      cerr << "Error: clGetPlatformIDs failed\n";
      return FAILURE;
    }
    platform = platforms[0];
    free(platforms);
  }
  else {
    cerr << "No platform found!\n";
    return FAILURE;
  }

  /*Step 2:Query the platform and choose the first GPU device if has one.Otherwise use the CPU as device.*/
  cl_uint				numDevices = 0;
  cl_device_id        *devices;
  status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, NULL, &numDevices);
  if (status != CL_SUCCESS || numDevices == 0)	//no GPU available.
  {
    cerr << "No GPU device available." << endl;
    cerr << "Choose CPU as default device." << endl;
    status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 0, NULL, &numDevices);
    if (status != CL_SUCCESS || numDevices == 0) {
      cerr << "No CPU device available.\n";
      return FAILURE;
    }

    devices = (cl_device_id*)malloc(numDevices * sizeof(cl_device_id));
    status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, numDevices, devices, NULL);
    if (status != CL_SUCCESS) {
      cerr << "Error: clGetDeviceIDs failed for CL_DEVICE_TYPE_CPU";
      return FAILURE;
    }
  }
  else
  {
    devices = (cl_device_id*)malloc(numDevices * sizeof(cl_device_id));
    status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, numDevices, devices, NULL);
    if (status != CL_SUCCESS) {
      cerr << "Error: clGetDeviceIDs failed for CL_DEVICE_TYPE_GPU";
      return FAILURE;
    }
  }

  /*Step 3: Create context.*/
  cl_int errCode;
  cl_context context = clCreateContext(NULL, numDevices, devices, NULL, NULL, &errCode);
  if (context == NULL) {
    cerr << "Error: clCreateContext failed, error " << errCode << "\n";
    return FAILURE;
  }

  /*Step 4: Creating command queue associate with the context.*/
  cl_command_queue commandQueue = clCreateCommandQueue(context, devices[0], 0, NULL);
  if (commandQueue == NULL) {
    cerr << "Error: clCreateCommandQueue failed\n";
    return FAILURE;
  }

  /*Step 5: Create program object */
  const char *filename = "Lab3.cl";
  SDKFile kernelFile;
  if (!kernelFile.open(filename)) {
    cerr << "Error: failed to open " << filename << endl;
    return FAILURE;
  }
  const string &sourceStr = kernelFile.source();

  const char *source = sourceStr.c_str();
  size_t sourceSize[] = { sourceStr.size() };
  cl_program program = clCreateProgramWithSource(context, 1, &source, sourceSize, NULL);
  if (program == NULL) {
    cerr << "Error: clCreateProgramWithSource failed\n";
    return FAILURE;
  }

  /*Step 6: Build program. */
  status = clBuildProgram(program, 1, devices, NULL, NULL, NULL);
  if (status != CL_SUCCESS) {
    cerr << "Error: clBuildProgram failed\n";
    return FAILURE;
  }

  /* Load bitmap image */
  SDKBitMap image(inputImage);
  if (!image.isLoaded()) {
    cerr << "Failed to load image file: " << inputImage << "\n";
    return FAILURE;
  }
  uchar4 *pixels = image.getPixels();  // pointer to pixel buffer (also used for output)
  
  /*Step 7: Initial input,output for the host and create memory objects for the kernel*/
  const size_t rows = image.getHeight();
  const size_t cols = image.getWidth();
  const int channels = image.getNumChannels();
  cout << "Loaded " << inputImage << ", size = " << rows << "x" << cols << ", " << channels << " channels\n";
  const size_t arraySize = rows * cols;
  const size_t arrayBytes = arraySize * sizeof(uchar4);

  cl_mem inputBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                      arrayBytes, (void *)pixels, NULL);
  cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, arrayBytes, NULL, NULL);

  /*Step 8: Create kernel object */
  cl_kernel kernel = clCreateKernel(program, "flip_image", &errCode);
  if (!kernel) {
    cout << "clCreateKernel failed with error code " << errCode << endl;
    return FAILURE;
  }

  /*Step 9: Sets Kernel arguments.*/
  bool argOK = (CL_SUCCESS == clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&inputBuffer));
  argOK = argOK && (CL_SUCCESS == clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&outputBuffer));
  if (!argOK) {
    cerr << "Error: clSetKernelArg failed\n";
    return FAILURE;
  }

  /*Step 10: Running the kernel.*/
  size_t global_work_size[2] = { rows, cols };  // two-dimensional work size
  status = clEnqueueNDRangeKernel(commandQueue, kernel, 2, NULL, global_work_size, NULL, 0, NULL, NULL);
  if (status != CL_SUCCESS) {
    cerr << "Error: clEnqueueNDRangeKernel failed\n";
    return FAILURE;
  }

  /*Step 11: Read the kernel output back to host memory (overwrite input pixels).*/
  status = clEnqueueReadBuffer(commandQueue, outputBuffer, CL_TRUE, 0,
                               arrayBytes, pixels, 0, NULL, NULL);
  if (status != CL_SUCCESS) {
    cerr << "Error: clEnqueueReadBuffer failed\n";
    return FAILURE;
  }
  
  // Write output
  if (!image.write(outputImage)) {
    cerr << "Write to output image failed: " << outputImage << endl;
    return FAILURE;
  }
  
  /*Step 12: Clean the resources.*/
  status = clReleaseKernel(kernel);				//Release kernel.
  status = clReleaseProgram(program);				//Release the program object.
  status = clReleaseMemObject(inputBuffer);		//Release mem object.
  status = clReleaseMemObject(outputBuffer);
  status = clReleaseCommandQueue(commandQueue);	//Release  Command queue.
  status = clReleaseContext(context);				//Release context.
  if (devices != NULL) {
    free(devices);
    devices = NULL;
  }

  std::cout << "Passed!\n";
  return SUCCESS;
}