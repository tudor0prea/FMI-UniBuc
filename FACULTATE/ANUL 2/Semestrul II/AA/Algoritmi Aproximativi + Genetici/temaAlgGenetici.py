import numpy
import math


f = open("intrare.in")
g = open("iesire.out", "w")


# Citirea datelor:
  # dimensiunea populatiei
dim_populatie= int(f.readline())
  # domeniul de definitie al functiei (capetele intervalului):
(a,b) = ( float(i) for i in f.readline().split())
  # coeficientii polinomului de grad 2
(x,y,z) = ( float(i) for i in f.readline().split())

    #deci functia cu care se lucreaza va fi urmatoarea:
def fct(n):
    return (x * n ** 2) + (y * n) + z

  # precizia
precizie=int(f.readline())
  # probabilitatea de recombinare
pRecombinare = float(f.readline())
  # probabilitatea de mutatie
pMutatie = float(f.readline())
  # numarul de etape ale algoritmului
etape = int(f.readline())


#Lungimea unui cromozom:
l = int(math.log2((b-a) * 10 ** precizie)) + 1



# def decodificare(c):
#      var = int( "".join(str(a) for a in c), 2)
#      rasp= (y-x) * var / (2*l -1) + x
#
#      return round(rasp, precizie)
def decodificare(c):
    var = int( "".join(str(v) for v in c), 2)
    rasp = (b - a) * var / (2 ** l) + a
    return round(rasp, precizie)

def selectie( populatie, top=False):
    if top:
        g.write("Probabilitate selectie:\n")

    # "F" = suma( f(c) )
    suma = sum ( [ fct(decodificare(c)) for c in populatie] )

    # "Pi" = f(c) / F
    probabilitati = [ fct(decodificare(c)) / suma for c in populatie]

    #!! AM ROTUNJIT FUNCTIA
    fitness = [ round( fct(decodificare(c)) , precizie) for c in populatie]

    maximP=float('-inf')
    indice=-1
    for xind in range (len(probabilitati)):
        var = "Cromozomul {0:0" + str(int(numpy.log10(dim_populatie)) +1) +"d}  - probabilitate " + str(probabilitati[xind]) +"\n"

        if fitness[xind]>maximP:
            maximP=fitness[xind]
            indice=xind
        if top:
            g.write(var.format(xind+1))


    # automat, individul cu cea mai buna valoare pentru fct(i) va trece in urmatoarea generatie
    populatie_curenta=[];  #populatie_curenta.append(populatie[indice])
    elitist=[]; elitist.append(populatie[indice])

    if top:
        g.write("\n Intrevalele formate:\n")

    numar=0
    intervale=[0]

    for i in range(len(probabilitati)):
        var = "q{0:0" + str(int(numpy.log10(dim_populatie)) +1) + "d} = [" + str(numar) +","

        if i != len(probabilitati) - 1 :
            numar= probabilitati[i]+numar
        else:
            numar=1

        intervale.append(numar)
        var = var + " " + str(numar)+"]\n"

        if top:
            g.write(var.format(i+1))

    if top:
        g.write("Selectie elitista: alegem cromozomul " + str(indice+1)+"\n")

    #generam nr aleatoare, vedem in ce interval pica
    #si trecem individul corespunzator intervalului in generatia urmatoare
    for i in range(dim_populatie - 1):
        aleator=numpy.random.uniform(0,1)
        #indice=numpy.searchsorted(intervale, aleator)

        #cautarea intervalului din care face parte nr aleator, cu cautare binara
        stanga = 0
        dreapta = len(intervale) - 1
        indice = -1

        while stanga <= dreapta:
            mijloc = (stanga + dreapta) // 2

            if intervale[mijloc] < aleator <= intervale[mijloc + 1]:
                indice = mijloc
                break
            elif aleator <= intervale[mijloc]:
                dreapta = mijloc - 1
            else:
                stanga = mijloc + 1

        populatie_curenta.append(populatie[indice-1])
        if top:
            g.write("numarul: "+str(aleator)+ "|-> cromozomul "+ str(indice+1)+"\n")

    return populatie_curenta, elitist



def incrucisare(populatie, top=False):
    selectie=[]
    for i in range(len(populatie)):
        c = populatie[i]
        var="Cromozom {0:0"+ str(int(numpy.log10(dim_populatie))+1) + "d} "
        var=var+ str(c)[1:-1].replace(' ','')+ " "

        aleator=numpy.random.uniform(0,1)
        var+="numarul: "+str(aleator)

        if aleator< pRecombinare:
            selectie.append((c,i+1))
            var+= "<" + str(pRecombinare)+" =>PARTICIPA"
        if top:
            g.write(var.format(i+1)+"\n")


    numpy.random.shuffle(selectie)

    if top:
        g.write("\n")

    #alegem cromozomii pentru recombinare

    if ( len(selectie)==1 or len(selectie)==0 ) and top:
        g.write("! Nu s-au ales destui cromozomi pentru incrucisare.\n")

    if len(selectie)%2==0 or len(selectie)<3:
        for i in range(1, len(selectie), 2):
            x= selectie[i-1]
            y= selectie[i]

            var="Recombinarea dintre {x} si {y}:"
            aleator=numpy.random.randint(0,l)
            var+="\n"+ str(x[0])[1:-1].replace(' ', '')+ " "+ str(y[0])[1:-1].replace(' ','')
            var+= " punct " + str(aleator) +"\n"

            x_rez=numpy.append(x[0][:aleator], y[0][aleator:])
            y_rez=numpy.append(x[0][:aleator], y[0][aleator:])

            var+="Rez: -> "+ str(x_rez)[1:-1].replace(' ','')+ " "+ str(y_rez)[1:-1].replace(' ','') + "\n"

            populatie[x[1] - 1] = x_rez
            populatie[y[1] - 1] = y_rez

            if top:
                g.write(var.format(x=x[1], y=y[1]))
    else:

        # avem nr impar de cromozomi selectati, deci facem incrucisare intre ultimii 3
        x = selectie[len(selectie) - 3]
        y = selectie[len(selectie) - 2]
        z = selectie[len(selectie) - 1]

        var = "Recombinarea dintre {x}, {y} si {z}:"
        aleator = numpy.random.randint(0, l)
        var += "\n" + str(x[0])[1:-1].replace(' ', '') + " " + str(y[0])[1:-1].replace(' ', '')
        var += " punct " + str(aleator) + "\n"

        x_rez = numpy.append(x[0][:aleator], z[0][aleator:])
        y_rez = numpy.append(y[0][:aleator], x[0][aleator:])
        z_rez = numpy.append(z[0][:aleator], y[0][aleator:])

        var += "Rez: -> " + str(x_rez)[1:-1].replace(' ', '') + " " + str(y_rez)[1:-1].replace(' ', '') + str(z_rez)[1:-1].replace(' ','') +"\n"

        populatie[x[1] - 1] = x_rez
        populatie[y[1] - 1] = y_rez
        populatie[z[1] - 1] = z_rez

        if top:
            g.write(var.format(x=x[1], y=y[1],z=z[1]))

        for i in range(1, len(selectie)-2, 2):
            x = selectie[i - 1]
            y = selectie[i]

            var = "Recombinarea dintre {x} si {y}:"
            aleator = numpy.random.randint(0, l)
            var += "\n" + str(x[0])[1:-1].replace(' ', '') + " " + str(y[0])[1:-1].replace(' ', '')
            var += " punct " + str(aleator) + "\n"

            x_rez = numpy.append(x[0][:aleator], y[0][aleator:])
            y_rez = numpy.append(x[0][:aleator], y[0][aleator:])

            var += "Rez: -> " + str(x_rez)[1:-1].replace(' ', '') + " " + str(y_rez)[1:-1].replace(' ', '') + "\n"

            populatie[x[1] - 1] = x_rez
            populatie[y[1] - 1] = y_rez
            if top:
                g.write(var.format(x=x[1], y=y[1]))

    return populatie


def mutatie(populatie, top=False):
    mutati = set()
    for i in range(len(populatie)):
        c=populatie[i]

        for j in range(l):
            aleator=numpy.random.uniform(0,1)
            if aleator< pMutatie:
                if c[i]==0:
                    c[i] = 1
                else:
                    c[i] = 0
                mutati.add(i+1)
    var=str(sorted(mutati))[1:-1].replace(', ','\n')
    if top:
        g.write(var)
    return populatie


def afisare(populatie):
    for i in range(len(populatie)):
        c=populatie[i]
        var=" Cromozom {0:0"+str(int(numpy.log10(dim_populatie)) +1) +"d} "+ str(c)[1:-1].replace(' ','')+' '

        dec=decodificare(c)
        var+= ("x=" if dec<0 else "x= ")+"{x:.6f}".format(x=dec) + " f(x)="+str(fct(dec)) + "\n"

        g.write(var.format(i+1))







#  PROGRAMUL PRINCIPAL


def main():
    # generarea populatiei initiale
    populatie= numpy.array( [ numpy.random.randint(0,2, l).tolist() for i in range(dim_populatie)])

    #afisare
    g.write("\nPopulatia initiala: \n")
    selectati, elitist= selectie(populatie,True)

    g.write("\n Selectie:\n")
    afisare(selectati)


    #incrucisare
    g.write("\nIncrucisare:\n")
    g.write("Probabilitate: " +str(pRecombinare) +"\n")
    populatie_incrucisata=incrucisare(selectati,True)
    afisare(populatie_incrucisata)


    #mutatie
    g.write("\nMutatie:\n")
    g.write("Probabilitate: " +str(pMutatie) +"\n")
    populatie_mutanta=mutatie(populatie_incrucisata,True)
    g.write("\nDupa mutatie:\n")
    #TO LIST ca altfel aveam eroare
    #populatie_mutanta = populatie_mutanta.tolist()
    populatie_mutanta.append(elitist[0])
    afisare(populatie_mutanta)



    g.write("\n \n EVOLUTIE \n")


    valori_max=[]
    valori_avg=[]

    fostul_maxim=-1
    for i in range(etape):
        populatie=populatie_mutanta
        selectati, elitist = selectie(populatie,False)


        populatie_incrucisata= incrucisare(selectati)
        populatie_mutanta=mutatie(populatie_incrucisata)
        populatie_mutanta.append(elitist[0])

        fitness = [ round( fct(decodificare(c)) , precizie) for c in populatie_mutanta]

        elitist_val = fct(decodificare(elitist[0]))
        maxim=max(fitness)

        if elitist_val>maxim:
            maxim=elitist_val

        if fostul_maxim>maxim and fostul_maxim!=-1:
            maxim=fostul_maxim

        media=numpy.mean(fitness)

        valori_max.append(maxim)
        valori_avg.append(media)

        var="MAX= " + str(maxim) + " AVG= "+str(media) + "\n"

        fostul_maxim=maxim
        g.write(var)

    # afisarea unui grafic de evolutie:
    import matplotlib.pyplot as plt

    plt.plot(range(etape), valori_max, label='MAX')
    plt.plot(range(etape), valori_avg, label='AVG')
    plt.xlabel('Generatie')
    plt.ylabel('Valoarea functiei de fit')
    plt.title('Evolutia maximului si a valorii medii pentru functia de fit')
    plt.legend()
    plt.show()




main()