#include <iostream>
#include <vector>

using namespace std;

enum {
	UP = 0,
	DOWN,
	LEFT,
	RIGHT
};

//回溯法
class Solution
{
private:
	int m = 0;
	int n = 0;
	int rows[4] = {-1, 1, 0, 0};
	int cols[4] = {0, 0, -1, 1};
	vector<vector<bool>> visited;
	
	bool search(vector<vector<char>> &board, int row, int col, string &word, int ci)
	{
		visited[row][col] = true;
		if (ci + 1 == word.size()) return true;

		//为了避免无效的方向也要调用一次search，增加函数调用栈操作，尽可能的在本次调用判断出是否可行状态
		int dir[4] = {-1, -1, -1, -1};//up, down, left, right
		if (row > 0 && !visited[row-1][col]) dir[UP] = board[row-1][col];
		if (row < n-1 && !visited[row+1][col]) dir[DOWN] = board[row+1][col];
		if (col > 0 && !visited[row][col-1]) dir[LEFT] = board[row][col-1];
		if (col < m-1 && !visited[row][col+1]) dir[RIGHT] = board[row][col+1];

		for (int i = 0; i < 4; ++i) {
			if (dir[i] > 0 && word[ci+1] == (char)dir[i]) {
				if (search(board, row+rows[i], col+cols[i], word, ci+1)) return true;
			}
		}
		visited[row][col] = false;
		return false;
	}

public:
	bool exist(vector<vector<char>>& board, string &word)
	{
		if (word == "") return true;
		if (board.size() == 0 || board[0].size() == 0) return false;

		n = board.size();
		m = board[0].size();
		visited.assign(n, vector<bool>(m, false));

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (board[i][j] == word[0] && search(board, i, j, word, 0)) return true;
			}
		}
		return false;
	}
};

int main(int argc, char **argv)
{
	vector<vector<char>> board;
	Solution s;
	string str;
	int m, n;

	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		vector<char> line(m);
		for (auto &c : line) {
			cin >> c;
		}
		board.push_back(line);
	}
	cin >> str;

	cout << s.exist(board, str) << endl;
	return 0;
}
