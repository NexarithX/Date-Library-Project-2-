#pragma once
#pragma warning(disable : 4996)
#include "clsString.h"
#include <iostream>
#include <string>
#include <compare>
#include <regex>
class clsDate {
public:
     struct sPeriod {
		clsDate* StartDate;
		clsDate* EndDate;
	};
private:
	short _Year;
	short _Month;
	short _Day;
	auto operator<=>(const clsDate&) const = default;
	enum enCompareDate { Before = -1, Equal = 0, After = 1 };
	static int ClaculatePeriodOverLap(const sPeriod &iterPeriod, const sPeriod &Period2)
	{
		int Counter = 0;

		// make local copies to avoid mutating caller's data
		if (iterPeriod.StartDate == nullptr || iterPeriod.EndDate == nullptr)
			return 0;

		clsDate current = *iterPeriod.StartDate;
		clsDate endDate = *iterPeriod.EndDate;

		while (IsDate1BeforeDate2(current, endDate))
		{
			if (isDateWithInPeriod(Period2, current))
				Counter++;
			current = IncreaseDateByOneDay(current);
		}
		return Counter;
	}
public:
	//Constructors
	clsDate()
	{
		clsDate Date = GetSystemDate();
		_Day = Date._Day;
		_Month = Date._Month;
		_Year = Date._Year;
	}
	clsDate(string Date)
	{
		// parse and assign
		*this = StringToDate(Date);
	}
	clsDate(short Day, short Month, short Year)
	{
		// validate provided values before assignment
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}
	clsDate(short OrderDayInYear, short Year) 
	{
		clsDate Date = clsDate::DateFromDayOrderInAYear(OrderDayInYear, Year);
		_Day = Date.getDay();
		_Month = Date.getMonth();
		_Year = Date.getYear();
	}
	// Getter & Setter
	void setDay(short Day)
	{
		_Day = Day;
	}
	void setMonth(short Month)
	{
		_Month = Month;
	}
	void setYear(short Year) {
		_Year = Year;
	}
	short getDay() const
	{
		return _Day;
	}
	short getMonth() const
	{
		return _Month;
	}
	short getYear() const
	{
		return _Year;
	}
	//------------
	
	static bool IsLeapYear(short Year) {
		return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
	}
	bool IsLeapYear() {
		return IsLeapYear(_Year);
	}
	//-------
	static short NumberOfDaysInAYear(short Year)
	{
		return IsLeapYear(Year) ? 366 : 365;
	}
	short NumberOfDaysInAYear() {

		return NumberOfDaysInAYear(_Year);

	}
	static short NumberOfHoursInAYear(short Year)
	{
		return NumberOfDaysInAYear(Year) * 24;
	}
	short NumberOfHoursInAYear()
	{
		return NumberOfDaysInAYear(_Year) * 24;
	}
	static int NumberOfMinutesInAYear(short Year)
	{
		return NumberOfHoursInAYear(Year) * 60;
	}
	int NumberOfMinutesInAYear()
	{
		return NumberOfHoursInAYear(_Year) * 60;
	}
	static int NumberOfSecondsInAYear(short Year)
	{
		return NumberOfMinutesInAYear(Year) * 60;
	}
	int NumberOfSecondsInAYear()
	{
		return NumberOfMinutesInAYear(_Year) * 60;
	}
	//----------
	static short NumberOfDaysInAMonth(short Month, short Year)
	{
		if (Month < 1 || Month>12)
			return 0;
		int NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31};
		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) :
			NumberOfDays[Month - 1];
	}
	short NumberOfDaysInAMonth() 
	{
		return NumberOfDaysInAMonth(_Month, _Year);
	}
	static short NumberOfHoursInAMonth(short Month, short Year)
	{
		return NumberOfDaysInAMonth(Month, Year) * 24;
	}
	short NumberOfHoursInAMonth() 
	{
		return NumberOfHoursInAMonth(_Month, _Year);
	}
	static int NumberOfMinutesInAMonth(short Month, short Year)
	{
		return NumberOfHoursInAMonth(Month, Year) * 60;
	}
	int NumberOfMinutesInAMonth() 
	{
		return NumberOfMinutesInAMonth(_Month, _Year);
	}
	static int NumberOfSecondsInAMonth(short Month, short Year)
	{
		return NumberOfMinutesInAMonth(Month, Year) * 60;
	}
	int NumberOfSecondsInAMonth()
	{
		return NumberOfSecondsInAMonth(_Month, _Year);
	}
	//--------
	static short DayOfWeekOrder(clsDate Date)
	{
		short a, y, m;
		a = (14 - Date._Month) / 12;
		y = Date._Year - a;
		m = Date._Month + (12 * a) - 2;
		// Gregorian:
		//0:sun, 1:Mon, 2:Tue...etc
		return (Date._Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m)/ 12)) % 7;
	}
	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(*this);
	}
	static std::string DayShortName(short DayOfWeekOrder)
	{
		std::string arrDayNames[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return arrDayNames[DayOfWeekOrder];
	}
	std::string DayShortName() 
	{
		return DayShortName(DayOfWeekOrder(*this));
	}
	//--------
	static std::string MonthShortName(short MonthNumber)
	{
		std::string Months[12] = { "Jan", "Feb", "Mar",
		"Apr", "May", "Jun",
		"Jul", "Aug", "Sep",
		"Oct", "Nov", "Dec"
		};
		return (Months[MonthNumber - 1]);
	}
	std::string MonthShortName() 
	{
		return MonthShortName(_Month);
	}
	//-------
	static void PrintMonthCalendar(short Month, short Year)
	{
		int NumberOfDays;
		// Index of the day from 0 to 6
		int current = DayOfWeekOrder(clsDate(1, Month, Year));
		NumberOfDays = NumberOfDaysInAMonth(Month, Year);
		// Print the current month name
		printf("\n _______________%s_______________\n\n",
			MonthShortName(Month).c_str());
		// Print the columns
		printf(" Sun  Mon  Tue  Wed  Thu  Fri   Sat \n");
		// Print appropriate spaces
		int i;
		for (i = 0; i < current; i++)
			printf("     ");
		for (int j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j);
			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}
		printf("\n _________________________________\n");
	}
	void PrintMonthCalendar()
	{
		return  PrintMonthCalendar(_Month, _Year);
	}
	static void PrintYearCalender(short Year)
	{
		printf("\n _________________________________\n\n");
		printf("        Calendar - %d\n", Year);
		printf(" _________________________________\n");
		for (short i = 1; i <= 12; i++) 
		{
			PrintMonthCalendar(i, Year);
			cout << endl;
		}
	}
	void PrintYearCalender() 
	{
		PrintYearCalender(_Year);
	}
	//----------
	static short DayOrderInAYear(clsDate Date)
	{
		short NumberOfDay = 0;

		for (short i = 1; i <= Date.getMonth() - 1; i++)
		{
			NumberOfDay += NumberOfDaysInAMonth(i, Date.getYear());
		}
		
		NumberOfDay += Date.getDay();

		return NumberOfDay;
	}
	short DayOrderInAYear()
	{
		return DayOrderInAYear(*this);
	}
	//-----------
	static clsDate DateFromDayOrderInAYear(short DayOrder, short Year) 
	{
		if (DayOrder<1 || DayOrder > NumberOfDaysInAYear(Year))
		{
			throw std::invalid_argument("DayOrder is out Of Range !");
		}

		clsDate Date = clsDate{0,0,0};
		Date.setYear(Year);
		short RemainingDay = DayOrder;
		Date.setMonth(1);

		while(true)
		{
			short DayInMonth = NumberOfDaysInAMonth(Date._Month, Year);
			if (RemainingDay > DayInMonth)
			{
				RemainingDay -= DayInMonth;
				Date._Month++;
			}
			else
			{
				Date._Day = RemainingDay;
				break;
			}
		}
		
		return Date;

	}
	//-----------
	static clsDate AddDaysToDate(short DaysToAdd, clsDate Date)
	{
		short RemainingDays = DaysToAdd + DayOrderInAYear(Date);
		Date.setMonth(1);
		while (true)
		{
			short MonthDays = NumberOfDaysInAMonth(Date._Month, Date._Year);
			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;

				if (++Date._Month > 12)
				{
					Date._Month = 1;
					Date._Year++;
				}

			}
			else
			{
				Date._Day = RemainingDays;
				break;
			}
		}
		return Date;
	}
	void AddDaysToDate(short DaysToAdd)
	{
		 AddDaysToDate(DaysToAdd, *this);
	}
	//-------------
	//Comparative
	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return Date1 < Date2;
	}
	bool IsDateBeforeDate2(clsDate Date2) 
	{
		return IsDate1BeforeDate2(*this, Date2);
	}
	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return Date1 == Date2;
	}
	bool IsDateEqualDate2(clsDate Date2)
	{
		return IsDate1EqualDate2(*this, Date2);
	}
	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return Date1 > Date2;
	}
	bool IsDateAfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this , Date2);
	}
	
	static enCompareDate Compare(clsDate Date1, clsDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
			return enCompareDate::Before;

		else if (IsDate1EqualDate2(Date1, Date2))
			return enCompareDate::Equal;

		return enCompareDate::After;
	}
	enCompareDate Compare(clsDate Date2)
	{
		return Compare(*this, Date2);
	}
	static bool IsLastDayInAMonth(clsDate Date) 
	{
		return Date._Day == NumberOfDaysInAMonth(Date._Month, Date._Year);
	}
	bool IsLastDayInAMonth() 
	{
		return IsLastDayInAMonth(*this);
	}
	static bool IsLastMonthInYear(short Month)
	{
		return (Month == 12);
	}
	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(clsDate::_Month);
	}
	static bool IsValidDate(clsDate Date) {
		if (Date._Year < 0) 
		{
			return false;
		}
		else if (Date._Month > 12 || Date._Month < 1)
		{
			return false;
		}
		else if (Date._Day < 1 || Date._Day > NumberOfDaysInAMonth(Date._Month, Date._Year))
		{
			return false;
		}

		return true;
	}
	static void SwapDate(clsDate &Date1, clsDate &Date2)
	{
		clsDate temp = Date1;
		Date1 = Date2;
		Date2 = temp;
	}
	void SwapDate(clsDate& Date2)
	{
		SwapDate(*this, Date2);
	}
	//-------------
	// Increase
	static clsDate IncreaseDateByOneDay(clsDate Date)
	{
		return IncreaseDateByXDay(Date, 1);
	}
	void IncreaseDateByOneDay()
	{
		*this = IncreaseDateByOneDay(*this);
	}
	static clsDate IncreaseDateByXDay(clsDate Date, short X)
	{
		return AddDaysToDate(X, Date);
	}
	void IncreaseDateByXDay(short X)
	{
		*this = IncreaseDateByXDay(*this, X);
	}
	static clsDate IncreaseDateByOneWeek(clsDate Date)
	{
		return IncreaseDateByXDay(Date, 7);
	}
	void IncreaseDateByOneWeek()
	{
		*this = IncreaseDateByOneWeek(*this);
	}
	static clsDate IncreaseDateByXWeek(clsDate Date , short X)
	{
		return IncreaseDateByXDay(Date, 7*X);
	}
	void IncreaseDateByXWeek(short X)
	{
		*this = IncreaseDateByXWeek(*this, X);
	}
	static clsDate IncreaseDateByOneMonth(clsDate Date)
	{
		return IncreaseDateByXDay(Date, NumberOfDaysInAMonth(Date._Month,Date._Year));
	}
	void IncreaseDateByOneMonth()
	{
		*this = IncreaseDateByOneMonth(*this);
	}
	static clsDate IncreaseDateByXMonth(clsDate Date ,short X)
	{
		return IncreaseDateByXDay(Date, NumberOfDaysInAMonth(Date._Month, Date._Year) * X);
	}
	void IncreaseDateByXMonth(short X)
	{
		*this = IncreaseDateByXMonth(*this, X);
	}
	// we can put Date._Year+=X or Date._Year+=1 ,this is the faster
	static clsDate IncreaseDateByOneYear(clsDate Date)
	{
		return IncreaseDateByXMonth(Date, 12);
	}
	void IncreaseDateByOneYear()
	{
		*this = IncreaseDateByOneYear(*this);
	}
	static clsDate IncreaseDateByXYear(clsDate Date, short X)
	{
		return IncreaseDateByXMonth(Date,12 * X);
	}
	void IncreaseDateByXYear(short X)
	{
		*this = IncreaseDateByXYear(*this, X);
	}
	// Decade is a 10 Years
	static clsDate IncreaseDateByOneDecade(clsDate Date)
	{
		return IncreaseDateByXYear(Date,10);
	}
	void IncreaseDateByOneDecade()
	{
		*this = IncreaseDateByOneDecade(*this);
	}
	static clsDate IncreaseDateByXDecade(clsDate Date, short X)
	{
		return IncreaseDateByXYear(Date,10*X);
	}
	void IncreaseDateByXDecade(short X)
	{
		*this = IncreaseDateByXDecade(*this, X);
	}
	// century is a 100 Years
	static clsDate IncreaseDateByOneCentury(clsDate Date)
	{
		return IncreaseDateByXYear(Date, 100);
	}
	void IncreaseDateByOneCentury()
	{
		*this = IncreaseDateByOneCentury(*this);
	}
	// Millenium is a 1000 Years
	static clsDate IncreaseDateByOneMillenium(clsDate Date)
	{
		return IncreaseDateByXYear(Date, 1000);
	}
	void IncreaseDateByOneMillenium()
	{
		*this = IncreaseDateByOneMillenium(*this);
	}
	//------------
	//Decrease

	// Subtract X days from a date (handles year rollbacks)
	static clsDate DecreaseDateByXDay(clsDate Date, short X)
	{
		short RemainingDays = DayOrderInAYear(Date) - X;
		// Move back years while remaining days are not positive
		while (RemainingDays <= 0)
		{
			Date._Year--;
			RemainingDays += NumberOfDaysInAYear(Date._Year);
		}
		// Convert remaining day-of-year to month/day
		Date._Month = 1;
		while (true)
		{
			short DayInMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);
			if (RemainingDays > DayInMonth)
			{
				RemainingDays -= DayInMonth;
				Date._Month++;
			}
			else
			{
				Date._Day = RemainingDays;
				break;
			}
		}
		return Date;
	}
	void DecreaseDateByXDay(short X)
	{
		*this = DecreaseDateByXDay(*this, X);
	}

	static clsDate DecreaseDateByOneDay(clsDate Date)
	{
		return DecreaseDateByXDay(Date, 1);
	}
	void DecreaseDateByOneDay()
	{
		*this = DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByOneWeek(clsDate Date)
	{
		return DecreaseDateByXDay(Date, 7);
	}
	void DecreaseDateByOneWeek()
	{
		*this = DecreaseDateByOneWeek(*this);
	}
	static clsDate DecreaseDateByXWeek(clsDate Date, short X)
	{
		return DecreaseDateByXDay(Date, 7 * X);
	}
	void DecreaseDateByXWeek(short X)
	{
		*this = DecreaseDateByXWeek(*this, X);
	}

	static clsDate DecreaseDateByOneMonth(clsDate Date)
	{
		return DecreaseDateByXDay(Date, NumberOfDaysInAMonth(Date._Month, Date._Year));
	}
	void DecreaseDateByOneMonth()
	{
		*this = DecreaseDateByOneMonth(*this);
	}
	static clsDate DecreaseDateByXMonth(clsDate Date, short X)
	{
		return DecreaseDateByXDay(Date, NumberOfDaysInAMonth(Date._Month, Date._Year) * X);
	}
	void DecreaseDateByXMonth(short X)
	{
		*this = DecreaseDateByXMonth(*this, X);
	}
	static clsDate DecreaseDateByOneYear(clsDate Date)
	{
		return DecreaseDateByXMonth(Date, 12);
	}
	void DecreaseDateByOneYear()
	{
		*this = DecreaseDateByOneYear(*this);
	}
	static clsDate DecreaseDateByXYear(clsDate Date, short X)
	{
		return DecreaseDateByXMonth(Date, 12 * X);
	}
	void DecreaseDateByXYear(short X)
	{
		*this = DecreaseDateByXYear(*this, X);
	}
	static clsDate DecreaseDateByOneDecade(clsDate Date)
	{
		return DecreaseDateByXYear(Date, 10);
	}
	void DecreaseDateByOneDecade()
	{
		*this = DecreaseDateByOneDecade(*this);
	}
	static clsDate DecreaseDateByXDecade(clsDate Date, short X)
	{
		return DecreaseDateByXYear(Date, 10 * X);
	}
	void DecreaseDateByXDecade(short X)
	{
		*this = DecreaseDateByXDecade(*this, X);
	}
	static clsDate DecreaseDateByOneCentury(clsDate Date)
	{
		return DecreaseDateByXYear(Date, 100);
	}
	void DecreaseDateByOneCentury()
	{
		*this = DecreaseDateByOneCentury(*this);
	}
	static clsDate DecreaseDateByOneMillenium(clsDate Date)
	{
		return DecreaseDateByXYear(Date, 1000);
	}
	void DecreaseDateByOneMillenium()
	{
		*this = DecreaseDateByOneMillenium(*this);
	}
	//--------
	static bool isEndOfWeek(clsDate Date)
	{
		return (DayOfWeekOrder(Date) == 6);
	}
	bool isEndOfWeek()
	{
		return isEndOfWeek(*this);
	}
	static bool isWeekEnd(clsDate Date)
	{
		return (DayOfWeekOrder(Date) == 6 || DayOfWeekOrder(Date) == 5);
	}
	bool isWeekEnd()
	{
		return isWeekEnd(*this);
	}
	static bool isBusineesDay(clsDate Date)
	{
		return !(isWeekEnd(Date));
	}
	bool isBusineesDay()
	{
		return isBusineesDay(*this);
	}
	static bool isEndOfMonth(clsDate Date)
	{
		return IsLastDayInAMonth(Date);
	}
	bool isEndOfMonth()
	{
		return isEndOfMonth(*this);
	}
	static short DaysUntilEndOfWeek(clsDate Date)
	{
		return 6 - DayOfWeekOrder(Date);
	}
	short DaysUntilEndOfWeek()
	{
		return DaysUntilEndOfWeek(*this);
	}
	static short DaysUntilEndOfMonth(clsDate Date)
	{
		clsDate EndOfMonth = clsDate{ NumberOfDaysInAMonth(Date._Month,Date._Year),Date._Month,Date._Year };

		return DiffInDays(Date, EndOfMonth);
	}
	short  DaysUntilEndOfMonth()
	{
		return  DaysUntilEndOfMonth(*this);
	}
	static short DaysUntilEndOfYear(clsDate Date)
	{
		clsDate EndOfYear = clsDate{ 31,12,Date._Year };

		return DiffInDays(Date, EndOfYear);
	}
	short DaysUntilEndOfYear()
	{
		return DaysUntilEndOfYear(*this);
	}
	//------------
	static short VacationDays(clsDate StartDate,clsDate EndDate)
	{
		short VacationCount = 0;
		short flag = 1;
		if (IsDate1AfterDate2(StartDate, EndDate))
		{
			SwapDate(StartDate, EndDate);
			flag = -1;
		}
		while (IsDate1BeforeDate2(StartDate, EndDate))
		{
			if (isBusineesDay(StartDate))
			{
				VacationCount++;
			}
			StartDate = IncreaseDateByOneDay(StartDate);
		}
		return flag * VacationCount;
	}
	short VacationDays(clsDate EndDate)
	{
		return VacationDays(*this, EndDate);
	}
	//---------
	static short DiffInDays(clsDate old_Date, clsDate new_Date,bool IncludeEndDay=true)
	{
		short totalDays = 0;
		short FLAG = 1;

		if (IsDate1AfterDate2(old_Date, new_Date)) 
		{
			SwapDate(old_Date, new_Date);
			FLAG = -1;
		}
		while (IsDate1BeforeDate2(old_Date, new_Date))
		{
			totalDays++;
			old_Date = IncreaseDateByOneDay(old_Date);
		}
		totalDays = (IncludeEndDay) ? ++totalDays : totalDays;
		return FLAG * totalDays;
	}
	short DiffInDays(clsDate new_Date, bool IncludeEndDay = true)
	{
		return DiffInDays(*this, new_Date, IncludeEndDay);
	}
	static clsDate GetSystemDate()
	{
		clsDate Date = clsDate{0,0,0};
		time_t t = time(0);
		tm* now = localtime(&t);
		Date._Year = now->tm_year + 1900;
		Date._Month = now->tm_mon + 1;
		Date._Day = now->tm_mday;
		return Date;
	}
	static short AgeInDays(clsDate DateOfBirth)
	{
		return DiffInDays(DateOfBirth, GetSystemDate());
	}
	static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
	{
		short WeekEndCounter = 0;

		while (isWeekEnd(DateFrom))
		{
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		for (short i = 1; i <= VacationDays + WeekEndCounter; i++)
		{
			if (isWeekEnd(DateFrom))
				WeekEndCounter++;
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		while (isWeekEnd(DateFrom))
		{
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		return DateFrom;
	}
	//----------
	//Period
    static short PeriodLength(const sPeriod &Period,bool IncludeEndDay = true)
	{
		return DiffInDays(*Period.StartDate, *Period.EndDate,IncludeEndDay);
	}
    static bool isOverlapPeriod(const sPeriod &Period1, const sPeriod &Period2)
	{
		return !(IsDate1BeforeDate2(*Period1.EndDate, *Period2.StartDate) || IsDate1BeforeDate2(*Period2.EndDate, *Period1.StartDate));
	}
    static bool isDateWithInPeriod(const sPeriod &Period, clsDate Date)
	{
		return !(IsDate1BeforeDate2(Date, *Period.StartDate) || IsDate1AfterDate2(Date, *Period.EndDate));
	}
    static short CountOverlapDays(const sPeriod &Period1,const sPeriod &Period2)
	{
		if (!isOverlapPeriod(Period1, Period2))
			return 0;

		int Period1Length = PeriodLength(Period1);
		int Period2Length = PeriodLength(Period2);
		int OverLapCount = 0;

		if (Period1Length < Period2Length)
		{
			OverLapCount = ClaculatePeriodOverLap(Period1, Period2);
		}

		else
		{
			OverLapCount = ClaculatePeriodOverLap(Period2, Period1);
		}

		return OverLapCount;
		
	}
	//------------
	// Conversion
	static clsDate StringToDate(std::string str)
	{
		clsDate Date{ 0,0,0 };
		// Accept formats like d/m/yyyy or dd/mm/yyyy (basic validation)
		std::string Pattern = R"(^\s*\d{1,2}\/\d{1,2}\/\d{2,4}\s*$)";

		if (!clsString::isValidFormatting(str, Pattern))
			throw invalid_argument("inValid Date");

		vector<std::string>vDate = clsString::Split(clsString::Trim(str), "/");

		Date.setDay(short(stoi(vDate[0])));
		Date.setMonth(short(stoi(vDate[1])));
		Date.setYear(short(stoi(vDate[2])));

		return Date;
	}
	static std::string DateToString(clsDate Date,std::string DateFormat = "dd/mm/yyyy")
	{
		if (!(clsString::isWordInString(DateFormat, "mm") && clsString::isWordInString(DateFormat, "dd") && clsString::isWordInString(DateFormat, "yyyy")))
		{
			throw invalid_argument("inValid Formatting");
		}
		std::string FormattedDateString = DateFormat;
		FormattedDateString = clsString::ReplaceWordInStringUsingBuiltInFunction(DateFormat, "dd",
			to_string(Date._Day));
		FormattedDateString = clsString::ReplaceWordInStringUsingBuiltInFunction(FormattedDateString,
			"mm", to_string(Date._Month));
		FormattedDateString = clsString::ReplaceWordInStringUsingBuiltInFunction(FormattedDateString,
			"yyyy", to_string(Date._Year));

		return FormattedDateString;
	}
	std::string ToString(string Formatting = "dd/mm/yyyy")
	{
		return DateToString(*this, Formatting);
	}
	//----------------End Of Class ❤️---------------------//
};
