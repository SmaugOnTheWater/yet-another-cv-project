//
// Created by andy on 10/7/17.
//

#include <regex>
#include <iostream>
#include "Classifier.h"

int sign_label_to_id(std::string label) {
    std::smatch m;
    std::regex e ("\\d+");   // matches words beginning by "sub"

    while (std::regex_search (label,m,e)) {
        for (auto x:m) std::cout << x << " ";
        std::cout << std::endl;
        label = m.suffix().str();
    }
}



Classifier::Classifier(const std::string &filename) {
    train_data = parseCSV(filename);
}

void Classifier::learn(int iterations_num) {
    for (int i = 0; i < iterations_num; i++) {

    }
}