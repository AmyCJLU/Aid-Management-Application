/***********************************************************
// File AidApp.h
// Date 2017/08/06
// Author Congjia Lu 
// Description
// Defines an AidApp class AidApp is a class to store and retrieve Perishable and Non-Perishable product information from and to a file.
//
***********************************************************/

#include <iostream>
#include "AidApp.h"
#include "AmaPerishable.h"
#include "AmaProduct.h"
#include "Product.h"
using namespace std;

namespace sict {

	// Constructor with one argument filename, copy, set elements to safe state, and load the records
	//
	AidApp::AidApp(const char * fileName) {
		long size = strlen(fileName);
		strncpy(filename_, fileName, size);
		filename_[size] = '\0';
		for (int i = 0; i < MAX_NO_RECS; i++) {
			product_[i] = nullptr;
		}
		noOfProducts_ = 0;
		loadRecs();
	}
	
	// Prints: "Press Enter to continue..."<NEWLINE> then waits for the user to hit enter.
	//
	void AidApp::pause() const {
		cout << "Press Enter to continue..." << endl;
		cin.ignore(1000, '\n');
	}

	// Menu() displays the menu as follows and waits for the user to select an option. 
	//
	int AidApp::menu() {
		int ret;
		cout << "Disaster Aid Supply Management Program" << endl;
		cout << "1- List products" << endl;
		cout << "2- Display product" << endl;
		cout << "3- Add non-perishable product" << endl;
		cout << "4- Add perishable product" << endl;
		cout << "5- Add to quantity of purchased products" << endl;
		cout << "0- Exit program" << endl;
		cout << "> ";
		cin >> ret;
		if (ret < 0 || ret > 5) ret = -1;
		cin.clear();
		cin.ignore(1000, '\n');
		return ret;
	}

	// Opens the data file for reading. If the file does not exist, it will create an empty file, close the file and exit.  
	//
	void AidApp::loadRecs() {
		datafile_.open(filename_, ios::in);
		int readindex = 0;
		if (datafile_.good()) {
			char Id;
			while (datafile_.get(Id).good()) {
				if (Id == 'P') {
					product_[readindex] = nullptr;
					delete product_[readindex];
					product_[readindex] = new AmaPerishable();
				}
				else if (Id == 'N') {
					product_[readindex] = nullptr;
					delete product_[readindex];
					product_[readindex] = new AmaProduct();
				}
				else {
					continue;
				}
				datafile_.ignore();
				product_[readindex]->load(datafile_);
				readindex++;
			}
			noOfProducts_ = readindex;
			datafile_.close();
		}
		else {
			datafile_.clear();
			datafile_.close();
			fstream f(filename_, ios::out);
			datafile_.close();
		}
	}

	//  Opens the data file for writing, Loops through the product_ array up to noOfProducts_ and stores them in the datafile_, close the file
	// 
	void AidApp::saveRecs() {
		datafile_.open(filename_, ios::out);
		for (int i = 0; i < noOfProducts_; i++) {
			product_[i]->store(datafile_);
		}
		datafile_.close();
	}

	// Prints the required title and the current Product in the loop. Finally, print the total cost
	//
	void AidApp::listProducts() const {
		cout << " Row | SKU    | Product Name       | Cost  | QTY| Unit     |Need| Expiry   " << endl;
		cout << "-----|--------|--------------------|-------|----|----------|----|----------" << endl;
		double totalCost = 0;
		for (int i = 0; i < noOfProducts_; i++) {
			if (i == 10) pause();
			cout.width(4);
			cout.fill(' ');
			cout << right << i + 1 << " | ";
			cout << *product_[i] << endl;
			totalCost += *product_[i];
		}
		cout << "---------------------------------------------------------------------------" << endl;
		cout.setf(ios::fixed);
		cout.precision(2);
		cout << "Total cost of support: $" << totalCost << endl << endl;
	}

	// Loops through the product_ up to noOfProducts_ and checks each of them for the same SKU as the incoming argument 
	//
	int AidApp::SearchProducts(const char* sku) const {
		int i = 0;
		for (; i < noOfProducts_; i++) {
			if (*product_[i] == sku) {
				return i;
			}
		}
		return -1;
	}

	// Updates the quantity on hand for a Product.
	//
	void AidApp::addQty(const char* sku) {
		int no = SearchProducts(sku);
		cout << endl;
		if (no == -1) cout << "Not found!" << endl;
		else {
			product_[no]->write(cout, false);
			cout << endl << endl;
			int q;
			cout << "Please enter the number of purchased items: ";
			cin >> q;
			cout << endl;
			if (cin.fail()) {
				cout << "Invalid quanlity value!" << endl;
			}
			else {
				int required = product_[no]->qtyNeeded() - product_[no]->quantity();
				if (q <= required) {
					*product_[no] += q;
				}
				else {
					*product_[no] += required;
					cout << "Too many items; only "<< required<< " is needed, please return the extra " << (q - required) << " items." << endl;
				}
				saveRecs();
				cout << "Updated!" << endl;
			}
			cout << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
	}

	// Depending on the value of the argument being true or false, create a Perishable or Non-perishable Product and get the values from the user and add it to the end of the product_ array and save the records 
	//
	void AidApp::addProduct(bool isPerishable) {
		product_[noOfProducts_] = nullptr;
		delete product_[noOfProducts_];
		if (isPerishable) {
			product_[noOfProducts_] = new AmaPerishable();
		}
		else {
			product_[noOfProducts_] = new AmaProduct();
		}
		cin >> *product_[noOfProducts_];
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << *product_[noOfProducts_] << endl << endl;
		}
		else {
			cin.ignore(1000, '\n');
			noOfProducts_++;
			saveRecs();
			cout << endl << "Product added" << endl << endl;
		}
	}

	// Display the menu, receive the user¡¯s selection, and do the action requested
	//
	int AidApp::run() {
		int select, found;
		bool exit = false;
		char sku[256];
		while (!exit) {
			select = menu();
			cout << endl;
			switch (select) {
				case 1:
					listProducts();
					pause();
					break;
				case 2:
					cout << "Please enter the SKU: ";
					cin >> sku;
					cout << endl;
					found = SearchProducts(sku);
					if (found != -1) {
						product_[found]->write(cout, false);
						cout << endl;
						cin.clear();
						cin.ignore(1000, '\n');
						cout << endl;
						pause();
					}
					else {
						cout << "Not found!" << endl;
						cin.clear();
						cin.ignore(1000, '\n');
					}
					break;
				case 3:
					addProduct(false);
					break;
				case 4:
					addProduct(true);
					break;
				case 5:
					cout << "Please enter the SKU: ";
					cin >> sku;
					addQty(sku);
					break;
				case 0:
					cout << "Goodbye!!" << endl;
					exit = true;
					break;
				default:
					cout << "===Invalid Selection, try again.===" << endl;
					pause();
					break;
			}
		}
		return 0;
	}
}