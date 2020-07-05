#include <iostream>

using namespace std;

//@func: 返回结果false放左边，true放右边
void reorder(int *data, unsigned int length, bool (*func)(int))
{
	if (data == NULL || length == 0) return;

	int *left = data, *right = data+length-1;
	while (left < right) {
		while (left < right && !func(*left)) ++left;
		while (left < right && func(*right)) --right;
		if (left < right) {
			int temp = *left;
			*left = *right;
			*right = temp;
		}
	}
}

bool is_even(int value)
{
	return (value & 1) == 0;
}

int main(int argc, char **argv)
{
	int n, *data = NULL;

	cin >> n;
	data = new int[n];
	for (int i = 0; i < n; ++i) cin >> data[i];
	reorder(data, n, is_even);
	for (int i = 0; i < n; ++i) {
		cout << data[i] << " ";
	}
	cout << endl;
	return 0;
}
