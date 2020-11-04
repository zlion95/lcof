#include <iostream>
#include <vector>

using namespace std;

/*
 * 解法1：利用partition的方法
 * 时间复杂度：O(n) ?????? 怎么分析出来的详见《算法导论》
 */
void gen_pivot_to_end(vector<int> &data, int start, int end)//medium in three
{
	int mid = start + (end - start) / 2;
	if (data[start] > data[mid]) swap(data[start], data[mid]);
	if (data[start] > data[end]) swap(data[start], data[end]);
	if (data[mid] < data[end]) swap(data[mid], data[end]);//swap medium value to end
}

int partition(vector<int> &data, int start, int end)
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

bool check_more_than_half(vector<int> &data, int number)
{
	int times = 0;
	for (int i = 0; i < data.size(); ++i) {
		if (data[i] == number) ++times;
	}
	if (times * 2 <= data.size()) {
		cout << "without more half value." << endl;
		return false;
	}
	return true;
}

int print_vec(vector<int> &data) {
	for (auto &value : data) {
		cout << value << " ";
	}
	cout << endl;
}

int get_more_than_half(vector<int> &data)
{
	if (data.size() == 0) return 0;

	int mid = data.size() >> 1;
	int start = 0;
	int end = data.size() - 1;
	int index = partition(data, start, end);

	while (index != mid) {
		if (index > mid) {
			end = index - 1;
			index = partition(data, start, end);
		} else {
			start = index + 1;
			index = partition(data, start, end);
		}
		print_vec(data);
	}
	
	int result = data[mid];
	if (!check_more_than_half(data, result)) result = 0;
	return result;
}

/*
 * 解法2：数组遍历求出现次数的解法
 * 时间复杂度：O(n) 遍历一次
 * 理解：对拼消耗，假设有多个阵营，你拥有超过其他阵营总和还多的兵力，只要你不自己内斗，混战最终留下的人一定是你的。最差情况也是所有人联合对付你，相当于1 2 1 3...交替排列
 */
int more_than_half_value2(vector<int> &data)
{
	if (data.size() == 0) return 0;

	int result = data[0];
	int times = 1;
	for (int i = 1; i < data.size(); ++i) {
		if (times == 0) {
			result = data[i];
			times = 1;
		} else if(data[i] == result) {
			++times;
		} else {
			--times;
		}
	}
	if (!check_more_than_half(data, result)) result = 0;

	return result;
}

int main()
{
	int n;
	vector<int> data;

	cin >> n;
	data.resize(n);
	for (int i = 0; i < n; ++i) {
		cin >> data[i];
	}
	cout << "init: ";
	print_vec(data);
	cout << more_than_half_value2(data) << endl;
	return 0;
}
