import matplotlib.pyplot as plt
import numpy as np

fin = open("timpi.txt")
Text=[x for x in fin]
fin.close()
Grafuri = {}

for linie in Text:
    if linie != "Bubble sort nu poate sorta\n" and linie != "Quick sort nu poate sorta\n":
        cuvinte=linie.split()
        if cuvinte[4] not in Grafuri.keys():
            Grafuri[cuvinte[4]] = {}
        if cuvinte[5] not in Grafuri[cuvinte[4]].keys():
            Grafuri[cuvinte[4]][cuvinte[5]] = {'nr_val':[],'durata':[]}
        if int(cuvinte[7]) == 0:
            pass
        else:
            Grafuri[cuvinte[4]][cuvinte[5]]['durata'].append(int(cuvinte[7]))
            Grafuri[cuvinte[4]][cuvinte[5]]['nr_val'].append(int(cuvinte[2]))

for maxi in Grafuri.keys():
    for graf in Grafuri[maxi].keys():
        plt.plot(Grafuri[maxi][graf]['nr_val'], Grafuri[maxi][graf]['durata'],'--o')
    plt.title('Valorile sunt <= '+maxi)
    plt.legend(Grafuri[maxi].keys())
    plt.xlabel('Numar valori')
    plt.ylabel('nanosecunde')
    plt.xscale('log', base=2)
    plt.yscale('log')
    plt.grid(True)
    plt.show()
