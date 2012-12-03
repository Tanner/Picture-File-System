
#include <sstream>

#include "util.h"

using namespace pfs;
using namespace std;

string pfs::root_for_path(string path) {
    RegexMatcher directory_regex("/([A-Za-z0-9.-_]+)");
    vector<string> matches(directory_regex.find_matches(path));
    if (matches.size() >= 2) {
        return matches[1];
    }

    return "";
}

string pfs::name_for_path(string path) {
    RegexMatcher directory_regex("/([A-Za-z0-9]+)/?$");
    vector<string> matches(directory_regex.find_matches(path));
    if (matches.size() >= 2) {
        return matches[1];
    }

    return "";
}

string pfs::int_to_str(int i) {
    stringstream ss;
    ss << i;
    return ss.str();
}
