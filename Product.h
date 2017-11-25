/***********************************************************
// File Product.h
// Date 2017/07/19
// Author Congjia Lu 
// Description
// Declares the Product class
***********************************************************/

#ifndef SICT_PRODUCT_H
#define SICT_PRODUCT_H

#include <iostream>
#include "general.h"
#include "Streamable.h"

namespace sict {
	class Product : public Streamable {
		char sku_[MAX_SKU_LEN + 1];
		char* name_;
		double price_;
		bool taxed_;
		int quantity_;
		int qtyNeeded_;
		void init(const Product& source);
	public:
		Product();
		Product(const char skuP[], const char* nameP, double priceP = 0.0, bool taxedP = true, int qtyNeededP = 0);
		Product(const Product&);		
		Product& operator=(const Product&);
		virtual ~Product();

		void sku(const char sku[]);
		void price(double price);
		void name(const char* name);
		void taxed(bool taxed);
		void quantity(int quantity);
		void qtyNeeded(int qtyNeeded);

		const char* sku() const;
		double price() const;
		const char* name() const;
		bool taxed() const;
		int quantity() const;
		int qtyNeeded() const;
		double cost() const;
		bool isEmpty() const;

		bool operator==(const char* sku) const;
		int operator+=(int quantity);
		int operator-=(int quantity);

	};

	double operator+=(double& value, const Product& p);
	std::istream& operator >> (std::istream& is, Product& p);
	std::ostream& operator << (std::ostream& os, const Product& p);

}
#endif