import heapq

class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        
        frequencies = {}
        for i in range(len(nums)):
            if not frequencies.get(nums[i]):
                frequencies[nums[i]] = 1
            else:
                frequencies[nums[i]] += 1
        
        nums_upd = []
        for frequency in frequencies:
            nums_upd.append((frequencies[frequency], frequency))
            
        k_largest = nums_upd[:k]
        nums_upd = nums_upd[k:]
        heapq.heapify(k_largest)
        for num in nums_upd:
            if num[0] > k_largest[0][0]:
                heapq.heappop(k_largest)
                heapq.heappush(k_largest, num)
                
        ans = []
        for element in k_largest:
            ans.append(element[1])
            
        return ans
        
