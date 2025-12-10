/*
  When an object moves at 1 unit per second in a grid or line:
  It moves along diagonals in the (position, time) space.
  These diagonals help model behavior efficiently.
*/    
    Right diagonal (x-y)                                
       0   1   2   3   4
     ---------------------
  t=0 | 0  -1  -2  -3  -4
  t=1 | 1   0  -1  -2  -3
  t=2 | 2   1   0  -1  -2
  t=3 | 3   2   1   0  -1
  t=4 | 4   3   2   1   0

     Left Diagonal  (x+y) 
       0   1   2   3   4
     ---------------------
  t=0 | 0   1   2   3   4
  t=1 | 1   2   3   4   5
  t=2 | 2   3   4   5   6
  t=3 | 3   4   5   6   7
  t=4 | 4   5   6   7   8

