class NodArbore:
    n = 100

    def __init__(self, info, parinte=None):
        self.info = info
        self.parinte = parinte

    def drumRadacina(self):
        l=[]
        nod=self
        while nod is not None:
            l.insert(0,nod)
            nod=nod.parinte
        return l

    def vizitat(self):
        nod=self.parinte
        while nod is not None:
            if nod.info==self.info :
                return True
            nod=nod.parinte
        return False

    def __str__(self):
        return str(self.info)

    def __repr__(self):
        return "({}, {})".format(self.info, "->".join( [str(x) for x in self.drumRadacina()] ) )


class Graf:

    def __init__(self, matr, start, scopuri):
        self.matr = matr
        self.start = start
        self.scopuri = scopuri
    def scop (self, infromatieNod):
        return infromatieNod in self.scopuri

    def succesori(self,nod):
        l=[]
        for i in range(len(self.matr)):
            if self.matr[nod.info][i] == 1:
                nodNou=NodArbore(i, nod)
                if not nodNou.vizitat():
                    l.append(nodNou)
        return l

def breadth_first(gr, nsol):
    c=[NodArbore(gr.start)]
    while c:
        nodCurent=c.pop(0)
        if gr.scop(nodCurent.info):
            print(repr(nodCurent))
            nsol-=1
            if nsol==0:
                return
        c+=gr.succesori(nodCurent)





m = [
    [0, 1, 0, 1, 1, 0, 0, 0, 0, 0],
    [1, 0, 1, 0, 0, 1, 0, 0, 0, 0],
    [0, 1, 0, 0, 0, 1, 0, 1, 0, 0],
    [1, 0, 0, 0, 0, 0, 1, 0, 0, 0],
    [1, 0, 0, 0, 0, 0, 0, 1, 0, 0],
    [0, 1, 1, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 1, 0, 0, 0, 0, 0, 0],
    [0, 0, 1, 0, 1, 0, 0, 0, 1, 1],
    [0, 0, 0, 0, 0, 0, 0, 1, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 1, 0, 0]
]

start = 0
scopuri = [5, 9]

gr=Graf(m, start, scopuri)


breadth_first(gr,3)

print("\n")

# -------------------------------------------
#   tema: ex.3


nsol=int(input("->"))

def dfs(nodCurent, nrSolutii):
    #daca am afisat deja toate solutiile
    if nrSolutii == 0:
        return nrSolutii
    #daca am ajuns la un nod scop
    if gr.scop(nodCurent.info):
        print(repr(nodCurent))
        return nrSolutii - 1

    #in caz contrar, cautam prin succesorii nodului curent
    for succesor in gr.succesori(nodCurent):
        nrSolutii = dfs(succesor, nrSolutii)
        if nrSolutii == 0:
            return nrSolutii

    return nrSolutii

dfs(NodArbore(gr.start), nsol)



# -----------------

#ex. 4
print("\n")

def dfs_iterativ(gr, nsol):
    start = NodArbore(gr.start)
    #pornim stiva cu nodul de start
    stiva = [start]
    nrSolutii = 0

    while stiva:
        #extragem un nod si vedem daca este de scop
        nodCurent = stiva.pop()
        if gr.scop(nodCurent.info):
            print(repr(nodCurent))
            nrSolutii += 1
            if nrSolutii == nsol:
                return
        if nrSolutii < nsol:
            succesori = gr.succesori(nodCurent)
            for succesor in succesori:
                stiva.append(succesor)

dfs_iterativ(gr, nsol)