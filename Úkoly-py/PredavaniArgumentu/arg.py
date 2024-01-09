#existují dvě metody zastaralá metoda využíva modulu sys rovnou zde vysvětlím modernější s využitím modulu argparse
import argparse

#Vytvoříme instanci nášeho parseru pomocí metody ArgumentParser(), který se stará o zpracování argumentů předaných přes příkazovou řádku
#, můžeme přidat také globální popis, jako například způsob jak mají být argumenty formátovány
parser = argparse.ArgumentParser(description='Program řešící faktoriál')

#přidáme argumenty pomocí metody add_argument() první definuje vlajku za jakou argument; metavar je celé jméno předávané v nápovědě; typ určuje typ argumentu;
#default určuje hodnotu, která je nastavená v případě že není žádná předána; help je dloubhý popis pro nápovědu
parser.add_argument('-f',metavar="--Faktorial",type=int, default=1, help="Jaký faktoriál vypočítat")
parser.add_argument('-m',metavar="--Mocnina",type=int, default=1, help="Na jakou mocninu udělat číslo")
parser.add_argument('-c',metavar="--Cislo",type=int, default=1, help="S jakým číslem budu počíat")
#můžeme přidat kolik chceme argumentů

#parse_args vrací specialní datový typ který umožňuje přistupovat k jednotlivým argumentům pomocí jejich vlajky bez -
args = parser.parse_args()

#přístup k argumentu
#Faktorial
def faktorial(cislo:int)->int:
    fak = 1
    for i in range(1,cislo+1):
        fak*=i
    return fak

#Mocnina
def mocnina(cislo:int,mocnina:int)->int:
    for i in range(1,mocnina):
        cislo*=cislo
    return cislo


print(faktorial(args.f))
print(mocnina(args.c,args.m))