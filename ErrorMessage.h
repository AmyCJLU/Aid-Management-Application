/***********************************************************
// File ErrorMessage.h
// Date 2017/07/11
// Author Congjia Lu
// Description
// Declares a ErrorMessage class that encapsulates an error message in a dynamic C-style string 
// and also is used as a flag for the error state of other classes.
//
***********************************************************/

#ifndef SICT_ERRORMESSAGE_H
#define SICT_ERRORMESSAGE_H

namespace sict{
    class ErrorMessage{
        char* message_;
    public:
        ErrorMessage();
        ErrorMessage(const char* errorMessage);
        ErrorMessage(const ErrorMessage& em) = delete;
        ErrorMessage& operator=(const ErrorMessage& em) = delete;
        ErrorMessage& operator=(const char* errorMessage);
        virtual ~ErrorMessage();
        void clear();
        bool isClear()const;
        void message(const char* value);
        const char* message()const;
    };
    std::ostream& operator<<(std::ostream& os, ErrorMessage& err);
}
#endif
