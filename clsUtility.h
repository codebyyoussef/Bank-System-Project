#pragma once
#include <iostream>
#include <string>
#include "clsDate.h"
using namespace std;

class clsUtility
{
public:

	static void Srand()
	{
		srand((unsigned)time(NULL));
	}

	static int randomNumber(int from, int to)
	{
		int randNum = rand() % (to - from + 1) + from;
		return randNum;
	}

	enum enCharType { smallLetter = 1, capitalLetter = 2, digit = 3, specialCharacter = 4, mixChars = 5 };

	static char getRandomCharacter(enCharType charType)
	{
		if (charType == mixChars)
		{
			charType = (enCharType) randomNumber(1, 3);
		}

		switch (charType)
		{
		case smallLetter:
			return randomNumber(97, 122);
		case capitalLetter:
			return randomNumber(65, 90);
		case digit:
			return randomNumber(48, 57);
		case specialCharacter:
			return randomNumber(32, 47);
		}
		return 0;
	}

	static string generateWord(enCharType charType, short length)
	{
		string word = "";
		for (int i = 1; i <= length; i++)
		{
			word += getRandomCharacter(charType);
		}
		return word;
	}

	static string generateKey(enCharType charType)
	{
		string key = "";
		key += generateWord(charType, 4) + '-';
		key += generateWord(charType, 4) + '-';
		key += generateWord(charType, 4) + '-';
		key += generateWord(charType, 4);
		return key;
	}

	static void generateKeys(short numberOfKeys, enCharType charType)
	{
		for (int i = 1; i <= numberOfKeys; i++)
		{
			cout << "Key [" << i << "] : ";
			cout << generateKey(charType) << endl;
		}
	}

	template <typename T> static void swap(T &value1, T &value2)
	{
		T temp;
		temp = value1;
		value1 = value2;
		value2 = temp;
	}

	static void shuffleArray(int arr[], int size)
	{
		for (int i = 0; i < size; i++)
		{
			swap(arr[randomNumber(0, size - 1)], arr[randomNumber(0, size - 1)]);
		}
	}

	static void shuffleArray(string arr[], int size)
	{
		for (int i = 0; i < size; i++)
		{
			swap(arr[randomNumber(0, size - 1)], arr[randomNumber(0, size - 1)]);
		}
	}

	static void fillArrayWithRandomNumbers(int arr[], int arrSize, int from, int to)
	{
		for (int i = 0; i < arrSize; i++)
		{
			arr[i] = randomNumber(from, to);
		}
	}

	static void fillArrayWithRandomWords(string arr[], int arrSize, enCharType charType, short length)
	{
		for (int i = 0; i < arrSize; i++)
		{
			arr[i] = generateWord(charType, length);
		}
	}

	static void fillArrayWithRandomKeys(string arr[], int size, enCharType charType)
	{
		for (int i = 0; i < size; i++)
			arr[i] = generateKey(charType);
	}

	static string tabs(short numberOfTabs)
	{
		string tabs;
		for (int i = 1; i <= numberOfTabs; i++)
		{
			tabs += "\t";
		}
		return tabs;
	}

	static string encryptText(string text, short encryptionKey)
	{
		for (int i = 0; i < text.length(); i++)
		{
			text[i] += encryptionKey;
		}
		return text;
	}

	static string decryptText(string text, short encryptionKey)
	{
		for (int i = 0; i < text.length(); i++)
		{
			text[i] -= encryptionKey;
		}
		return text;
	}

	static string convertNumberToText(int num)
	{
		if (num == 0)
		{
			return "";
		}

		if (num >= 1 && num <= 19)
		{
			string arr[] = { "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
			"eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
			return arr[num];
		}

		if (num >= 20 && num <= 99)
		{
			string arr[] = { "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };
			return arr[num / 10] + (num % 10 != 0 ? " " + convertNumberToText(num % 10) : "");
		}

		if (num >= 100 && num <= 199)
		{
			return "One hundred " + convertNumberToText(num % 100);
		}

		if (num >= 200 && num <= 999)
		{
			return convertNumberToText(num / 100) + " hundreds " + convertNumberToText(num % 100);
		}

		if (num >= 1000 && num <= 1999)
		{
			return "One thousand " + convertNumberToText(num % 1000);
		}

		if (num >= 2000 && num <= 999999)
		{
			return convertNumberToText(num / 1000) + " thousands " + convertNumberToText(num % 1000);
		}

		if (num >= 1000000 && num <= 1999999)
		{
			return "One million " + convertNumberToText(num % 1000000);
		}


		if (num >= 2000000 && num <= 999999999)
		{
			return convertNumberToText(num / 1000000) + " millions " + convertNumberToText(num % 1000000);
		}

		if (num >= 1000000000 && num <= 1999999999)
		{
			return "One billion " + convertNumberToText(num % 1000000000);
		}

		if (num >= 2000000000 && num <= 999999999999)
		{
			return convertNumberToText(num / 1000000000) + " billions " + convertNumberToText(num % 1000000000);
		}
		return "";
	}
};

