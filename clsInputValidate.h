#pragma once
#include <iostream>
#include "clsDate.h"
using namespace std;

class clsInputValidate
{
public:
	template <typename T> static bool isNumberBetween(T num, T from, T to)
	{
		return num >= from && num <= to;
	}

	static bool isDateBetween(clsDate date, clsDate from, clsDate to)
	{
		if (clsDate::isDate1AfterDate2(from, to))
		{
			clsDate::swapDates(from, to);
		}
		return !(clsDate::compareDates(date, from) == clsDate::Before || clsDate::compareDates(date, to) == clsDate::After);
	}

	template <typename T> static T readNumber(string errorMsg = "Invalid Number! Enter a valid number: ")
	{
		T number;
		while (!(cin >> number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << errorMsg;
		}
		return number;
	}

	template <typename T> static T readNumberBetween(T from, T to, string errorMsg)
	{
		T number = readNumber<T>();
		while (!isNumberBetween(number, from, to))
		{
			cout << errorMsg;
			number = readNumber<T>();
		}
		return number;
	}

	static bool isValidDate(clsDate date)
	{
		return clsDate::isValidDate(date);
	}

	static string readString()
	{
		string str;
		getline(cin >> ws, str);
		return str;
	}
};

