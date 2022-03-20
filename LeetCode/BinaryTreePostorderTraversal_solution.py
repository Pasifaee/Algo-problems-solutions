# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
def postordTrav(root,List):
    
    if(root.left!=None):
        postordTrav(root.left,List)
    if(root.right!=None):
        postordTrav(root.right,List)
    if(root.val!=None):
        List.append(root.val)
        root.val = None

class Solution:
    def postorderTraversal(self, root: TreeNode) -> List[int]:
        List = []
        
        if(root!=None):
            postordTrav(root,List)
        return List
        
