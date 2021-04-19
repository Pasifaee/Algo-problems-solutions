# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def sortedListToBST(self, head: ListNode) -> TreeNode:
        if head == None:
            return None
        helper, pnt1, pnt2 = None, head, head.next
        while pnt2 != None:
            if pnt2.next == None: break
            helper = pnt1
            pnt1 = pnt1.next
            pnt2 = pnt2.next.next
        value = pnt1.val
        print (value)
        head_right = pnt1.next
        if not helper: head_left = None
        else: 
            helper.next = None 
            head_left = head
        solution = TreeNode(value)
        solution.left = self.sortedListToBST(head_left)
        solution.right = self.sortedListToBST(head_right)
        return solution
