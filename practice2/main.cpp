#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <vector>
#include "queue.h"
#include "stack.h"
#include "SortedList.h"
#include "functions.h"

using namespace std;

int main()
{
	
	#define HELP "Usage: $ palindrome [parameter]\nWhere: parameter is one of:\n\t\t-h (help)\n\t\t-k (read from keyboard)\n\t\t-f file (read from file)\n\t\t-d letter (remove all palindromes which start by this letter)\n\t\t-s (show data)\n\t\t-q (exit)\n";
	
	string input ("\0");
	string original ("\0");
	string command;

	SortedList list;

	//always print the help at the begin
	cout << HELP;	

	do
	{
		//print a new prompt until -q
		cout << "$ palindrome ";

		//read command
		getline(cin, command, '\n');

		//create our own argv
		vector<string> myArgv;
		istringstream iss(command);
		string token;
		while(getline(iss, token, ' '))
		{
			myArgv.push_back(token);
		} 

		//create our own argc
		int myArgc = myArgv.size();

		//main method
		if (myArgc == 1)
		{
			if (myArgv[0] == "-h")
			{
				cout << HELP;
			}
			else if (myArgv[0] == "-s")
			{
				//show in the screen the number of queues in the list, the total number of palindromes in each queue and their starting letter
				cout << list.toString() << endl;
			}
			else if (myArgv[0] == "-k")
			{
				int i = 0;

				cout << "(-q to exit)" << endl;

				do
				{
					cout << "(" << i << ") "; i++;
					getline(cin, original, '\n');
					input = rmSpace(original);

					if (isPalindrome(input))
					{
						//insert original in the list
						list.insert(original);
						cout << "Palindrome inserted!" << endl;
					}
					else
						if (original!="-q")
							cout << "This is not palindrome, then not inserted!" << endl;
				} 
				while(original!="-q");
			}
			else
			{
				if (myArgv[0] != "-q")
				{
					cout << "Paremeter unknown " << myArgv[0] << endl;
				}
			}
		}
		else if (myArgc == 2)
		{
			if (myArgv[0] == "-f")
			{
				int cont0 = 0, cont1 = 0;

				ifstream inputFile (myArgv[1]);
				if(inputFile.is_open())
				{
					string tmp;
					while(getline(inputFile, tmp))
					{
						input = rmSpace(tmp);
						if (isPalindrome(input))
						{
							//insert tmp in the list
							list.insert(tmp);
							cont1++;
						}
						else
							cont0++;
					}
					cout << cont1 << " palindromes inserted." << endl;
					cout << cont0 << " sentences that are not palindrome, not inserted." << endl;
				}	
				else
				{
					//filename does not exists
					cout << "The file couldn't be opened, maybe doesn't exists :(\n";
				}
			}
			else if (myArgv[0] == "-d")
			{
				//delete the node of the leter passed in parameter
				if (myArgv[1].length() == 1)
					if(list.remove(myArgv[1].front()))
						cout << "Removed!" << endl;
					else
						cout<< "Node does not exists!" << endl;
				else
					cout << "just one char pleaaaaaase :)" << endl;
			}
			else
			{
				cout << "Paremeter unknown " << myArgv[0] << endl;
			}
		}
		else if (myArgc > 2)
		{
			cout << "There's way too much arguments :')\n";
		}
	}
	while(command != "-q");
}