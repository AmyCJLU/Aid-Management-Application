/***********************************************************
// File Date.h
// Date 2017/07/08
// Author Congjia Lu 
// Description
// Declares a Date class with member functions to validate the data read in and display it
//
***********************************************************/

#ifndef SICT_DATE_H
#define SICT_DATE_H

namespace sict{
    const int NO_ERROR = 0;
    const int CIN_FAILED = 1;
    const int YEAR_ERROR = 2;
    const int MON_ERROR = 3;
    const int DAY_ERROR = 4;
    
    class Date {
        int year_;
        int mon_;
        int day_;
        int readErrorCode_;
        int value()const;
        void errCode(int errorCode);
    public:
        Date();
		Date(int year, int mon, int day);
        bool operator==(const Date& D)const;
        bool operator!=(const Date& D)const;
        bool operator<(const Date& D)const;
        bool operator>(const Date& D)const;
        bool operator<=(const Date& D)const;
        bool operator>=(const Date& D)const;
        int errCode()const;
        bool bad()const;
        int mdays()const;  
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr)const;
    };

	std::istream& operator>>(std::istream& is, Date& d);
	std::ostream& operator<<(std::ostream& os, Date& d);

}
#endif
