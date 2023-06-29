n = 5


def bkt(i):
    if i == n + 1:
        for j in range(1, n + 1):
            print(x[j], end="")
        print(" ")
    else:
        for j in range(1, n + 1):
            x[i] = j
            if x[i] not in x[:i]:  #if valid
                bkt(i + 1)


viz = [0 for i in range(0, 2 * n)]
vec = [0, 1, 2, 3,4,5]
x = [0 for i in range(0, 2 * n)]

#bkt(f)