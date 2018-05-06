// Dang, Charles        CS546 Section 3122  Date completed
// Fourth Laboratory Assignment – Cache Simulation

#include <iostream>
#include <fstream>
using namespace std;

bool validatePrimaryValues(int a, int b, int c, int d);
bool isPowerOfTwo(int primaryValue);

int main()
{
	ifstream inData;
	inData.open("input.txt");

	if (!inData)
	{
		cout << "Error in opening input file." << endl;
		exit(EXIT_FAILURE);
	}

	int lineSizeCache = 0;
	int totalSizeCache = 0;
	int associativityCache = 0;
	int totalSizeMemory = 0;
	int varCheck = 0;

	while (!inData.eof() && varCheck < 4)
	{
		char primaryChar;
		int pvalue;
		inData >> primaryChar;
		inData.ignore();
		inData >> pvalue;
		inData.ignore();
		switch (primaryChar)
		{
		case 'A': lineSizeCache = pvalue;
			break;
		case 'B': totalSizeCache = pvalue;
			break;
		case 'C': associativityCache = pvalue;
			break;
		case 'D': totalSizeMemory = pvalue;
			break;
		default:
		{
			cout << "Error in obtaining the primary values. Exiting program." << endl;
			exit(EXIT_FAILURE);
		}
		}

		varCheck++;
	}

	if (!validatePrimaryValues(lineSizeCache, totalSizeCache, associativityCache, totalSizeMemory))
	{
		cout << "Error in the four primary values. Exiting program." << endl;
		exit(EXIT_FAILURE);
	}


	inData.close();
	system("pause");
	return 0;
}

bool validatePrimaryValues(int a, int b, int c, int d)
{
	if (a <= 0 || b <= 0 || c <= 0 || d <= 0)
		return false;
	if (!(isPowerOfTwo(a) && isPowerOfTwo(b) && isPowerOfTwo(c) && isPowerOfTwo(d)))
		return false;
	if ((double)a > b * 0.1)
		return false;
	if ((double)b > d * 0.1)
		return false;

}

bool isPowerOfTwo(int primaryValue)
{
	return primaryValue & (primaryValue - 1) == 0;
}