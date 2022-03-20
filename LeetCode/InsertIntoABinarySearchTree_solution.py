# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def insertIntoBST(self, root: TreeNode, val: int) -> TreeNode:
        def helper(node, value):
            if(node.val<value and not node.right):
                node.right = TreeNode(value)
            if(node.val<value):
                helper(node.right,value)
            if(node.val>value and not node.left):
                node.left = TreeNode(value)
            if(node.val>value):
                helper(node.left,value)
        if not root:
            return TreeNode(val)
        helper(root,val)
        return root
