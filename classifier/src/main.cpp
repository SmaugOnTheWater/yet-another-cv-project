#include <iostream>
#include <boost/filesystem.hpp>
#include <opencv2/imgcodecs.hpp>
#include "Classifier.h"


namespace fs = boost::filesystem;
/**
 * @function main
 * @brief Main function
 */
int main( int argc, char** argv ) {
    if (argc < 2) {
        std::cout << "Usage: ./detect <image>" << std::endl;
        return 0;
    }

    Detector detector("../resources/cascade.xml");

    cv::Mat img = cv::imread(argv[1]);
    if (img.empty()) {
        std::cout << "Image couldn't be read" << std::endl;
        return 0;
    }
    auto res = detector.find_signs(img);
    for (auto &v: res) {
        std::cout << v.label << " found in " << v.bbox << std::endl;
        cv::rectangle(img, v.bbox, {0,0,255}, 2);
    }

    cv::imshow("signs", img);
    cv::waitKey();
    return 0;
}
