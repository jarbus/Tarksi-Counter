import operator as op
from functools import reduce

def ncr(n, r):
    r = min(r, n-r)
    numer = reduce(op.mul, range(n, n-r, -1), 1)
    denom = reduce(op.mul, range(1, r+1), 1)
    return int(numer / denom)

f = open("chart_loop.txt")
world_count = 0;
data = f.readlines()
for n in range(13):
    data[n] = data[n].split()
    data[n].reverse()
    for l in range(n+1):
        for j in range(65):
            world_count += int(data[l][j])*(3**n)*(2**(n-l))*((n+1)**6)*ncr(j,n-l)
print("There are",world_count,"tarski worlds. This number has",len(str(world_count)),"digits!")
