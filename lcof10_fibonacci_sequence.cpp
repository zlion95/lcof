#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;

class Solution
{
public:
	//DP: 自顶向下，递归实现
	//递归树结构，时间复杂度O(2^n)
	//空间复杂度O(logn)
	/*
    int fib(int n) {
		if (n <= 0) return 0;
		if (n == 1) return 1;
		return fib(n-1) + fib(n-2);
    }
	*/

	//DP: 自定向下，递归实现+缓存数据
	//时间复杂度O(n): 0~n只会被traversal函数调用一次
	//空间复杂度O(logn + n) = O(n)
	/*
	vector<int> cache;
    int fib(int n)
	{
		if (n <= 0) return 0;
		cache.assign(n+1, -1);
		cache[0] = 0;
		cache[1] = 1;
		return traversal(n);
    }
	int traversal(int n)
	{
		if (cache[n-1] < 0) traversal(n-1);
		if (cache[n-2] < 0) traversal(n-2);

		return cache[n] = cache[n-1] + cache[n-2];
	}
	*/
	
	//DP: 自下向上，循环实现
	//时间复杂度O(n)
	//空间复杂度O(n)
	/*
	int fib(int n)
	{
		if (n <= 0) return 0;
		int *dp = new int[n+1];
		dp[0] = 0;
		dp[1] = 1;
		for (int i = 2; i <= n; ++i) {
			dp[i] = dp[i-1] + dp[i-2];
		}
		int result = dp[n];
		delete[] dp;
		return result;
	}
	*/

	//优化内存使用
	//时间复杂度O(n)
	//空间复杂度O(1)
	/*
	int fib(int n)
	{
		if (n <= 0) return 0;
		int first = 0, second = 1, temp;
		for (int i = 2; i <= n; ++i) {
			temp = second;
			second = first + second;
			first = temp;
		}
		return second;
	}
	*/

	//矩阵快速幂解法
	//存在矩阵M = [[1 1][1 0]]
	//是的递推关系成立：M * [[f(n)][f(n-1)]] = [[f(n)+f(n-1)][f(n)]] = [[f(n+1)][f(n)]]
	//连续相乘之后可以得到关系:
	//	[[f(n+1)][f(n)]] = M(^n) * [[f(1)][f(0)]]       其中f(1)=f(0)=1
	//本题的关键就转化为如何快速求取矩阵的幂 M(^n)
	//时间复杂度：O(logn)
	//空间复杂度：O(1)
	//优点：想法很独特，理论算法复杂度确实低
	//缺点：隐含的时间常数比较大【矩阵乘法所需要的操作数很多】，而且实现起来容易出错
	/*
	unsigned long long temp[4];//临时矩阵，用于保存矩阵乘法的结果
	int fib(int n)
	{
		unsigned long long M[4] = {1, 1, 1, 0}, res[4] = {1, 0, 0, 1};
		pow(M, n, res);
		return res[2]; //f(0) = 0, f(1) = 1; f(n) = res[2] * f(1) + res[3] * f(0) = res[2]
	}
	void pow(unsigned long long *m, int n, unsigned long long *res)
	{
		while (n) {//快速幂解法: 二分法的思想 将幂乘 M^n = M^(n/2) * M^(n/2) * ((n & 1) ? M : 1)	这样就只需要计算M^(n/2)的结果后，多乘自己一次，乘法计算少了一半
			if (n & 1) multiply(res, m);//奇数时无法等分，需要先多乘一个最终结果
			n >>= 1;
			multiply(m, m);
		}
	}
    void multiply(unsigned long long *m1, unsigned long long *m2)
	{
        // cout << m1[0] << " " << m1[1] << "\n" << m1[2] << " " << m1[3] <<endl << endl;
        memset(temp, 0, sizeof(temp));
        temp[0] = m1[0]*m2[0] + m1[1]*m2[2];
        temp[1] = m1[0]*m2[1] + m1[1]*m2[3];
        temp[2] = m1[2]*m2[0] + m1[3]*m2[2];
        temp[3] = m1[2]*m2[1] + m1[3]*m2[3];
        for (int i = 0; i < 4; ++i) m1[i] = temp[i];
    }
	*/

	//题解: 测试用例是n属于[1, 100]，因此int会溢出，题解要求用1e9+7取模避免溢出
	int fib(int n)
	{
		if (n <= 0) return 0;
		int first = 0, second = 1, temp;
		for (int i = 2; i <= n; ++i) {
			temp = second;
			second = (first + second) % 1000000007;
			first = temp;
		}
		return second;
	}
};

int main(int argc, char **argv)
{
	Solution s;
	int n;
	cin >> n;
	cout << s.fib(n) << endl;
	return 0;
}
