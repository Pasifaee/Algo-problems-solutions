def DFS(a,b,vis,brd):
    if(vis[a][b]==True or brd[a][b]=='X'):
        return
    vis[a][b] = True
    for i in range(0,4):
        if(a-1>=0 and brd[a-1][b]=='O' and vis[a-1][b]==False):
            DFS(a-1,b,vis,brd)
        if(a+1<len(brd) and brd[a+1][b]=='O' and vis[a+1][b]==False):
            DFS(a+1,b,vis,brd)
        if(b-1>=0 and brd[a][b-1]=='O' and vis[a][b-1]==False):
            DFS(a,b-1,vis,brd)
        if(b+1<len(brd[0]) and brd[a][b+1]=='O' and vis[a][b+1]==False):
            DFS(a,b+1,vis,brd)
        
            

class Solution:
    def solve(self, board: List[List[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        if(len(board)==0):
            return
        print(len(board),len(board[0]))
       
        visited = [[False] * len(board[0]) for i in range(0,len(board))]
        for i in range(0,len(board)):
            DFS(i,0,visited,board)
            DFS(i,len(board[0])-1,visited,board)
        for i in range(1,len(board[0])-1):
            DFS(0,i,visited,board)
            DFS(len(board)-1,i,visited,board)
            
            
        print(visited)
        for i in range(0,len(board)):
            for j in range(0,len(board[0])):
                if(visited[i][j]==False):
                    board[i][j]='X'
               
                   
