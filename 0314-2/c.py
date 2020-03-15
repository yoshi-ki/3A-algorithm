import numpy as np
a,b,c = (int(x) for x in input().split())
if(c-a-b < 0):
    print("No")
else:
    if((c-a-b) * (c-a-b) - 4 * a * b > 0):
        print("Yes")
    else:
        print("No")
