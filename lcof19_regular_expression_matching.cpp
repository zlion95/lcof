#include <iostream>
#include <vector>

using namespace std;

// struct PatternException : public exception
// {
//   const char * what () const throw ()
//   {
//     return "Input pattern start with '*'!";
//   }
// };

class Solution {
public:
    //DP自顶向下匹配
    /*
    bool isMatch(string s, string p) {
        if (s.size() == 0 && p.size() == 0) return true;
        else if (p.size() == 0) return false;
        return match(s.c_str(), p.c_str());
    }
    bool match(const char *s, const char *p) 
    {
        if (*s == '\0' && *p == '\0') return true;
        else if (*p == '\0') return false;

        if (*(p+1) == '*') {
            if (*p == *s || (*p == '.' && *s != '\0')) {
                return match(s+1, p+2)  //(*)匹配 1 个
                    || match(s+1, p)    //(*)匹配 n 个
                    || match(s, p+2);   //(*)匹配 0 个
            } else {//当前 字符串s 不能匹配上 模式串p，但当前的模式串是(*)，可以被忽略，因此还能继续
                return match(s, p+2);
            }
        }
        //p+1不是*，说明当前不是(*)串，只有完全匹配 或 (.)才能继续
        if (*p == *s || (*p == '.' && *s != '\0'))
            return match(s+1, p+1);
        return false;//非(*)，*p != *s 也不是(.)，匹配失败
    }
    */
    //DP自底向上
    bool isMatch(string s, string p) {
        if (p.size() == 0) return s.size() == 0;
        else if (p[0] == '*') return false;  //pattern以"*"开头的，是错误输入，其实这里也可以改成抛出异常
        if (s.size() == 0 && p.size() == 1) return false;

        int n = s.size(), m = p.size();
        vector<vector<bool>> dp(n+1, vector<bool>(m+1, false));
        dp[0][0] = true;  //字符串s 和 模式串p 都是空的时候，匹配成功
        dp[0][1] = false; //模式串为1，即不符合*串，那就必须要有字符来匹配，由于s串为空，因此匹配失败
        for (int i = 2; i <= m; ++i) 
            if (p[i-1] == '*') dp[0][i] = dp[0][i-2]; //DP状态转移方程当p[i] == '*'的时候，都需要用到dp[j]][i-2]来计算
                                                    //我们是从索引1开始遍历的，因此第一行必须要提前设置好

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (s[i-1] == p[j-1] || p[j-1] == '.') {
                    dp[i][j] = dp[i-1][j-1];
                } else if (p[j-1] == '*') {
                    if (p[j-2] == s[i-1] || p[j-2] == '.') {
                        dp[i][j] = dp[i-1][j] || dp[i][j-2];    //(*)串匹配掉s[i-1] 或 (*)串不匹配s[i-1]
                    } else {//既等于p[j-2]，p[j-2]也不是'.'，只能让(*)不配，跳过继续查看后面的
                        dp[i][j] = dp[i][j-2];      //(*)串不匹配，因此与前面的匹配结果保持一致
                    }
                } else {
                    dp[i][j] = false;
                }
                // cout << "[" << i << ", " << j << "] = " << dp[i][j] <<endl;
            }
        }
        return dp[n][m];
    }
};


int main(int argc, char **argv)
{
	Solution solution;
	string s, p;
	getline(cin, s);
	getline(cin, p);
	solution.isMatch(s, p);
	return 0;
}
