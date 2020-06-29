#include <iostream>
#include <cmath>
#include <memory.h>

using namespace std;

//解法1：排列组合的思路：实际速度不一定快【当n比较大的时候O(n^2)】
//解释：2步出现的次数最多为n/2，因此罗列所有2出现的可能，并求当前2步的次数m，对应的组合可能；全部相加就可以得到n有多少种走法
//求和1+2+3+...+m   m为[0, n/2]
/*
class Solution {
public:
    int climbStairs(int n)
    {
        int max2 = n / 2, res = 0;
        for (int i = 0; i <= max2; ++i) {	//执行了 n/2 次
            res += combine(n - i, i);
        }
        return res;
    }
    unsigned long long combine(int n, int m)	// 组合数C(m, n)	时间复杂度为O(m)
    {
        if (m == 0 || m == n) return 1;
        unsigned long long res = 1;
        for (int i = 1; i <= m; ++i) res = res * (n - m + i) / i;
        return res;
    }
};
*/

//DP自下向上: 递推表达式OPT(i) = OPT(i-1) + OPT(i-2)  代表的含义是当前第i阶梯，可以是通过i-2跨2步到达，也可以是i-1跨1步到达
//从这个递推公式来看，其实就是所谓的斐波那契数的递推关系
//优化：从上面式子可以看出，其实OPT(i)只依赖于前两次递归的结果，因此没必要保留所有结果，可以优化成三个变量
//时间复杂度O(n) 适用于n比较小的情况，当n比较大时，这个方法其实效果并不好
//空间复杂度O(1)
/*
class Solution {
public:
    int climbStairs(int n)
    {
        if (n < 2) return 1;
        int res[3] = {1, 1, 1}; //res[0], res[1]初始代表0, 1层阶梯，只能有一种走法，res[2]需要被求取
        for (int i = 2; i <= n; ++i) {
            res[0] = res[1];
            res[1] = res[2];
            res[2] = res[0] + res[1];
        }
        return res[2];
    }
};
*/

//矩阵快速幂：利用矩阵乘法来构建递推关系  存在矩阵M = [[1 1][1 0]]
//递推关系：M * [[f(n)][f(n-1)]] = [[f(n)+f(n-1)][f(n)]] = [[f(n+1)][f(n)]]
//因此存在连续乘关系使得   [[f(n+1)][f(n)]] = M(^n) * [[f(1)][f(0)]]       其中f(1)=f(0)=1
//综上，本题的关键就转化为如何快速求取矩阵的幂 M(^n)
//优点：想法很独特，很值得学习，但实际使用几乎还是有点问题，快速计算矩阵幂时，太容易类型溢出了，但如果是改动为针对大数计算的话，该方法效率还是比DP方法要快的
//时间复杂度O(logn) 空间复杂度O(1)
/*
class Solution {
private:
    unsigned long long temp[4];
public:
    int climbStairs(int n) {
        unsigned long long M[4] = {1, 1, 1, 0}, res[4] = {1, 0, 0, 1};
        pow(M, n, res);
        return res[0];	//为什么是res[0] ???	从公式推导来看应该是 f(n) = res[2] * f(1) + res[3] * f(0)
    }
    
    void pow(unsigned long long *m, int n, unsigned long long *res) {
        while (n) {
            if (n & 1) multiply(res, m);
            n >>= 1;
            multiply(m, m);
        }
    }
    
    void multiply(unsigned long long *m1, unsigned long long *m2) {
        // cout << m1[0] << " " << m1[1] << "\n" << m1[2] << " " << m1[3] <<endl << endl;
        memset(temp, 0, sizeof(temp));
        temp[0] = m1[0]*m2[0] + m1[1]*m2[2];
        temp[1] = m1[0]*m2[1] + m1[1]*m2[3];
        temp[2] = m1[2]*m2[0] + m1[3]*m2[2];
        temp[3] = m1[2]*m2[1] + m1[3]*m2[3];
        for (int i = 0; i < 4; ++i) m1[i] = temp[i];
    }
};
*/

//斐波那契公式：有上面DP的方法（斐波那契数列）可以知道递推关系，可知 OPT(n) 是齐次线性递推，可以证明得到它的通项公式，直接用通项公式就能求解
//如何证明需要用到高数的 齐次线性方程，非齐次线性方程通项公式
//时间复杂度：O(logn) 主要为求幂函数pow带来的消耗
//空间复杂度：O(1)
//注意：这种方法无法通过leetcode上剑指offer 10.2，原因是浮点数计算后取模和原始的int型取模再来计算结果是存在偏差的，无法通过用例
class Solution {
public:
    int climbStairs(int n)
    {
        double sqrt5 = sqrt(5);
        double fn = pow((1+sqrt5)/2, n+1) - pow((1-sqrt5)/2, n+1);
        return (int) (fn/sqrt5);
    }
};


int main(int argc, char **argv)
{
	Solution s;
	int n;
	cin >> n;
	cout << s.climbStairs(n) << endl;
	return 0;
}
