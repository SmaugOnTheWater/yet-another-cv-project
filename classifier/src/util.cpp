//
// Created by andy on 10/8/17.
//

#include <unordered_set>
#include <boost/filesystem.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv/cv.hpp>
#include "util.h"
#include "../../parser/CSVParser.h"
#include <opencv/cv.h>
#include <regex>

namespace fs = boost::filesystem;

// Это для обучения Хаара
// Надо убрать в питон
void prepare_dataset(const std::vector<std::string> &filenames) {
    std::map<std::string, std::vector<BoundingBox> > train_data;
    for (const std::string &filename: filenames) {
        auto res = parseCSV(filename);
        train_data.insert(res.begin(), res.end());
    }

    std::unordered_set<int> unique_ids;
    fs::path cropped = fs::path(get_dataset_dir()) / "cropped_train";
    fs::path negative = fs::path(get_dataset_dir()) / "negative";
    fs::create_directories(cropped);
    fs::create_directories(negative);
    int counter_positive = 0;
    int counter_negative = 0;
    for (auto &v: train_data) {
        cv::Mat img = cv::imread(get_train_images_dir() + "/" + v.first);
        cv::Mat neg = img.clone();
        for (auto &b: v.second) {
            unique_ids.insert(sign_label_to_id(b.sign_class));
            cv::Mat bb = img(cv::Rect(b.x, b.y, b.width, b.height));
            neg(cv::Rect(0,0,b.width, b.height)).copyTo(neg(cv::Rect(b.x, b.y, b.width, b.height)));
            cv::imwrite((cropped / fs::path(std::to_string(counter_positive) + ".jpg")).string(), bb);
            counter_positive++;
        }
        cv::imwrite((negative / fs::path(std::to_string(counter_negative) + ".jpg")).string(), neg);
        counter_negative++;
    }
}

int sign_label_to_id(std::string label) {
    std::smatch m;
    std::regex e ("\\d+");   // matches words beginning by "sub"

    int id = 0;
    while (std::regex_search (label,m,e)) {
        //  for (auto x:m) std::cout << x << " ";
        //  std::cout << std::endl;

        id = (id << 8) + std::stoi(m[0]);
        label = m.suffix().str();
    }

    return id;
}