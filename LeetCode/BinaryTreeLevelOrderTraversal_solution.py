# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def levelOrder(self, root: TreeNode) -> List[List[int]]:
        List = []
        if not root:
            return List
        stack1 = [root]
        stack2 = []
        
        while stack1:
            for node in stack1:
                if node.left:
                    stack2.append(node.left)
                if node.right:
                    stack2.append(node.right)
        
            List.append([node.val for node in stack1])
            stack1 = stack2
            stack2 = []
        
        return List
        
        
