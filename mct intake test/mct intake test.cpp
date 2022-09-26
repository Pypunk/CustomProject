#include "pch.h"
#include <iostream>
#include <string>
enum class Language
{
	French,
	English
};
void ExerciseOne();
void ExerciseTwo();
void ExerciseThree();
std::string Translate(const Language& language, const std::string& word );
int main()
{
	ExerciseOne();
	ExerciseTwo();
	ExerciseThree();
	std::cin.ignore();
	std::cin.get();
}

void ExerciseOne()
{
	std::cout << "-- Oefening 1 --\n";
	std::cout << "Hoevel mensen gaan op reis?";
	int aantalPersonen{};
	int prijsPervlucht{};
	int aantalNachten{};
	float prijsPernacht{};
	std::string zomerActie{};
	float total{};
	std::cin >> aantalPersonen;
	std::cout << "Wat is de prijs van een vlucht?";
	std::cin >> prijsPervlucht;
	std::cout << "Hoeveel nachten wordt er geboekt?";
	std::cin >> aantalNachten;
	std::cout << "Wat is de prijs per nacht?";
	std::cin >> prijsPernacht;
	std::cout << "Zomeractie:";
	std::cin >> zomerActie;
	const int administratieKosten{ 20 };
	if (zomerActie == "ja")
	{
		total = ((aantalPersonen * (prijsPervlucht + (float(aantalNachten) * prijsPernacht))) + administratieKosten) * 0.9f;
	}
	else if (zomerActie == "nee")
	{
		total = (aantalPersonen * (prijsPervlucht + (float(aantalNachten) * prijsPernacht))) + administratieKosten;
	}
	std::cout << "De prijs voor de volledige groep kost: " << total << " euro\n";
}

void ExerciseTwo()
{
	std::cout << "\n-- oefening 2 --\n";
	std::string word{};
	std::string languageString{};
	std::string translated{};
	std::cout << "Geef een woord: ";
	std::cin >> word;
	std::cout << "Geef een doeltaal: ";
	std::cin >> languageString;
	if (languageString == "Frans")
	{
		translated = Translate(Language::French, word);
	}
	else
	{
		translated = Translate(Language::English, word);
	}
	std::cout << "Het vertaalde woord is: " << translated << std::endl;
}

void ExerciseThree()
{
	std::cout << "\n-- oefening 3 --\n";
	const int amountOfPlaces{ 5 };
	bool places[amountOfPlaces]{ false,true,false,false,true };
	int totalFreeSpaces{};
	for (int i{}; i < amountOfPlaces; ++i)
	{
		std::cout << "Plaats " << i << " ";
		if (places[i])
		{
			std::cout << "bezet\n";
		}
		else
		{
			std::cout << "vrij\n";
			totalFreeSpaces++;
		}
	}
	std::cout << "Aantal vrije plaatsen\n" << totalFreeSpaces;
}

std::string Translate(const Language& language, const std::string& word)
{
	switch (language)
	{
		case Language::French:
			if (word == "hond") return "chien";
			if (word == "kat") return "chat";
			break;
		case Language::English:
			if (word == "hond") return "dog";
			if (word == "kat") return "cat";
			break;
	}
	return std::string{};
}
