/***********************************************************
// File AmaProduct.cpp
// Date 2017/07/30
// Author Congjia Lu
// Description
// Defines an AmaProduct class as the derived class of Product, designed to work with the Aid Management Application
//
***********************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "AmaProduct.h"
#include "ErrorMessage.h"
#include "general.h"

namespace sict{
	
	//default constructor, to set member variables to safe state.
	//
	AmaProduct::AmaProduct():Product(){
		fileTag_ = 'N';
		unit_[0] = '\0';
	}

	//constructor that receives the value for the filetag_
	//
	AmaProduct::AmaProduct(char fTag):Product(){
		if (fTag != '\0'){
			fileTag_ = fTag;
		}
		else {
			fileTag_ = 'N';
		}
	}

	//returns a constant pointer to the unit_ member variable
	//
	const char* AmaProduct::unit() const{
		return unit_;
	}

	//Copies the incoming value string into the unit_ string
	//
	void AmaProduct::unit(const char* value){
		strncpy(unit_, value, 10);
		unit_[10] = '\0';
	}

	//Using the operator<< of ostream prints out the data in a certain formatinto the file
	//
	std::fstream& AmaProduct::store(std::fstream& file, bool addNewLine)const{
		if (!isEmpty()){
			file << fileTag_ << ',';
			file << sku() << ',' << name() << ',' << price() << ',' << taxed() << ',' << quantity() << ',' << unit() << ',' << qtyNeeded();
			if (addNewLine == true){
				file << std::endl;
			}
		}
		return file;
	}

	//AmaProduct reads all the fields in the file and sets the member variables 
	//
	std::fstream& AmaProduct::load(std::fstream& file){
		char tpSku[100];
		char tpName[100];
		double tpPrice;
		bool tpTaxed;
		int tpQuantity;
		char tpUnit[100];
		int tpQtyNeeded;

		file.getline(tpSku, 2000, ',');
		sku(tpSku);
		file.getline(tpName, 2000, ',');
		name(tpName);
		file >> tpPrice;
		price(tpPrice);
		file.ignore();
		file >> tpTaxed;
		taxed(tpTaxed);
		file.ignore();
		file >> tpQuantity;
		quantity(tpQuantity);
		file.ignore();
		file.getline(tpUnit, 2000, ',');
		unit(tpUnit);
		file >> tpQtyNeeded;
		qtyNeeded(tpQtyNeeded);
		
		return file;
	}

	//depending on the value of linear, write(), prints the Product in different formats, or err_ if not clear
	//
	std::ostream& AmaProduct::write(std::ostream& os, bool linear) const{
		if (err_.isClear()){
			if (linear){
				os.width(MAX_SKU_LEN);
				os.fill(' ');
				os << std::left << sku() << "|" << std::flush;
				os.width(20);
				os << std::left;
				if (sizeof(name()) > 20) {
					char tmp[21];
					strncpy(tmp, name(), 20);
					tmp[20] = '\0';
					os << tmp;
				}
				else {
					os << name();
				}
				os << "|" << std::flush;
				os.width(7);
				os.setf(std::ios::fixed);
				os.precision(2);
				os << std::right << cost() << "|" <<std::flush;
				os.width(4);
				os << std::right << quantity() << "|" << std::flush;
				os.width(10);
				os << std::left << unit() << "|" << std::flush;
				os.width(4);
				os << std::right << qtyNeeded() << "|" << std::flush;
			}
			else {
				if (taxed()) {
					os << "Sku: " << sku() << std::endl;
					os << "Name: " << name() << std::endl;
					os << "Price: " << price() << std::endl;
					os << "Price after tax: " << cost() << std::endl;
					os << "Quantity On Hand: " << quantity() << " " << unit() << std::endl;
					os << "Quantity Needed: " << qtyNeeded();
				}
				else {
					os << "Sku: " << sku() << std::endl;
					os << "Name: " << name() << std::endl;
					os << "Price: " << price() << std::endl;
					os << "Price after tax: " << "N/A" << std::endl;
					os << "Quantity On Hand: " << quantity() << " " << unit() << std::endl;
					os << "Quantity Needed: " << qtyNeeded();
				}
			}
		}
		else {
			os << err_.message();
		}
		return os;
	}

	// Receives the values using istream
	//
	std::istream& AmaProduct::read(std::istream& istr){
		char tpSku[100];
		char tpName[100];
		double tpPrice;
		bool tpTaxed;
		char tpTax;
		int tpQuantity;
		char tpUnit[100];
		int tpQtyNeeded;
		err_.clear();

		std::cout << "Sku: ";
		istr.getline(tpSku, 100);
		std::cout << "Name: ";
		istr.getline(tpName, 100);
		std::cout << "Unit: ";
		istr.getline(tpUnit, 100);
		std::cout << "Taxed? (y/n): ";
		istr >> tpTax;
		if (tpTax == 'Y' || tpTax == 'y'){
			tpTaxed = true;
			istr.clear();
			istr.ignore(2000, '\n');
		}
		else if (tpTax == 'N' || tpTax == 'n'){
			tpTaxed = false;
			istr.clear();
			istr.ignore(2000, '\n');
		}
		else {
			err_.message("Only (Y)es or (N)o are acceptable");
			istr.setstate(std::ios::failbit);
		}
		if (istr.fail()){
			return istr;
		}
		std::cout << "Price: ";
		istr >> tpPrice;
		if (istr.fail()){
			err_.message("Invalid Price Entry");
			return istr;
		}
		std::cout << "Quantity On hand: ";
		istr >> tpQuantity;
		if (istr.fail()){
			err_.message("Invalid Quantity Entry");
			return istr;
		}
		std::cout << "Quantity Needed: ";
		istr >> tpQtyNeeded;
		if (istr.fail()){
			err_.message("Invalid Quantity Needed Entry");
			return istr;
		}
		sku(tpSku);
		name(tpName);
		unit(tpUnit);
		taxed(tpTaxed);
		price(tpPrice);
		quantity(tpQuantity);
		qtyNeeded(tpQtyNeeded);
		return istr;
	}
}
