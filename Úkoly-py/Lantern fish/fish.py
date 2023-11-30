from os.path import join, realpath, dirname
from collections import deque

def play(fish:list[int], turn_count:int)->int:
    fish = deque(fish)
    for i in range(turn_count):
        fish.rotate(-1)
        fish[6]+=fish[-1]
        print(fish)
    return sum(fish)
    """ for i in range(turn_count):
        for i,f in enumerate(fish):
            fish[i]-=1
            if fish[i]<0:
                fish[i] = 6
                fish.append(9)
    return len(fish) """

with open(join(dirname(realpath(__file__)), "data.txt"),"r", encoding="utf_8") as file:
    list =[0]*9
    for fish in file.read().split(","):
        list[int(fish)]+=1
    print(play(list,18))