#include <iostream>
#include <cstring>

using namespace std;

class CMyString
{
public:
	CMyString(const char *pdata = nullptr)
	{
		m_pData = new char[strlen(pdata) + 1];
		strcpy(m_pData, pdata);
	}

	CMyString(const CMyString &str)
	{
		m_pData = new char[strlen(str.m_pData) + 1];
		strcpy(m_pData, str.m_pData);
	}

	~CMyString(void)
	{
		delete[] m_pData;
	}

	/* 1. 检查是否为当前用例， 2. 返回值为引用类型，保证可以连续赋值
	CMyString& operator=(const CMyString &str)
	{
		if (&str == this) return *this;

		delete[] m_pData;
		m_pData = nullptr;

		m_pData = new char[strlen(str.m_pData) + 1];
		strcpy(m_pData, str.m_pData);

		return *this;
	}
	*/

	/* 在上面的基础上，增加对new分配内存失败的【异常安全性】保证: 就算分不出内存，也不会破坏当前实例的m_pData */
	CMyString& operator=(const CMyString &str)
	{
		if (this != &str) {
			CMyString temp(str);	//通过构造临时实例，将内存分配前清空当前m_pData的问题消除掉
			
			char *temp_c = temp.m_pData;	//从临时实例中提取出分配出来的内存空间
			temp.m_pData = m_pData;
			m_pData = temp_c;
		}

		return *this;
	}

	void output()
	{
		cout << m_pData << endl;
	}

private:
	char *m_pData;
};


int main(int argc, char **argv)
{
	CMyString s1("string1"), s6("string2");
	CMyString s2(s1);
	CMyString s3 = s2, s4 = s1;
	s3 = s4 = s6;
	s3.output();
}
