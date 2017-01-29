#include <iostream>
#include <stdlib.h>

using namespace std;


int convertToIntArray(int argc, char* argv[], int array[]){
	if (argc > 22)
		return -21;
	
	int numElements = 0;
	
	// i is a count variable in terms of the int array[]
	
	for (int i = 2; i < argc; i++){
		
		// cout << "atoi(argv[" << i << "]) = " << atoi(argv[i]) << endl;
		
		for (int j = 0; (argv[i][j]) != 0; j++){
			if (argv[i][0] != '0'){
				if (atoi(argv[i]) <= 0 && atol(argv[i]) >= 0)
					return -(i);
			}
		}
		
		// Error code if atoi of a char gives a negative value
		//if (atoi(argv[i]) < 0)
			//return -22;
		
		if (atoi(argv[i]) == 0 && *argv[i] != '0'){
			return -(i);
		}
	
		else {
			array[i - 2] = atoi(argv[i]);
			numElements++;
		}
	}	
	
	return numElements;
}

// May have to change the function after overflow problem is solved
// printError takes a negative error code
void printError(int errorCode){
	if (errorCode == -21)
		cerr << "Error: too many input arguments; maximum 20 permitted.";
	else if (errorCode == -22)
		cerr << "Error: Invalid Window Size.";	
	else
		cerr << "Error: Argument " << errorCode * -1 << " is not an integer.";
	return;
}

int slideAvg(int inputVoltages[], int sampleSize, int windowSize, float slidingAverage[]){
	
	int numSlidingAvg = 0;
	int voltSum = 0;
	for (int i = 0; i < sampleSize - windowSize + 1; i++){
		for (int n = 0; n < windowSize; n++){
			voltSum += inputVoltages[i + n];	
		}
		
		slidingAverage[i] = (float)(voltSum) / windowSize;
		voltSum = 0;
		numSlidingAvg++;
	}
	
	// Include code for error checking
	
	return numSlidingAvg;
}


void roundingArray(int numElements, float array[]){
	
	for (int i = 0; i < numElements; i++){
		
		// Checks if the decimal part is < 0.25 and rounds down to 0.0
		if (array[i] - int(array[i]) < 0.25)
			array[i] = int(array[i]);
		
		// Checks if the decimal part is < 0.5 and > 0.25 and rounds up to 0.5
		else if (array[i] - int(array[i]) < 0.5) 
			array[i] = int(array[i]) + 0.5;
		
		// Checks if the decimal part is >= 0.75 and rounds up to 1.0
		else if (array[i] - int(array[i]) >= 0.75)
			array[i] = int(array[i]) + 1;
		
		// Checks if the decimal part is >= 0.5 and < 0.75 and rounds down to 0.5
		else
			array[i] = int(array[i]) + 0.5;
	}
	
	return;	
}

void displayHistogram(int numElements, float array[]){

	cout << "100V------105V------110V------115V------120V------125V------130V------135V------140V" << endl;
	
	roundingArray(numElements, array);
	
	for (int i = 0; i < numElements; i++){
		
		if (array[i] < 100){
			cout << '!' << endl;
		}
		
		else if (array[i] <= 140){
			for (float j = 100; j <= array[i]; j += 0.5)
				cout << "#";
			cout << endl;
		}
		
		else{
			for (float j = 0; j < 81; j++)
				cout << "#";
			cout << "+" << endl;
		}
	}
	
	cout << endl;
	return;
}

int main(int argc, char* argv[]){
	
	int inputVoltages[argc - 1];
	
	// Either stores the number of elements in the integer array
	// Or it stores the error code from convertToIntArray function
	int sampleSize;
		
	// Assigns sampleSize a value
	if (argc - 1 == 0)
		sampleSize = 0;
	else
		sampleSize = convertToIntArray(argc, argv, inputVoltages);

	// Prints out an error if sampleSize < 0
	if (sampleSize < 0){
		printError(sampleSize);
		return -1;
	}
	
	// The second argument from command line (argv[1])
	int windowSize = atoi(argv[1]);
	
	// Prints windowSize
	// cout << "\nWindow size: " << windowSize << endl;
	
	// Prints out an error if windowSize < 0 or > sampleSize
	if (windowSize <= 0 || windowSize > sampleSize){
		printError(-22);
		return -1;
	}
	
	// Declares a slidingAvg array
	float slidingAvg[sampleSize - windowSize + 1];
	
	// Assigns length of slidingAvg[] to numSlidingAvg
	// by calling the slideAvg function
	int numSlidingAvg = slideAvg(inputVoltages, sampleSize, windowSize, slidingAvg);
	
	/*
	// Prints the inputVoltages array
	cout << "Input Voltages: " << endl;
	for (int p = 0; p < sampleSize; p++)
		cout << inputVoltages[p] << " ";
	
	cout << endl;
		
	// Prints the slidingAvg array
	cout << "Sliding Averages: " << endl;
	for (int p = 0; p < numSlidingAvg; p++)
		cout << slidingAvg[p] << " ";
	cout << endl;
	*/
	
	float inputVoltsFloat[sampleSize];
	for (int i = 0; i < sampleSize; i++)
		inputVoltsFloat[i] = (float)inputVoltages[i];
	
	// Displays histogram for inputVoltages array
	displayHistogram(sampleSize, inputVoltsFloat);

	// Displays histogram for slidingAvg array
	displayHistogram(numSlidingAvg, slidingAvg);	
	
	return 0;
}