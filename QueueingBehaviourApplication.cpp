	/* 

	exampleApplication.cpp - application file for a program named example
	=====================================================================

	Problem Definition
	-------------------
	This program simulates the queuing behaviour of cars in a single lane of traffic as a
	function of the arrival rate of the cars and the traffic light sequencing, i.e. the amount of time
	the lights stay green, amber, and red. The following information is read from a file and used as variables
	in the program.

	• The arrival rate in vehicles per minute.
	• The average departure time per car in seconds.
	• The running time for the simulation, specified in minutes.
	• The time increment to use for each discrete interval of simulation, specified in milliseconds.
	• The traffic light sequencing given by the time the lights stay green, amber, and red,
	specified in seconds.

	The program calculates the average and maximum lengths of the queue of cars and
	average and maximum waiting time of the cars during the simulation period.
	The program imposes no restriction on the length of the queue.
	Cars can only proceed when the light is green.

	The arrival of vehicles is modelled using a Poisson distribution, 
	using the average arrival rate as a parameter.

	Input
	------

	The first line of input comprises an integer N (0 < N < 1000); this determines the number of
	simulation scenarios in the input file (i.e. the number of sets of seven simulation parameters:
	arrival rate, departure rate, running time, time increment, red light duration, amber light
	duration, green light duration). It is followed by N sets of seven key-value pairs, each pair
	specifying the input parameter and its value. The key-value pairs can appear in any order.
	There will be only one key-value pair for each parameter. All input provided is valid and 
	contains no errors.

	Output
	The output begins with my Andrew Id.
	The program write the computed statistics in tabular form to a text file and the input parameters.

	Sample Input

	1
	Arrival 10
	Departure 5
	Runtime 5
	Increment 10
	Green 10
	Amber 1
	Red 30

	Sample Output

	dchukwue
	Arrival rate: 10 cars per min
	Departure rate:	5 s per car
	Runtime: 5 mins
	Time increment:	10 ms
	Light sequence:	Green 0 s; Amber 1 s; Red 30 s
	Average length: 24 cars
	Maximum length: 48 cars
	Average wait: 152 s
	Maximum wait: 288 s

	Solution Description
	=====================================================================

	I begin by storing values read from the input file. Each test case is exactly seven(7) lines, so I loop for seven lines
	per test case.

	Then a simulation loop is implemented that counts from zero to the full simulation period, in increments equal to the runtime in milliseconds.

	A sample poisson function is called by passing in the lambda.

	Next I implement a queue Data structure using a linkedlist implementation.

	I use my new implementation to enqueue n cars per time increment, where n is the integer value the sample poisson returns.

	I also dequeue as if certain conditions are met, like if the light is green. This is possible because I have an enumeration 
	of traffic light colors and I keep track of when they change.

	At This point I start getting statistics

	• Total number of cars in the simulation.
	• Queue lenght per interval.
	• Averag queue length
	• maximum queue length
	• Maximum waiting time
	• Average and maximum waiting time

	After the main simulation loop, I check the queue to see if there are any cars still
	waiting. These have to be dequeued and the time they have been waiting is added to the running total
	to ensure more accurate statistics.

	Complexity Analysis
	=====================================================================

	Reading all the values from file has a big O of n^2 because there is a for loop nested in a for loop.

	The main simulation loop also has a big O of n^2 because there is a nested for loop in a while loop.

	The while loop to dequeue the remaining cars has a big O of n.

	Dequeuing a car has a big O of 1, since it is always the first element that is being removed.

	Enqueuing has a big O of n since it is adding a car to the end of the list, which means it has to iterate
	over all the elements in the queue.

	Therefore my complexity equation is n^2 + n^2 + n + n + 1 = 2n^2 + 2n + 2

	therefore the big O of this solution is n^2.

	Test Strategy Description
	=====================================================================
	Testing with the same values repeatedly 

	Testing when the runtime is zero

	Testing when arrival or departure is zero

	Author
	------

	David Chukwuma
	21/01/2017


	Audit Trail
	-----------


	- Added prompt_and_exit() to allow users to read the terminal messages before it is closed. Ran as is, code was written by David Vernon, 29/12/2016.

	*/

#include "QueueingBehaviour.h"
#include "linkedList.h"

#define KEY_LENGTH 2000
#define STRING_LENGTH 2000
#define NUMBER_OF_KEYS 7

int main() {


	int debug = TRUE;
	typedef char keyword[KEY_LENGTH];
	char input_string[STRING_LENGTH]; // a line read from the input file
	//long int increment = 0; // milliseconds
	keyword key; // the key string when reading parameters
	int value=0;
	int number_of_test_cases;

	keyword keylist[NUMBER_OF_KEYS] = {
		"arrival",
		"departure",
		"runtime",
		"increment",
		"red",
		"amber",
		"green"
	};

	long int increment=0; // similation interval (i.e. time increment)
	//int arrival;
	int departure;
	int runtime;
	int red;
	int amber;
	int green;
	double lambda;
	int count;
	int arrival_rate_input; // the arrival rate in cars per minute
	double arrival_rate=0; // the arrival rate in cars per millisecond




	FILE *fp_in, *fp_out;

	if ((fp_in = fopen("../data/input.txt","r")) == 0) {
		printf("Error can't open input input.txt\n");
		prompt_and_exit(1);
	}

	if ((fp_out = fopen("../data/output.txt","w")) == 0) {
		printf("Error can't open output output.txt\n");
		prompt_and_exit(1);
	}


	fgets(input_string, STRING_LENGTH, fp_in); 
	sscanf(input_string, "%d", &value);
	number_of_test_cases=value;


	printf("dchukwue \n");
	fprintf(fp_out,"dchukwue\n"); /*Prints Andrew ID to file*/

	for (int i=0;i<number_of_test_cases;i++)
	{

		ELEMENT_TYPE e;
		LIST_TYPE list;

		initialize_list(&list); 
		empty(&list);


		for (int q =0; q<7;q++)
		{
			fgets(input_string, STRING_LENGTH, fp_in); // read a line from the input file

			//printf("Input string: %s",input_string); // write it out to the terminal to check
			/* extract the key */

			sscanf(input_string, " %s %d", key, &value); // extracts the key and the value from the string

			//printf("key-value: %s %d\n", key, value); // write it out to the terminal to check

			/* convert the key to lower case to be safe */
			for (int j=0; j < (int) strlen(key); j++)
				key[j] = tolower(key[j]);

			//printf("key-value: %s %d\n",key, value); // write it out to the terminal to check
			/* now compare it */

			if (strcmp(key, "increment") == 0)// strcmp() return 0 when there is a match
			{ 
				increment=value;
				//increment = value; // milliseconds
			}
			else if (strcmp(key, "arrival")== 0)
			{
				arrival_rate_input=value;
			}
			else if (strcmp(key, "departure")== 0)
			{
				departure=value*1000;
			}
			else if (strcmp(key, "runtime")== 0)
			{
				runtime=value*60*1000;
			}
			else if (strcmp(key, "red")== 0)
			{
				red=value;
			}
			else if (strcmp(key, "amber")== 0)
			{
				amber=value;
			}
			else if (strcmp(key, "green")== 0)
			{
				green=value;
			}
		}

		int time=0;
		if (arrival_rate_input>0)
		{
			arrival_rate = ((float) arrival_rate_input) / (60 * 1000); /* arrival_rate_input is in cars per second so convert to cars per millisecond */
		}
		else
		{
			arrival_rate=0;
		}
		lambda = arrival_rate * increment; /* the Poisson distribution mean, lambda, is the arrival rate of cars during */
		int cars=0;
		int qlenght=0;
		int totalqlenght=0;
		int maxqLenght=0;
		int departTimer=0;
		int lightTimer=0;
		int waitTime=0;
		int intervals=0; /* the simulation interval, i.e. arrival rate per millisecond multiplied by */
		int maxWaitTime=0;
		int totalWaiTime=0;
		int avgWaitTime=0;
		int avgqLenght=0;


		enum lightState{RED,AMBER,GREEN}; // Enum that store traffic light colors.

		lightState lstate=RED;

		while(time<runtime )
		{	
			count = samplePoisson(lambda); // the number of cars that arrive in any given // simulation interval (i.e time increment)

			if(count >0)
			{
				for(int k=0;k < count;k++)
				{
					assign_element_values(&e, time, "Car");
					enqueue(list,e);
					cars++;
					qlenght++; /* Compute the number of cars that have arrived in the current simulation interval */

				}
				//printf("count is: %d %d\n",count,time);

			}

			if(lstate==RED && lightTimer > (red*1000))
			{
				lstate = AMBER;
				//printf("Light is now Yellow \n");
				lightTimer=0;
			}
			if(lstate==AMBER && lightTimer > (amber*1000))
			{
				lstate = GREEN;
				//printf("Light is now Green \n");
				lightTimer=0;
				departTimer=0;
			}

			if(lstate==GREEN && lightTimer > (green*1000))
			{
				lstate = RED;
				//printf("Light is now Red \n");
				lightTimer=0;

			}

			lightTimer+=increment;


			if (departTimer > departure && lstate==GREEN)
			{
				if(!is_empty(&list))
				{
					e=dequeue(list);
					waitTime=time-e.number;
					totalWaiTime +=waitTime;

					if (waitTime>maxWaitTime)
					{
						maxWaitTime=waitTime;
					}

					//printf("Dequeued %s,it stayed in queue for %d milliseconds \n", e.string,waitTime);
					departTimer=0;
					qlenght--;
				}
			}


			if (qlenght > maxqLenght)
			{
				maxqLenght= qlenght;
			}


			departTimer+=increment;
			time=time+increment;
			intervals++;
			totalqlenght+=qlenght;
		}

		while(!(is_empty(&list)))
		{
			e=dequeue(list);
			waitTime=time-e.number;
			totalWaiTime +=waitTime;

			if (waitTime>maxWaitTime)
			{
				maxWaitTime=waitTime;
			}

		}

		if(intervals>0)
		{
			avgqLenght= totalqlenght/intervals;
		}
		else
		{
			avgqLenght=0;
		}

		if(cars>0 )
		{
			avgWaitTime=totalWaiTime/cars;			
		}
		else
		{
			avgWaitTime=0;
		}

		printf("Arrival rate: %d cars per min\n", arrival_rate_input);
		printf("Departure rate:	%d s per car\n", departure/1000);
		printf("Runtime: %d mins\n", runtime/(60*1000));
		printf("Time increment:	%d ms\n", increment);
		printf("Light sequence:	Green %d s; Amber %d s; Red %d s\n", green,amber,red);
		printf("Average length: %d cars\n", avgqLenght);
		printf("Maximum length: %d cars\n", maxqLenght);
		printf("Average wait: %d s\n", avgWaitTime/1000);
		printf("Maximum wait: %d s\n", maxWaitTime/1000);
		printf("\n");


		fprintf(fp_out,"Arrival rate: %d cars per min\n", arrival_rate_input);
		fprintf(fp_out,"Departure rate:	%d s per car\n", departure/1000);
		fprintf(fp_out,"Runtime: %d mins\n", runtime/(60*1000));
		fprintf(fp_out,"Time increment:	%d ms\n", increment);
		fprintf(fp_out,"Light sequence:	Green %d s; Amber %d s; Red %d s\n", green,amber,red);
		fprintf(fp_out,"Average length: %d cars\n", avgqLenght);
		fprintf(fp_out,"Maximum length: %d cars\n", maxqLenght);
		fprintf(fp_out,"Average wait: %d s\n", avgWaitTime/1000);
		fprintf(fp_out,"Maximum wait: %d s\n", maxWaitTime/1000);
		fprintf(fp_out,"\n");


		//printf("Total number of cars that arrived are: %d %d %d\n",cars, qlenght,size(list));
		//print(&list);
		//printf("Values: %d %f %d %d %d %d %d %f\n", arrival_rate_input,arrival_rate,runtime,increment,green,amber,red,lambda);

	}
	fclose(fp_in);
	fclose(fp_out);

	prompt_and_exit(0);
}
