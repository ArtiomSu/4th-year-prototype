/*
 * To change this license header, choose License Headers in Project Properties.    
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: mrarchinton
 *
 * Created on 28 November 2018, 18:15
 */

#include "tpminputvector.h"
#include "dynamicarray.h"
#include "treeparitymachine.h"
#include "tpmhandler.h"
#include <iostream>
#include <stdlib.h>
#include <string>



#include <sstream>
using namespace std;




int main(int argc, char** argv) {
int showWeights = 1;


int i, ii, ss, itrMax, j, K=0,sum, key_size, key_length, initN, initL, initK;
TreeParityMachine A, B;
TPMInputVector tmpinputvector;


DynamicArray<char> key;
const char Dictionary [] = "0123456789_abcdefghijklmnopqrstuvwxyz";

cout << "Dictionary size " <<sizeof(Dictionary);

srand (time(NULL)); //random generator
initK = 8;  // k is hidden neurons													//9 def, +1 = 4 key increase
initN = 10; // n is input neurons													//12 def +1 = 3 increase
initL = 6;	// range of weights														//4 def  +1 = 9 increase, + 2 = 18, maxes out at 54 at 6 if only increasing this

        
A.K=initK, A.N=initN, A.L=initL;//InitA
A.Initialize (); 
A.RandomWeight ();

B.K=initK, B.N=initN, B.L=initL;//InitB
B.Initialize (); 
B.RandomWeight ();


if(showWeights){
	cout << "\n\n Weights of a and b before sync" << "\n";
	for(i=0; i< initK * initN; i++){
		cout << i << ": \t" << A.W.Z[i] << "\t" << B.W.Z[i] << "\n";
	}
	cout << "\n\n\n";
}


itrMax=(A.L*A.L*A.L*A.L)*A.N*A.K; /////
cout << "\nMaximum Iterations: "<<itrMax;
tmpinputvector.xLength (A.K, A.N);
cout<<"\nSynchronizing TPM Networks...";



for (i=1; i!=itrMax; i++) {
	tmpinputvector.CreateRandomVector(A.K, A.N);



	A.ComputeTPMResult(tmpinputvector.X);


	std::string in_string = tmpinputvector.to_string(A.K , A.N);


	TPMInputVector in;
   	in.xLength(A.K, A.N);

   	in.set_from_string(in_string, A.K, A.N);


	B.ComputeTPMResult(in.X);
	
	if(A.TPMOutput == B.TPMOutput) {
		A.UpdateWeight (tmpinputvector.X);
		B.UpdateWeight (tmpinputvector.X);
		sum = 0;
		for(ss=0;ss<A.K*A.N;ss++)	//Find sum
			sum += abs(A.W.Z[ss]-	B.W.Z[ss]);
		if ( sum == 0 ) break;	
	} 
}
if (sum == 0)
	cout << "Status: SUCCESS! after " << i << " itterations";
else{
	cout << "Status: FAILED!";
	return 1;
}

cout << "\nDataExchanged: " << (i*(A.K*A.N+4)/1024) << " KiB\n";
key_size = (sizeof(Dictionary)-1) / (A.L * 2 + 1);
key_length = A.K * A.N / key_size;

cout << "Key length: " << key_length;
key.length(key_length + 1);
	
for(i = 0; i < key_length; i++)
	key.Z[i] = 0;
	
for (i=1; i < key_length+1; i++) {
	K = 1;
	for(j=(i-1)*key_size; j<i*key_size;j++)
		K = K + A.W.Z[j] + A.L;
	//
	key.Z[i-1]=Dictionary[K];
}

key.Z[key_length]='\0'; //Null char
cout << "\nKey: " << key.Z << "\n\n";


if(showWeights){
	cout << "\n\n Weights of a and b after sync" << "\n";
	for(i=0; i< initK * initN; i++){
		cout << i << ": \t" << A.W.Z[i] << "\t" << B.W.Z[i] << "\n";
	}
	cout << "\n\n\n";
}

   tmpinputvector.CreateRandomVector(A.K, A.N);
   
   //cout << TPMInputVector_to_string(&tmpinputvector, A.K * A.N);
   cout << tmpinputvector.to_string(A.K , A.N);

   cout << endl;

   string t = tmpinputvector.to_string(A.K , A.N);
   cout << t << endl;

   TPMInputVector in;
   in.xLength(A.K, A.N);
   //in.CreateRandomVector(A.K, A.N);

   cout<< "made it here" << endl;

   //string_to_TPMInputVector(&in, t);

   in.set_from_string(t, A.K, A.N);

   cout<< "made it here1" << endl;
   cout << in.to_string(A.K , A.N);
	cout << endl;

    return 0;
}

