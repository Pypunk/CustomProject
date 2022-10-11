#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
int SortByMax(const int lhs, const int rhs);
bool IsZero(const int number);
bool IsEven(const int number);
void TestSortAlgorithm(std::vector<int>& intvector);
void TestAllOfAnyOfNoneOf(std::vector<int>& intvector);
void TestCountCountIf(std::vector<int>& intvector);
void TestFindFindIfFindIfNot(std::vector<int>& intvector);
void TestSearch(std::vector<int>& intvector);
int main()
{
	std::vector<int>intvector{ 2,4,0,9,6,4,2,1,4,8 };
	std::cout << "--Intvector:\n";
	for (const int& i : intvector)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl << std::endl;
	TestAllOfAnyOfNoneOf(intvector);
	TestSortAlgorithm(intvector);
	TestCountCountIf(intvector);
	TestFindFindIfFindIfNot(intvector);
	TestSearch(intvector);
	std::cin.get();
}

int SortByMax(const int lhs, const int rhs)
{
	return lhs > rhs;
}

bool IsZero(const int number)
{
	return number == 0;
}

bool IsEven(const int number)
{
	return !(number % 2) && number != 0;
}

void TestSortAlgorithm(std::vector<int>& intvector)
{
	std::cout << "\n--Testing std::sort--\n";
	std::sort(intvector.begin(), intvector.end());
	for (const int& i : intvector)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
	std::cout << "\n--Testing std::sort with functor--\n";
	std::sort(intvector.begin(), intvector.end(), SortByMax);
	for (const int& i : intvector)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
	std::cout << "\n--Testing std::sort with lamda--\n";
	std::sort(intvector.begin(), intvector.end(), [](int lhs, int rhs)
		{
			return lhs < rhs;
		});
	for (const int& i : intvector)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

void TestAllOfAnyOfNoneOf(std::vector<int>& intvector)
{
	std::cout << "--Testing std::all_of--\n";
	if (std::all_of(intvector.begin(), intvector.end(), IsZero))
	{
		std::cout << "All of them are 0\n";
	}
	else
	{
		std::cout << "Not all of them are 0\n";
	}
	std::cout << "\n--Testing std::any_of--\n";
	if (std::any_of(intvector.begin(), intvector.end(), IsZero))
	{
		std::cout << "There is at least one 0 in the list\n";
	}
	else
	{
		std::cout << "There is no 0 in the list\n";
	}
	std::cout << "\n--Testing std::none_of--\n";
	if (std::none_of(intvector.begin(), intvector.end(), IsZero))
	{
		std::cout << "None of them are 0\n";
	}
	else
	{
		std::cout << "There is at least one 0 in the list\n";
	}
}

void TestCountCountIf(std::vector<int>& intvector)
{
	std::cout << "\n--Testing std::count--\n";
	std::cout << "There are " << std::count(intvector.begin(), intvector.end(), 2) << " twos in the list\n";
	std::cout << "\n--Testing std::countif--\n";
	std::cout << "There are " << std::count_if(intvector.begin(), intvector.end(), IsEven) << " even numbers in the list\n";
}

void TestFindFindIfFindIfNot(std::vector<int>& intvector)
{
	std::cout << "\n--Testing std::find--\n";
	const int value{ 6 };
	if (std::find(intvector.begin(), intvector.end(), value) != intvector.end())
	{
		std::cout << "We found a " << value << " in the list\n";
	}
	else
	{
		std::cout << "We didnt find a " << value << " in the list\n";
	}
	std::cout << "\n--Testing std::find_if--\n";
	std::cout << "We found an even number in the list: " << *std::find_if(intvector.begin(), intvector.end(), IsEven) << std::endl;
	std::cout << "\n--Testing std::find_if_not--\n";
	std::cout << "We found an odd number in the list: " << *std::find_if_not(intvector.begin(), intvector.end(), IsEven) << std::endl;
}

void TestSearch(std::vector<int>& intvector)
{
	const std::vector<int> value{ 2,6,9 };
	std::cout << "\n--Testing std::search--\n";
	std::cout << "We found the elements at location " << std::search(intvector.begin(), intvector.end(), value.begin(), value.end()) - intvector.begin() << std::endl;
}
