from os.path import realpath, dirname, join



with open(join(dirname(realpath(__file__)), "2000.txt"),"r", encoding="utf_8") as file:
    maximum = [max([sum([int(cal) for cal in elf.split("\n")])] for elf in file.read().split("\n\n"))]
    """ for line in int(file.read().split()):
        if line =="\n":
               if cislo>Elf:
                    Elf=cislo
               cislo=0
        else:
             cislo+=line
        cislo+=cislo """
    print (maximum)
    #for line in file:
       # data.append(int(line.strip()))




