/***********************************************************
// File Date.cpp
// Date 2017/07/08
// Author Congjia Lu 
// Description
// Defines a Date class with member functions to validate the data read in and display it
//
***********************************************************/

#include <iostream>
#include "Date.h"
#include "general.h"

namespace sict{
    
	//This function returns a unique integer number based on the date. 
	//
    int Date::value()const {
        return year_ * 372 + mon_ * 31 + day_;
    }
    
	//Returns the number of days in a month.
	//
    int Date::mdays()const {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = mon_ >= 1 && mon_ <= 12 ? mon_ : 13;
        mon--;
        return days[mon] + int((mon == 1)*((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
    }
    
    //Sets the readErrorCode_ member-variable to one of the values above.
    //
    void Date::errCode(int errorCode){
        switch(errorCode){
			case NO_ERROR:
                readErrorCode_= NO_ERROR;
                break;
			case CIN_FAILED:
                readErrorCode_ = CIN_FAILED;
                break;
			case YEAR_ERROR:
				readErrorCode_ = YEAR_ERROR;
                break;
			case MON_ERROR:
                readErrorCode_ = MON_ERROR;
                break;
			case DAY_ERROR:
                readErrorCode_ = DAY_ERROR;
                break;
            default:
                std::cout << "Invalid error code\n";
        }
    }
    
    //Default Constructor. sets year_, mon_ and day_ to “0” and readErrorCode_ to NO_ERROR.
    //
    Date::Date(){
        year_ = 0;
        mon_ = 0;
        day_ = 0;
        errCode(0);
    }
    
    //3 Argument Constructor. Sets the values of year_, mon_ and day_, and the readErrorCode_ to NO_ERROR
    //
    Date::Date(int year, int mon, int day){
		year_ = year;
		mon_ = mon;
		day_ = day;
		errCode(NO_ERROR);
    }

    // operator == overload
	//
	bool Date::operator==(const Date& D)const{
		if (this->value() == D.value()){
			return true;
		}
		else {
			return false;
		}
	}

	// operator != overload
	//
	bool Date::operator!=(const Date& D)const{
		if (!(*this==D)){
			return true;
		}
		else {
			return false;
		}
	}

	// operator < overload
	//
	bool Date::operator<(const Date& D)const{
		if (this->value() < D.value()){
			return true;
		}
		else {
			return false;
		}
	}

	// operator > overload
	//
	bool Date::operator>(const Date& D)const{
		if (!(*this < D || *this == D)) {
			return true;
		} 
		else {
			return false;
		}
	}

	// operator <= overload
	//
	bool Date::operator<=(const Date& D)const{
		if (!(*this > D)){
			return true;
		}
		else {
			return false;
		}
	}

	// operator >= overload
	//
	bool Date::operator>=(const Date& D)const{
		if (!(*this < D)){
			return true;
		}
		else {
			return false;
		}
	}
    
	// Returns the readErrorCode_ value
	//
	int Date::errCode()const{
		return readErrorCode_;
	}

	// Returns true if readErrorCode_ is not equal to zero
	//
	bool Date::bad()const{
		if (readErrorCode_ != 0){
			return true;
		}
		else {
			return false;
		}
	}

	// Reads the date and set appropriate error code to the data
	//
	std::istream& Date::read(std::istream& istr){
		int year;
		int mon;
		int day;
		char c;

		istr >> year >> c >> mon >> c >> day;

		if (istr.fail()){
			errCode(CIN_FAILED);
		}
		else {
			year_ = year;
			mon_ = mon;
			day_ = day;
			bool validYear = year >= MIN_YEAR && year <= MAX_YEAR;
			if (validYear){				
				bool validMon = mon >= 1 && mon <= 12;
				if (validMon){	
					int days = mdays();
					if (day >= 1 && day <= days){
						errCode(NO_ERROR);
					}
					else {
						errCode(DAY_ERROR);
					}
				}
				else {
					errCode(MON_ERROR);
				}
			}
			else {
				errCode(YEAR_ERROR);
			}
		}
		return istr;
	}

	//Writes the date using the ostr argument in the following format: YYYY/MM/DD, then return the ostr
	//
	std::ostream& Date::write(std::ostream& ostr)const{
		ostr << year_ << '/' << std::flush;
		std::cout.fill('0');
		std::cout.width(2);
		ostr << mon_ << '/' << std::flush;
		std::cout.width(2);
		ostr << day_;
		return ostr;
	}

	// Read a Date from the console
	//
	std::istream& operator>>(std::istream& is, Date& d){
		return d.read(is);
	}

	// Print a Date to the console
	//
	std::ostream& operator<<(std::ostream& os, Date& d){
		return d.write(os);
	}

}
