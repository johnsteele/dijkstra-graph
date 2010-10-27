//====================================================================
// Object.cpp 
//  
// This class represents an Object that stores a description of a 
// vertex. It is used in Graph.h. Max description length is 50 char. 
//
// Author: John Steele <steelejr@u.washington.edu> 
// Date  : 2010/11/02
// Class : CSS 343 - Lab 3
//====================================================================
// Object class: 
//   Includes following features:
// 	- allows outputing an Object using <<.
// Assumptions:
// 	- When creating an Object the parameter string description is
//	  not more than 50 characters long. 
//==================================================================== 

#include "Object.h" 

//========================Constructor=================================
// Creates a Object with an empty description.
// 
// Preconditions: None. 
//		
// Postconditions: This Object has been instanitiated with its 
// 		   description initialized to empty.
//====================================================================
Object::Object ()
{
	// Initialize description array.
	int i;
	for (i = 0; i < MAX_SIZE; i++) 
		my_desc [i] = '\0';	
}


//=======================Copy-Constructor============================
// Creates a Object with its description set to the_other's 
// description.
// 
// Preconditions: The end of the_other's description is marked with a
//		  terminating character. 
//		
// Postconditions: This Object has been instanitiated with its 
//		   description set to the_other's. 
//====================================================================
Object::Object (const Object &the_other)
{
	copy_data (my_desc, the_other.my_desc);
}


//========================copy_data===================================
// Copies the data the data from the_val2 into the_val1.
// 
// Preconditions: The end of the_val2 is marked with a terminating 
//		  '\0' character. 
//		
// Postconditions: the_val2 is copied into the_val1. 
//==================================================================== 
void Object::copy_data (char *the_val1, const char *the_val2) 
{
	// Stop when we reach '\0', or MAX_SIZE.
	while ((*the_val1++ = *the_val2++) && 
		(the_val1 != &my_desc [MAX_SIZE]));

	// Terminate end of string.	
	*the_val1 = '\0';
}


//========================setData=====================================
// Sets this Object's description to the line of characters extracted
// from the infile stream. If the description is longer than 
// MAX_SIZE the trailing data will be omitted. 
// 
// Preconditions: The give ifstream is open. 
//		
// Postconditions: my_desc is set to the first MAX_SIZE of chars in 
//		   the infile.
//====================================================================
void Object::setData (ifstream &infile)
{
	if (infile.is_open()) 
		infile.getline (my_desc, MAX_SIZE + 1);	
}	


//========================operator<<==================================
// Overloaded operator<<.
// Sends my_desc to the outupt stream and returns it.
//====================================================================
ostream& operator<< (ostream &the_output, const Object &the_object)
{
	the_output << the_object.my_desc;
	return the_output;
}

