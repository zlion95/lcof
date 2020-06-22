#include <iostream>
#include <vector>

using namespace std;

int merge_sorted_array_to_first(int *list1, int len1, int *list2, int len2)
{
	if (!list1 || !list2) return -1;

	int p1 = len1-1, p2 = len2-1, p3 = len1+len2-1;
	while (p3 >= 0) {
		if (p1 < 0) {
			list1[p3--] = list2[p2--];
		}
		if (p2 < 0) {
			list1[p3--] = list1[p1--];
		}
		if (list1[p1] < list2[p2]) {
			list1[p3--] = list2[p2--];
		} else {
			list1[p3--] = list1[p1--];
		}
	}
	return 0;
}

int main(int argc, char **argv)
{
	int size1, size2;
	int *l1 = NULL, *l2 = NULL;

	cin >> size1;
	l1 = new int[size1];
	for (int i = 0; i < size1; ++i) {
		cin >> l1[i];
	}

	cin >> size2;
	l2 = new int[size1 + size2];
	for (int i = 0; i < size2; ++i) {
		cin >> l2[i];
	}

	merge_sorted_array_to_first(l2, size2, l1, size1);
	cout << "merge result:" << endl;
	for (int i = 0; i < size1+size2; ++i) {
		cout << l2[i] << " ";
	}
	cout << endl;
	return 0;
}
