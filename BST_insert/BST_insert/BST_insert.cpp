// BST_insert.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<vector>
struct TreeNode
{
	int  val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x):val(x),left(NULL),right(NULL){}

};

//递归使用
void BST_insert(TreeNode *node, TreeNode *insert_node) {
	if (insert_node->val<node->val)//当左子树不空的时候
	{
		if (node->left)
		{
			BST_insert(node->left, insert_node);//递归的将insert_node插入左子树
		}
		else//当左子树为空时，将node左指针的与待插入节点连接
		{
			node->left = insert_node;
		}
		
	}
	else//当右子树不为空的时候，递归的将insert_node插入右子树
	{
		if (node->right)
		{
			BST_insert(node->right, insert_node);
		}
		else//当右子树为空时，将node的右指针与待插入节点相连
		{
			node->right = insert_node;
		}
	}
}
//循环使用
//void BST_insert(TreeNode *node, TreeNode *insert_node)
//{
//	while (node != insert_node)
//	{
//		if (insert_node->val<node->val)
//		{
//			if (!node->left)
//			{
//				node->left = insert_node;
//			}
//			node = node->left;
//		}
//		else
//		{
//			if (!node->right)
//			{
//				node->right = insert_node;
//			}
//			node = node->right;
//		}
//		
//	}
//}
//二叉树的前序遍历
void preorder_print(TreeNode *node, int layer)
{
	if (!node)
	{
		return;
	}
	for (int i = 0; i < layer; i++)
	{
		printf("----------------------");
	}
	printf("[%d]\n", node->val);
	preorder_print(node->left, layer + 1);
	preorder_print(node->right, layer + 1);
}
//二叉查找树查找数值，递归
bool BST_search(TreeNode *node, int value)
{
	if (node->val == value)
	{
		return true;
	}
	if (value<node->val)
	{
		if (node->left)
		{
			return BST_search(node->left, value);
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (node->right)
		{
			return BST_search(node->right, value);
		}
		else
		{
			return false;
		}
	}
}
//二叉查找树查找数值，循环
//bool BST_search(TreeNode *node, int value)
//{
//	while (node)
//	{
//		if (node->val == value)
//		{
//			return true;
//		}
//		if (value<node->val)
//		{
//			node = node->left; 
//		}
//		else
//		{
//			node = node->right;
//		}
//	}
//	return false;
//
//}
void preorder_insert(const std::vector<int> &nums, std::vector<TreeNode *> &node_vec, int begin, int end)
{
	if (begin>end)
	{
		return;
	}
	int mid = (begin + end) / 2;
	node_vec.push_back(new TreeNode(nums[mid]));
	preorder_insert(nums, node_vec, begin, mid - 1);
	preorder_insert(nums, node_vec, mid+1, end);
}
class  Solution
{
public:
	TreeNode *sortedArrayToBST(std::vector<int>& nums)
	{
		if (nums.size()==0)
		{
			return NULL;
		}
		std::vector<TreeNode *>node_vec;
		preorder_insert(nums, node_vec, 0, nums.size() - 1);
		for (int i = 0; i < node_vec.size(); i++)
		{
			BST_insert(node_vec[0], node_vec[i]);
		}
		return node_vec[0];
	}

private:

};
class Solution2
{
public:
	TreeNode *deleteNode(TreeNode* root, int key)
	{

	}
	
	

private:

};
void delete_node(TreeNode *parent, TreeNode *node)
{
	if (node->val<parent->val)
	{
		if (node->left && !node->right)
		{
			parent->left = node->left;
		}
		else if (!node->left && node->right)
		{
			parent->left = node->right;
		}
		else
		{
			parent->left = NULL;
		}
	}
	else if (node->val > parent->val)
	{
		if (node->left && !node->right)
		{
			parent->right = node->left;
		}
		else if (!node->left && node->right)
		{
			parent->right = node->right;
		}
		else
		{
			parent->right = NULL;
		}
	}
}
TreeNode * BST_search(TreeNode *node, int value, TreeNode *&parent)
{
	while (node)
	{
		if (node->val == value)
		{
			break;
		}
		parent = node;//记录父节点
		if (value<node->val)
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
	}
	return node;
}
TreeNode * find_successor(TreeNode *node, TreeNode *&parent)
{
	parent = node;
	TreeNode *ptr = node->right;
	while (ptr->left)
	{
		parent = ptr;
		ptr = ptr->left;
	}
	return ptr;
}

class Solution3 {
public:
	TreeNode *deleteNode(TreeNode *root, int key)
	{
		TreeNode *parent = NULL;
		TreeNode *node = BST_search(root,key,parent);
		if (!node)
		{
			return root;
		}
		if (node->left && node->right )
		{
			TreeNode *successor = find_successor(node, parent);
			delete_node(parent, successor);
			node->val = successor->val;
			return root;
		}
		if (parent)
		{
			delete_node(parent, node);
			return root;
		}
		if (node->left)
		{
			root = node->left;
		}
		else
		{
			root = node->left;
		}
		return root;
	}
};

int main()
{
	for (int i = 0; i < 7; i++)
	{
		printf("key = %d\n", i);

		TreeNode a(5);
		TreeNode b(3);
		TreeNode c(6);
		TreeNode d(2);
		TreeNode e(4);
		TreeNode f(7);
		a.left = &b;
		a.right = &c;
		b.left = &d;
		b.right = &e;
		c.right = &f;
		Solution3 solve;
		TreeNode * root = solve.deleteNode(&a,i);
		preorder_print(root, 0);
		printf("\n");
	}
	//TreeNode root(8);//以8为根的二叉树
	//std::vector<TreeNode *>node_vec;
	//int test[] = { 3,10,1,6,15 };
	//for (int i = 0; i < 5; i++)
	//{
	//	node_vec.push_back(new TreeNode(test[i]));
	//}
	//for (int i = 0; i < node_vec.size(); i++)
	//{
	//	BST_insert(&root, node_vec[i]);
	//}
	//preorder_print(&root, 0);
	/*TreeNode a(8);
	TreeNode b(3);
	TreeNode c(10);
	TreeNode d(1);
	TreeNode e(6);
	TreeNode f(15);
	a.left = &b;
	a.right = &c;
	b.left = &d;
	b.right = &e;
	c.right = &f;
	for (int i = 0; i < 20; i++)
	{
		if (BST_search(&a,i))
		{
			printf("%d is in the BST.\n", i);
		}
		else
		{
			printf("%d is not in the BST.\n", i);
		}
	}*/
	/*int test[] = { -10,-3,0,5,9 };
	std::vector<int>nums;
	for (int i = 0; i < 5; i++)
	{
		nums.push_back(test[i]);
	}
	Solution solve;
	TreeNode* root = solve.sortedArrayToBST(nums);
	preorder_print(root, 0);*/
    return 0;
}

