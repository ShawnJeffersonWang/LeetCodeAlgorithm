//
// Created by shawn on 23-11-2.
//
#include <vector>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right)
            : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode *traversel(vector<int> &inorder, vector<int> &postorder) {
        if (postorder.size() == 0) return nullptr;
        int value = postorder[postorder.size() - 1];
        TreeNode *root = new TreeNode(value);
        if (postorder.size() == 1) return root;
        int delimiterIndex;
        for (delimiterIndex = 0; delimiterIndex < inorder.size();
             delimiterIndex++) {
            if (inorder[delimiterIndex] == value) {
                break;
            }
        }
        vector<int> leftInorder(inorder.begin(),
                                inorder.begin() + delimiterIndex);
        vector<int> rightInorder(inorder.begin() + delimiterIndex + 1,
                                 inorder.end());
        postorder.resize(postorder.size() - 1);
        vector<int> leftPostorder(postorder.begin(),
                                  postorder.begin() + leftInorder.size());
        vector<int> rightPostorder(postorder.begin() + leftInorder.size(),
                                   postorder.end());
        root->left = traversel(leftInorder, leftPostorder);
        root->right = traversel(rightInorder, rightPostorder);
        return root;
    }

    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        if (inorder.empty() || postorder.empty()) return nullptr;
        return traversel(inorder, postorder);
    }
};