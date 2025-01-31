#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <ctime> 
//#include "C:\Users\XPRISTO\Desktop\Programming Fundamentals course\10_OOP_Level01\Projects\String_Library\String_Library\clsString.h"
#include "clsString.h"
using namespace std;

class clsDate
{
private:
	short _day;
	short _month;
	short _year;

public:

	clsDate()
	{
		time_t currentTime = time(0);
		tm* localTime = localtime(&currentTime);

		_day = localTime->tm_mday;
		_month = localTime->tm_mon + 1;
		_year = localTime->tm_year + 1900;
	}
	clsDate(string date)
	{
		vector<string> dateComponents = clsString::splitString(date, "/");

		_day = stoi(dateComponents[0]);
		_month = stoi(dateComponents[1]);
		_year = stoi(dateComponents[2]);
	}
	clsDate(short day, short month, short year)
	{
		_day = day;
		_month = month;
		_year = year;
	}
	clsDate(short totalDays, short year)
	{
		*this = getDateFromTotalDays(totalDays, year);
		_day = this->day;
		_month = this->month;
		_year = this->year;
	}

	void setDay(short day)
	{
		_day = day;
	}
	short getDay()
	{
		return _day;
	}
	_declspec(property(get = getDay, put = setDay)) short day;

	void setMonth(short month)
	{
		_month = month;
	}
	short getMonth()
	{
		return _month;
	}
	_declspec(property(get = getMonth, put = setMonth)) short month;
	
	void setYear(short year)
	{
		_year = year;
	}
	short getYear()
	{
		return _year;
	}
	_declspec(property(get = getYear, put = setYear)) short year;

	void print()
	{
		cout << dateToString() << "\n";
	}

	static bool isLeapYear(short year)
	{
		return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
	}
	bool isLeapYear()
	{
		return isLeapYear(_year);
	}

	static short numberOfDaysInAYear(short year)
	{
		return isLeapYear(year) ? 366 : 365;
	}
	short numberOfDaysInAYear()
	{
		return numberOfDaysInAYear(_year);
	}

	static short numberOfHoursInAYear(short year)
	{
		return numberOfDaysInAYear(year) * 24;
	}
	short numberOfHoursInAYear()
	{
		return numberOfHoursInAYear(_year);
	}

	static int numberOfMinutesInAYear(short year)
	{
		return numberOfHoursInAYear(year) * 60;
	}
	int numberOfMinutesInAYear()
	{
		return numberOfMinutesInAYear(_year);
	}

	static int numberOfSecondsInAYear(short year)
	{
		return numberOfMinutesInAYear(year) * 60;
	}
	int numberOfSecondsInAYear()
	{
		return numberOfSecondsInAYear(_year);
	}

	static short numberOfDaysInAMonth(short month, short year)
	{
		if (month < 1 || month > 12)
			return 0;

		short numberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

		return month == 2 ? (isLeapYear(year) ? 29 : 28) : numberOfDays[month - 1];
	}
	short numberOfDaysInAMonth()
	{
		return numberOfDaysInAMonth(_month, _year);
	}

	static short numberOfHoursInAMonth(short month, short year)
	{
		return numberOfDaysInAMonth(month, year) * 24;
	}
	short numberOfHoursInAMonth()
	{
		return numberOfHoursInAMonth(_month, _year);
	}

	static int numberOfMinutesInAMonth(short month, short year)
	{
		return numberOfHoursInAMonth(month, year) * 60;
	}
	int numberOfMinutesInAMonth()
	{
		return numberOfMinutesInAMonth(_month, _year);
	}

	static int numberOfSecondsInAMonth(short month, short year)
	{
		return numberOfMinutesInAMonth(month, year) * 60;
	}
	int numberOfSecondsInAMonth()
	{
		return numberOfSecondsInAMonth(_month, _year);
	}

	static short dayOfWeekOrder(short day, short month, short year)
	{
		short a, y, m, d;
		a = (14 - month) / 12;
		y = year - a;
		m = month + 12 * a - 2;
		// Gregorian:
		// 0:Sun, 1:Mon, 2:Tue...
		d = (day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;
		return d;
	}
	static short dayOfWeekOrder(clsDate date)
	{
		return dayOfWeekOrder(date.day, date.month, date.year);
	}
	short dayOfWeekOrder()
	{
		return dayOfWeekOrder(*this);
	}

	static string dayShortName(short dayOrder)
	{
		string daysOfTheWeek[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
		return daysOfTheWeek[dayOrder];
	}
	string dayShortName()
	{
		return dayShortName(dayOfWeekOrder());
	}

	static string monthShortName(short month)
	{
		string monthsOfTheYear[12] = { "Jan", "Fer", "Mar","Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		return monthsOfTheYear[month - 1];
	}
	string monthShortName()
	{
		return monthShortName(_month);
	}

	static void printWeekDays()
	{
		string daysOfTheWeek[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		for (short i = 0; i < 7; i++)
		{
			cout << daysOfTheWeek[i] << "  ";
		}
		cout << "\n  ";
	}

	static void printMonthCalendar(short month, short year)
	{
		// Index of the day from 0 to 6
		short current = dayOfWeekOrder(1, month, year);

		short numberOfDays = numberOfDaysInAMonth(month, year);

		// Print the current month name
		printf("  _____________%s_________________\n\n", monthShortName(month).c_str());

		// Print the columns
		printf("  Sun  Mon  Tue  Wen  Thu  Fri  Sat\n");

		// Print appropriate spaces
		short i;
		for (i = 0; i < current; i++)
		{
			printf("     ");
		}

		for (short j = 1; j <= numberOfDays; j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}
		printf("\n  _________________________________\n");
	}
	void printMonthCalendar()
	{
		printMonthCalendar(_month, _year);
	}

	static void printYearCalendar(short year)
	{
		printf("\n  _________________________________\n\n");
		printf("           Calendar - %d           ", year);
		printf("\n  _________________________________\n\n");

		const short numberOfMonts = 12;
		for (short month = 1; month <= numberOfMonts; month++)
		{
			printMonthCalendar(month, year);
		}
	}
	void printYearCalendar()
	{
		printYearCalendar(_year);
	}

	static short numberOfDaysFromTheBeginningOfTheYear(short day, short month, short year)
	{
		short totalDays = 0;

		for (short i = 1; i <= month - 1; i++)
		{
			totalDays += numberOfDaysInAMonth(i, year);
		}

		totalDays += day;

		return totalDays;
	}
	short numberOfDaysFromTheBeginningOfTheYear()
	{
		return numberOfDaysFromTheBeginningOfTheYear(_day, _month, _year);
	}

	static clsDate getDateFromTotalDays(short totalDays, short year)
	{
		clsDate date;

		short remainingDays = totalDays;
		short monthDays = 0;

		date.year = year;
		date.month = 1;

		while (true)
		{
			monthDays = numberOfDaysInAMonth(date.month, year);
			if (remainingDays > monthDays)
			{
				remainingDays -= monthDays;
				date.month++;
			}
			else
			{
				date.day = remainingDays;
				break;
			}
		}
		return date;
	}

	static clsDate addDaysToDate(short additionalDays, clsDate &date)
	{
		short remainingDays = additionalDays + numberOfDaysFromTheBeginningOfTheYear(date.day, date.month, date.year);
		short monthDays = 0;

		date.month = 1;

		while (true)
		{
			monthDays = numberOfDaysInAMonth(date.month, date.year);
			if (remainingDays > monthDays)
			{
				remainingDays -= monthDays;
				date.month++;

				if (date.month > 12)
				{
					date.month = 1;
					date.year++;
				}
			}
			else
			{
				date.day = remainingDays;
				break;
			}
		}
		return date;
	}
	void addDaysToDate(short additionalDays)
	{
		addDaysToDate(additionalDays, *this);
	}

	static bool isDate1LessThanDate2(clsDate date1, clsDate date2)
	{
		return date1.year < date2.year ? true : (date1.year == date2.year ? (date1.month < date2.month ? true : (date1.month == date2.month ? date1.day < date2.day : false)) : false);
	}
	bool isDateLessThanDate2(clsDate date2)
	{
		// note; *this sends current object
		return isDate1LessThanDate2(*this, date2);
	}

	static bool isDate1EqualToDate2(clsDate date1, clsDate date2)
	{                                                              
		return (date1.year == date2.year) && (date1.month == date2.month) && (date1.day == date2.day);
	}
	bool isDateEqualToDate2(clsDate date2)
	{
		return isDate1EqualToDate2(*this, date2);
	}

	static bool isLastDayInMonth(clsDate &date)
	{
		return date.day == numberOfDaysInAMonth(date.month, date.year);
	}
	bool isLastDayInMonth()
	{
		return isLastDayInMonth(*this);
	}

	static bool isLastMonthInYear(short month)
	{
		return month == 12;
	}
	bool isLastMonthInYear()
	{
		return _month == 12;
	}

	static clsDate increaseDateByOneDay(clsDate &date)
	{
		if (isLastDayInMonth(date))
		{
			if (isLastMonthInYear(date.month))
			{
				date.day = 1;
				date.month = 1;
				date.year++;
			}
			else
			{
				date.day = 1;
				date.month++;
			}
		}
		else
		{
			date.day++;
		}
		return date;
	}
	void increaseDateByOneDay()
	{
		increaseDateByOneDay(*this);
	}

	static void swapDates(clsDate& date1, clsDate& date2)
	{
		clsDate tempDate;
		tempDate = date1;
		date1 = date2;
		date2 = tempDate;
	}
	void swapDates(clsDate& date2)
	{
		swapDates(*this, date2);
	}

	static int getDifferenceInDays(clsDate date1, clsDate date2, bool includeEndDay = false)
	{
		int days = 0;
		short swapFlagValue = 1;

		if (!isDate1LessThanDate2(date1, date2) && !isDate1EqualToDate2(date1, date2))
		{
			swapDates(date1, date2);
			swapFlagValue = -1;
		}

		while (isDate1LessThanDate2(date1, date2))
		{
			days++;
			date1 = increaseDateByOneDay(date1);
		}

		if (includeEndDay == false)
			days--;

		return days * swapFlagValue;
	}
	int getDifferenceInDays(clsDate date2, bool includeEndDay = false)
	{
		return getDifferenceInDays(*this, date2, includeEndDay);
	}

	static clsDate getCurrentDate()
	{
		clsDate currentDate;
		time_t currentTime = time(0);
		tm* localTime = localtime(&currentTime);

		currentDate.year = localTime->tm_year + 1900;
		currentDate.month = localTime->tm_mon + 1;
		currentDate.day = localTime->tm_mday;

		return currentDate;
	}

	static string getSystemDateTimeString()
	{
		string currentTime;
		time_t t = time(0);
		tm* localTime = localtime(&t);

		short day, month, year, hour, minute, second;

		day = localTime->tm_mday;
		month = localTime->tm_mon + 1;
		year = localTime->tm_year + 1900;
		hour = localTime->tm_hour;
		minute = localTime->tm_min;
		second = localTime->tm_sec;

		return to_string(day) + "/" + to_string(month) + "/" + to_string(year) + " - " + to_string(hour) + ":" + to_string(minute) + ":" + to_string(second);
	}

	static short caluclateMyAgeInDays(clsDate birthDate)
	{
		return getDifferenceInDays(birthDate, getCurrentDate());
	}
	short caluclateMyAgeInDays()
	{
		return caluclateMyAgeInDays(*this);
	}

	static clsDate increaseDateByXDays(clsDate &date, short daysToAdd)
	{
		for (short i = 1; i <= daysToAdd; i++)
		{
			date = increaseDateByOneDay(date);
		}
		return date;
	}
	void increaseDateByXDays(short daysToAdd)
	{
		increaseDateByXDays(*this, daysToAdd);
	}

	static clsDate increaseDateByOneWeek(clsDate &date)
	{
		return increaseDateByXDays(date, 7);
	}
	void increaseDateByOneWeek()
	{
		increaseDateByOneWeek(*this);
	}

	static clsDate increaseDateByXWeeks(clsDate &date, short weeksToAdd)
	{
		for (short i = 1; i <= weeksToAdd; i++)
		{
			date = increaseDateByOneWeek(date);
		}
		return date;
	}
	void increaseDateByXWeeks(short weeksToAdd)
	{
		increaseDateByXWeeks(*this, weeksToAdd);
	}

	static clsDate increaseDateByOneMonth(clsDate &date)
	{
		if (date.month == 12)
		{
			date.month = 1;
			date.year++;
		}
		else
		{
			date.month++;
		}

		// last check day in date should not exceed max days in the current month
		// example if date is 31/1/2022 increasing one month should not be 31/2/2022, it should be 28/2/2022
		short numberOfDaysInCurrentMonth = numberOfDaysInAMonth(date.month, date.year);
		if (date.day > numberOfDaysInCurrentMonth)
		{
			date.day = numberOfDaysInCurrentMonth;
		}

		return date;
	}
	void increaseDateByOneMonth()
	{
		increaseDateByOneMonth(*this);
	}

	static clsDate increaseDateByXMonths(clsDate &date, short monthsToAdd)
	{
		for (short i = 1; i <= monthsToAdd; i++)
		{
			date = increaseDateByOneMonth(date);
		}
		return date;
	}
	void increaseDateByXMonths(short monthsToAdd)
	{
		increaseDateByXMonths(*this, monthsToAdd);
	}

	static clsDate increaseDateByOneYear(clsDate &date)
	{
		date.year++;
		return date;
	}
	void increaseDateByOneYear()
	{
		increaseDateByOneYear(*this);
	}
	static clsDate increaseDateByXYears(clsDate &date, short yearsToAdd)
	{
		date.year += yearsToAdd;
		return date;
	}
	void increaseDateByXYears(short yearsToAdd)
	{
		increaseDateByXYears(*this, yearsToAdd);
	}

	static clsDate increaseDateByOneDecade(clsDate &date)
	{
		date.year += 10;
		return date;
	}
	void increaseDateByOneDecade()
	{
		increaseDateByOneDecade(*this);
	}

	static clsDate increaseDateByXDecades(clsDate &date, short decadesToAdd)
	{
		date.year += decadesToAdd * 10;
		return date;
	}
	void increaseDateByXDecades(short decadesToAdd)
	{
		increaseDateByXDecades(*this, decadesToAdd);
	}

	static clsDate increaseDateByOneCentury(clsDate &date)
	{
		date.year += 100;
		return date;
	}
	void increaseDateByOneCentury()
	{
		increaseDateByOneCentury(*this);
	}

	static clsDate increaseDateByMillennium(clsDate &date)
	{
		date.year += 1000;
		return date;
	}
	void increaseDateByMillennium()
	{
		increaseDateByMillennium(*this);
	}

	static clsDate decreaseDateByOneDay(clsDate &date)
	{
		if (date.day == 1)
		{
			if (date.month == 1)
			{
				date.month = 12;
				date.day = 31;
				date.year--;
			}
			else
			{
				date.month--;
				date.day = numberOfDaysInAMonth(date.month, date.year);
			}
		}
		else
		{
			date.day--;
		}
		return date;
	}
	void decreaseDateByOneDay()
	{
		decreaseDateByOneDay(*this);
	}

	static clsDate decreaseDateByXDays(clsDate &date, short days)
	{
		for (short i = 1; i <= days; i++)
		{
			date = decreaseDateByOneDay(date);
		}
		return date;
	}
	void decreaseDateByXDays(short days)
	{
		decreaseDateByXDays(*this, days);
	}

	static clsDate decreaseDateByOneWeek(clsDate &date)
	{
		return decreaseDateByXDays(date, 7);
	}
	void decreaseDateByOneWeek()
	{
		decreaseDateByOneWeek(*this);
	}

	static clsDate decreaseDateByXWeeks(clsDate &date, short weeks)
	{
		for (short i = 1; i <= weeks; i++)
		{
			date = decreaseDateByOneWeek(date);
		}
		return date;
	}
	void decreaseDateByXWeeks(short weeks)
	{
		decreaseDateByXWeeks(*this, weeks);
	}

	static clsDate decreaseDateByOneMonth(clsDate &date)
	{
		if (date.month == 1)
		{
			date.month = 12;
			date.year--;
		}
		else
		{
			date.month--;
		}

		// last check day in date should not exceed max days in the current month
		// example if date is 31/3/2022 decreasing one month should not be 31/2/2022, it should be 28/2/2022
		short numberOfDaysInCurrentMonth = numberOfDaysInAMonth(date.month, date.year);
		if (date.day > numberOfDaysInCurrentMonth)
		{
			date.day = numberOfDaysInCurrentMonth;
		}
		return date;
	}
	void decreaseDateByOneMonth()
	{
		decreaseDateByOneMonth(*this);
	}

	static clsDate decreaseDateByXMonths(clsDate &date, short months)
	{
		for (short i = 1; i <= months; i++)
		{
			date = decreaseDateByOneMonth(date);
		}
		return date;
	}
	void decreaseDateByXMonths(short months)
	{
		decreaseDateByXMonths(*this, months);
	}

	static clsDate decreaseDateByOneYear(clsDate &date)
	{
		date.year--;
		return date;
	}
	void decreaseDateByOneYear()
	{
		decreaseDateByOneYear(*this);
	}

	static clsDate decreaseDateByXYears(clsDate &date, short years)
	{
		date.year -= years;
		return date;
	}
	void decreaseDateByXYears(short years)
	{
		decreaseDateByXYears(*this, years);
	}

	static clsDate decreaseDateByOneDecade(clsDate &date)
	{
		date.year -= 10;
		return date;
	}
	void decreaseDateByOneDecade()
	{
		decreaseDateByOneDecade(*this);
	}

	static clsDate decreaseDateByXDecades(clsDate &date, short decades)
	{
		date.year -= decades * 10;
		return date;
	}
	void decreaseDateByXDecades(short decades)
	{
		decreaseDateByXDecades(*this, decades);
	}

	static clsDate decreaseDateByOneCentury(clsDate &date)
	{
		date.year -= 100;
		return date;
	}
	void decreaseDateByOneCentury()
	{
		decreaseDateByOneCentury(*this);
	}

	static clsDate decreaseDateByMillennium(clsDate &date)
	{
		date.year -= 1000;
		return date;
	}
	void decreaseDateByMillennium()
	{
		decreaseDateByMillennium(*this);
	}

	static bool isEndOfWeek(clsDate date)
	{
		return dayOfWeekOrder(date) == 0;
	}
	bool isEndOfWeek()
	{
		return isEndOfWeek(*this);
	}

	static bool isWeekEnd(clsDate date)
	{
		// weekends are Sat and Sun
		short dayIndex = dayOfWeekOrder(date);
		return dayIndex == 6 || dayIndex == 0;
	}
	bool isWeekEnd()
	{
		return isWeekEnd(*this);
	}

	static bool isBusinessDay(clsDate date)
	{
		return !isWeekEnd(date);
	}
	bool isBusinessDay()
	{
		return isBusinessDay(*this);
	}

	static short daysUntilTheEndOfWeek(clsDate date)
	{
		return 6 - dayOfWeekOrder(date);
	}
	short daysUntilTheEndOfWeek()
	{
		return daysUntilTheEndOfWeek(*this);
	}

	static short daysUntilTheEndOfMonth(clsDate date)
	{
		return numberOfDaysInAMonth(date.month, date.year) - date.day;
	}
	short daysUntilTheEndOfMonth()
	{
		return daysUntilTheEndOfMonth(*this);
	}

	short daysUntilTheEndOfYear(clsDate date)
	{
		short numberOfDaysInYear = isLeapYear(date.year) ? 366 : 365;
		short totalDays = numberOfDaysFromTheBeginningOfTheYear(date.day, date.month, date.year);
		return numberOfDaysInYear - totalDays;
	}
	short daysUntilTheEndOfYear()
	{
		return daysUntilTheEndOfYear(*this);
	}

	static short calculateVacationDays(clsDate dateFrom, clsDate dateTo)
	{
		short daysCount = 0;
		while (isDate1LessThanDate2(dateFrom, dateTo))
		{
			if (isBusinessDay(dateFrom))
			{
				daysCount++;
			}
			dateFrom = increaseDateByOneDay(dateFrom);
		}
		return daysCount;
	}
	short calculateVacationDays(clsDate dateTo)
	{
		return calculateVacationDays(*this, dateTo);
	}

	/*static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
	{

		short Days = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				Days++;

			DateFrom = AddOneDay(DateFrom);
		}

		return Days;

	}

	static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
	{
		return CalculateBusinessDays(DateFrom, DateTo);

	}*/

	static clsDate calculateVacationReturnDate(clsDate dateFrom, short vacationDays)
	{
		short weekendCounter = 0;

		//in case the data  is weekend keep adding one day util you reach business day
		//we get rid of all weekends before the first business day
		while (isWeekEnd(dateFrom))
		{
			dateFrom = increaseDateByOneDay(dateFrom);
		}

		//here we increase the vacation dates to add all weekends to it.
		for (short i = 1; i <= vacationDays + weekendCounter; i++)
		{
			if (isWeekEnd(dateFrom))
				weekendCounter++;

			dateFrom = increaseDateByOneDay(dateFrom);
		}

		//in case if return date is week end keep adding one day util you reach business day
		while (isWeekEnd(dateFrom))
		{
			dateFrom = increaseDateByOneDay(dateFrom);
		}

		return dateFrom;
	}
	clsDate calculateVacationReturnDate(short vacationDays)
	{
		return calculateVacationReturnDate(*this, vacationDays);
	}

	static bool isDate1BeforeDate2(clsDate date1, clsDate date2)
	{
		return date1.year < date2.year ? true : (date1.year == date2.year ? (date1.month < date2.month ? true : (date1.month == date2.month ? date1.day < date2.day : false)) : false);
	}
	bool isDateBeforeDate2(clsDate date2)
	{
		return isDate1BeforeDate2(*this, date2);
	}

	static bool isDate1AfterDate2(clsDate date1, clsDate date2)
	{
		return !isDate1BeforeDate2(date1, date2) && !isDate1EqualToDate2(date1, date2);
	}
	bool isDateAfterDate2(clsDate date2)
	{
		return isDate1AfterDate2(*this, date2);
	}

	enum enComparisonResult { Before = -1, Equal = 0, After = 1 };
	static enComparisonResult compareDates(clsDate date1, clsDate date2)
	{
		if (isDate1BeforeDate2(date1, date2))
			return Before;

		if (isDate1EqualToDate2(date1, date2))
			return Equal;

		return After;
	}
	enComparisonResult compareDates(clsDate date2)
	{
		return compareDates(*this, date2);
	}

	static bool isValidDate(clsDate date)
	{
		bool validMonth = (date.month > 0 && date.month <= 12);
		bool validDay = (date.day > 0 && date.day <= numberOfDaysInAMonth(date.month, date.year));
		bool validYear = (date.year > 0);
		return validMonth && validDay && validYear;
	}
	bool isValidDate()
	{
		return isValidDate(*this);
	}

	clsDate stringToDate(string dateStr)
	{
		clsDate date;
		vector<string> dateParts = clsString::splitString(dateStr, "/");

		date.day = stoi(dateParts[0]);
		date.month = stoi(dateParts[1]);
		date.year = stoi(dateParts[2]);

		return date;
	}
	static string dateToString(clsDate date)
	{
		return to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year);
	}
	string dateToString()
	{
		return dateToString(*this);
	}

	static string formatDate(clsDate date, string dateFormat = "dd/mm/yyyy")
	{
		string formattedDateString;
		formattedDateString = clsString::replaceSubstring(dateFormat, "dd", to_string(date.day));
		formattedDateString = clsString::replaceSubstring(formattedDateString, "mm", to_string(date.month));
		formattedDateString = clsString::replaceSubstring(formattedDateString, "yyyy", to_string(date.year));
		return formattedDateString;
	}
	string formatDate(string dateFormat = "dd/mm/yyyy")
	{
		return formatDate(*this, dateFormat);
	}
};


