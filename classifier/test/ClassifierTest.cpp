//
// Created by andy on 10/7/17.
//

#include <gtest/gtest.h>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv/cv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include "../src/Classifier.h"
#include "../src/util.h"

using namespace std;

namespace
{
    TEST(classifier, aplusb) {
        ASSERT_EQ(1 + 1, 2);
    }

    TEST(detector, preparedataset) {

        std::vector<std::string> train = {get_dataset_dir() + "/rtsd-d1-gt/prohibitory/train_gt.csv",
                                          get_dataset_dir() + "/rtsd-d1-gt/mandatory/train_gt.csv",
                                          get_dataset_dir() + "/rtsd-d1-gt/danger/train_gt.csv"};
        prepare_dataset(train);
    }

    TEST(detector, detect1) {
        Detector d("/home/andy/hackcv/opencv-haar-classifier-training/classifier/cascade.xml");

        cv::Mat img = cv::imread(get_test_images_dir() + "/autosave21_01_2013_13_53_12_2.jpg");
        auto bbs = d.find_signs(img);
        cv::Mat hsv_img;
        cv::cvtColor(img, hsv_img, cv::COLOR_BGR2HSV);
        cv::Mat lab_img;
        cv::cvtColor(img, lab_img, cv::COLOR_BGR2Lab);

        cv::Ptr<cv::xfeatures2d::SIFT> star = cv::xfeatures2d::SIFT::create();

        cv::Mat reference = cv::imread("/home/andy/hackcv/yet-another-cv-project/custom/pesheh_perehod.jpg");
    cv::resize(reference, reference, {50, 50});
        std::vector<cv::KeyPoint> keypoints1, keypoints2;
        cv::Mat descriptors_1, descriptors_2;
        star->detectAndCompute(reference, {}, keypoints1, descriptors_1);


    }


}