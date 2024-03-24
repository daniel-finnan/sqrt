from decimal import *
import math
import sys

# Using decimal library rather than float, and default of 28 significant places

def closest(x, y, target):
    if abs(target - x**2) < abs(target - y**2):
        return x
    else:
        return y

def recursive(i, j, target):
    try:
        mid = Decimal(i+j)/2
        mid_sq = mid**2
        i_sq = Decimal(i**2)
        if i_sq < target and mid_sq > target:
            interval_1 = True
            recursive(i, mid, target)
        else:
            interval_1 = False
            recursive(mid, j, target)
    except RecursionError:
        if interval_1 == True:
            answer = closest(i, mid, target)
        else:
            answer = closest(mid, j, target)
        print(f'sqrt: {answer}')
        quit()

def sqrt(input):
    for i in range(1, input+1):
        sq = i**2
        if sq == input:
            print(f'sqrt: {i}')
            quit()
        else:
            sq_peek = (i+1)**2
            if sq < input and sq_peek > input:
                recursive(i, i+1, input)

# 42 is the answer to the universe!
sqrt(42)
# How does this compare to math library
#print(math.sqrt(42))
