#include <iostream>
#include <vector>
#include <stack>
#include "linked_list.h"

using namespace std;

class Solution
{
public:
	//要求不能修改链表结构
	//解法1：栈
	//时间复杂度：O(n) 空间复杂度：O(n)
	vector<int> reversePrint(ListNode *head)
	{
		stack<int> st;
		vector<int> output;
		ListNode *cur = head;
		while (cur) {
			st.push(cur->val);
			cur = cur->next;
		}
		while (!st.empty()) {
			output.push_back(st.top());
			st.pop();
		}
		return output;
	}

	//解法2：递归		缺点：如果递归层次太深就会崩溃
	//时间复杂度：O(n) 空间复杂度：O(n)
	/*
	vector<int> reversePrint(ListNode *head)
	{
		vector<int> output;
		traversal(output, head);
		return output;
	}
	void traversal(vector<int> &output, ListNode *cur)
	{
		if (cur) {
			traversal(output, cur->next);
			output.push_back(cur->val);
		}
	}
	*/

	//可以修改链表结构
	//解法1：链表逆序再输出
	//时间复杂度：O(n) 空间复杂度：O(1)
	/*
	vector<int> reversePrint(ListNode *head)
	{
		int count = 0;
		vector<int> res;
		ListNode *phead = new ListNode(0), *cur = head, *temp;

		while (cur) {
			temp = cur;
			cur = cur->next;
			temp->next = phead->next;
			phead->next = temp;
			++count;
		}
		cur = phead->next;
		res.assign(count, 0);
		auto it = res.begin();
		while (cur) {
			*it = cur->val;
			cur = cur->next;
		}
		return res;
	}
	*/
};

int main(int argc, char **argv)
{
	return 0;
}
