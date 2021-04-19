class Solution:
    def maxArea(self, height: List[int]) -> int:
        
        left = 0
        right = len(height) - 1
        waterArea = min(height[left],height[right])*(right-left)
        maxArea = waterArea
        
        while(right - left > 0):
            if(height[left] <= height[right]):
                left += 1
                waterArea = min(height[left],height[right])*(right-left)
            else:
                right -= 1
                waterArea = min(height[left],height[right])*(right-left)
            if(waterArea > maxArea):
                maxArea = waterArea
        
        return maxArea
