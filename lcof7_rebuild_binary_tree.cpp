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
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
	{
		for (int i = 0; i < inorder.size(); ++i) {
			inmap[inorder[i]] = i;
		}
		return build_by_pre_in(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1);
	}

	/*
	TreeNode* buildTree(vector<int>& postorder, vector<int>& inorder)
	{
		for (int i = 0; i < inorder.size(); ++i) {
			inmap[inorder[i]] = i;
		}
		return build_by_in_post(inorder, 0, inorder.size()-1, postorder, 0, postorder.size()-1);
	}
	*/

	//前序遍历 + 中序遍历	leetcode q105
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
		return root;
	}
	//中序遍历 + 后序遍历	leetcode q106
	TreeNode* build_by_in_post(vector<int> &inorder, int in_start, int in_end,
							   vector<int> postorder, int post_start, int post_end)
	{
		if (in_start > in_end || post_start > post_end) return NULL;

		TreeNode *root = new TreeNode(postorder[post_end]);
		auto got = inmap.find(root->val);
		if (got == inmap.end()) {
			cerr << "ERROR: Not found element [" << root->val << "] in inmap!" << endl;
			exit(-1);
		}
		int in = got->second;
		int left_count = in - in_start;

		root->left = build_by_in_post(inorder, in_start, in-1,
									  postorder, post_start, post_start+left_count-1);
		root->right = build_by_in_post(inorder, in+1, in_end,
									   postorder, post_start+left_count, post_end-1);
		return root;
	}
	
	//前序遍历 + 后序遍历	无法构建，只靠前序和后序序列无法判断左右子树是哪部分序列，构建的二叉树结构不唯一
};

int main(int argc, char **argv)
{
	return 0;
}
