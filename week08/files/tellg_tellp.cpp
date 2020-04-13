//C++ program to demonstrate example of tellg() and tellp() function.

#include <iostream>
#include <fstream>

// get / put stream positioning
// ifstream / istream -> get
// ofstream / ostream -> put
// fstream -> get & put

// tellg -> where is get position in the file | tellp -> where is put position in file
// seekg -> move get position in the file | seekp -> move put position in file

// seekg(<position>);
// seekp(<position>);

// seekg(offset, direction)
// seekp(offset, direction)

// offset
// literal -> 0, 1, 2 ...
// std::ios::beg -> 0 / std::ios::end -> end of file / std::ios::cur -> current position

// seekg(0, ios::end);

// ofstream -> write(<memory_block>, <size>);
// out.write (array, 10);

// ifstream -> read(<memory_block>, <size>);
// in.read (array, 10);

using namespace std;

int main()
{
	fstream file;
	//open file sample.txt in and Write mode
	file.open("sample.txt", ios::out);
	if (!file)
	{
		cout << "Error in creating file!!!";
		return 0;
	}

	//write A to Z
	file << "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	//print the position
	cout << "Current position is: " << file.tellp() << endl;
	file.close();

	//again open file in read mode
	file.open("sample.txt", ios::in);
	if (!file)
	{
		cout << "Error in opening file!!!";
		return 0;
	}
	cout << "After opening file position is: " << file.tellg() << endl;

	//read characters untill end of file is not found
	char ch;
	while (!file.eof())
	{
		cout << "At position : " << file.tellg();   //current position
		file >> ch;   //read character from file
		cout << " Character \"" << ch << "\"" << endl;
	}

	//close the file
	file.close();

	// Size of file: 1
	//ifstream file("sample.txt", ios::binary | ios::ate);
	//int sizeOfFile = file.tellg();

	// Size of file: 2
	//int beg, end;
	//ifstream file("sample.txt");
	//beg = file.tellg();
	//file.seekg(0, ios::end);
	//end = file.tellg();
	//int size = end - beg;

	system("pause");
	return 0;
}