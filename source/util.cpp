
#include <sstream>

#include "util.h"

#include <iostream>

using namespace pfs;
using namespace std;

string pfs::root_for_path(string path) {
    if (path.length() == 1 && path[0] == '/') {
        return "";
    }

    auto second_forward_slash = -1;
    for (unsigned int i = 1; i < path.length(); ++i) {
        if (path[i] == '/') {
            second_forward_slash = i;
            break;
        }
    }

    if (second_forward_slash < 0) {
        return path.substr(1, path.length());
    } else {
        return path.substr(1, second_forward_slash - 1);
    }
}

string pfs::deeper_path(string path) {
    string root = pfs::root_for_path(path);

    return path.substr(root.length() + 1, path.length());
}

int pfs::path_depth(string path) {
    int depth = 0;

    for (unsigned int i = 0; i < path.length(); ++i) {
        if (path[i] == '/') {
            ++depth;
        }
    }

    return depth - 1;
}

string pfs::int_to_str(int i) {
    stringstream ss;
    ss << i;
    return ss.str();
}
