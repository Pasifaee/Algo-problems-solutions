# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
def preordTrav(root,List):
    if(root.val!=None):
        List.append(root.val)
        root.val = None
    if(root.left!=None):
        preordTrav(root.left,List)
    if(root.right!=None):
        preordTrav(root.right,List)
class Solution:
    def preorderTraversal(self, root: TreeNode) -> List[int]:
        List = []
        
        if(root!=None):
            preordTrav(root,List)
        return List
        
