#include <string>
#include <cstdio>
#include <cstdlib>

class Date {
 private:
  int year_, month_, day_;

 public:
  explicit Date(int year, int month, int day) :
      year_(year), month_(month), day_(day) {}

  bool IsLeap() {
    return (year_ % 4 == 0 && year_ % 100 != 0) || (year_ % 400 == 0);
  }

  std::string ToString() {
    std::ostringstream out;
    std::string day, month, year;
    if (day_ < 10) day = "0" + std::to_string(day_);
    else
      day = std::to_string(day_);
    if (month_ < 10) month = "0" + std::to_string(month_);
    else
      month = std::to_string(month_);
    if (year_ < 10) year = "000" + std::to_string(year_);
    else if (year_ < 100) year = "00" + std::to_string(year_);
    else if (year_ < 1000) year = "0" + std::to_string(year_);
    else
      year = std::to_string(year_);
    out << day << "." << month << "." << year;
    return out.str();
  }

  int DaysLeft(Date date) {
    return abs(DateToJDN(date) - DateToJDN(Date(year_, month_, day_)));
  }

  Date DaysLater(int days) {
    return JDNToDate(DateToJDN(Date(year_, month_, day_)) + days);
  }

  static int DateToJDN(Date date) {
    int a = static_cast<int> ((14 - date.month_) / 12);
    int y = date.year_ + 4800 - a;
    int m = date.month_ + 12 * a - 3;
    return date.day_ + static_cast<int> ((153 * m + 2) / 5) + 365 * y +
        static_cast<int> (y / 4) - static_cast<int> (y / 100) +
        static_cast<int> (y / 400) - 32045;
  }

  static Date JDNToDate(int jdn) {
    int a = jdn + 32044;
    int b = static_cast<int> ((4 * a + 3) / 146097);
    int c = a - static_cast<int> (146097 * b / 4);
    int d = static_cast<int> ((4 * c + 3) / 1461);
    int e = c - static_cast<int> (1461 * d / 4);
    int m = static_cast<int> ((5 * e + 2) / 153);
    int day = e - static_cast<int> ((153 * m + 2) / 5) + 1;
    int month = m + 3 - 12 * static_cast<int> (m/10);
    int year = 100 * b + d - 4800 + static_cast<int> (m /10);
    return Date(year, month, day);
  }
};
