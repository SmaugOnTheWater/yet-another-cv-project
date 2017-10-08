//
// Created by andy on 10/8/17.
//

#ifndef FUCKCV_UTIL_H
#define FUCKCV_UTIL_H

#include <vector>
#include <string>
#include <stdexcept>

void prepare_dataset(const std::vector<std::string> &filenames);

inline std::string get_dataset_dir() {
    const char * dsdir = getenv("DATASET_DIR");

    if (dsdir == nullptr) {
        throw std::logic_error("Environment variable DATASET_DIR is not set!");
    }

    return dsdir;
}

inline std::string get_test_images_dir() {
    return get_dataset_dir() + "/rtsd-d1-frames/test/";
}

inline std::string get_train_images_dir() {
    return get_dataset_dir() + "/rtsd-d1-frames/train/";
}

int sign_label_to_id(std::string label);
std::string sign_id_to_string(int id);

#endif //FUCKCV_UTIL_H
