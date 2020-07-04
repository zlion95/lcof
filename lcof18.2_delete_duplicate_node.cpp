#include <iostream>
#include <climits>
#include "linked_list.h"

using namespace std;

ListNode* delete_duplicate(ListNode *head)
{
	if (!head) return NULL;

	ListNode *phead = new ListNode(INT_MAX);
	ListNode *pre = phead, *cur = head, *next;

	phead->next = head;
	bool to_delete = false;
	while (cur) {
		next = cur->next;
		if (next && next->val == cur->val) {//有重复节点，但现在只删除next，不删除cur，避免后面继续出现需要删除的节点
			to_delete = true;
			cur->next = next->next;
			delete next;
		} else if (to_delete) {//next为NULL或next不等于cur，但cur是之前标记需要删除的节点
			cur = cur->next;
			delete pre->next;
			pre->next = cur;
			to_delete = false;
		} else {//next为NULL或next不等于cur，cur也没有被标记需要删除
			pre = cur;				//pre节点应该时刻维护作为不一样的前序节点
			cur = cur->next;
		}
	}
	return phead->next;
}


int main(int argc, char **argv)
{
	ListNode *head = new ListNode(0), *cur = head;
	int n;

	cin >> n;
	for (int i = 0; i < n; ++i) {
		cur->next = new ListNode(0);
		cur = cur->next;
		cin >> cur->val;
	}
	head->next = delete_duplicate(head->next);
	printList(head);
	return 0;
}
