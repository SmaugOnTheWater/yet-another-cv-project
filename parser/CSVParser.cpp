#include <iostream>
#include <fstream>
#include <cstdlib>
#include "CSVParser.h"

using namespace std;

map<string, vector<BoundingBox> > parseCSV(string path)
{
	ifstream input(path.c_str());
	string line;
	map<string, vector<BoundingBox> > result;

	getline(input, line);
	while (getline(input, line, ','))
	{
		vector<BoundingBox> &list = result[line];
		BoundingBox box;

		getline(input, line, ',');
		box.x = atoi(line.c_str());

		getline(input, line, ',');
		box.y = atoi(line.c_str());

		getline(input, line, ',');
		box.width = atoi(line.c_str());

		getline(input, line, ',');
		box.height = atoi(line.c_str());

		getline(input, line);
		box.sign_class = line;

		list.push_back(box);
	}

	return result;
}
