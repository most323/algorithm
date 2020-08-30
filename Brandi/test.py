n, k = map(int, input().split())
arr = list(map(int, input().split()))

if (n-k)%(k-1) == 0:
    return 1 + (n-k)//(k-1)
else:
    return 2 + (n-k)//(k-1)