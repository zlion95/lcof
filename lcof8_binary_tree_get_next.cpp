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


TreeNode *get_in_next(TreeNode *node)//获取中序遍历时的下一个节点
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

TreeNode *get_pre_next(TreeNode *node)//获取前序遍历时的下一个节点
{
	if (!node) return NULL;

	TreeNode *next = NULL;
	if (node->left) {//当左子树不为空时，next在左子树的根节点
		next = node->left;
	} else if (node->right) {//当右子树不为空时，next在右子树的根节点
		next = node->right;
	} else {//左右子树为空时，迭代查找父节点
		TreeNode *cur = node, *parent = node->parent;
		while (parent && (cur == parent->right || parent->right == NULL)) {
			cur = parent;
			parent = cur->parent;
		}
		if (parent) next = parent->right;//如果parent不为NULL，说明cur在parent的左子树，parent->right不为NULL
	}
	return next;
}

TreeNode *get_post_next(TreeNode *node)//获取后序遍历时的下一个节点
{
	if (!node) return NULL;

	TreeNode *parent = node->parent;

	if (!parent) return NULL;	//没有parent，没有后续节点
	if (parent->right == node) return parent; //cur在右子树上时，next必定是parent

	//cur在左子树上时，需要迭代查找parent右子树最深的叶子节点
	parent = parent->right;
	while (parent->left || parent->right) {
		if (parent->left) parent = parent->left;
		else parent = parent->right;
	}
	return parent;
}

enum {
	PRE_ORDER = 0,
	IN_ORDER,
	POST_ORDER
};

TreeNode* get_next(TreeNode *node, int type)//根据遍历方式获取下一个节点
{
	TreeNode *next = NULL;
	switch (type) {
	case PRE_ORDER:
		next = get_pre_next(node);
		break;
	case IN_ORDER:
		next = get_in_next(node);
		break;
	case POST_ORDER:
		next = get_post_next(node);
		break;
	default:
		cerr << "Error: Unknown traversal type: " << type << "!" << endl;
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

	int type;
	cin >> type;
	cout << "Next: ";
	TreeNode *next = get_next(dest, type);
	if (next) cout << next->val << endl;
	else cout << "null" << endl;
	return 0;
}
