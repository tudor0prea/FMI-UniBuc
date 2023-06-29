import numpy
import math

f = open('introducereGeneticaInput')
g = open('introducereGeneticaOutput.txt', 'w')


def decode(chromosome):

    aux = int("".join(str(x) for x in chromosome), 2)
    decoded = (b - a) * aux / (2 ** chromosomeLength - 1) + a
    return round(decoded, 6)


def fitness(chromosome):
    return fun(chromosome)


def print_population(population):
    for i in range(len(population)):
        chromosome = population[i]
        aux = "cromozom {0:0" + str(int(numpy.log10(populationSize)) + 1) + "d} "
        aux += str(chromosome)[1:-1].replace(' ', '') + ' '
        decoded = decode(chromosome)
        aux += ('x=' if decoded < 0 else 'x= ') + '{x:.6f}'.format(x=decoded) + ' f(x)=' + str(fitness(decoded)) + '\n'
        g.write(aux.format(i + 1))


def selection(population, first=False, selectie_elitista=True):
    if first:
        g.write('\nProbabilitati selectie:\n')
    s = sum([fitness(decode(chromosome)) for chromosome in population])
    prob = [fitness(decode(chromosome)) / s for chromosome in population]
    for x in range(len(prob)):
        aux = "cromozom {0:0" + str(int(numpy.log10(populationSize)) + 1) + "d} "
        aux += "probabilitate " + str(prob[x]) + '\n'
        if first:
            g.write(aux.format(x + 1))
    if first:
        g.write('\nIntervale selectie:\n')
    q = 0
    intervals = [0]
    for x in range(len(prob)):
        aux = "q{0:0" + str(int(numpy.log10(populationSize)) + 1) + "d} = "
        aux += '[' + str(q) + ','
        q = prob[x] + q if x != len(prob) - 1 else 1
        intervals.append(q)
        aux += ' ' + str(q) + ']' + '\n'
        if first:
            g.write(aux.format(x + 1))

    new_population = []
    # select either best chromosome or first 1% best chromosomes if elitist selection is selected
    elitist_selection = max(1, int(populationSize / 100)) if selectie_elitista else 0
    elitist_population = []
    for x in sorted(prob, reverse=True)[:elitist_selection]:
        index = prob.index(x)
        elitist_population.append(population[index])
        if first:
            g.write("\nselectie elitista, selectez cromozomul " + str(index + 1) + '\n')

    for x in range(populationSize - elitist_selection):
        u = numpy.random.uniform(0, 1)
        index = numpy.searchsorted(intervals, u)
        new_population.append(population[index - 1])
        if first:
            g.write("u = " + str(u) + " selectez cromozomul " + str(index + 1) + '\n')
    return new_population, elitist_population


def crossover(population, first=False):
    selected = []
    for i in range(len(population)):
        chromosome = population[i]
        aux = "cromozom {0:0" + str(int(numpy.log10(populationSize)) + 1) + "d} "
        aux += str(chromosome)[1:-1].replace(' ', '') + ' '
        u = numpy.random.uniform(0, 1)
        aux += "u = " + str(u)
        if u < crossoverRate:
            selected.append((chromosome, i + 1))
            aux += '<' + str(crossoverRate) + " participa"
        if first:
            g.write(aux.format(i + 1) + '\n')
    numpy.random.shuffle(selected)
    if first:
        g.write('\n')
    for i in range(1, len(selected), 2):
        x = selected[i - 1]
        y = selected[i]
        aux = "Recombinare dintre cromozomul {x} cu cromozomul {y}:\n"
        u = numpy.random.randint(0, chromosomeLength)
        aux += str(x[0])[1:-1].replace(' ', '') + ' ' + str(y[0])[1:-1].replace(' ', '') + " punct " + str(u) + '\n'
        new_x = numpy.append(x[0][:u], y[0][u:])
        new_y = numpy.append(y[0][:u], x[0][u:])
        aux += "Rezultat " + str(new_x)[1:-1].replace(' ', '') + ' ' + str(new_y)[1:-1].replace(' ', '') + '\n'
        population[x[1] - 1] = new_x
        population[y[1] - 1] = new_y
        if first:
            g.write(aux.format(x=x[1], y=y[1]))
    return population


def mutation(population, first=False):
    mutated = set()
    for i in range(len(population)):
        chromosome = population[i]
        for x in range(chromosomeLength):
            u = numpy.random.uniform(0, 1)
            if u < mutationRate:
                chromosome[x] = 1 if chromosome[x] == 0 else 0
                mutated.add(i+1)
    aux = str(sorted(mutated))[1:-1].replace(', ', '\n')
    if first:
        g.write(aux)
    return population


def main(selectie_elitista=True):
    # generate initial population
    population = numpy.array([numpy.random.randint(0, 2, chromosomeLength).tolist() for _ in range(populationSize)])
    g.write("Populatie initiala:\n")

    # selectie
    selected, elitist_population = selection(population, True, selectie_elitista)

    g.write("\nDupa selectie:\n")
    print_population(selected)

    # incrucisare
    g.write("\nProbabilitate de incrucisare " + str(crossoverRate) + ":\n")
    crossed_population = crossover(selected, True)
    print_population(crossed_population)

    # mutatie
    g.write("\nProbabilitate de mutatie pentru fiecare gena este " + str(mutationRate) + "\nAu fost modificati "
                                                                                         "cromozomii:\n")
    mutated_population = mutation(crossed_population, True)
    g.write("\n\nDupa mutatie:\n")
    mutated_population.extend(elitist_population)
    print_population(mutated_population)

    g.write("\nEvolutie:\n")
    for i in range(n_iter):
        population = mutated_population
        selected, elitist_population = selection(population, False, selectie_elitista)
        crossed_population = crossover(selected)
        mutated_population = mutation(crossed_population)
        mutated_population.extend(elitist_population)
        decoded = [fitness(decode(chromosome)) for chromosome in mutated_population]
        mx = max(decoded)
        mean = numpy.mean(decoded)
        aux = "max = " + str(mx) + " mean = " + str(mean) + '\n'
        g.write(aux)


populationSize = int(f.readline())
(a, b) = (float(x) for x in f.readline().split())
(x, y, z) = (float(x) for x in f.readline().split())


def fun(val):
    return x * val ** 2 + y * val + z


p = int(f.readline())
chromosomeLength = int(math.log2((b - a) * 10 ** p)) + 1
crossoverRate = float(f.readline())
mutationRate = float(f.readline())
n_iter = int(f.readline())
main(True)