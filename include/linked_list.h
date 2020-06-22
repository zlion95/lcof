/* *
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
 
inline void printList(ListNode *head) {
    ListNode *p = head;
    std::cout << "List: [";
    if (p) {
        while (p->next) {
            std::cout << p->val << ", ";
            p = p->next;
        }
        std::cout << p->val << "]" << std::endl;
    } else {
        std::cout << "]" << std::endl;
    }
}
