#include "CSVParser.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	if (argc == 2)
	{
		map<string, vector<BoundingBox> > dataset = parseCSV(argv[1]);
		for (map<string, vector<BoundingBox> >::iterator i = dataset.begin(); i != dataset.end(); ++i)
		{
			cout << "File " << i->first << endl;

			vector<BoundingBox> &list = i->second;
			for (vector<BoundingBox>::iterator j = list.begin(); j != list.end(); ++j)
			{
				cout << "\t" <<
					"x: " << j->x << ", " <<
					"y: " << j->y << ", " <<
					"width: " << j->width << ", " <<
					"height: " << j->height << ", " <<
					"class: " << j->sign_class << endl;
			}
		}
	}
	return 0;
}
