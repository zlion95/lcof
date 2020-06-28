#include <iostream>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
	TreeNode *parent;
	TreeNode(int x) : val(x), left(NULL), right(NULL), parent(NULL) {}
    TreeNode(int x, TreeNode *t_left, TreeNode *t_right, TreeNode *t_parent)
		: val(x), left(t_left), right(t_right), parent(t_parent) {}
};

inline std::string treeNodeToString(TreeNode* root) {
    if (!root) return "[]";

    std::string output = "";
    std::queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        if (node == nullptr) {
          output += "null, ";
          continue;
        }

        output += std::to_string(node->val) + ", ";
        q.push(node->left);
        q.push(node->right);
    }
    return "[" + output.substr(0, output.length() - 2) + "]";
}

TreeNode *get_next(TreeNode *node)
{
	if (!node) return NULL;

	TreeNode *next = NULL;
	if (node->right) {//当右子树不为空时，next在右子树的最左节点
		TreeNode *right = node->right;
		while (right->left) right = right->left;
		next = right;
	} else if (node->parent) {//当右子树为空，需要回退到parent去找
		TreeNode *cur = node, *parent = node->parent;
		while (parent && cur == parent->right) {//如果cur是parent的右子树，则需要继续回退到parent的parent去找next
			cur = parent;
			parent = cur->parent;
		}//如果parent不为NULL，则说明此时cur为parent的左子树节点，next为parent
		next = parent;
	}
	return next;
}

int main(int argc, char **argv)
{
	TreeNode *root = new TreeNode(0), *cur = root, *dest = NULL;
	string input, slice;
	queue<TreeNode *> q;

	root->left = NULL;
	root->right = root;

	getline(cin, input);
	input += ' ';
	for (auto &c : input) {
		if (c != ' ') {
			slice += c;
			continue;
		}
		if (slice.empty()) continue;//去除多余的空格

		if (slice != "null") {
			TreeNode *insert = new TreeNode(stoi(slice), root, root, cur);
			if (slice[slice.size()-1] == '*') dest = insert;//需要find_next的节点

			if (cur->left == root) {
				cur->left = insert;
				q.push(cur->left);
			} else if (cur->right == root) {
				cur->right = insert;
				q.push(cur->right);
				if (!q.empty()) {
					cur = q.front();
					q.pop();
				} else {
					break;
				}
			} else {
				cerr << "Error input!" << endl;
				exit(-1);
			}
		} else {
			if (cur->left == root) {
				cur->left = NULL;
			} else if (cur->right == root) {
				cur->right = NULL;
				if (!q.empty()) {
					cur = q.front();
					q.pop();
				} else {
					break;
				}
			} else {
				cerr << "Error input!" << endl;
				exit(-1);
			}
		}
		slice = "";
	}
	if (cur->left == root) cur->left = NULL;
	if (cur->right == root) cur->right = NULL;
	while (!q.empty()) {
		cur = q.front();
		q.pop();
		cur->left = NULL;
		cur->right = NULL;
	}
	root->right->parent = NULL;
	cout << "tree: " << treeNodeToString(root->right) << endl;

	cout << "Next: ";
	TreeNode *next = get_next(dest);
	if (next) cout << next->val << endl;
	else cout << "null" << endl;
	return 0;
}
