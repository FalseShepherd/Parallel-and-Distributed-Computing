// Program2 WireWorld OpenCL Kernel
//

__kernel void wire_world (__global uchar* in, __global uchar* out)
{
	int y = get_global_id(0);
	int x = get_global_id(1);
	size_t rows = get_global_size(0);
	size_t cols = get_global_size(1);   
	int index = y*cols+x;
	int count = 0;
	if(in[index] == 0)
	{
		out[index] = 0;
	}
	if(in[index] == 1)
	{
		out[index] = 2;
	}
	if(in[index] == 2)
	{
		out[index] = 3;
	}
	if(in[index] == 3)
	{
			for(int yo=-1;yo<=1;yo++)
			{
				for(int xo =-1;xo<=1;xo++)
				{
					if(in[(y+yo)*cols+x+xo] ==1)
					{
						count++;
					}
				}
			}
		if(count <3 && count >=1)
		{
			out[index] = 1;
		}
		else
		{
			out[index] = 3;
		}
	}
}
