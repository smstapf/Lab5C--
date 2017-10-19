//============================================================================
// Name        : Lab5B.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include<stdlib.h>

using namespace std;

class Signal{
	private:
		int length;
		double maximum;
		double *data;
		double average;
		void loadArray(char*);
		void stats();

	public:
		Signal();
		Signal(int);//constructor to pass file number
		Signal(char*);//constructor to pass file name
		~Signal();//destructor

		void offset(double num);
		void scale(double num);
		void center();
		void normalize();
		void Sig_info();
		void Save_File(char* );
		void printStats();
};

Signal::~Signal(){
	free( data );
	cout<<"Signal destructed"<<endl;
}

Signal::Signal(){
	length = 0;
	maximum = 0.00;
	data = NULL;
	average = 0.00;

	loadArray("Raw_data_01.txt");

}

Signal::Signal(int n){
	length = 0;
	maximum = 0.00;
	data = NULL;
	average = 0.00;

	char* filename = (char*)malloc(sizeof(char)*50);
	sprintf(filename,"Raw_data_%02d.txt",n);
	loadArray(filename);
}

Signal::Signal(char* filename){
	length = 0;
	maximum = 0.00;
	data = NULL;
	average = 0.00;

	loadArray(filename);
}

void Signal::loadArray(char* file)
{
	// Open the file and check for empty failure case
	FILE* filePointer = fopen(file, "r");
	if (filePointer == NULL)
	{
		printf("Error opening input file. File pointer was equal to NULL.");
		return;
		//terminates program
	}

	// Read the length and max from the first line
	fscanf(filePointer, "%d %lf", &length, &maximum);

	// read the signal data into an array
	data = (double *)malloc(sizeof(double) * length);
	int i = 0;
	for (i = 0; i < length; i++)
	{
		fscanf(filePointer, "%lf", (data + i));
	}
	fclose(filePointer);
}

void Signal::offset(double num)
{
	int i=0;
	for(i=0; i<length; i++){
		*(data+i) += num;
	}
	stats();
}

void Signal::normalize()
{
	int i=0;

	for(i=0; i<length; i++){
		*(data+i)=*(data+i)/maximum;
	}
	stats();
}

void Signal::scale(double num)
{
	int i=0;

	for(i=0; i<length; i++){
		*(data+i)=*(data+i)*num;
	}
	stats();
}

void Signal::stats()
{

	int i=0;
	double add=0;
	maximum=-99999999.0;

	for (i = 0; i < length; i++)
	{
		if (*(data+i) > maximum)
		maximum = *(data+i);
	}

	for (i = 0; i < length; i++)
	{
		add += *(data+i);
	}

	average = (double)add/length;
}

void Signal::center()
{
	int i=0;

	for(i=0; i<length; i++){
		*(data+i)=*(data+i)-average;
	}
	stats();
}

void Signal::Sig_info()
{
	cout << "Length: " << length << endl;
	cout << "Maximum Value: " << maximum << endl;
	cout << "Current Average: " << average << endl;
}

void Signal::Save_File(char* output_filename)
{
	FILE* filePointer = fopen(output_filename, "w");

		if (filePointer == NULL) //making sure the input file exists
		{
			freopen(output_filename, "w", filePointer);
		}

		fprintf(filePointer, "%d %6.4f\n", length, maximum); //writes to file
		int i;
		for (i = 0; i < length; i++)
		{
			fprintf(filePointer, "%6.4f\n", *(data+i));
		}

		fclose(filePointer);

		return;
}

void printHelp(void)
{
	printf("The program should be called through use of commmand line arguments. ");
}

void Signal::printStats()
{
	cout << "Length:" << length << endl;
	cout << "Maximum value: " << maximum << endl;
}

int main(int argc, char **argv)
{

	Signal *obj1 = new Signal();

	// Loop through and process all the arguments
	int arg_count = 1;
	while (arg_count < argc)
	{
		// File Number - this one has to be there or it won't run
		if ((argv[arg_count][0] == '-') && (argv[arg_count][1] == 'n'))
		{
			arg_count++;
			delete obj1;
			obj1 = new Signal(atoi(argv[arg_count]));
			break;
		}

		// File Name
		if ((argv[arg_count][0] == '-') && (argv[arg_count][1] == 'f'))
		{
			arg_count++;
			delete obj1;
			obj1 = new Signal(argv[arg_count]);
			break;
		}
	}

	int exit = 0;
	int choice = 0;

	while(exit == 0)
	{
		cout << "What would you like to do?" << endl;
		cout << "1. Normalize" << endl;
		cout << "2. Center " << endl;
		cout << "3. Scale " << endl;
		cout << "4. Statistics" << endl;
		cout << "5. Offset" << endl;
		cout << "6. Write to a file" << endl;
		cout << "7. Exit" << endl;
		cin  >>  choice;

		switch(choice)
		{
			case 1:
			{
				obj1->normalize();
				break;
			}
			case 2:
			{
				obj1->center();
				break;
			}
			case 3:
			{
				double value;
				cout << "Please enter a scale value." << endl;
				cin >> value;
				obj1->scale(value);
				break;
			}
			case 4:
			{
				obj1->printStats();
				break;
			}
			case 5:
			{
				double offsetValue;
				cout <<"Please enter an offset value." << endl;
				cin >> offsetValue;
				obj1->offset(offsetValue);
				break;
			}
			case 6:
			{
				obj1->Save_File("Output.txt");
				break;
			}
			case 7:
			{
				exit = 1;
				cout <<"You have exited the program" << endl;
				break;
			}
			default:
			{
				cout << "You did not enter the a correct number."<< endl;
			}
		}
	}


}




