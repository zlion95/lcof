#include <iostream>
#include "linked_list.h"

using namespace std;

ListNode* reverse(ListNode *head)
{
	if (!head) return NULL;
	ListNode *cur = head, *rhead = new ListNode(0), *temp;//使用哨兵技巧，避免循环里面需要判断尾部节点
	while (cur) {
		temp = cur;
		cur = cur->next;
		temp->next = rhead->next;//将cur节点插入到rhead头部，从而实现了逆序
		rhead->next = temp;
	}
	cur = rhead->next;
	delete rhead;
	return cur;
}

int main(int argc, char **argv)
{
	int n, val;
	ListNode *head = new ListNode(0), *tail = head;

	cin >> n;
	while (n-- > 0) {
		cin >> val;
		tail->next = new ListNode(val);
		tail = tail->next;
		cout << val << " ";
	}
	cout << endl;
	tail = reverse(head->next);
	printList(tail);
	return 0;
}
