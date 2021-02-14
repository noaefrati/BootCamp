/*****************************************************************************/
/*****************************************************************************/
#include <cstring>
#include <iostream>

#include "simple_string.hpp"

namespace ilrd
{

/***************************Constructors***********************************/

String::String(const char *str_)
{
	size_t length = strlen(str_) + 1;
	m_cstr = new char[length];
	
	strcpy(m_ctr, str_);
}

String::String(const String& str_)
{
	size_t length =  str_.Length() + 1;
	m_cstr = new char[length];
	
	strcpy(m_cstr, str_.m_cstr);
}

 /****************************Destructor************************************/

String::~String()
{
	delete m_cstr;
	m_cstr = 0;
}
 
/****************************Operators*************************************/
    
//Copy assignmet operator.
String& String:: operator=(const String& str_)
{
	if (this.m_cstr != str_.m_cstr)
	{
			delete this.m_cstr;
			
			size_t length = str_.Length() + 1;
			this.m_cstr = new char[length];
			
			strcpy(this.m_cstr, str_.m_cstr);
	}
	
	return *this;
}	

/*************************Member Functions*********************************/
    
    // Function calculates the length of the string,
    // excluding the terminating null byte ('\0').    
size_t Length() const
{
	return strlen(this.m_cstr);
}

    // Function returns pointer to string.
const char *CStr() const
{
	return this.m_cstr;
}


} // namspace ilrd 