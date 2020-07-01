#include <iostream>
#include <vector>
#include <climits>

using namespace std;

//leetcode 提供的官方解法：通过另mid==high时，缩减区间的办法，不丢失旋转点的情况下，完成区间的缩减，另下一次循环的mid和high发生改变
//注意：这个缩减区间的办法对于求最小值有效，但如果是要求找到旋转点本身，这个办法就是无效的
class Solution {
public:
	int minArray(vector<int>& numbers) {
		if (!numbers.size()) return -1;

		int low = 0, high = numbers.size()-1;
		int mid = 0;
		while (low < high) {
			int mid = low + ((high - low) >> 1);
			if (numbers[mid] > numbers[high]) low = mid + 1;
			else if (numbers[mid] < numbers[high]) high = mid;
			else --high;//这一步的想法非常妙，由于mid和high相等，可能涵盖了 [5 1 5 5 5] [5 5 5 1 5] [3 4 2 2 2] 这三种情况
						//其中前两种无法判断区间，因此直接将右边的指针减1位，这时候mid还在区间里面【因为low < high，所以mid必定小于high】
						//既能够继续缩减区间，又能保证不丢失旋转点
		}
		return numbers[low];
	}
};

//剑指offer的解法：这种接法能找到最小值，改一下min_in_order也能做成找到旋转点本身
//但考虑的情况有点多，代码也比较乱，不是很简洁
/*
class Solution {
public:
	int minArray(vector<int>& numbers) {
		if (!numbers.size()) return -1;

		int low = 0, high = numbers.size()-1;
		int mid = 0;
		while (numbers[low] >= numbers[high]) {
			if (high - low <= 1) {//相邻时，low>high，就代表了high就是最小值
				mid = high;
				break;
			}
			mid = low + ((high-low) >> 1);
			if (numbers[mid] == numbers[low] && numbers[mid] == numbers[high]) //存在[5 1 5 5 5] or [5 5 5 1 5]这两种情况，无法判断在那个区间
				return min_in_order(numbers, low, high);

			if (numbers[mid] >= numbers[low]) low = mid;
			else if (numbers[mid] <= numbers[high]) high = mid;
			else return -1;//那么 low > mid  && higt < mid 时呢,如[5 2 1]， 必定不满足rotate array：不能从一个有序数组经过旋转得到
		}
		return numbers[mid];
	}

	int min_in_order(vector<int> &numbers, int low, int high)
	{
		int min_value = INT_MAX;
		for (int i = low; i < high; ++i) {
			min_value = min(numbers[i], min_value);
		}
		return min_value;
	}
};
*/


int main(int argc, char **argv)
{
	vector<int> data;
	Solution s;
	int n;

	cin >> n;
	if (n <= 0) exit(-1);
	data.assign(n, 0);

	for (auto it = data.begin(); it != data.end(); ++it) {
		cin >> *it;
		cout << *it << " ";
	}
	cout << endl;

	cout << s.minArray(data) << endl;
	return 0;
}
