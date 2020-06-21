#include <iostream>
#include <cstdio>

int get_size(int data[])
{
	return sizeof(data);
}

int main(int argc, char **argv)
{
	int data1[] = {1, 2, 3, 4, 5};
	int size1 = sizeof(data1);

	int *data2 = data1;
	int size2 = sizeof(data2);
	
	int size3 = get_size(data1);
	int size4 = sizeof(data1+1);
	printf("%d, %d, %d, %d\n", size1, size2, size3, size4);
}
