/***********************************************************
// OOP244 Milestone 5
// File AmaPerishable.cpp
// Date 2017/07/30
// Author Congjia Lu (137832168)
// Description
// Defines an AmaPerishable class as the derived class of AmaProduct class, with an expiry date.
//
***********************************************************/

#include <iostream>
#include "AmaPerishable.h"
#include "Date.h"

namespace sict {
	// invokes the AmaProduct constructor passing the value ¡®P¡¯ for the fileTag argument
	//
	AmaPerishable::AmaPerishable() : AmaProduct('P') {}

	// Returns a constant reference to expiry_ member variable
	//
	const Date& AmaPerishable::expiry()const{
		return expiry_;
	}

	//Sets the expiry_ attribute to the incoming value
	//
	void AmaPerishable::expiry(const Date &value) {
		expiry_ = value;
	}

	// writes a comma and the expiry date into the file
	//
	std::fstream& AmaPerishable::store(std::fstream& file, bool addNewLine)const{
		AmaProduct::store(file, false);
		file << ',';
		expiry_.write(file);
		if (addNewLine == true){
			file << std::endl;
		}
		return file;
	}

	// Calls the parent¡¯s load passing the file as the argument and then calls the read method of the expiry_ object passing the file as the argument
	//
	std::fstream& AmaPerishable::load(std::fstream& file){
		AmaProduct::load(file);
		file.ignore();
		expiry_.read(file);
		file.ignore();
		return file;
	}

	// Calls the write of the parent passing ostr and linear as arguments. 
	//
	std::ostream& AmaPerishable::write(std::ostream& ostr, bool linear)const{
		AmaProduct::write(ostr, linear);
		if (err_.isClear() && !isEmpty()){
			if (linear){
				expiry_.write(ostr);
			}
			else {
				ostr << std::endl << "Expiry date: ";
				expiry_.write(ostr);
			}
		}
		return ostr;
	}

	// read the date from the console and set error codes if needed
	//
	std::istream& AmaPerishable::read(std::istream& istr){
		Date temp;
		AmaProduct::read(istr);
		if (err_.isClear()){
			std::cout << "Expiry date (YYYY/MM/DD): ";
			istr >> temp;
			if (temp.bad()){
				if (temp.errCode() == CIN_FAILED) err_.message("Invalid Date Entry");
				else if (temp.errCode() == YEAR_ERROR) err_.message("Invalid Year in Date Entry");
				else if (temp.errCode() == MON_ERROR) err_.message("Invalid Month in Date Entry");
				else if (temp.errCode() == DAY_ERROR) err_.message("Invalid Day in Date Entry");
				istr.setstate(std::ios::failbit);
			}
			else {
				expiry(temp);
			}
		}
		return istr;
	}
}
