"""
# Definition for a Node.
class Node:
    def __init__(self, val: int = 0, left: 'Node' = None, right: 'Node' = None, next: 'Node' = None):
        self.val = val
        self.left = left
        self.right = right
        self.next = next
"""

class Solution:
    def connect(self, root: 'Node') -> 'Node':
        
        curr_node = root
        if not root or not root.left: return root 
        queue = [root.left, root.right]
        iterator, curr_exp = 1, 0
        while queue:
            prev_node = curr_node
            curr_node = queue.pop(0)
            iterator += 1
                
            if curr_node.left is not None:
                queue.append(curr_node.left)
                queue.append(curr_node.right)
                
            if iterator == 2**(curr_exp + 1): 
                curr_exp += 1
                continue
                
            prev_node.next = curr_node
            
        return root
                
            
            
            
            
