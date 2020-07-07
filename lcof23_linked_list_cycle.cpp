#include <iostream>
#include "linked_list.h"

using namespace std;

bool has_cycle(ListNode *head) 
{
	if (!head) return false;

	ListNode *slow = head, *fast = head->next;
	while (slow && fast) {//设置一快，一慢的指针，交汇就说明有环存在
		if (slow == fast) return true;
		slow = slow->next;
		fast = fast->next;
		if (fast) fast = fast->next;
	}
	return false;
}

ListNode* entry_node_of_loop(ListNode *head)
{
	if (!head) return NULL;
	
	//获取环检查得到的meeting节点
	ListNode *slow = head, *fast = head->next;
	while (slow && fast) {
		if (slow == fast) break;
		slow = slow->next;
		fast = fast->next;
		if (fast) fast = fast->next;
	}
	if (!slow || !fast) return NULL;
	
	int count_loop_node = 1;
	while (fast->next != slow) {//检查环有多少个节点
		fast = fast->next;
		++count_loop_node;
	}
	cout << "loop count: " << count_loop_node << endl;

	slow = head;//p1先移动环大小的步数
	for (int i = 0; i < count_loop_node; ++i) slow = slow->next;

	fast = head;
	while (slow != fast) {//两指针同时走，由于p1先走了loopcount步，因此必定与p2交汇于入口节点
		slow = slow->next;
		fast = fast->next;
	}

	return fast;
}

int main(int argc, char **argv)
{
	int n;
	string str;
	ListNode *head = new ListNode(0), *cur = head, *to_link = NULL;

	cin >> n;
	while (n) {
		cin >> str;
		if (str == "*") {
			to_link = cur;

		} else {
			cur->next = new ListNode(stoi(str));
			cur = cur->next;
			--n;
		}
		cout << str << " ";
	}
	cout << endl;

	if (to_link) cur->next = to_link;
	cout << "linked_list has cycle: " << (has_cycle(head->next)?"yes":"no") << endl;
	cur = entry_node_of_loop(head->next);
	cout << "Entry of loop is: ";
	if (cur) cout << cur->val << endl;
	else cout << "NONE" << endl;

	return 0;
}
