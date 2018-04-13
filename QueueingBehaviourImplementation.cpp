/* 

   QueueingBehaviourImplementation.cpp - implementation file for a program named example
   ============================================================================

   This program is for course 04-630 Data Structures and Algorithms for Engineers, Assignment No. 3 

   Please refer to the application file - QueueingBehaviourApplication.cpp - for details of the functionality of this program


   File organization
   -----------------

	QueueingBehaviour.h						interface file:      
											contains the declarations required to use the functions that implement the solution to this problem
											typically, these will include the definitions of the abstract data types used in the implementation

	QueueingBehaviourImplementation.cpp		implementation file: 
											contains the definitions of the functions that implement the algorithms used in the implementation
 
	QueueingBehaviourApplication.cpp		application file:    
											contains the code that instantiates the abstract data types and calls the associated functions
											in order to effect the required functionality for this application


   Author
   ------

   David Chukwuma
   7/03/2017


   Audit Trail
   -----------

   - Added prompt_and_exit() to allow users to read the terminal messages before it is closed.  David Vernon, 29/12/2016.

*/

 
 
#include "QueueingBehaviour.h"
#include "linkedList.h" 

void prompt_and_exit(int status) {
   printf("Press any key to continue and close terminal\n");
   getchar();
   exit(status);
}

void print_message_to_file(FILE *fp, char message[]) {
 
   fprintf(fp,"The message is: %s\n", message);
}



int samplePoisson(double lambda)
{
	if (lambda == 0)
	{
		return (0);	
	}
	/* Generate a random sample from a Poisson distribution with a given mean, lambda */
	/* Use the function rand to generate a random number */

	static bool first_call = true;
	int count;
	double product;
	double zero_probability;

	/* Seed the random-number generator with current time so */
	/* that the numbers will be different every time we run */
	if (first_call)
	{
		srand( (unsigned)time( NULL ));
		first_call = false;
	}

	count = 0;
	product = (double) rand() / (double) RAND_MAX;
	zero_probability = exp(-lambda);

	while (product > zero_probability) 
	{
		count++;
		product = product * ((double) rand() / (double) RAND_MAX);
	}

	return(count);
}

