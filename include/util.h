
#ifndef UTIL_H_
#define UTIL_H_

#include "regex_matcher.h"

namespace pfs {
    using namespace std;

    string root_for_path(string path);
    string filename_for_path(string path);
    string extension_for_path(string path);
    string deeper_path(string path);
    int path_depth(string path);
    string int_to_str(int i);
    string month_to_str(int month);
    bool is_image_path(string path);
    bool is_file_private(string filename);
}

#endif
