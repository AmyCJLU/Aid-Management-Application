/***********************************************************
// File AidApp.h
// Date 2017/08/06
// Author Congjia Lu 
// Description
// Declares an AidApp class AidApp is a class to store and retrieve Perishable and Non-Perishable product information from and to a file. 
//
***********************************************************/

#ifndef SICT_AIDAPP_H__
#define SICT_AIDAPP_H__
#include "Product.h"
#include "general.h"

using namespace std;

namespace sict {
	class AidApp {
		char filename_[256];
		Product* product_[MAX_NO_RECS];
		fstream datafile_;
		int noOfProducts_;

		AidApp& operator=(const AidApp&) = delete;
		void pause() const;
		int menu();
		void loadRecs();
		void saveRecs();
		void listProducts() const;
		int SearchProducts(const char*) const;
		void addQty(const char*);
		void addProduct(bool);

	public:
		AidApp();
		AidApp(const char *);
		AidApp(const AidApp&) = delete;
		int run();
	};
}

#endif