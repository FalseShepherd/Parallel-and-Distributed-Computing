// Lab 3 OpenCL Kernel
//
// Image input/output

__kernel void flip_image(__global uchar4* in, __global uchar4* out)
{
	 int x = get_global_id(1);
	 int y = get_global_id(0);
	 int width = get_global_size(1);
	 int height = get_global_size(0);
	
	 out[x + width * y] = in[(width-x) + width* (height-y)];
}