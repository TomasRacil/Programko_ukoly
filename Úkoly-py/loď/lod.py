from os.path import join, realpath, dirname

class Lod:
    def __init__(self) -> None:
        self.smer ="E"
        self.north=0
        self.east=0
        self.deg=0


    def turn(self,smer:str):
        self.smer = smer
        if self.smer== 'R':  
            self.deg-=90
        if self.smer== 'L': 
            self.deg+=90
        

        if self.deg<0:
            self.deg+=360
        if self.deg>360:
            self.deg-=360

    def move(self,smer:str,vzdalenost:int):
        self.smer = smer
        self.vzdalenost = vzdalenost
        if self.smer=="N":
            self.north+=self.vzdalenost
        if self.smer=="S":
            self.north-=self.vzdalenost
        if self.smer=="E":
            self.east+=self.vzdalenost
        if self.smer=="W":
            self.east-=self.vzdalenost
        if self.smer=="F":
            if self.deg == 0:
                self.east += self.vzdalenost
            if self.deg == 90:
                self.north += self.vzdalenost
            if self.deg == 180:
                self.east -= self.vzdalenost
            if self.deg == 270:
                self.north -= self.vzdalenost
    def print_pos(self):
    
        print(f"North: {self.north}")
        print(f"East: {self.east}")
        print(f"Deg: {self.deg}") 
        if self.north<0:
            self.north*=-1
        if self.east<0:
            self.east*=-1
        print(f"Manhatten distance: {self.north + self.east}")


smer_list = []
vzdalenost_list = []
with open(join(dirname(realpath(__file__)), "data.txt"),"r", encoding="utf_8") as file:
    for cor in file:
        smer = cor[0]
        vzdalenost = cor[1:].strip()
        smer_list.append(smer)
        vzdalenost_list.append(int(vzdalenost))
        print (vzdalenost_list)


lod = Lod()
for i in range(len(smer_list)):
    lod.turn(smer_list[i])
    lod.move(smer_list[i],vzdalenost_list[i])

lod.print_pos()