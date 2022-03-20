import heapq

class Solution:
    def nthUglyNumber(self, n: int) -> int:
        seen = {1}
        heap = [1]
        
        for _ in range(n):
            curr_ugly = heapq.heappop(heap)
            for i in [2, 3, 5]:
                new_ugly = curr_ugly * i
                if not new_ugly in seen:
                    seen.add(new_ugly)
                    heapq.heappush(heap, new_ugly)
                    
        return curr_ugly
