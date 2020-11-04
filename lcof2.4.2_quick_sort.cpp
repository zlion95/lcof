#include <iostream>

static inline void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

//优化快排pivot选取：三数中值法，将pivot放到end位置
void gen_pivot_to_end(int data[], int start, int end)
{
	int mid = start + (end - start) / 2;
	
	if (data[start] > data[mid]) swap(data[start], data[mid]);
	if (data[start] > data[end]) swap(data[start], data[end]);//把最小的放到了start位置
	if (data[mid] < data[end]) swap(data[mid], data[end]);//将最大值放到mid位置，这样end位置就是三数中间值
}

int partition(int data[], int start, int end)
{
	int small = start - 1;
	gen_pivot_to_end(data, start, end);//pivot交换到end位置

	for (int i = start; i < end; ++i) {
		if (data[i] < data[end]) {
			++small;
			swap(data[i], data[small]);//small代表的是小于pivot的区间end位置: 从index=0开始，只要碰上小于pivot的值，就让其与data[small]交换
		}
	}//退出循环时，small为小于pivot的区间的end
	++small;//small+1为pivot应该放的位置
	swap(data[small], data[end]);//由于已经退出循环，因此i==end>small必然成立，因此必定有data[small] >= pivot_value
	return small;
}

void sort(int data[], int start, int end)
{
	if (start >= end) return;

	int index = partition(data, start, end);
	sort(data, start, index-1);
	sort(data, index+1, end);
}

void quick_sort(int data[], int length, int start, int end)
{
	if (data == NULL || length < 2 || start < 0 || end >= length) return;

	sort(data, start, end);
}

int main(int argc, char **argv)
{
	int n, *data = NULL;
	std::cin >> n;
	if (n <= 0) {
		std::cerr << "Can't input minus n!" << std::endl;
		return -1;
	}

	data = new int[n];
	for (int i = 0; i < n; ++i) {
		std::cin >> data[i];
	}
	quick_sort(data, n, 0, n-1);
	for (int i = 0; i < n; ++i) {
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
	return 0;
}
