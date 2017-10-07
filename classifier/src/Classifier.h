//
// Created by andy on 10/7/17.
//

#ifndef CLASSIFIER_CLASSIFIER_H
#define CLASSIFIER_CLASSIFIER_H

#include <string>
#include "CSVParser.h"

int sign_label_to_id(std::string label);
std::string sign_id_to_string(int id);

struct Sign {
    int id;

};

class Classifier {
public:
    Classifier(const std::string &filename);
    void learn(int iterations_num);

private:
    std::map<std::string, std::vector<BoundingBox> > train_data;
};


#endif //CLASSIFIER_CLASSIFIER_H
