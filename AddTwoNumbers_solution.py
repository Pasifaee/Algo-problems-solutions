# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> ListNode:
        
        number1_rev = []
        number1 = 0
        number2_rev = []
        number2 = 0
        
        
        node = l1
        while(node != None):
            number1_rev.append(node.val)
            node = node.next
        for i in range(len(number1_rev)):
            j = -i-1
            number1 *= 10
            number1 += number1_rev[j]
        
        node = l2
        while(node != None):
            number2_rev.append(node.val)
            node = node.next
        for i in range(len(number2_rev)):
            j = -i-1
            number2 *= 10
            number2 += number2_rev[j]
            
        number3 = int(number1 + number2)
        l3 = ListNode(number3%10)
        node = l3
        print(number1, number2, number3)
        number3 = number3//10
        print(number3)
        while(number3 != 0):
            node.next = ListNode()
            node = node.next
            node.val = number3%10
            number3 = int(number3//10)
        
        return l3
