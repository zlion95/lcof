#include <iostream>
#include <sstream>
#include <cstring>
#define MEM_LEFT 10

using namespace std;

class Solution
{
public:
	//PART1: 这个用于提交leetcode，需要开辟新内存
	//解法1：借助ostringstream实现	需要#include <sstream>
	//时间复杂度：O(n)
	string replaceSpace(string s)
	{
		ostringstream os;
		for (auto &c : s) {
			if (c == ' ') os << "%20";
			else os << c;
		}
		return os.str();
	}

	int get_blocks(string &s)
	{
		int count = 0;
		for (auto &c : s) {
			if (c == ' ') ++count;
		}
		return count;
	}

	//PART2: 直接在原来的string数组上替换
	//解法：先统计空格有多少，然后从尾部开始拷贝替换，这样就不用频繁移动后面的元素
	//时间复杂度: O(n)
	void replace_space(char *str, int length)
	{
		int ori = 0, blank_count = 0;
		if (!str || length <= 0) return;

		while (str[ori] != '\0') {
			if (str[ori] == ' ') ++blank_count;
			++ori;
		}
		int new_len = ori + blank_count * 2;
		if (new_len >= length) return;//空间不足

		int p1 = ori, p2 = new_len;
		while (p1 >= 0 && p1 < p2) {//当p1==p2时，说明已经没有空格了，可以提前退出
			if (str[p1] == ' ') {
				str[p2--] = '0';
				str[p2--] = '2';
				str[p2--] = '%';
			} else {
				str[p2--] = str[p1];
			}
			--p1;
		}
	}
};

int main(int argc, char **argv)
{
	string str;
	int block_size, size;
	Solution s;
	char *data = NULL;

	//cin >> str;
	getline(cin, str);
	size = str.size();
	cout <<	"replace for new string: " << s.replaceSpace(str) << endl;

	block_size = s.get_blocks(str);
	size = size + 2 * block_size + MEM_LEFT;//计算预留的char数组空间
	data = new char[size];
	strncpy(data, str.c_str(), str.size()+1);//+1是为了'\0'，是否需要？
	s.replace_space(data, size);
	cout << "replace in origin char[]: " << data << endl;
	return 0;
}
