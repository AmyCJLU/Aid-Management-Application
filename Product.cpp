/***********************************************************
// File Product.cpp
// Date 2017/07/019
// Author Congjia Lu 
// Description
// Defines the Product class
***********************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include "Product.h"
#include "general.h"
#include "Streamable.h"

namespace sict{
	
	//Default Constructor. sets the Product to a safe recognizable empty state. 
	//
	Product::Product(){
		sku_[0] = '\0';
		name_ = nullptr;
		price_ = 0.0;
		taxed_ = true;
		quantity_ = 0;
		qtyNeeded_ = 0;
	}

	//Constructor with 5 parameters
	//
	Product::Product(const char skuP[], const char* nameP, double priceP, bool taxedP, int qtyNeededP){
		name_ = nullptr;
		sku(skuP);
		name(nameP);
		price(priceP);
		taxed(taxedP);
		quantity(0);
		qtyNeeded(qtyNeededP);
	}

	//Private function to avoid duplication
	//
	void Product::init(const Product& source){
		strncpy(sku_, source.sku_, MAX_SKU_LEN);
		sku_[MAX_SKU_LEN] = '\0';
		quantity_ = source.quantity_;
		price_ = source.price_;
		taxed_ = source.taxed_;
		qtyNeeded_ = source.qtyNeeded_;
		if (source.name_ != nullptr){
			int size = strlen(source.name_);
			name_ = new char[size + 1];
			strncpy(name_, source.name_, size);
			name_[size] = '\0';
		}
		else {
			name_ = nullptr;
		}
	}

	//Operator =. so the Product is copied from and assigned to another Product safely.
	//
	Product& Product::operator=(const Product& p){
		if (this != &p){
			delete[] name_;
			init(p);
		}
		return *this;
	}

	//Copy Constructor. so the Product is copied from and assigned to another Product safely.
	//
	Product::Product(const Product& p){     
		name_ = nullptr;
		*this = p;
	}

	//virtual destructor. To make sure the memory allocated by name_ is freed when Product is destroyed.
	//
	Product::~Product(){
		delete[] name_;
		name_ = nullptr;
	}

	//sku setter, set the sku member variables
	//
	void Product::sku(const char sku[]){
		strncpy(sku_, sku, MAX_SKU_LEN);
		sku_[MAX_SKU_LEN] = '\0';
	}

	//price setter. set the price member variables
	//
	void Product::price(double price){
		price_ = price;
	}

	//name setter, set the name member variables
	//
	void Product::name(const char* name){
		delete[] name_;
		name_ = nullptr;
		int size = strlen(name);
		name_ = new char[size + 1];
		strncpy(name_, name, size);
		name_[size] = '\0';
	}

	//taxed setter, set the taxed member variables
	//
	void Product::taxed(bool taxed){
		taxed_ = taxed;
	}

	//quantity setter, set the quantity member variables
	//
	void Product::quantity(int quantity){
		quantity_ = quantity;
	}

	//quantity needed setter, set the qtyNeeded_ member variables
	//
	void Product::qtyNeeded(int qtyNeeded){
		qtyNeeded_ = qtyNeeded;
	}

	//sku getter, set the sku member variables
	//
	const char* Product::sku() const{
		return sku_;
	}

	//price getter,  return the values or addresses of the member variable price
	//
	double Product::price() const{
		return price_;
	}

	//name getter,  return the values or addresses of the member variable name
	//
	const char* Product::name() const {
		return name_;
	}

	//taxed getter,  return the values or addresses of the member variable taxed
	//
	bool Product::taxed() const {
		return taxed_;
	}

	//quantity getter,  return the values or addresses of the member variable quantity
	//
	int Product::quantity() const {
		return quantity_;
	}

	//quantity needed getter,  return the values or addresses of the member variable qtyNeeded_
	//
	int Product::qtyNeeded() const {
		return qtyNeeded_;
	}

	//cost getter,  return the values or addresses of the member variable cost
	//
	double Product::cost() const {
		return taxed_ ? (price_ * (1 + TAX)) : price_;
	}

	//isEmpty. return true if the Product is in a safe empty state
	//
	bool Product::isEmpty() const {
		return (sku_[0] == '\0' &&
			name_ == nullptr &&
			price_ == 0 &&
			taxed_ == true &&
			quantity_ == 0 &&
			qtyNeeded_ == 0);
	}

	//== operator. receives a constant character pointer and returns a Boolean.
	//
	bool Product::operator==(const char* sku) const {
		return strcmp(this->sku_, sku) == 0;
	}

	//+= operator. receives an integer and returns an integer.
	//
	int Product::operator+=(int q) {
		this->quantity_ += q;
		return this->quantity_;
	}

	//-= operator. receives an integer and returns an integer.
	//
	int Product::operator-=(int q) {
		this->quantity_ -= q;
		return this->quantity_;
	}

	//overloaded += operator. receives a double reference value as left operand and a constant Product //reference as right operand and returns a double value
	//
	double operator+=(double& value, const Product& P) {
		value = (P.cost() * P.quantity()) + value;
		return value;
	}

	//istream operator,  to read a Product from the console
	//
	std::istream& operator>>(std::istream& is, Product& P) {
		return P.read(is);
	}

	//ostream operator, to print a Product to the console
	//
	std::ostream& operator<<(std::ostream& os, const Product& P) {
		return P.write(os, true);
	}
}
