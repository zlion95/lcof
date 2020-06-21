#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
	//解法1：暴力查找
	//时间复杂度：O(mn)		空间复杂度：O(1)
	/*
	bool findNumberIn2DArray(vector<vector<int>>& matrix, int target)
	{
		if (matrix.size() == 0 || matrix[0].size() == 0) return false;//matrix错误
		int n = matrix.size(), m = matrix[0].size();
		for (auto &line : matrix) if (line.size() != m) return false;	 //检查矩阵是否规范，应该改成throw exception，这是题意范围外的用例输入错误

		for (auto &line : matrix) {
			for (auto &num : line) {
				if (num == target) return true;
			}
		}
		return false;
	}
	*/

	//解法2：逐行二分查找
	//时间复杂度：O(nlogm)	空间复杂度：O(1)
	/*
	bool findNumberIn2DArray(vector<vector<int>>& matrix, int target)
	{
		if (matrix.size() == 0 || matrix[0].size() == 0) return false;//matrix错误
		int n = matrix.size(), m = matrix[0].size();
		for (auto &line : matrix) if (line.size() != m) return false;	 //检查矩阵是否规范，应该改成throw exception，这是题意范围外的用例输入错误

		for (auto &line : matrix) {
			if (line[0] > target) return false;
			if (binary_search(line, target)) return true;
		}
		return false;
	}
	bool binary_search(vector<int> &line, int target)
	{
		int left = 0, right = line.size()-1;
		while (left <= right) {
			int mid = (right-left) / 2 + left;
			if (line[mid] == target) return true;
			if (line[mid] > target) right = mid - 1;
			else left = mid + 1;
		}
		return false;
	}
	*/
	
	//解法3：按区域递归
	//时间复杂度：O(nlogm)		空间复杂度：O(logm)	递归函数栈
	/*
	bool findNumberIn2DArray(vector<vector<int>>& matrix, int target)
	{
		if (matrix.size() == 0 || matrix[0].size() == 0) return false;//matrix错误
		int n = matrix.size(), m = matrix[0].size();
		for (auto &line : matrix) if (line.size() != m) return false;	 //检查矩阵是否规范，应该改成throw exception，这是题意范围外的用例输入错误

		return search(matrix, target, 0, m-1, 0, n-1);
	}
	bool search(vector<vector<int>> &matrix, int target, int left, int right, int top, int bottom)
	{
		if (left > right || top > bottom) return false;
		if (target < matrix[top][left] || target > matrix[bottom][right]) return false;

		int mid = (right - left) / 2 + left, row = top;
		while (row <= bottom && matrix[row][mid] <= target) {//TODO：这里可以优化复杂度，能将时间复杂度从O(nlogm) 提升到 O(logn * logm)
			if (matrix[row][mid] == target) return true;
			++row;
		}//跳出条件: matrix[row][mid] > target		此时target不可能在右下方[行>=row, 列>=mid+1] 和 左上区域[行<row, 列<=mid-1]
		return search(matrix, target, left, mid-1, row, bottom)		//左下区域
			|| search(matrix, target, mid+1, right, top, row-1);	//右上区域
	}
	*/

	//解法4：线性查找，可以从左下角判断，也可以从右上角判断【这里已右上角为例】
	//	当右上角大于target，说明当前列都大于target，直接去除当前列；
	//	当右上角小于target，说明当前行都小于target，直接去除当前行；
	//		m+n-1次循环以内就能判断matrix内是否有target
	//时间复杂度：O(m+n)		空间复杂度：O(1)
	bool findNumberIn2DArray(vector<vector<int>>& matrix, int target)
	{
		if (matrix.size() == 0 || matrix[0].size() == 0) return false;//matrix错误
		int n = matrix.size(), m = matrix[0].size();
		for (auto &line : matrix) if (line.size() != m) return false;	 //检查矩阵是否规范，应该改成throw exception，这是题意范围外的用例输入错误

		int i = 0, j = m-1;
		while (i < n && j >= 0) {
			if (matrix[i][j] == target) return true;
			if (matrix[i][j] > target) --j;
			else ++i;
		}
		return false;
	}
};

int main(int argc, char **argv)
{
	vector<vector<int>> matrix;
	Solution s;
	int m, n;
	
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		vector<int> line(m);
		for (int j = 0; j < m; ++j) {
			cin >> line[j];
		}
		matrix.push_back(line);
	}

	cin >> n;
	while (n-- > 0) {
		cin >> m;
		cout << "target: " << m << "\tfind: " << s.findNumberIn2DArray(matrix, m) << endl;
	}
	return 0;
}
