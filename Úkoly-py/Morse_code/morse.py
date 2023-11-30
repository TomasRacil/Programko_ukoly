from os.path import realpath,dirname,join



text=input("Zadej text, který chceš převést do morseovky: ")

morse_list_znak = []
morse_list_code = []
with open(join(dirname(realpath(__file__)), "data.txt"),"r", encoding="utf_8") as file:
    for morse in file:
        znak = morse[0]
        morse_code = morse[1:].strip()
        morse_list_znak.append(znak)
        morse_list_code.append(morse_code)


text_chars=list(text)
final_morse=""

for char in text_chars:
    if char in morse_list_znak:
        index = morse_list_znak.index(char)
        final_morse += morse_list_code[index] + " "
print(f"Váš text v morzeovce je : {final_morse}")

