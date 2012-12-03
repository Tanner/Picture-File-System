
#ifndef UTIL_H_
#define UTIL_H_

#include "regex_matcher.h"

namespace pfs {
    using namespace std;

    string root_for_path(string path) {
        RegexMatcher directory_regex("/([A-Za-z0-9.-_]+)");
        vector<string> matches(directory_regex.find_matches(path));
        if (matches.size() >= 2) {
            return matches[1];
        }

        return "";
    }

    string name_for_path(string path) {
        RegexMatcher directory_regex("/([A-Za-z0-9]+)/?$");
        vector<string> matches(directory_regex.find_matches(path));
        if (matches.size() >= 2) {
            return matches[1];
        }

        return "";
    }
    
}

#endif
