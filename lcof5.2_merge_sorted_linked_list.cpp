#include <iostream>
#include "linked_list.h"

using namespace std;

ListNode* merge(ListNode *l1, ListNode *l2)
{
	if (!l1 && !l2) return NULL;

	ListNode *phead = new ListNode(0), *cur = phead, *p1 = l1, *p2 = l2;
	while (p1 && p2) {
		if (p1->val <= p2->val) {
			cur->next = p1;
			p1 = p1->next;
		} else {
			cur->next = p2;
			p2 = p2->next;
		}
		cur = cur->next;
		//cur->next = NULL;
	}
	if (p1) cur->next = p1;
	if (p2) cur->next = p2;

	return phead->next;
}

int main(int argc, char **argv)
{
	int m, n, value;
	ListNode *head1 = new ListNode(0), *head2 = new ListNode(0), *cur;

	cin >> m;
	cur = head1;
	while (m--) {
		cin >> value;
		cur->next = new ListNode(value);
		cur = cur->next;
		cout << value << " ";
	}
	cout << endl;

	cin >> n;
	cur = head2;
	while (n--) {
		cin >> value;
		cur->next = new ListNode(value);
		cur = cur->next;
		cout << value << " ";
	}
	cout << endl;
	
	head1 = merge(head1->next, head2->next);
	printList(head1);
	return 0;
}
