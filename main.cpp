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

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    int i, ii, ss, itrMax, j, K=0,sum, key_size, key_length, initN, initL, initK;
TreeParityMachine A, B;
TPMInputVector objInput;


DynamicArray<char> publickey;
const char Dictionary [] = "01234567890_abcdefghijklmnopqrstuvwxyz";

srand (time(NULL)); //random generator
cout << "Parameter settings (K, N, L)";
initK = 9;  // k is hidden neurons
initN = 12; // n is input neurons
initL = 4;

        
A.K=initK, A.N=initN, A.L=initL;//InitA
A.Initialize (); A.RandomWeight ();

B.K=initK, B.N=initN, B.L=initL;//InitB
B.Initialize (); B.RandomWeight ();

itrMax=(A.L*A.L*A.L*A.L)*A.N*A.K; /////
cout << "\nMaximum Iterations: "<<itrMax;
objInput.xLength (B.K, B.N);
cout<<"\nSynchronizing TPM Networks...";




for (i=1; i!=itrMax; i++) {
	objInput.CreateRandomVector(B.K, B.N);
	A.ComputeTPMResult(objInput.X);
	B.ComputeTPMResult(objInput.X);
	
	if(A.TPMOutput == B.TPMOutput) {
		A.UpdateWeight (objInput.X);
		B.UpdateWeight (objInput.X);
		sum = 0;
		for(ss=0;ss<A.K*A.N;ss++)	//Find sum
			sum += abs(A.W.Z[ss]-	B.W.Z[ss]);
		if ( sum == 0 ) break;	
	} 
}
if (sum == 0)
	cout << "Status: SUCCESS! itterations=" << i;
else cout << "Status: FAILED!";



cout << "\n\n\n";
cout << "Iterations:" << i << "DataExchanged:" << (i*(A.K*A.N+4)/1024) << " KiB";
key_size = 37 / (A.L * 2 + 1);
key_length = A.K * A.N / key_size;

cout << "Key length: " << key_length;
publickey.length(key_length + 1);
	
for(i = 0; i < key_length; i++)
	publickey.Z[i] = 0;
	
for (i=1; i < key_length+1; i++) {
	K = 1;
	for(j=(i-1)*key_size; j<i*key_size;j++)
		K = K + A.W.Z[j] + A.L;
	//
	publickey.Z[i-1]=Dictionary[K];
}

publickey.Z[key_length]='\0'; //Null char
cout << "Public Key: " << publickey.Z;










cout << "\n\n\n\nMade it to end";
    
    return 0;
}

