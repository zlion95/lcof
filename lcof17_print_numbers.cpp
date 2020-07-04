#include <iostream>
#include <cstring>

using namespace std;

//递归遍历方式：n一旦大了，函数调用栈开销非常大
/*
void print_i(char *str, const int n, int level)
{
	if (level == n) {
		//cout << str << endl;
		return;
	}
	for (int i = 0; i < 10; ++i) {
		str[level] = '0' + i;
		print_i(str, n, level+1);
	}
}
*/


bool error_input = false;
void print_to_max_of_digit(int n)
{
	char *str = NULL;
	int level;

	if (n <= 0) {
		error_input = true;
		return;
	}

	/*
	char *str = new char[n+1];
	memset(str, '0', n);
	str[n+1] = '\0';
	print_i(str, n, 0);
	*/
	str = new char[n+2];
	memset(str, '0', n+1);
	str[n+1] = '\0';

	//用字符串模拟加法进位
	while (str[0] == '0') {//0号位置是用于标志目前是否可以终止的条件，不应该被打印
		level = n;
		while (++str[level] > '9') {
			str[level--] = '0';
		}
		//cout << str + 1 << endl;
	}
	//cout << "last:" << str << endl;

	delete[] str;
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	print_to_max_of_digit(n);
	return 0;
}
