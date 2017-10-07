#ifndef CSV_PARSER_H_INCLUDED
#define CSV_PARSER_H_INCLUDED

#include <map>
#include <vector>
#include <string>

struct BoundingBox
{
	unsigned x;
	unsigned y;
	unsigned width;
	unsigned height;
	std::string sign_class;
};

std::map<std::string, std::vector<BoundingBox> > parseCSV(std::string path);

#endif
