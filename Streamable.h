/***********************************************************
// File Streamable.h
// Date 2017/07/12
// Author Congjia Lu s
// Description
// Declares the Streamable class, which has four pure virtual member functions
//
***********************************************************/

#ifndef SICT_STREAMABLE_H
#define SICT_STREAMABLE_H
#include<iostream>
#include<fstream>

namespace sict {
	class Streamable {
	public:
		virtual std::fstream& store(std::fstream& file, bool addNewLine = true)const =0;
		virtual std::fstream& load(std::fstream& file) = 0;
		virtual std::ostream& write(std::ostream& os, bool linear)const = 0;
		virtual std::istream& read(std::istream& is) = 0;
	};
}

#endif
