#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	char str1[] = "hello world";
	char str2[] = "hello world";

	char *str3 = "hello world";
	char *str4 = "hello world";
	
	//由于是char数组，索引给定一个字符串字面量，实际会先分配str1，str2的内存，再将该字符串常量copy到str1和str2，因此str1和str2地址是不同的
	if (str1 == str2) cout << "str1 is same to str2" << endl;
	else cout << "str1 is not same to str2" << endl;

	//这是因为"hello world"是一个常量字符串，只会被分配一次，str3和str4都是指向该常量字符串的指针
	if (str3 == str4) cout << "str3 is same to str4" << endl;
	else cout << "str3 is not same to str4" << endl;

	return 0;
}
