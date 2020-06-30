#include <iostream>

enum {
	INSERT_SORT = 0,
	BUBBLE_SORT,
	MERGE_SORT,
	QUICK_SORT,
	SELECT_SORT,
};

static inline void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

class Sort
{
private:
	void quick_sort(int data[], int start, int end)
	{
		if (start >= end) return;

		int pivot = partition(data, start, end);
		quick_sort(data, start, pivot-1);
		quick_sort(data, pivot+1, end);
	}

	int partition(int data[], int start, int end)
	{
		int small = start - 1;

		gen_pivot_to_end(data, start, end);//select a pivot and swap it to end of this partition
		for (int i = start; i < end; ++i) {
			if (data[i] < data[end]) {
				++small;
				swap(data[small], data[i]);
			}
		}
		swap(data[++small], data[end]);//because i > small, data[small] >= data[end]
		return small;
	}

	void gen_pivot_to_end(int data[], int start, int end)//medium in three
	{
		int mid = start + (end - start) / 2;
		if (data[start] > data[mid]) swap(data[start], data[mid]);
		if (data[start] > data[end]) swap(data[start], data[end]);
		if (data[mid] < data[end]) swap(data[mid], data[end]);//swap medium value to end
	}

	int *list_merge_sorted = NULL;
	void merge_sort(int data[], int start, int end)
	{
		if (start >= end) return;

		int mid = start + (end - start) / 2;
		merge_sort(data, start, mid);
		merge_sort(data, mid+1, end);
		merge(data, start, mid, end);
	}

	void merge(int data[], int start, int mid, int end)
	{
		int i = start, j = mid+1, cur = start;
		while (i <= mid || j <= end) {
			if (data[i] > data[j])
				list_merge_sorted[cur++] = data[j++];
			else 
				list_merge_sorted[cur++] = data[i++];

			if (i > mid) while (j <= end) list_merge_sorted[cur++] = data[j++];
			if (j > end) while (i <= mid) list_merge_sorted[cur++] = data[i++];
		}

		for (int i = start; i <= end; ++i) data[i] = list_merge_sorted[i];
	}

public:
	void quick_sort(int data[], int length, int start, int end)
	{
		if (data == NULL || length < 2 || start < 0 || end >= length) return;
		quick_sort(data, start, end);
	}

	void insert_sort(int data[], int length, int start, int end)
	{
		if (data == NULL || length < 2 || start < 0 || end >= length) return;

		for (int i = start; i <= end; ++i) {
			for (int j = i-1; j >= start && data[j] > data[j+1]; --j) {
				swap(data[j], data[j+1]);
			}
		}
	}

	void bubble_sort(int data[], int length, int start, int end)
	{
		if (data == NULL || length < 2 || start < 0 || end >= length) return;
		
		for (int j = end; j > start; --j) {
			for (int i = start; i < j; ++i) {
				if (data[i] > data[i+1]) {
					swap(data[i], data[i+1]);
				}
			}
		}
	}

	void merge_sort(int data[], int length, int start, int end)
	{
		if (data == NULL || length < 2 || start < 0 || end >= length) return;

		list_merge_sorted = new int [end - start + 1];//Assign extra array to merge two sorted list
		merge_sort(data, start, end);
		delete[] list_merge_sorted;
	}

	void select_sort(int data[], int length, int start, int end)
	{
		if (data == NULL || length < 2 || start < 0 || end >= length) return;
		
		int small;
		for (int i = start; i < end; ++i) {
			small = i;
			for (int j = i; j <= end; ++j) {
				if (data[j] < data[small]) small = j;
			}
			swap(data[i], data[small]);
		}
	}
};

int main(int argc, char **argv)
{
	Sort s;
	int n = 0, action = 0, *data = NULL;

	std::cin >> n;
	if (n <= 0) {
		std::cerr << "Error data length!" << std::endl;
		exit(-1);
	}

	data = new int[n];
	for (int i = 0; i < n; ++i) {
		std::cin >> data[i];
	}
	
	std::cout << "List: ";
	for (int i = 0; i < n; ++i) {
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
	

	std::cin >> action;
	switch (action) {
	case INSERT_SORT:
		std::cout << "Use insert sort." << std::endl;
		s.insert_sort(data, n, 0, n-1);
		break;
	case BUBBLE_SORT:
		std::cout << "Use bubble sort." << std::endl;
		s.bubble_sort(data, n, 0, n-1);
		break;
	case MERGE_SORT:
		std::cout << "Use merge sort." << std::endl;
		s.merge_sort(data, n, 0, n-1);
		break;
	case QUICK_SORT:
		std::cout << "Use quick sort." << std::endl;
		s.quick_sort(data, n, 0, n-1);
		break;
	case SELECT_SORT:
		std::cout << "Use select sort." << std::endl;
		s.select_sort(data, n, 0, n-1);
		break;
	default:
		std::cerr << "Error action code!" << std::endl;
		exit(-2);
	}

	std::cout << "Sorted list: ";
	for (int i = 0; i < n; ++i) {
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}
