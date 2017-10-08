//
// Created by andy on 10/7/17.
//

#ifndef CLASSIFIER_CLASSIFIER_H
#define CLASSIFIER_CLASSIFIER_H

#include <string>
#include <opencv2/core/mat.hpp>
#include <unordered_map>
#include <opencv/cv.hpp>
#include "CSVParser.h"

struct SignData {
    cv::Rect bbox;
    std::string label;
    std::string additional_info;
};

class Detector {
public:
    Detector(const std::string &xml);
    std::vector<SignData> find_signs(const cv::Mat &img);
    void find_sift(const cv::Mat &img);
private:
    cv::CascadeClassifier cc;
    std::unordered_map<std::string, cv::Mat> references;
};




#endif //CLASSIFIER_CLASSIFIER_H
