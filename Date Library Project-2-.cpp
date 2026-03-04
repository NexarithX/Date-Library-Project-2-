#include <iostream>
#include "clsDate.h"
using namespace std;
int main() {
    try {
        cout << "--- clsDate Test Suite ---\n";

        // Constructors
        clsDate sys; // system date
        cout << "System Date: " << sys.ToString() << "\n";

        clsDate fromString = clsDate::StringToDate("  31  /   12 /   2022  ");
        cout << "From String: " << fromString.ToString() << "\n";

        clsDate ymd(15, 8, 1947);
        cout << "Y/M/D ctor: " << ymd.ToString() << "\n";

        clsDate fromOrder = clsDate(100, 2020); // 100th day of 2020
        cout << "100th day of 2020: " << fromOrder.ToString() << " (DayOrder: " << fromOrder.DayOrderInAYear() << ")\n";

        // Conversions
        cout << "Formatting dd-mm-yyyy: " << fromString.DateToString(fromString, "dd-mm-yyyy") << "\n";

        // Leap year and year related
        cout << "Is 2000 leap: " << clsDate::IsLeapYear(2000) << "\n";
        cout << "Is 1900 leap: " << clsDate::IsLeapYear(1900) << "\n";
        cout << "Days in 2020: " << clsDate::NumberOfDaysInAYear(2020) << "\n";

        // Month calculations
        cout << "Days in Feb 2020: " << clsDate::NumberOfDaysInAMonth(2, 2020) << "\n";
        cout << "Hours in Feb 2020: " << clsDate::NumberOfHoursInAMonth(2, 2020) << "\n";

        // Day of week
        cout << "15/8/1947 DayOfWeekOrder: " << ymd.DayOfWeekOrder() << " (" << ymd.DayShortName() << ")\n";

        // Month name and calendars (prints to stdout)
        cout << "Month short name for 8: " << clsDate::MonthShortName(8) << "\n";
        cout << "Print sample month calendar for Aug 1947:\n";
        clsDate::PrintMonthCalendar(8, 1947);

        // Day order conversions
        short order = clsDate::DayOrderInAYear(ymd);
        cout << "Day order in year for " << ymd.ToString() << " is " << order << "\n";

        clsDate add = clsDate::AddDaysToDate(10, ymd);
        cout << "15/8/1947 + 10 days = " << add.ToString() << "\n";

        // Increase / Decrease
        clsDate inc = clsDate::IncreaseDateByOneMonth(ymd);
        cout << "Increase by one month: " << inc.ToString() << "\n";
        clsDate dec = clsDate::DecreaseDateByOneMonth(ymd);
        cout << "Decrease by one month: " << dec.ToString() << "\n";

        // Comparisons
        cout << "Is ymd before fromString? " << clsDate::IsDate1BeforeDate2(ymd, fromString) << "\n";
        cout << "Compare ymd vs fromString: " << (int)clsDate::Compare(ymd, fromString) << "\n";

        // Last day / month / valid
        clsDate lastMonthDay = clsDate::DateFromDayOrderInAYear(366, 2020);
        cout << "Last day of 2020: " << lastMonthDay.ToString() << " IsLastDayInAMonth: " << clsDate::IsLastDayInAMonth(lastMonthDay) << "\n";
        cout << "Is month 12 last month in year: " << clsDate::IsLastMonthInYear(12) << "\n";
        cout << "Is valid date 31/2/2020: " << clsDate::IsValidDate(clsDate(31,2,2020)) << "\n";

        // Swap
        clsDate d1(1,1,2000), d2(31,12,1999);
        cout << "Before swap d1=" << d1.ToString() << " d2=" << d2.ToString() << "\n";
        clsDate::SwapDate(d1, d2);
        cout << "After swap d1=" << d1.ToString() << " d2=" << d2.ToString() << "\n";

        // Week/weekend/business
        cout << "isEndOfWeek for " << d1.ToString() << ": " << clsDate::isEndOfWeek(d1) << "\n";
        cout << "isWeekEnd for " << d1.ToString() << ": " << clsDate::isWeekEnd(d1) << "\n";
        cout << "isBusinessDay for " << d1.ToString() << ": " << clsDate::isBusineesDay(d1) << "\n";

        // Days until end
        cout << "Days until end of week for " << d1.ToString() << ": " << clsDate::DaysUntilEndOfWeek(d1) << "\n";
        cout << "Days until end of month for " << d1.ToString() << ": " << clsDate::DaysUntilEndOfMonth(d1) << "\n";

        // Vacation / Diff
        clsDate vacStart = clsDate::StringToDate("01/05/2021");
        clsDate vacEnd = clsDate::StringToDate("10/05/2021");
        cout << "Vacation business days between " << vacStart.ToString() << " and " << vacEnd.ToString() << ": " << clsDate::VacationDays(vacStart, vacEnd) << "\n";

        cout << "Diff in days include end: " << clsDate::DiffInDays(vacStart, vacEnd, true) << "\n";

        // System and age
        cout << "System date again: " << clsDate::GetSystemDate().ToString() << "\n";
        cout << "Age in days for 01/01/2000: " << clsDate::AgeInDays(clsDate::StringToDate("01/01/2000")) << "\n";

        // Calculate vacation return
        clsDate ret = clsDate::CalculateVacationReturnDate(clsDate::StringToDate("01/07/2022"), 5);
        cout << "Vacation return date: " << ret.ToString() << "\n";

        // Period tests
        clsDate p1s = clsDate::StringToDate("01/03/2022");
        clsDate p1e = clsDate::StringToDate("10/03/2022");
        clsDate p2s = clsDate::StringToDate("05/03/2022");
        clsDate p2e = clsDate::StringToDate("15/03/2022");

        clsDate::sPeriod period1{ &p1s, &p1e };
        clsDate::sPeriod period2{ &p2s, &p2e };

        cout << "Period1 length: " << clsDate::PeriodLength(period1) << "\n";
        cout << "Period2 length: " << clsDate::PeriodLength(period2) << "\n";
        cout << "isOverlapPeriod (period1 vs period2): " << clsDate::isOverlapPeriod(period1, period2) << "\n";
        cout << "CountOverlapDays (period1 vs period2): " << clsDate::CountOverlapDays(period1, period2) << "\n";
        cout << "isDateWithInPeriod 06/03/2022 in period1: " << clsDate::isDateWithInPeriod(period1, clsDate::StringToDate("06/03/2022")) << "\n";

        // Non-overlapping period
        clsDate p3s = clsDate::StringToDate("11/04/2022");
        clsDate p3e = clsDate::StringToDate("20/04/2022");
        clsDate::sPeriod period3{ &p3s, &p3e };
        cout << "isOverlapPeriod (period1 vs period3): " << clsDate::isOverlapPeriod(period1, period3) << "\n";
        cout << "CountOverlapDays (period1 vs period3): " << clsDate::CountOverlapDays(period1, period3) << "\n";

        cout << "--- End of tests ---\n";

    }
    catch (const exception &ex) {
        cerr << "Exception: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}