
#ifndef UTIL_H_
#define UTIL_H_

#include "regex_matcher.h"

namespace pfs {
    using namespace std;

    string root_for_path(string path);
    string deeper_path(string path);
    int path_depth(string path);
    string int_to_str(int i);
    string month_to_str(int month);
}

#endif
