#include <iostream>
#include <cstring>

using namespace std;

void combination(string s)
{
	char *str = new char[s.size()];
	strcpy(str, s.c_str());

}

//这道题的本质是求全组合，罗列所有可能需要输出2^(n)个结果

int main(int argc, char **argv)
{
	string str;
	cin >> str;
	/*
	char *data = new char[str.size() + 1];
	strcpy(data, str.c_str());
	*/
}
