# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
def inordTrav(root,List):
    if(root.left!=None):
        inordTrav(root.left,List)
    
    if(root.val!=None):
        List.append(root.val)
        root.val = None
    
    if(root.right!=None):
        inordTrav(root.right,List)

class Solution:
    def inorderTraversal(self, root: TreeNode) -> List[int]:
        List = []
        
        if(root!=None):
            inordTrav(root,List)
        return List
