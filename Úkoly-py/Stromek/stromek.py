


def koruna(vyska_koruny:int)->None:
    for i in range(vyska_koruny):
        for j in range(vyska_koruny-i):
                print(" ", end = "")
            
        print("*"*((i*2)+1))

def kmen(vyska_koruny:int, vyska_kmene:int)->None:
    for i in range(vyska_kmene):
        for j in range(vyska_koruny-1):
            print(" ", end = "")
        
        print("#"*3)


def main()->None:

    vyska_koruny = int((input("Zadej výšku koruny: ")))
    vyska_kmene = int((input("Zadej výšku kmene: ")))
    koruna(vyska_koruny)
    kmen(vyska_koruny,vyska_kmene)


if __name__ == "__main__":
     main()


