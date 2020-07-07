#include <iostream>
#include "linked_list.h"

using namespace std;

ListNode* get_medium(ListNode *head)
{
	if (!head) return NULL;

	ListNode *pfront = head, *pback = head;
	int count = 1;
	while (pfront->next) {
		++count;
		pfront = pfront->next;
		if (count&1) pback = pback->next;
	}
	return pback;
}

int main(int argc, char **argv)
{
	int n, value;
	ListNode *head = new ListNode(0), *cur = head;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> value;
		cur->next = new ListNode(value);
		cur = cur->next;
		cout << value << " ";
	}
	cout << endl;
	cur = get_medium(head->next);
	if (cur)
		cout << cur->val << endl;
	else
		cout << "NULL" << endl;
	return 0;
}
