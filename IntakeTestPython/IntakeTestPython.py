print("-- Oefening 1 --")
aantalpersonen = int(input("Hoeveel mensen gaan op reis? "))
prijsPerVlucht = int(input("Wat is de prijs van een vlucht? "))
aantalNachten = int(input("Hoeveel nachten wordt er geboekt? "))
prijsPerNacht = float(input("Wat is de prijs per nacht? "))
zomeractie = input("zomeractie: ")
administratiekosten = 20
if zomeractie == "ja": 
    totaal = ((aantalpersonen * (prijsPerVlucht + (float(aantalNachten)*prijsPerNacht))) + administratiekosten) * 0.9
elif zomeractie == "nee":
    totaal = ((aantalpersonen * (prijsPerVlucht + (float(aantalNachten)*prijsPerNacht))) + administratiekosten)
print(totaal)

print("-- Oefening 2 --")
word = input("Geef een woord: ")
taal = input("Geef een doeltaal: ")
def translate(word, taal):
    if taal == "frans":
        if word == "hond":
            return "chien"
        elif word == "kat":
            return "chat"
    elif taal == "engels":
        if word == "hond":
            return "dog"
        elif word == "kat":
            return "cat"
print("het vertaalde woord is: " + translate(word,taal))

print("-- Oefening 3 --")
places = [False,True,False,False,True]
for item in places:
    if item == True:
        print("plaats " + item + "bezet")
    elif item == False:
        print("plaats " + item + "vrij")
