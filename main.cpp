#include <iostream>
#include <cstdlib>
#include <string>
#include <stdlib.h>

using namespace std;

// words
string hundreds[] =	{""," sto "," dwiescie "," trzysta "," czterysta "," piecset "," szescset "," siedemset "," osiemset "," dziewiecset "};
string thousands[] = {""," tysiac "," tysiace "," tysiace "," tysiace "," tysiecy "," tysiecy "," tysiecy "," tysiecy "," tysiecy "};
string teens[] = {""," jedenascie "," dwanascie "," trzynascie "," czternascie "," pietnascie "," szesnascie "," siedemnascie "," osiemnascie "," dziewietnascie "};
string ones[] = {""," jeden "," dwa "," trzy "," cztery "," piec "," szesc "," siedem "," osiem "," dziewiec "};
string tens[] = {""," dziesiec "," dwadziescia "," trzydziesci "," czterdziesci "," piecdziesiat "," szescdziesiat "," siedemdziesiat "," osiemdziesiat "," dziewiecdziesiat "};

// prototypes
void transform(int number);
bool isBinary(long long int number);
int binaryFactor(int arg);

int main(int argc, char **argv) {
	int c = atoi(argv[1]);
	while ((c<0) || (c>1000000)) {
		cout << "Liczba spoza zakresu. Sprobuj jeszcze raz." << endl;
		cin >> c;
	}
	cout << "Wybrana liczba to " << c << endl;
	transform(c);
	cout << "Jesli pomnozymy argument (czyli " << c << ") przez " << binaryFactor(c) << " otrzymamy najmniejsza liczbe skladajaca sie z zer i jedynek." << endl;
	if (binaryFactor(c)<1000001) {
		cout << binaryFactor(c) << " to inaczej " << endl;
		transform(binaryFactor(c));
	}
	else
	cout << "Niestety jest to liczba wieksza od miliona, wiec nie mozemy jej przedstawic jako polskiego liczebnika" << endl;
	cout << "Iloczyn tych dwoch liczb to " << (long long int)c*binaryFactor(c) << endl;
	if ((c*binaryFactor(c))<1000001) {
		cout << c*binaryFactor(c) << " to inaczej " << endl;
		transform(c*binaryFactor(c));
	}
	else
	cout << "Niestety jest to liczba wieksza od miliona, wiec nie mozemy jej przedstawic jako polskiego liczebnika." << endl;
}

// Number-to-text transforming function.
void transform(int numArg) {
	string result;
	if (numArg==1000000) {
		cout << "Jestes milionerem :) A liczba to oczywiscie milion." << endl;
	}
	else {
		// But what if it's not million?
		int numTab[6];
		for(int i=5;i>-1;i--) {
			if(numArg!=0) {
				numTab[i]=numArg%10;
			}
			else numTab[i]=0;
			numArg/=10;
		}
		// Main part.
		result += hundreds[numTab[0]];
		if (numTab[1]==1 && numTab[2]!=0) { // if first three digits are ending with 1*
			result += teens[numTab[2]] + thousands[9]; // any index in thousands array with "tysiecy".
		}
		else
		if (numTab[2]==0 && ((numTab[0]!=0) || (numTab[1]!=0))) {
			result += tens[numTab[1]] + ones[numTab[2]] + thousands[9];
		}
		else
		result += tens[numTab[1]] + ones[numTab[2]] + thousands[numTab[2]];
		// Thousands done.
		result += hundreds[numTab[3]];
		if (numTab[4]==1 && numTab[5]!=0) { // same as above, but group of three last digits.
			result += teens[numTab[5]];
		}
		else
		result += tens[numTab[4]] + ones[numTab[5]];
		cout << result << endl;
		// And... it's done!
	}
}

// Function determining if given number consists only of 1's and 0's.
bool isBinary(long long int number) {
	while(number > 0) {
		if (number%10 > 1) {
			return false;
		}
		else
		number/=10;
	}
	return true;
}


// Computing factor, which multiplied by program main argument gives binary number.
int binaryFactor (int arg) {
	long long int k;
	while (k>0) {
		if(isBinary(arg*k)) break;
		k++;
	}
	return k;
}

