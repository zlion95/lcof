#include <iostream>

int binary_search(int data[], int n, int value)
{
	int low = 0, high = n - 1;

	while (low <= high) {
		int mid = low + ((high - low) >> 1);
		if (data[mid] > value) {
			high = mid - 1;
		} else if (data[mid] < value){
			low = mid + 1;
		} else {
			if ((mid == 0) || (data[mid-1] != value)) return mid;//查找第一个出现的value的索引
			return high = mid - 1;
		}
	}
	return -1;
}

int main(int argc, char **argv)
{
	int n, value;
	std::cin >> n >> value;
	if (n <= 0) return -1;

	int *data = new int[n];
	for (int i = 0; i < n; ++i) {
		std::cin >> data[i];
	}

	std::cout << "list: [";
	for (int i = 0; i < n-1; ++i) {
		std::cout << data[i] << ", ";
	}
	std::cout << data[n-1] << "] search value: " << value << std::endl;
	
	std::cout << binary_search(data, n, value) << std::endl;;
	return 0;
}
