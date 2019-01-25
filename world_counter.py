import operator as op
from functools import reduce

def ncr(n, r):
    r = min(r, n-r)
    numer = reduce(op.mul, range(n, n-r, -1), 1)
    denom = reduce(op.mul, range(1, r+1), 1)
    return int(numer / denom)

f = open("chart.txt")
world_count = 0;
for n in range(13):
    row = f.readlines()
    for j in range(65):
        world_count += (3**n)*(2**n)*((n+1)**6)*ncr(j,n)
print(world_count)

