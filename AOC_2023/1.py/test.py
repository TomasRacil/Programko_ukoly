from os.path import join,dirname,realpath
import re

with open(join(dirname(realpath(__file__)), "data.txt"),"r", encoding="utf_8") as file:
    text = [line.strip() for line in file]

text2 =[]
ans=0

word_to_digit = {
    "one": 1,
    "two": 2,
    "three": 3,
    "four": 4,
    "five": 5,
    "six": 6,
    "seven": 7,
    "eight": 8,
    "nine": 9,
}

ans=0
with open(join(dirname(realpath(__file__)), "data.txt"),"r", encoding="utf_8") as file:
    for line in file:
        # r'\d+|' + '|' finds all digits      re.findall(r'\d|' + '|' finds single digits
        #.join(word_to_digit.keys()) joins the keys of directory to the digits
        matches = re.findall(r'\d|' + "|".join(word_to_digit.keys()), line)
        if matches:
            matches=[word_to_digit[match] if match in word_to_digit else int(match) for match in matches]
            ans+= int(str(matches[0]) + str((matches[-1])))
        #print (matches)
        #print (ans)
print (ans)




