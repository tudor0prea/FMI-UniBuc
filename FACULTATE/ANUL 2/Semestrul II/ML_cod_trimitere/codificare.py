import math

a=int(input())
b=int(input())

p=int(input())
m=int(input())



def codificare(a,b):

    l = math.log( ((b - a) * 10 ^ p),2)
    cheie=input()
    nr=float(input())
    if cheie=="TO":
        #transformam din int in binar
        print(  bin(int(nr))[2:].zfill(int(l)) )
    elif cheie=="FROM":
            print( eval('0b' + str(nr)) )

for i in range(1,m):
    codificare(a,b)

L = int(math.log2((b - a) * 10 ** p)) + 1
def decode(chromosome):

    aux = int("".join(str(x) for x in chromosome), 2)
    decoded = (b - a) * aux / (2 ** L - 1) + a
    return round(decoded, 6)
