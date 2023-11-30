cislo = int(input("Zadej číslo: "))

def faktorial(int:cislo)->int:
    fak = 1
    for i in range(1,cislo+1):
        fak*=i
    return fak

print(f"faktorial {cislo} je {faktorial(cislo)}")
