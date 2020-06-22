#include <iostream>
#include <unordered_map>
#include <vector>
#include "tree.h"

using namespace std;

class Solution
{
private:
	unordered_map<int, int> inmap;
public:
	//前序遍历 + 中序遍历
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
	{
		for (int i = 0; i < inorder.size(); ++i) {
			inmap[inorder[i]] = i;
		}
		return build_by_pre_in(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1);
	}

	//q105
	TreeNode* build_by_pre_in(vector<int> &preorder, int pre_start, int pre_end, 
							  vector<int> inorder, int in_start, int in_end)
	{
		if (pre_start > pre_end || in_start > in_end) return NULL;

		TreeNode *root = new TreeNode(preorder[pre_start]);
		auto got = inmap.find(root->val);
		if (got == inmap.end()) {
			cerr << "ERROR: Not found element [" << root->val << "] in inmap!" << endl;
			exit(-1);
		}
		int in = got->second;
		int left_count = in - in_start;
		
		root->left = build_by_pre_in(preorder, pre_start+1, pre_start+left_count,
									 inorder, in_start, in-1);
		root->right = build_by_pre_in(preorder, pre_start+left_count+1, pre_end,
									  inorder, in+1, in_end);
	}
	//q106
	//TreeNode* build_by_in_post(vector<int> &inorder, vector<int> postorder);
};

int main(int argc, char **argv)
{
	return 0;
}
