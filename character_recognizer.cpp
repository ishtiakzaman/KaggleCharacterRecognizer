/*
To partition train and validation set
g++ character_recognizer.cpp -o cr
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

int main(int argc, char *argv[])
{	
	srand (time(NULL));

	if ( strcmp(argv[1], "train") == 0)
	{
		int n_validation = 1250, validation_index = 0;
		string line;		
		int id, target, count = 0;
		char c;
		ofstream ofs_train("train.txt");
		ofstream ofs_validation("validation.txt");
		ifstream ifs("trainLabels.csv");
		getline(ifs, line); // skip first header line
		while (ifs.eof() == false)
		{
			getline(ifs, line);
			if (line.length() < 2) continue;			
			sscanf(line.c_str(), "%d,%c", &id, &c);
			if (c <= '9')
				target = c - '0';
			else if (c <= 'Z')
				target = 10 + c - 'A';
			else
				target = 36 + c - 'a';
			//cout << id << " " << target << endl;

			int rnd = rand() % 4;
			if (rnd == 0 && validation_index < n_validation)
			{
				ofs_validation << id << ".Bmp " << target << endl;
				ostringstream oss;
				oss << "mv resized_train/" << id << ".Bmp validation/" << id << ".Bmp";
				system((oss.str()).c_str());
				++validation_index;
			}
			else
			{
				ofs_train << id << ".Bmp " << target << endl;
				ostringstream oss;
				oss << "mv resized_train/" << id << ".Bmp train/" << id << ".Bmp";
				system((oss.str()).c_str());				
			}

			count++;
			if (count % 500 == 0)
			{
				cout << count << " images processed." << endl;
			}
		}
		cout << count << endl;
	}
}