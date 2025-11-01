#pragma once
#include<iostream>
#include<vector>
#include"ClsString.h"
#pragma warning(disable : 4996)
using namespace std;

class ClsDate
{
private:
	short _Day = 1;
	short _Month = 1;
	short _Year = 1900;

public:

	void setDay(short D)
	{
		_Day = D;
	}
	short GetDay()
	{
		return _Day;
	}

	void setMonth(short M)
	{
		_Month = M;
	}
	short GetMonth()
	{
		return _Month;
	}

	void setYear(short Y)
	{
		_Year = Y;
	}
	short GetYear()
	{
		return _Year;
	}

	// One Line Property
	__declspec(property(get = GetDay, put = setDay)) short Day;
	__declspec(property(get = GetMonth, put = setMonth)) short Month;
	__declspec(property(get = GetYear, put = setYear)) short Year;

	// Default Constructor
	ClsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;
	}
	// Paramitariz Constructor
	ClsDate(string DateString)
	{
		vector<string>Date = ClsString::Split(DateString, "/");

		_Day = stoi(Date[0]);
		_Month = stoi(Date[1]);
		_Year = stoi(Date[2]);
	}
	// Paramitariz Constructor
	ClsDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}


	void Print()
	{
		cout << _Day << "/" << _Month << "/" << _Year << endl;
	}

	static	ClsDate GetSystemDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		short Day, Month, Year;
		Day = now->tm_mday;
		Month = now->tm_mon + 1;
		Year = now->tm_year + 1900;

		return ClsDate(Day, Month, Year);
	}
	static short NumberOfDaysInMonth(short Month, short Year)
	{
		if (Month < 1 || Month > 12)return 0;
		short ArrM[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

		return (Month == 2) ? IsLeapYear(Year) ? 29 : 28 :
			ArrM[Month - 1];
	}
	short NumberOfDaysInMonth()
	{
		return NumberOfDaysInMonth(_Month, _Year);
	}

	static bool InValedDate(ClsDate Date)
	{
		if (Date.Day < 1 || Date.Day > 31) return false;

		if (Date.Month < 1 || Date.Month>12)return false;

		if (Date.Month == 2)
		{
			if (IsLeapYear(Date.Year))
			{
				if (Date.Day > 29 || Date.Day < 1)return false;

				else if (Date.Month > 28)
				{
					return false;
				}

			}

		}
		if (Date.Day > NumberOfDaysInMonth(Date.Month, Date.Year))
		{
			return false;
		}
		return true;
	}
	bool InValedDate()
	{
		return InValedDate(*this);
	}

	static string DateToString(ClsDate Date)
	{
		string SDate =
			to_string(Date.Day) + "/"
			+ to_string(Date.Month) + "/"
			+ to_string(Date.Year);
		return SDate;
	}
	string DateToString()
	{
		return DateToString(*this);
	}


	static bool IsLeapYear(short Year)
	{
		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0) ? true : false;
	}
	bool IsLeapYear()
	{
		return IsLeapYear(_Year);
	}

	static	short NumberOfDayInYear(short Year)
	{
		return IsLeapYear(Year) ? 366 : 365;
	}
	short NumberOfDayInYear()
	{
		return NumberOfDayInYear(Year);
	}

	static	short NumberOfHoursInYear(short Year)
	{
		return NumberOfDayInYear(Year) * 24;
	}
	short NumberOfHoursInYear()
	{
		return NumberOfHoursInYear(Year);
	}

	static int NumberOfMinutesInYear(short Year)
	{
		return NumberOfHoursInYear(Year) * 60;
	}
	int NumberOfMinutesInYear()
	{
		return NumberOfMinutesInYear(Year);
	}

	static int NumberOfSecondsInYear(short Year)
	{
		return	NumberOfMinutesInYear(Year) * 60;
	}
	int NumberOfSecondsInYear()
	{
		return NumberOfSecondsInYear();
	}


	static	short NumberOfHoursInMonth(short Year, short Month)
	{
		return NumberOfDaysInMonth(Month, Year) * 24;
	}
	short NumberOfHoursInMonth()
	{
		return NumberOfHoursInYear(_Year);
	}

	static int NumberOfMinutesInMonth(short Year, short Month)
	{
		return NumberOfHoursInMonth(Year, Month) * 60;
	}
	int NumberOfMinutesInMonth()
	{
		return NumberOfMinutesInMonth(_Year, _Month);
	}

	static int NumberOfSecondsInMonth(short Year, short Month)
	{
		return	NumberOfSecondsInMonth(Year, Month) * 60;
	}
	int NumberOfSecondsInMonth()
	{
		return NumberOfSecondsInMonth(Year, Month);
	}


	static	short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a, y, m;
		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + (12 * a) - 2;
		// Gregorian://0:sun, 1:Mon, 2:Tue...etc
		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}
	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(_Day, _Month, _Year);
	}



	static string NameOfDayWeek(short NumberOfDay)
	{
		string arrDayNames[]
			= { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

		return arrDayNames[NumberOfDay - 1];
	}
	static string NameOfDayWeek(short Day, short Month, short Year)
	{
		int NumberOfDays = DayOfWeekOrder(Day, Month, Year);
		string arrDayNames[]
			= { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return arrDayNames[NumberOfDays - 1];
	}
	string NameOfDayWeek()
	{
		return NameOfDayWeek(_Day, _Month, _Year);
	}

	static string NameOfMonth(short Month)
	{
		if (Month < 1 || Month > 12)return "";
		string MonhtName[12] = { "Jan", "Feb", "Mar", "Apr", "May",
			"Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

		return MonhtName[Month - 1];
	}
	string NameOfMonth()
	{
		return NameOfMonth(_Month);
	}

	static void PrintMonthCalender(short Month, short Year)
	{
		short Current = DayOfWeekOrder(1, Month, Year);
		int NumberOfDInMonth = NumberOfDaysInMonth(Month, Year);

		printf("\n------------------%s----------------\n\n",
			NameOfMonth(Month).c_str());

		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		int i = 0;
		for (i = 0; i < Current; i++)
			printf("     ");//                

		for (int f = 1; f <= NumberOfDInMonth;f++)
		{
			printf("%5d", f);
			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}

		printf("\n----------------------------\n");

	}
	void PrintMonthCalender()
	{
		PrintMonthCalender(_Month, _Year);
	}

	static void PrintYearCalender(short Month, short Year)
	{
		printf("\n-----------------------------\n\n");
		printf("          Calender - %d \n", Year);
		printf("\n-----------------------------\n\n");

		for (int t = 1; t <= 12; t++)
		{
			PrintMonthCalender(t, Year);
		}
	}
	void PrintYearCalender()
	{
		PrintYearCalender(_Month, _Year);
	}

	static int NumberOfDaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
	{
		int TotalDays = 0;

		for (int t = 1;t < Month; t++)
		{
			TotalDays += NumberOfDaysInMonth(Year, Month);
		}
		return TotalDays;
	}
	int NumberOfDaysFromTheBeginingOfTheYear()
	{
		return NumberOfDaysFromTheBeginingOfTheYear
		(_Day, _Month, _Year);
	}

	static ClsDate GetDateFromDayOrderInYear(short DateOrderInYear, short Year)
	{
		ClsDate Date;
		int Remaining = DateOrderInYear;
		Date.Month = 1;
		Date.Year = Year;
		while (true)
		{
			int DayOfMonth = NumberOfDaysInMonth(Date.Month, Year);

			if (Remaining > DayOfMonth)
			{
				Remaining -= DayOfMonth;
				Date.Month++;

				if (Date.Month > 12)
				{
					Date.Year++;
					Date.Month = 1;
				}

			}

			else
			{
				Date.Day = Remaining;
				break;
			}

		}
		return Date;
	}

	void AddDays(int Days)
	{
		int TotalDays = Days + NumberOfDaysFromTheBeginingOfTheYear
		(_Day, _Month, _Year);
		_Month = 1;
		while (true)
		{
			int DaysOfCurrentMonth = NumberOfDaysInMonth();

			if (TotalDays > DaysOfCurrentMonth)
			{
				TotalDays -= DaysOfCurrentMonth;
				_Month++;

				if (_Month == 12)
				{
					_Month = 1;
					_Year++;
				}

			}
			else
			{
				_Day = TotalDays;
				break;
			}
		}

	}


	static void SwapDates(ClsDate& Date1, ClsDate& Date2)
	{
		ClsDate Temp;
		Temp = Date1;
		Date1 = Date2;
		Date2 = Temp;
	}

	static bool IsDate1BeforeDate2(ClsDate Date1, ClsDate Date2)
	{
		return(Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ?
			(Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ?
				Date1.Day < Date2.Day : false)) : false);

		/*(Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ?

		( (Date1.Month < Date2.Month) ? true : (Date1.Month == Date2.Month) ?

		( (Date1.Day < Date2.Day) ? true : false) : false ): false);*/

	}
	bool IsDateBeforeDate2(ClsDate Date2)
	{
		//note: *this sends the current object :-) 
		return  IsDate1BeforeDate2(*this, Date2);

	}

	static bool IsDate1DEQualDate2(ClsDate Date1, ClsDate Date2)
	{
		return  (Date1.Year == Date2.Year) ?
			((Date1.Month == Date2.Month) ?
				((Date1.Day == Date2.Day) ? true : false) : false) : false;
	}
	bool IsDate1DEQualDate2(ClsDate Date2)
	{
		return IsDate1DEQualDate2(*this, Date2);
	}

	static bool LastDayInMonth(ClsDate Date)
	{

		return
			(Date.Day == NumberOfDaysInMonth(Date.Month, Date.Month));

	}
	bool LastDayInMonth()
	{
		return LastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(ClsDate Date)
	{
		return (Date.Month == 12);
	}

	static ClsDate AddOneDay(ClsDate Date)
	{
		if (LastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date))
			{
				Date.Year++;
				Date.Month = 1;
				Date.Day = 1;
			}
			else
			{
				Date.Month++;
				Date.Day = 1;
			}
		}
		else
		{
			Date.Day++;
		}
		return Date;
	}
	void AddOneDay()
	{
		*this = AddOneDay(*this);
	}

	static int GetDifferenceInDays(ClsDate Date1, ClsDate Date2, bool IncludeEndDay = false)
	{
		//this will take care of negative diff
		int Days = 0;
		short SawpFlagValue = 1;

		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			//Swap Dates 
			SwapDates(Date1, Date2);
			SawpFlagValue* (-1);

		}

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = AddOneDay(Date1);
		}

		return IncludeEndDay ? ++Days * SawpFlagValue : Days * SawpFlagValue;
	}
	int GetDifferenceInDays(ClsDate Date)
	{
		return GetDifferenceInDays(*this, Date);
	}

	static int CalculateMyAgeImDays(ClsDate BirthDate)
	{
		return GetDifferenceInDays(BirthDate, ClsDate::GetSystemDate());

	}

	// Not need To Any Nonstatic Funcation Because did't Depend On Any Data From It;
	static ClsDate IncreasDateByOneWeek(ClsDate& Date)
	{
		for (int t = 0;t < 7;t++)
		{
			Date = AddOneDay(Date);
		}

		return Date;
	}
	void IncreasDateByOneWeek()
	{
		IncreasDateByOneWeek(*this);
	}

	static ClsDate IncreasByXWeek(short Weeks, ClsDate& Date)
	{
		for (int i = 0; i < Weeks;i++)
		{
			Date = IncreasDateByOneWeek(Date);
		}
		return Date;
	}
	void IncreasByXWeek(short Weeks)
	{
		IncreasByXWeek(Weeks, *this);
	}

	static ClsDate IncreasByOneMonth(ClsDate& Date)
	{
		if (IsLastMonthInYear(Date))
		{

			Date.Year++;
			Date.Month = 1;
		}
		else
		{
			Date.Month++;
		}
		short NumberOfDaysInCurrentMonth =
			NumberOfDaysInMonth(Date.Month, Date.Year);
		// 31/1/2024 --> 31/2/2024 ===> InCorrect Case
		if (Date.Day > NumberOfDaysInCurrentMonth)
		{
			Date.Day = NumberOfDaysInCurrentMonth;
		}
		// 31/1/2024 --> 28/2/2024 ===> Correct Case

		return Date;
	}
	void IncreasByOneMonth()
	{
		IncreasByOneMonth(*this);
	}

	ClsDate IncreaseDateByXDays(short Days, ClsDate& Date)
	{

		for (short i = 1; i <= Days; i++)
		{
			Date = AddOneDay(Date);
		}
		return Date;
	}
	void IncreaseDateByXDays(short Days)
	{

		IncreaseDateByXDays(Days, *this);
	}

	ClsDate IncreaseDateByXMonths(short Months, ClsDate& Date)
	{

		for (short i = 1; i <= Months; i++)
		{
			Date = IncreasByOneMonth(Date);
		}
		return Date;
	}
	void IncreaseDateByXMonths(short Months)
	{
		IncreaseDateByXMonths(Months, *this);
	}

	static ClsDate IncreaseDateByOneYear(ClsDate& Date)
	{
		Date.Year++;
		return Date;
	}
	void IncreaseDateByOneYear()
	{
		IncreaseDateByOneYear(*this);
	}

	ClsDate IncreaseDateByXYears(short Years, ClsDate& Date)
	{
		Date.Year += Years;
		return Date;

	}
	void IncreaseDateByXYears(short Years)
	{
		IncreaseDateByXYears(Years);
	}

	ClsDate IncreaseDateByOneDecade(ClsDate& Date)
	{
		//Period of 10 years
		Date.Year += 10;
		return Date;
	}
	void IncreaseDateByOneDecade()
	{
		IncreaseDateByOneDecade(*this);
	}

	ClsDate IncreaseDateByXDecades(short Decade, ClsDate& Date)
	{
		Date.Year += Decade * 10;
		return Date;
	}
	void IncreaseDateByXDecades(short Decade)
	{
		IncreaseDateByXDecades(Decade, *this);
	}

	ClsDate IncreaseDateByOneCentury(ClsDate& Date)
	{
		//Period of 100 years
		Date.Year += 100;
		return Date;
	}
	void IncreaseDateByOneCentury()
	{
		IncreaseDateByOneCentury(*this);
	}

	ClsDate IncreaseDateByOneMillennium(ClsDate& Date)
	{
		//Period of 1000 years
		Date.Year += 1000;
		return Date;
	}
	ClsDate IncreaseDateByOneMillennium()
	{
		IncreaseDateByOneMillennium(*this);
	}

	static ClsDate DecreaseDateByOneDay(ClsDate Date)
	{
		if (Date.Day == 1)
		{
			if (Date.Month == 1)
			{
				Date.Month = 12;
				Date.Day = 31;
				Date.Year--;
			}
			else
			{

				Date.Month--;
				Date.Day = NumberOfDaysInMonth(Date.Month, Date.Year);
			}
		}
		else
		{
			Date.Day--;
		}

		return Date;
	}
	void DecreaseDateByOneDay()
	{
		DecreaseDateByOneDay(*this);
	}

	static ClsDate DecreaseDateByOneWeek(ClsDate& Date)
	{

		for (int i = 1; i <= 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}
	void DecreaseDateByOneWeek()
	{
		DecreaseDateByOneWeek(*this);
	}

	static ClsDate DecreaseDateByXWeeks(short Weeks, ClsDate& Date)
	{

		for (short i = 1; i <= Weeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}
	void DecreaseDateByXWeeks(short Weeks)
	{
		DecreaseDateByXWeeks(Weeks, *this);
	}

	static ClsDate DecreaseDateByOneMonth(ClsDate& Date)
	{

		if (Date.Month == 1)
		{
			Date.Month = 12;
			Date.Year--;
		}
		else
			Date.Month--;


		//last check day in date should not exceed max days in the current month
	   // example if date is 31/3/2022 decreasing one month should not be 31/2/2022, it should
	   // be 28/2/2022

		short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Month, Date.Year);
		if (Date.Day > NumberOfDaysInCurrentMonth)
		{
			Date.Day = NumberOfDaysInCurrentMonth;
		}


		return Date;
	}
	void DecreaseDateByOneMonth()
	{
		DecreaseDateByOneMonth(*this);
	}

	static ClsDate DecreaseDateByXDays(short Days, ClsDate& Date)
	{

		for (short i = 1; i <= Days; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}
	void DecreaseDateByXDays(short Days)
	{
		DecreaseDateByXDays(Days, *this);
	}

	static ClsDate DecreaseDateByXMonths(short Months, ClsDate& Date)
	{

		for (short i = 1; i <= Months; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}
	void DecreaseDateByXMonths(short Months)
	{
		DecreaseDateByXMonths(Months, *this);
	}

	static ClsDate DecreaseDateByOneYear(ClsDate& Date)
	{

		Date.Year--;
		return Date;
	}
	void DecreaseDateByOneYear()
	{
		DecreaseDateByOneYear(*this);
	}

	static ClsDate DecreaseDateByXYears(short Years, ClsDate& Date)
	{

		Date.Year -= Years;
		return Date;
	}
	void DecreaseDateByXYears(short Years)
	{
		DecreaseDateByXYears(Years, *this);
	}

	static ClsDate DecreaseDateByOneDecade(ClsDate& Date)
	{
		//Period of 10 years
		Date.Year -= 10;
		return Date;
	}
	void DecreaseDateByOneDecade()
	{
		DecreaseDateByOneDecade(*this);
	}

	static ClsDate DecreaseDateByXDecades(short Decades, ClsDate& Date)
	{

		Date.Year -= Decades * 10;
		return Date;
	}
	void DecreaseDateByXDecades(short Decades)
	{
		DecreaseDateByXDecades(Decades, *this);
	}

	static ClsDate DecreaseDateByOneCentury(ClsDate& Date)
	{
		//Period of 100 years
		Date.Year -= 100;
		return Date;
	}
	void DecreaseDateByOneCentury()
	{
		DecreaseDateByOneCentury(*this);
	}

	static ClsDate DecreaseDateByOneMillennium(ClsDate& Date)
	{
		//Period of 1000 years
		Date.Year -= 1000;
		return Date;
	}
	void DecreaseDateByOneMillennium()
	{
		DecreaseDateByOneMillennium(*this);
	}

	static short IsEndOfWeek(ClsDate Date)
	{
		return  DayOfWeekOrder(Date.Day, Date.Month, Date.Year) == 6;
	}
	short IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(ClsDate Date)
	{
		//Weekends are Fri and Sat
		short DayIndex = DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
		return  (DayIndex == 5 || DayIndex == 6);
	}
	bool IsWeekEnd()
	{
		return  IsWeekEnd(*this);
	}

	static bool IsBusinessDay(ClsDate Date)
	{
		//Weekends are Sun,Mon,Tue,Wed and Thur

	   /*
		short DayIndex = DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
		return  (DayIndex >= 5 && DayIndex <= 4);
	   */

	   //shorter method is to invert the IsWeekEnd: this will save updating code.
		return !IsWeekEnd(Date);

	}
	bool IsBusinessDay()
	{
		return  IsBusinessDay(*this);
	}
	//i added this method to calculate business days between 2 days
	static short CalculateBusinessDays(ClsDate DateFrom, ClsDate DateTo)
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

	static short CalculateVacationDays(ClsDate DateFrom, ClsDate DateTo)
	{
		/*short Days = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				Days++;

			DateFrom = AddOneDay(DateFrom);
		}*/

		return CalculateBusinessDays(DateFrom, DateTo);

	}
	//above method is eough , no need to have method for the object

	static ClsDate CalculateVacationReturnDate(ClsDate DateFrom, short VacationDays)
	{

		short WeekEndCounter = 0;

		for (short i = 1; i <= VacationDays; i++)
		{

			if (IsWeekEnd(DateFrom))
				WeekEndCounter++;

			DateFrom = AddOneDay(DateFrom);
		}
		//to add weekends 
		for (short i = 1; i <= WeekEndCounter; i++)
			DateFrom = AddOneDay(DateFrom);

		return DateFrom;
	}

	static bool IsDate1AfterDate2(ClsDate Date1, ClsDate Date2)
	{
		bool Value = (!IsDate1BeforeDate2(Date1, Date2) &&
			!IsDate1DEQualDate2(Date1, Date2));
		return Value;
	}
	bool IsDateAfterDate2(ClsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	enum enDateCompare { Before = -1, Equal = 0, After = 1 };
	static enDateCompare CompareDates(ClsDate Date1, ClsDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Before;

		if (IsDate1DEQualDate2(Date1, Date2))
			return enDateCompare::Equal;

		/* if (IsDate1AfterDate2(Date1,Date2))
			 return enDateCompare::After;*/

			 //this is faster
		return enDateCompare::After;

	}
	enDateCompare CompareDates(ClsDate Date2)
	{
		return CompareDates(*this, Date2);
	}

};
