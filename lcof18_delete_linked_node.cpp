#include <iostream>
#include <exception>
#include "linked_list.h"

using namespace std;

struct NotFountException : public exception
{
	const char* what() const throw() {
		return "Invalid to delete node!";
	}
};

//最好时间复杂度：对于n大小的链表，对于非链表尾节点的节点，可以O(1)时间内删除
//最差时间复杂度：而对于尾部节点，则需要遍历与整个链表找到前序节点O(n)时间
//平均时间复杂度：[O(n) + (n-1)*O(1)] / n = O(1)
ListNode* delete_node(ListNode *head, ListNode *to_delete)
{
	if (!head || !to_delete) return head;

	if (to_delete->next != NULL) {//删除节点后面还有其他节点，替换即可
		ListNode *next = to_delete->next;
		to_delete->val = next->val;
		to_delete->next = next->next;
		delete next;
	} else if (to_delete == head) {//后面无节点，且只有一个to_delete一个节点
		delete to_delete;
		head = NULL;
	} else {//to_delete后无节点，前面至少有一个节点，只能顺序查找到前序节点，再来删除
		ListNode *pre = head;
		while (pre && pre->next != to_delete) {
			pre = pre->next;
		}
		if (!pre) {//遍历完链表却没有找到to_delete节点，正常使用中不应该出现这种状况，属于异常情况，上层调用存在问题，抛出异常比较合适，让程序终止，避免继续使用引发更大的风险
			throw NotFountException();
		}
		pre->next = to_delete->next;
		delete to_delete;
	}
	return head;
}

int main(int argc, char **argv)
{
	int n, val;
	ListNode *head = new ListNode(0), *cur = head;
	
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> val;
		cur->next = new ListNode(val);
		cur = cur->next;
	}
	printList(head);
	cin >> val;
	cout << "need: to delete: " << val << endl;
	cur = head->next;
	while (cur && cur->val != val) {
		cur = cur->next;
	}
	if (!cur) cur = new ListNode(val);
	try {
		head->next = delete_node(head->next, cur);
	} catch (NotFountException e) {
		cout << e.what() << endl;
		exit(-1);
	}
	printList(head);
	return 0;
}
