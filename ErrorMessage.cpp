/***********************************************************
// File ErrorMessage.cpp
// Date 2017/07/11
// Author Congjia Lu 
// Description
// Defines a ErrorMessage class that encapsulates an error message in a dynamic C-style string 
// and also is used as a flag for the error state of other classes.
//
***********************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include "ErrorMessage.h"

namespace sict{
    // Default constructor. Sets the message_ member variable to nullptr.
    //
    ErrorMessage::ErrorMessage(){
        message_ = nullptr;
    }
    
    // Uses the message() setter member function to set the error message to the errorMessage argument
    //
    ErrorMessage::ErrorMessage(const char* errorMessage){
        message_ = nullptr;
        message(errorMessage);
    }
    
    // Sets the message_ to the  errorMessage argument and returns the current object
    //
    ErrorMessage& ErrorMessage ::operator=(const char* errorMessage){
        clear();
        message(errorMessage);
        return *this;
    }

    // De-allocates the memory pointed by message_
    //
    ErrorMessage::~ErrorMessage(){
        clear();
    }
    
    // De-allocates the memory pointed by message_ and then sets message_ to nullptr
    //
    void ErrorMessage::clear(){
        delete [] message_;
        message_=nullptr;
    }
    
    // Returns true if message_  is nullptr
    //
    bool ErrorMessage::isClear()const{
        return (message_ == nullptr);
    }

    // Sets the message_ of the ErrorMessage object to a new value
    //
    void ErrorMessage::message(const char *value){
        clear();
        long int size= strlen(value);
        message_ = new char[size+1];
        strncpy(message_, value, size);
        message_[size] = '\0';
    }
    
    // Returns the address kept in message_
    //
    const char* ErrorMessage::message()const{
        return message_;
    }
    
    // Overload operator<< so the ErrorMessage can be printed using cout
    //
    std::ostream& operator<<(std::ostream& os, ErrorMessage& err){
        if (!err.isClear()){
            os << err.message();
        }
        return os;
    }
}



