#include <iostream>
#include "linked_list.h"

using namespace std;

bool insert_n(ListNode *head, int index, int val)
{
	if (!head) return false;//由于哨兵技巧的存在，这里正常使用不应该出现空指针

	int i = 0;
	ListNode *pnew = new ListNode(val), *cur = head;

	while (i++ != index && cur->next) {
		cur = cur->next;
	}
	pnew->next = cur->next;
	cur->next = pnew;
	return true;
}

bool delete_n(ListNode *head, int index)
{
	if (!head || index < 0) return false;

	int i = 0;
	ListNode *todelete = NULL, *cur = head;
	while (i++ != index && cur->next) {
		cur = cur->next;
	}

	if (i > index) {//index未超出或刚好等于尾节点索引
		todelete = cur->next;
		if (todelete) {//cur不能刚好是尾部节点
			cur->next = todelete->next;
			delete[] todelete;
		}
	}
	return true;
}

bool reverse(ListNode *head)
{
	if (!head) return false;
	ListNode *cur = head->next, *rhead = new ListNode(0), *temp;
	while (cur) {
		temp = cur;
		cur = cur->next;
		temp->next = rhead->next;
		rhead->next = temp;
	}
	head->next = rhead->next;
	delete[] rhead;
	return true;
}

int main(int argc, char **argv)
{
	int n, val, action;
	ListNode *head = new ListNode(0), *tail = head;//创建一个哨兵head节点，消除head的特殊操作

	cin >> n;
	while (n-- > 0) {
		cin >> val;
		tail->next = new ListNode(val);
		tail = tail->next;
	}

	cin >> action;
	switch (action) {
	case 0://NOTHING
		break;
	case 1://INSERT
		cin >> n >> val;
		cout << "Insert val: " << val << " into index: " << n << " ret: " << insert_n(head, n, val) << endl;
		break;
	case 2://DELETE
		cin >> n;
		cout << "Delete index: " << n << " ret: " << delete_n(head, n) << endl;
		break;
	case 3://REVERSE
		cout << "Reverse ret: " << reverse(head) << endl;
		break;
	default:
		cerr << "Error Action!" << endl;
		return -1;
	}
	printList(head->next);
	return 0;
}
