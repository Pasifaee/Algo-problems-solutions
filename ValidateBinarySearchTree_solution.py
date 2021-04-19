# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

def isBST(node, lower=-float('inf'), upper=float('inf')):
    if not node:
        return True
    
    if(node.val<=lower or node.val>=upper):
        return False
    if not isBST(node.left, lower, node.val):
        return False
    if not isBST(node.right, node.val, upper):
        return False
    
    return True
    
    

class Solution:
    def isValidBST(self, root: TreeNode) -> bool:
        return isBST(root)
