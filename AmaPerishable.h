/***********************************************************
// File AmaPerishable.h
// Date 2017/07/30
// Author Congjia Lu 
// Description
// Declares an AmaPerishable class as the derived class of AmaProduct class, with an expiry date.
//
***********************************************************/

#ifndef SICT_AMAPERISHABLE_H
#define SICT_AMAPERISHABLE_H

#include "AmaProduct.h"
#include "Date.h"

namespace sict{
	class AmaPerishable : public AmaProduct{
		Date expiry_;
	public:
		AmaPerishable();
		const Date& expiry()const;
		void expiry(const Date &value);
		std::fstream& store(std::fstream& file, bool addNewLine = true)const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& ostr, bool linear)const;
		std::istream& read(std::istream& istr);
	};
}
#endif