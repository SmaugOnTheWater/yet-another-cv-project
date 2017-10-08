//
// Created by andy on 10/7/17.
//

#include <regex>
#include <iostream>
#include <unordered_set>
#include <opencv2/imgproc.hpp>
#include <opencv/cv.hpp>
#include <opencv/highgui.h>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include "Classifier.h"

#include <CGAL/Cartesian.h>
#include <CGAL/MP_Float.h>
#include <CGAL/Quotient.h>
#include <CGAL/Arr_segment_traits_2.h>
#include <CGAL/Arrangement_2.h>
#include <opencv2/xfeatures2d/nonfree.hpp>

typedef CGAL::Quotient<CGAL::MP_Float> Number_type;
typedef CGAL::Cartesian<Number_type> Kernel;
typedef CGAL::Arr_segment_traits_2<Kernel> Traits_2;
typedef Traits_2::Point_2 Point_2;
typedef Traits_2::Vector_2 Vector_2;
typedef Traits_2::Direction_2 Direction_2;
typedef Traits_2::X_monotone_curve_2 Segment_2;
typedef CGAL::Arrangement_2<Traits_2> Arrangement_2;

namespace fs = boost::filesystem;


Detector::Detector(const std::string &xml) {
    cc.load(xml);

    for(auto& entry : boost::make_iterator_range(fs::directory_iterator(fs::path("../resources/signs")), {})) {
        cv::Mat m = cv::imread(entry.path().string());
        cv::resize(m, m, {50, 50});
        references.insert({entry.path().stem().string(), m});
    }
}


std::vector<SignData> Detector::find_signs(const cv::Mat &img) {
    std::vector<cv::Rect> bboxes;
    cc.detectMultiScale(img, bboxes,  1.1, 3, 0, {20, 20}, {60, 60});

    cv::Ptr<cv::xfeatures2d::SIFT> sift = cv::xfeatures2d::SIFT::create();

    std::vector<SignData> result;
    for (cv::Rect &bb: bboxes) {
        std::vector<cv::KeyPoint> keypoints1, keypoints2;
        std::string best_sign;
        float best_dist = 1e30;
        cv::Mat descriptors_2;
        sift->detectAndCompute(img(bb), {}, keypoints2, descriptors_2);

        if (keypoints2.size() < 3) continue;
        for (auto &r: references) {
            cv::Mat descriptors_1;
            sift->detectAndCompute(r.second, {}, keypoints1, descriptors_1);


            cv::FlannBasedMatcher matcher;
            std::vector< cv::DMatch > matches;
            matcher.match( descriptors_1, descriptors_2, matches );

            matches.erase(std::remove_if(matches.begin(), matches.end(), [](const cv::DMatch &d)
            {return d.distance > 350; }), matches.end());
            if (matches.size() < 5) continue;

            float dist = std::accumulate(matches.begin(), matches.end(), 0.0f, [](float dist, cv::DMatch &m){
                return dist + m.distance;
            });

            if (best_dist > dist) {
                best_dist = dist;
                best_sign = r.first;
            }
        }

        if (!best_sign.empty()) {
            result.push_back({bb, best_sign, ""});
        }
    }
    return result;
}

