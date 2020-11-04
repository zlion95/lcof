#include <iostream>
#include <vector>
#include <unordered_set>
#include <memory.h>
#include <algorithm>

using namespace std;

class Solution
{
public:
	//解法1：hash方法，如果不限定nums值的范围，就只能使用这个方法【通用性强，但并非当前问题的最优解】
	//核心思想：哈希表
	//空间复杂度：O(n)		时间复杂度：O(n)
	/*
	int findRepeatNumber(vector<int>& nums)
	{
		unordered_set<int> exist;
		for (auto &i : nums) {
			if (exist.count(i)) return i;
			exist.insert(i);
		}
		return -1;//题目没有定义没有出现任何重复数字的情况，所以这里为了编译通过，只能返回一个范围外的值，实际用例执行不到这里
	}
	*/

	//解法2：数组哈希方法【限定条件：nums值的范围为 0 ~ (n-1)】
	//可以直接构造一个n大小的数组，索引为key，出现次数为value，用数组来当做哈希表使用;
	//核心思想：哈希表
	//空间复杂度：O(n)		时间复杂度：O(n)
	/*
	int findRepeatNumber(vector<int>& nums)
	{
		int *counts = new int[nums.size()];
		memset(counts, 0, sizeof(counts));
		for (auto &i : nums) {
			if (counts[i]) return i;
			++counts[i];
		}
		delete[] counts;
		return -1;//未定义行为，实际用例执行不到这里
	}
	*/

	//解法3：最低效的方法，排序之后再来检查
	//核心思想：排序
	//空间复杂度：O(1)		时间复杂度：O(nlogn)
	/*
	int findRepeatNumber(vector<int>& nums)
	{
		sort(nums.begin(), nums.end());
		for (int i = 1; i < nums.size(); ++i) {
			if (nums[i-1] == nums[i]) return nums[i];
		}
		return -1;//未定义行为，实际用例执行不到这里
	}
	*/

	//解法4：按位置置换排序，置换正确的数字到正确的索引位置【限定条件nums的值只会出现0 ~（n-1）】
	//核心思想：排序
	//空间复杂度：O(1)		时间复杂度：O(n)
	/*
	int findRepeatNumber(vector<int>& nums)
	{
		for (int i = 0; i < nums.size(); ++i) {
			while (nums[i] != i) {									//最终要的效果是: 每个值放到对应的索引位置
				if (nums[nums[i]] == nums[i]) return nums[i];		//如果发现nums[i]，和它应该出现的索引位置上的值相等，就说明该nums[i]有重复值，可以直接退出
				swap(nums[nums[i]], nums[i]);
			}
		}
		return -1;//未定义行为，实际用例执行不到这里
	}
	*/

	//在解法4的基础上，考虑健壮性等问题
	//最好的做法其实是在调用过程上检查返回值，这种方式来确定错误类型【因为正常不会出现负值，因此将负值作为返回错误类型区分很方便，不需要exception也可以】
	int findRepeatNumber(vector<int>& nums)
	{
		if (nums.size() < 2) return -1;//返回-1改成触发exception更好，因为这是一个未定义错误
		for (auto &i : nums) if (i > nums.size()-1 || i < 0) return -1;//检查数值范围，如果超出范围，会出现数组越界索引错误: exception

		for (int i = 0; i < nums.size(); ++i) {
			while (nums[i] != i) {
				if (nums[nums[i]] == nums[i]) return nums[i];
				swap(nums[nums[i]], nums[i]);
			}
		}
		return -1;//没有重复数值，用例有问题: exception
	}

	//加入新的要求：【不能改动输入的数组, 数组长度为n，则数值在1~n-1，即至少有一个数字是重复的】
	//如果采用解法1, 2可以实现，但空间复杂度比较高
	//解法5：二分法
	//收缩区间
};

int main(int argc, char **argv)
{
	int n;
	Solution s;
	vector<int> nums;

	cin >> n;
	nums.assign(n, 0);
	for (int i = 0; i < n; ++i) {
		cin >> nums[i];
	}
	cout << s.findRepeatNumber(nums) << endl;
}
