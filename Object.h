//====================================================================
// Object.h 
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

#ifndef _OBJECT_H
#define _OBJECT_H
#include <iostream>
using namespace std;

class Object {

	//========================operator<<==========================
	// Overloaded operator<<.
	//============================================================ 
	friend ostream& operator<< (ostream &, const Object &);

public: 

	//========================Constructor=========================
	// Creates a Object with its description set to the 
	// description in the provided pointer.  
	// 
	// Preconditions: The end of the string that is passed is 
	//		  marked with a terminating character.
	//		
	// Postconditions: This Object has been instanitiated with
	//		   its description set to the_desc.  
	//============================================================ 
	Object (const char *);


	//========================Copy-Constructor====================
	// Creates a Object with its description set to the_other's 
	// description.
	// 
	// Preconditions: The end of the_other's description is marked
	//		  with a terminating character. 
	//		
	// Postconditions: This Object has been instanitiated with
	//		   its description set to the_other's. 
	//============================================================ 
	Object (const Object &);


private:

	//========================copy_data===========================
	// Copies the data the data from the_val2 into the_val1.
	// 
	// Preconditions: The end of the_val2 is marked with a 
	//		  terminating character. 
	//		
	// Postconditions: the_val2 is copied into the_val1. 
	//============================================================ 
	void copy_data (char *, const char *); 


	// The max size of the description.
	static const int MAX_SIZE = 50;

	// The Object description.
	char my_desc [MAX_SIZE];
};
#endif /* _OBJECT_H */


