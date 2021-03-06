// SortedDriver.cpp
// Sidney Jensen
//11/10/18

// tom bailey   1445  25 mar 2014
// Construct sorted sequences and call functions that
//   process the sorted sequences.

#include "stdafx.h"
#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"//CHANGE: this to unixTimer.h if on mac/linux
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre:  number is not empty;
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double
mostIsolated(vector<double> & number)
{
	double greatestDif = 0, isolated = 0;
	for (int i = 1; i < (number.size()-1); i++)
	{
		double bDif = abs(number.at(i - 1) - number.at(i));
		double fDif = abs(number.at(i) - number.at(i + 1));
		double diff = 0;
		if (bDif > fDif)
		{
			diff = fDif;
		}
		if (bDif < fDif)
		{
			diff = bDif;
		}
		if (diff > greatestDif)
		{
			greatestDif = diff;
			isolated = number.at(i);
		}
	}
	double begining = abs(number.at(0) - number.at(1));
	if (begining > greatestDif)
	{
		greatestDif = begining;
		isolated = number.at(0);
	}
	return isolated;
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int
unmatched(list<string> & A, list<string> & B)
{
	int wordCount = 0;

	// attempt to make a faster function, so it would work for big values. Does not work.
	//std::list<string>::iterator it;
	//string a = A.front();
	//for (it = A.begin(); it != A.end(); it++)
	//{
	//	if (A.end() == it)
	//	{
	//		wordCount = wordCount + B.size();
	//	}
	//	if (B.empty())
	//	{
	//		wordCount = wordCount + A.size();
	//	}
	//	if (*it < B.front())
	//	{
	//		wordCount++;
	//		B.pop_front();
	//	}
	//	else if (*it == B.front())
	//	{
	//		wordCount++;
	//		A.pop_front();
	//		B.pop_front();
	//	}
	//	else
	//	{
	//		B.pop_front();
	//	}

	//}
	// Works for small values, but not for the big values.
	bool end = false;
	while (end == false)
	{
		if (A.empty())
		{
			wordCount = wordCount + B.size();
			end = true;
		}
		if (B.empty())
		{
			wordCount = wordCount + A.size();
			end = true;
		}

		if (!end) {
			string a = A.front();
			string b = B.front();
			if (a < b)
			{
				A.pop_front();
			}
			else if (a == b)
			{
				wordCount++;
				A.pop_front();
				B.pop_front();
			}
			else
			{
				B.pop_front();
			}
		}
	}
	return wordCount;
}


int
main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}
