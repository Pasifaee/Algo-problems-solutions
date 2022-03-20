import heapq

class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        
        
        heap = nums[:k]
        heapq.heapify(heap)
        for i in nums[k:]:
            if heap[0] < i:
                heapq.heappop(heap)
                heapq.heappush(heap, i)
                
        return heap[0]
