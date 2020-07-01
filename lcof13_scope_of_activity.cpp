#include <iostream>

using namespace std;

class Solution
{
private:
	bool *visited;

	int count(int n) {
		int value = 0;
		while (n > 0) {
			value += n % 10; 
			n /= 10;
		}
		return value;
	}
	int move(int m, int n, int k, int row, int col)
	{
		int next = 0;
		if (row >= 0 && row < m && col >= 0 && col < n && 
				count(row) + count(col) <= k && !visited[row*n + col]) {
			visited[row*n + col] = true;
			next = 1 + move(m, n, k, row-1, col) + move(m, n, k, row+1, col)
					 + move(m, n, k, row, col-1) + move(m, n, k, row, col+1);
		}
		return next;
	}

public:
	int movingCount(int m, int n, int k)
	{
		if (k < 0 || m <= 0 || n <= 0) return 0;
		visited = new bool[n * m];
		for (int i = 0; i < n * m; ++i) visited[i] = false;
		int count = move(m, n, k, 0, 0);
		delete[] visited;
		return count;
	}
};


int main(int argc, char **argv)
{
	Solution s;
	int n, m, k;

	cin >> m >> n >> k;
	cout << s.movingCount(m, n, k) << endl;
	return 0;
}
