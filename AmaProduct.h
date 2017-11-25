/***********************************************************
// File AmaProduct.h
// Date 2017/07/30
// Author Congjia Lu 
// Description
// Declares an AmaProduct class as the derived class of Product, designed to work with the Aid Management Application
//
***********************************************************/

#ifndef SICT_AMAPRODUCT_H
#define SICT_AMAPRODUCT_H

#include <iostream>
#include <cstring>
#include "Product.h"
#include "ErrorMessage.h"

namespace sict{
	class AmaProduct : public Product{
		char fileTag_;
		char unit_[11];
	protected:
		ErrorMessage err_;
	public:
		AmaProduct();
		AmaProduct(char);
		const char* unit()const;
		void unit(const char*);

		std::fstream& store(std::fstream& file, bool addNewLine = true)const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear)const;
		std::istream& read(std::istream& istr);
	};
}

#endif


