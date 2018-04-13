/* 

   example.h - interface file for a program named example
   ======================================================

   This program is for course 04-630 Data Structures and Algorithms for Engineers, Assignment No. 0 

   Please refer to the application file - exampleApplication.cpp - for details of the functionality of this program

      
   File organization
   -----------------

   QueueingBehaviour.h			interface file:      
								contains the declarations required to use the functions that implement the solution to this problem
								typically, these will include the definitions of the abstract data types used in the implementation

	QueueingBehaviourImplementation.cpp	implementation file: 
								contains the definitions of the functions that implement the algorithms used in the implementation
 
	QueueingBehaviourApplication.cpp		application file:    
								contains the code that instantiates the abstract data types and calls the associated functions
								in order to effect the required functionality for this application

   Author
   ------

   David Chukwuma
   21/01/2017


   Audit Trail
   -----------

   - Added prompt_and_exit() to allow users to read the terminal messages before it is closed.  David Vernon, 29/12/2016.

*/

 
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <ctype.h>
#include <time.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define MAX_MESSAGE_LENGTH 81



/* function prototypes go here */

void prompt_and_exit(int status);
void print_message_to_file(FILE *fp, char message[]);
int samplePoisson(double lambda);
