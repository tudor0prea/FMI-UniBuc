class NodArbore:

    def __init__(self, info, parinte=None):
        self.info = info
        self.parinte = parinte
    
    def drumRadacina(self):
        l = []
        nod = self
        while(nod is not None):
            l.insert(0, nod)
            nod = nod.parinte
        return l
    
    def vizitat(self):
        nod = self.parinte
        while(nod is not None):
            if(nod.info == self.info):
                return True
            nod = nod.parinte
        return False

    ########################################################################
    # afisare in fisier : Laborator 2: ex 3
    def afisSolFisier(self, file):
        with open(file, "w") as f:
            drumRadacina = self.drumRadacina()
            for nod in drumRadacina:
                if nod.info != (Graf.N, Graf.N, 1):
                    f.writelines(nod.deplasare())
                f.writelines(nod.state())

    def deplasare(self):
        state = self.info
        if self.parinte is None:
            parent = (Graf.N, Graf.N, state[2])
        else:
            parent = self.parinte.info

        if state[2] == 1:
            barca_stanga = "drept"
            barca_dreapta = "stang"
        else:
            barca_stanga = "stang"
            barca_dreapta = "drept"
            
        return f">>>Barca s-a deplasat de la malul {barca_stanga} la malul {barca_dreapta} cu {abs(parent[1] - state[1])} canibali si {abs(parent[0] - state[0])} misionari.\n"

    def state(self):
        state = self.info

        if state[2] == 0:
            barca_stanga = ":<barca>"
            barca_dreapta = ""
        else:
            barca_stanga = ""
            barca_dreapta = ":<barca>"
    
        return f"(Stanga{barca_stanga}) {state[1]} canibali {state[0]} misionari ...... (Dreapta{barca_dreapta}) {Graf.N - state[1]} canibali {Graf.N - state[0]} misionari\n\n"
    #####################################################################

    def __str__(self):
        return str(self.info)
    
    def __repr__(self):
        return "({}, {})".format(self.info, "->".join([str(nod) for nod in self.drumRadacina()]))
    
class Graf:

    def __init__(self, start, scopuri):
        self.start = start
        self.scopuri = scopuri

    def scop(self, informatieNod):
        return informatieNod in self.scopuri

    def succesori(self, nod):
        def test (m, c):
            return m==0 or m>=c
        
        l = []
        if nod.info[2]==1: #mal stanga, mal initial = mal curent = mal cu barca
            misMalCurent = nod.info[0]
            canMalCurent = nod.info[1]
            misMalOpus = Graf.N - nod.info[0]
            canMalOpus = Graf.N - nod.info[1]

        else: # mal dreapta
            misMalCurent = Graf.N - nod.info[0]
            canMalCurent = Graf.N - nod.info[1]
            misMalOpus = nod.info[0]
            canMalOpus = nod.info[1]

        maxMixBarca = min(misMalCurent, Graf.N)
        for mb in range(maxMixBarca + 1):
            if mb == 0:
                minCanBarca=1
                maxCanBarca=min(Graf.M, canMalCurent)
            else:
                minCanBarca = 0
                maxCanBarca = min(mb, Graf.M-mb, canMalCurent)

            for cb in range(minCanBarca, maxCanBarca+1):
                misMalCurentNou=misMalCurent - mb
                canMalCurentNou=canMalCurent - cb

                misMalOpusNou = misMalOpus + mb
                canMalOpusNou = canMalOpus + cb

                if not test(misMalCurentNou, canMalCurentNou):
                    continue
                if not test(misMalOpusNou, canMalOpusNou):
                    continue

                if nod.info[2]==1:
                    infoNod=(misMalCurentNou, canMalCurentNou, 0)
                else:
                    infoNod=(misMalOpusNou, canMalOpusNou, 1)

                nodNou=NodArbore(infoNod, nod)
                if not nodNou.vizitat():
                    l.append(nodNou)
        return l
    
# BFS implem
def breadthfirst(gr, nsol):
    c = [NodArbore(gr.start)]

    while(c):
        nodCurent = c.pop(0)
        if gr.scop(nodCurent.info):
            print(repr(nodCurent))
            ###################################################################
            nodCurent.afisSolFisier("solutie.txt")

            nsol -= 1
            if not nsol:
                return

        c += gr.succesori(nodCurent)

# DFS implem - recursive
def dfs(gr, nodCurent):
    if gr.scop(nodCurent.info):
        print(repr(nodCurent))

        global nsol
        nsol -= 1
        if not nsol:
            return True
        
    if not nodCurent.vizitat():
        succesori = gr.succesori(nodCurent)
        for neighbour in succesori:
            if dfs(gr, neighbour):
                return True

def recursivedepthfirst(gr):
    nodCurent = NodArbore(gr.start)
    dfs(gr, nodCurent)

# DFS implem - non - recursive
def nonrecursivedepthfirst(gr, nsol):
    s = [NodArbore(gr.start)]

    while s:
        nodCurent = s.pop()
        if gr.scop(nodCurent.info):
            print(repr(nodCurent))

            nsol -= 1
            if not nsol:
                return
        
        if not nodCurent.vizitat():
            succesori = gr.succesori(nodCurent)
            for neighbour in succesori:
                s.append(neighbour)


f=open("lab2_kr_input.txt", 'r')
continut=f.read().strip().split()
Graf.N=int(continut[0])
Graf.M=int(continut[1])
 
start=(Graf.N, Graf.N, 1)
scopuri=[(0,0,0)]

gr = Graf(start, scopuri)
# nsol = int(input("Introduceti nr de solutii solicitate = "))

breadthfirst(gr, 1)
# recursivedepthfirst(gr)
# nonrecursivedepthfirst(gr, nsol)