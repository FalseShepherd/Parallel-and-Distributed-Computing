//
//  COMP3705/4705 Spring 2016
//  Program 2 - Wire World Cellular Automata
//
//  Author: Mike Goss (using AMD source code)
//
/**********************************************************************
 Copyright ©2013 Advanced Micro Devices, Inc. All rights reserved.

 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

 ï	Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 ï	Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or
 other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ********************************************************************/

#include "Timer.h"
#include "ReadWireWorld.h"
#include "WriteWireWorld.h"

#include "CLUtil.hpp"
#include "SDKBitMap.hpp"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#define SUCCESS 0
#define FAILURE 1
#if defined(_OPENMP)
#include <omp.h>
#endif
using namespace std;
using namespace appsdk;

using appsdk::checkVal;
using appsdk::SDKFile;
using appsdk::SDKBitMap;
using std::min;

#if defined(_OPENMP)

// COMP4705 OpenMP version here

#endif

int main(int argc, char* argv[])
{
	if (argc != 4) {
		std::cerr << "usage: program2 inputfile outputfile count\n";
		exit(1);
	}
	std::string input_file(argv[1]);
	std::string output_file(argv[2]);
  // Check arguments


  int iterations = atoi(argv[3]);
  bool useCPU = iterations < 0;
  if (useCPU) iterations = -iterations;

  // Image object to use for both read and write
  SDKBitMap image;

  // Load the input file
  std::vector<cl_uchar> wire_world;
  size_t rows, cols;
  if (!ReadWireWorld(argv[1], image, wire_world, rows, cols)) {
    exit(2);
  }

  std::cout << "Running " << iterations << " with state size "
            << rows << "x" << cols << std::endl;

  /*Step1: Getting platforms and choose an available one.*/
  cl_uint numPlatforms;	//the NO. of platforms
  cl_platform_id platform = NULL;	//the chosen platform
  cl_int	status = clGetPlatformIDs(0, NULL, &numPlatforms);
  CHECK_OPENCL_ERROR(status, "Error: Getting platforms!" );

  /*For clarity, choose the first available platform. */
  if (numPlatforms > 0)
  {
    cl_platform_id* platforms = (cl_platform_id*)malloc(numPlatforms* sizeof(cl_platform_id));
    status = clGetPlatformIDs(numPlatforms, platforms, NULL);
    CHECK_OPENCL_ERROR(status, "Error: clGetPlatformIDs failed");
    platform = platforms[0];
    free(platforms);
  }
  else {
    std::cerr << "No platform found!\n";
    return SDK_FAILURE;
  }

  /*Step 2:Query the platform and choose the first GPU device if has one.Otherwise use the CPU as device.*/
  cl_uint				numDevices = 0;
  cl_device_id        *devices;
  if (!useCPU) {
    status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, NULL, &numDevices);
  }
  if (status != CL_SUCCESS || numDevices == 0)	//no GPU available.
  {
    std::cerr << "No GPU device available." << std::endl;
    std::cerr << "Choose CPU as default device." << std::endl;
    status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 0, NULL, &numDevices);
    CHECK_OPENCL_ERROR(status, "No CPU device available.");

    devices = (cl_device_id*)malloc(numDevices * sizeof(cl_device_id));
    status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, numDevices, devices, NULL);
    CHECK_OPENCL_ERROR(status, "clGetDeviceIDs failed for CL_DEVICE_TYPE_CPU");
  }
  else
  {
    devices = (cl_device_id*)malloc(numDevices * sizeof(cl_device_id));
    status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, numDevices, devices, NULL);
    CHECK_OPENCL_ERROR(status, "clGetDeviceIDs failed for CL_DEVICE_TYPE_GPU");
  }

  /*Step 3: Create context.*/
  cl_int errCode;
  cl_context context = clCreateContext(NULL, numDevices, devices, NULL, NULL, &errCode);
  if (context == NULL) {
    std::cerr << "Error: clCreateContext failed, error " << errCode << "\n";
    return SDK_FAILURE;
  }

  /*Step 4: Creating command queue associate with the context.*/
  cl_command_queue commandQueue = clCreateCommandQueue(context, devices[0], 0, NULL);
  if (commandQueue == NULL) {
    std::cerr << "Error: clCreateCommandQueue failed\n";
    return SDK_FAILURE;
  }

  /*Step 5: Create program object */
  const char *filename = "WireWorld.cl";
  SDKFile kernelFile;
  if (!kernelFile.open(filename)) {
    std::cerr << "Error: failed to open " << filename << std::endl;
    return SDK_FAILURE;
  }
  const std::string &sourceStr = kernelFile.source();

  const char *source = sourceStr.c_str();
  size_t sourceSize[] = { sourceStr.size() };
  cl_program program = clCreateProgramWithSource(context, 1, &source, sourceSize, &errCode);
  CHECK_OPENCL_ERROR(errCode, "clCreateProgramWithSource failed");
  if (program == NULL) {
    std::cerr << "Error: clCreateProgramWithSource failed\n";
    return SDK_FAILURE;
  }

  /*Step 6: Build program. */

  status = clBuildProgram(program, 1, devices, NULL, NULL, NULL);
  if (status != CL_SUCCESS) {
    size_t length;
    char buffer[2048];
    clGetProgramBuildInfo(program, devices[0], CL_PROGRAM_BUILD_LOG,
                          sizeof(buffer), buffer, &length);
    std::cout <<"ERROR: clBuildProgram failed, see log below:\n "
              << buffer << std::endl;  
    CHECK_OPENCL_ERROR(status, "clBuildProgram failed");
  }
  /*Step 7: Initial input,output for the host and create memory objects for the kernel*/
  // TODO: YOUR CODE HERE
  const size_t arraySize = rows * cols;
  const size_t arrayBytes = arraySize * sizeof(cl_uchar);
  size_t global_work_size[2] = { rows, cols };
  
  cl_mem buffer0 = clCreateBuffer(context, CL_MEM_COPY_HOST_PTR, arrayBytes, (void *) wire_world.data(), NULL);
  cl_mem buffer1 = clCreateBuffer(context, 0, arrayBytes, NULL, NULL);

  /*Step 8: Create kernel object */
  cl_kernel kernel = clCreateKernel(program, "wire_world", &errCode);
  if (!kernel) {
	  cout << "clCreateKernel failed with error code " << errCode << endl;
	  return FAILURE;
  }

  Timer t;
  for (int i = 0; i < iterations; i++)
  {
	  if (i % 2 == 0)
	  {
		  /*Step 9: Sets Kernel arguments.*/
		  bool argOK = (CL_SUCCESS == clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&buffer0));
		  argOK = argOK && (CL_SUCCESS == clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&buffer1));
		  if (!argOK) {
			  cerr << "Error: clSetKernelArg failed\n";
			  return FAILURE;
		  }
	  }
	  else
	  {
		  /*Step 9: Sets Kernel arguments.*/
		  bool argOK = (CL_SUCCESS == clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&buffer1));
		  argOK = argOK && (CL_SUCCESS == clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&buffer0));
		  if (!argOK) {
			  cerr << "Error: clSetKernelArg failed\n";
			  return FAILURE;
		  }
	  }
	  /*Step 10: Running the kernel.*/
	  status = clEnqueueNDRangeKernel(commandQueue, kernel, 2, NULL, global_work_size, NULL, 0, NULL, NULL);
	  if (status != CL_SUCCESS) {
		  cerr << "Error: clEnqueueNDRangeKernel failed\n";
		  return FAILURE;
	  }
  }
  if (clFinish(commandQueue) != CL_SUCCESS)
  {
	  return FAILURE;
  }
  std::cout << "Time for " << iterations << " iterations: " << t.GetElapsedTime() << "\n";
  /*Step 11: Read the kernel output back to host memory (overwrite input wire_world).*/
  std::cout << "Finished Iterations \n";
  status = clEnqueueReadBuffer(commandQueue, buffer1, CL_TRUE, 0,
	  arrayBytes, (void *)wire_world.data(), 0, NULL, NULL);
  if (status != CL_SUCCESS) {
	  cerr << "Error: clEnqueueReadBuffer failed\n";
	  return FAILURE;
  }


  
  /*Step 12: Clean the resources.*/
  status = clReleaseKernel(kernel);				//Release kernel.
  status = clReleaseProgram(program);				//Release the program object.
 status = clReleaseMemObject(buffer0);		//Release mem object.
 status = clReleaseMemObject(buffer1);
  status = clReleaseCommandQueue(commandQueue);	//Release  Command queue.
  status = clReleaseContext(context);				//Release context.
  if (devices != NULL) {
    free(devices);
    devices = NULL;
  }

  std::cout << "Passed!\n";

  // Write output file
  if (!WriteWireWorld(argv[2], image, wire_world, rows, cols)) {
    exit(2);
  }

  #if defined(_OPENMP)

  // COMP4705 code here

  #endif

  return SDK_SUCCESS;
}
