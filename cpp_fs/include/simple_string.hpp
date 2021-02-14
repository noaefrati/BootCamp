//******************************************************************************
// Header file Containing API of String                                        *
//                                                                             *
// Infinity Labs - RD97                                                        *
//******************************************************************************
#ifndef ILRD_RD97_SIMPLE_STRING_HPP
#define ILRD_RD97_SIMPLE_STRING_HPP

#include <iostream> // ostream

namespace ilrd
{

class String
{
public:
    /***************************Constructors***********************************/

    // Regular Ctor, initializes string to str_.
    String(const char *str_ = ""); //non explicit on purpose

    // CCtor, copies str_ to String.
    String(const String& str_);

    /****************************Operators*************************************/
    
    //Copy assignmet operator.
    String& operator=(const String& str_);   

    /****************************Destructor************************************/
    
    // Defult destructor 
    ~String();

    /*************************Member Functions*********************************/
    
    // Function calculates the length of the string,
    // excluding the terminating null byte ('\0').    
    size_t Length() const;

    // Function returns pointer to string.
    const char *CStr() const;

private:
    char *m_cstr;
};//class String

} // namspace ilrd 

#endif /// ILRD_RD97_SIMPLE_STRING_HPP
