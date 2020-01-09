/**********************************************************************************************************
* Copyright:             XX Tech.co,Ltd. 2015-. All rights reserved
* File name:		      
* Description:		     求二叉查找树的最大深度 leetcode：https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/ 
* Author:                sky
* Version:               V1.0
* Date:				  
* History:					  
                         1. Date:          2. Author:         3. Modification:
**********************************************************************************************************/
/**
 * 给定一个二叉树，找出其最大深度。

 * 二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。

 * 说明: 叶子节点是指没有子节点的节点。

 * 示例：
 * 给定二叉树 [3,9,20,null,null,15,7]，
 * 
 *  3
 * / \
 * 9  20
 *   /  \
 *  15   7
 * 返回它的最大深度 3 。
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution 
{
public:
    int maxDepth(TreeNode* root) 
    {
        //1.递归解法
        if ( NULL == root )
        {
            return 0;
        }
        
        int iLDepth = maxDepth( root->left );
        int iRDepth = maxDepth( root->right );
        
        return (iLDepth > iRDepth) ? (iLDepth + 1) : (iRDepth + 1);

        //2.非递归解法
        //
    }
};

