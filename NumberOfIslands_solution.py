class Solution:
    
    def islandDFS(self, grid, visited, row, clm):
        
        if visited[row][clm] == True: return visited
        visited[row][clm] = True
        
        if row - 1 >= 0:
            self.islandDFS(grid, visited, row - 1, clm)
        if row + 1 < len(grid):
            self.islandDFS(grid, visited, row + 1, clm)
        if clm - 1 >= 0:
            self.islandDFS(grid, visited, row, clm - 1)
        if clm + 1 < len(grid[0]):
            self.islandDFS(grid, visited, row, clm + 1)
        return
    
    def numIslands(self, grid: List[List[str]]) -> int:
        
        visited = [ [False]*len(grid[0]) for i in range(len(grid)) ]
        
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] == "0": visited[i][j] = True
        
        num_islands = 0
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if visited[i][j] == False:
                    num_islands += 1
                    self.islandDFS(grid, visited, i, j)
                    
        return num_islands
