def round_up_middle (a, b):
    if (a + b) % 2 == 0: return int((a + b) / 2)
    return int((a + b + 1) / 2)
    

class Solution:
    def searchRange(self, nums: List[int], target: int) -> List[int]:
        
        if not nums: return [-1,-1]
        
        left_ptr, right_ptr = 0, len(nums) - 1
        while(left_ptr < right_ptr - 1):
            middle = int((left_ptr + right_ptr) / 2)
            if nums[middle] >= target:
                right_ptr = middle
            else:
                left_ptr = middle
        if nums[left_ptr] == target: ans = [left_ptr]
        elif nums[right_ptr] == target: ans = [right_ptr]
        else: return [-1, -1]
        
        left_ptr, right_ptr = 0, len(nums) - 1
        while(left_ptr < right_ptr - 1):
            middle = round_up_middle (left_ptr, right_ptr)
            if nums[middle] <= target:
                left_ptr = middle
            else:
                right_ptr = middle
        if nums[right_ptr] == target: ans.append(right_ptr)
        else: ans.append(left_ptr)
        
        return ans
