// Dang, Charles        CS546 Section 3122  Date completed
// Fourth Laboratory Assignment ÅECache Simulation

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <bitset>
using namespace std;

bool validatePrimaryValues(int a, int b, int c, int d);
bool isPowerOfTwo(int primaryValue);
int getPoweOfTwoOf(int num);
void getNextCommand(ifstream & inData, char & nextLetter, int & inputAddress, int & inputValue);
unsigned int countSetBits(unsigned int n);
bool isValid(vector<bool> validTable, int cacheLine);
void getBitsFromAddress(int & bitHolder, int & bitFinder, int bitLimit, int inputAddress);
void setDataInCacheAndMemory(vector<bool> validTable, vector<bool> dirtyTable, vector<int> tagTable, vector<int> dataTable, vector<int> memory, int associativityCache, int segment, int lineNumbers);
void outputValidTable(vector<bool> validTable, int lineNumbers, int associativityCache);

int main()
{
	ifstream inData;
	inData.open("input.txt");

	if (!inData)
	{
		cout << "Error in opening input file." << endl;
		system("pause");
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
			system("pause");
			exit(EXIT_FAILURE);
		}
		}

		varCheck++;
	}

	if (!validatePrimaryValues(lineSizeCache, totalSizeCache, associativityCache, totalSizeMemory))
	{
		cout << "Error in the four primary values. Exiting program." << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}

	int lineNumbers = totalSizeCache / lineSizeCache;
	
	vector<bool> validTable(lineNumbers, 0);
	vector<bool> dirtyTable(lineNumbers, 0);
	vector<int> tagTable(lineNumbers, 0);
	vector<int> dataTable(lineNumbers, 0);
	vector<int> memory(totalSizeMemory, 0);

	int associativityOffset = lineNumbers / associativityCache;
	int offSetBits = getPoweOfTwoOf(lineSizeCache);
	int cacheLineBits = getPoweOfTwoOf(lineNumbers / associativityCache);

	char charCode = 'a';
	int inputAddress = 0;
	int inputValue;
	getNextCommand(inData, charCode, inputAddress, inputValue);
	if (charCode == 'E')
	{
		int bitFinder = 1;
		//inputAddress = 0x1008;//
		int offset = inputAddress & bitFinder;
		getBitsFromAddress(offset, bitFinder, offSetBits, inputAddress);
		/*for (int i = 0; i < offSetBits; i++)
		{
			offset = offset | (bitFinder & inputAddress);
			bitFinder = bitFinder << 1;
		}*/
		/*offset = 0x3274 & 15;*/
		/*cout << bitset<16>(offset) << endl;*/
		/*bitFinder = bitFinder << 1;*/
		int segment = inputAddress & bitFinder;
		getBitsFromAddress(segment, bitFinder, cacheLineBits, inputAddress);
		/*for (int i = 0; i < cacheLineBits; i++)
		{
			segment = segment | (bitFinder & inputAddress);
			bitFinder = bitFinder << 1;
		}*/

		/*cout << bitset<16>(segment) << endl;*/
		int tag = inputAddress & bitFinder;
		int tagBitsCount = 20;//20 should be substituted
		getBitsFromAddress(tag, bitFinder, tagBitsCount, inputAddress);
		/*for (int i = 0; i < tagBitsCount; i++)
		{
			tag = tag | (bitFinder & inputAddress);
			bitFinder = bitFinder << 1;
		}*/
		int mainMemoryAddress = tag | segment;
		segment = segment >> offSetBits;
		tag = tag >> (offSetBits + cacheLineBits);
		//cout << bitset<16>(inputAddress) << " : "  << inputAddress << endl;//
	
		bool writeSuccessful = true;
		for (int i = 0; i < associativityCache; i++)
		{
			int trueCacheLine = segment + (lineNumbers / associativityCache) * i;
			if (!isValid(validTable, trueCacheLine))// errorCheck segment value
			{
				dataTable[trueCacheLine] = inputValue;
				tagTable[trueCacheLine] = tag;
				validTable[trueCacheLine] = true;
				dirtyTable[trueCacheLine] = true;
				break;
			}
			else if (i == associativityCache - 1 && isValid(validTable, trueCacheLine))
			{
				writeSuccessful = false;
			}
		}

		if (!writeSuccessful)
		{
			memory[mainMemoryAddress] = dataTable[segment];
			tagTable[segment] = tag;
			dataTable[segment] = inputValue;
		}
		cout << "Data: " << dataTable[segment] << endl;
		/*outputValidTable(validTable, lineNumbers, associativityCache);*/
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
	return (primaryValue & (primaryValue - 1)) == 0;
}

int getPoweOfTwoOf(int num)
{
	return logb(num);
}

void getNextCommand(ifstream & inData, char & nextLetter, int & inputAddress, int & inputValue)
{
	inData >> nextLetter;
	inData.ignore();
	if (nextLetter == 'E')
	{
		char writeChar = 'e';
		inData >> hex >> inputAddress;
		inData.ignore();
		inData >> writeChar;
		inData.ignore();
		inData >> dec >> inputValue;
		inData.ignore();
	}
	else if (nextLetter == 'F')
	{

	}
}

unsigned int countSetBits(unsigned int n)
{
	unsigned int count = 0;
	while (n)
	{
		count += n & 1;
		n >>= 1;
	}
	return count;
}

bool isValid(vector<bool> validTable, int cacheLine)
{
	return validTable[cacheLine] == 1;
}

void getBitsFromAddress(int & bitHolder, int & bitFinder, int bitLimit, int inputAddress)
{
	for (int i = 0; i < bitLimit; i++)
	{
		bitHolder = bitHolder | (bitFinder & inputAddress);
		bitFinder = bitFinder << 1;
	}
}

void setDataInCacheAndMemory(vector<bool> validTable, vector<bool> dirtyTable, vector<int> tagTable, vector<int> dataTable, vector<int> memory, int associativityCache, int segment, int lineNumbers)
{

}

void outputValidTable(vector<bool> validTable, int lineNumbers, int associativityCache)
{
	cout << "Valid Table:" << endl;
	for (int i = 0; i < lineNumbers; i++)
	{
		if (i == lineNumbers / associativityCache)
		{
			cout << endl << "Associativty Starts Here: " << endl;
		}
		cout << validTable[i] << " ";
	}
}