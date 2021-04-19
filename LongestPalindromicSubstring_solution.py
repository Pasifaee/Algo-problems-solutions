class Solution:
    def longestPalindrome(self, s: str) -> str:
        
        if(s==''):
            return ''
        
        maxLength = 1
        even = True
        theMiddle = 0
        for i in range(0,len(s)-1):
            
            if(s[i]==s[i+1]): 
                if(maxLength < 2):
                    theMiddle = i
                    maxLength = 2
                    even = True
                it = 1
                while(i-it >= 0 and i+it+1 < len(s)):
                    
                    if(s[i-it]!=s[i+it+1]):
                        if(maxLength < it*2):
                            maxLength = it*2
                            even = True
                            theMiddle = i
                        break
                    it += 1
                    if(maxLength < it*2):
                        maxLength = it*2
                        even = True
                        theMiddle = i
                        
                
            if(s[i-1]==s[i+1] and i != 0):
                if(maxLength < 3):
                    theMiddle = i
                    maxLength = 3
                    even = False
                it = 2
                while(i-it >= 0 and i+it < len(s)):
                        
                    if(s[i-it]!=s[i+it]):
                        if(maxLength < (it-1)*2+1):
                            maxLength = (it-1)*2+1
                            even = False
                            theMiddle = i
                        break
                    it += 1
                    if(maxLength < (it-1)*2+1):
                        maxLength = (it-1)*2+1
                        even = False
                        theMiddle = i
        
        if(maxLength==1):
            return s[0]
        
        if(even):
            result = ''
            for i in range(int(-maxLength/2)+1, int(maxLength/2)+1):
                result += s[theMiddle+i]
            return result
        
        if(not even):
            result = ''
            for i in range(int(-(maxLength-1)/2), int((maxLength-1)/2)+1):
                result += s[theMiddle+i]
            return result
                           
