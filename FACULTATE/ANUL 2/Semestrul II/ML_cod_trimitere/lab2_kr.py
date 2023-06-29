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

    # --------------------------------------------------------------
    #   TEMA
    def afisSolFisier(self, nume_fisier):
        with open(nume_fisier, "w") as f:
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


class Graf:

    def __init__(self, start, scopuri):
        # self.matr = matr (sters)
        self.start = start
        self.scopuri = scopuri
    def scop (self, infromatieNod):
        return infromatieNod in self.scopuri

    def succesori(self,nod):
        l=[]

        def test(m,c):
            return m==0 or m>=c

        if nod.info[2]==1: #mal initial=mal curent=mal cu barca
            misMalCurent=nod.info[0]
            canMalCurent=nod.info[1]

            misMalOpus=Graf.N-nod.info[0]
            canMalOpus=Graf.N-nod.info[1]
        else:
            #valorile invers
            misMalCurent = Graf.N - nod.info[0]
            canMalCurent = Graf.N - nod.info[1]

            misMalOpus = nod.info[0]
            canMalOpus = nod.info[1]

        maxMisBarca = min(misMalCurent, Graf.M)
        #cati misionari putem trimite, adica min dintre nr de locuri sau nr de mis

        for mb in range(maxMisBarca + 1):
            if mb==0:
                minCanBarca=1
                maxCanBarca=min(canMalCurent, Graf.M)
            else:
                minCanBarca=0
                maxCanBarca= min(mb, Graf.M - mb)

            for cb in range(minCanBarca, maxCanBarca+1):
                misMalCurentNou=misMalCurent-mb
                canMalCurentNou=canMalCurent-cb
                misMalOpusNou=misMalOpus+mb
                canMalOpusNou=canMalOpus+cb

                if not test(misMalCurentNou, canMalCurentNou):
                    continue
                if not test(misMalOpusNou, canMalOpusNou):
                    continue

                if nod.info[2]==1: #daca suntem pe mal initial
                    infoNod=(misMalCurentNou,canMalCurentNou, 0)

                else:
                    infoNod=(misMalOpusNou, canMalOpusNou, 1)

                nodNou=NodArbore(infoNod, nod)

                if not nodNou.vizitat():
                    l.append(nodNou)
        return l

def breadth_first(gr, nsol):
    c=[NodArbore(gr.start)]
    while c:
        nodCurent=c.pop(0)
        if gr.scop(nodCurent.info):
            print(repr(nodCurent))

            ##pentru afisarea completa in fisier:
            nodCurent.afisSolFisier("lab2_kr_output_complet.txt")


            nsol-=1
            if nsol==0:
                return
        c+=gr.succesori(nodCurent)

f=open("lab2_kr_input.txt", "r")
citire=f.read().strip().split()

Graf.N=int(citire[0])

Graf.M=int(citire[1])

start = (Graf.N, Graf.N, 1) #1 = mal initial
scopuri = [(0,0,0)] #vrem sa avem mutati toti canibalii si misionarii

gr=Graf(start, scopuri)
breadth_first(gr,3)


#tema: ex.3 ca sa fie mai usor de citit



# --------------------------------------------------------------
#   TEMA

# nsol = 3
nume_fisier = open("lab2_kr_output_complet.txt", "w")
# c = [NodArbore(gr.start)]
# while c:
#     nodCurent = c.pop(0)
#     if gr.scop(nodCurent.info):
#         nodCurent.afisSolFisier(nume_fisier)
#         nsol -= 1
#         if nsol == 0:
#             break
#     c += gr.succesori(nodCurent)
# f.close()

f=open("lab2_kr_input.txt", 'r')
cont_fisier=f.read().strip().split()
Graf.N=int(cont_fisier[0])
Graf.M=int(cont_fisier[1])
start=(Graf.N,Graf.N,1)
scopuri=[(0,0,0)]

gr=Graf(start,scopuri)

breadth_first(gr,1)
