
#ifndef REGEX_MATCHER_H_
#define REGEX_MATCH_ERH_

#include <string>
#include <vector>

#include <regex.h>

namespace pfs {
    using namespace std;

    /**
     * Finds matches of a regular expression (extended POSIX format) in input strings.
     */
    class RegexMatcher {
    public:
        /**
         * Creates a RegexMatcher with an extended POSIX regular expression string.
         */
        RegexMatcher(string pattern);

        /**
         * Cleans up resources.
         */
        ~RegexMatcher();

        /**
         * Executes the regular expression on an input string and returns the matching groups
         * as a vector of strings.
         * @param input    the input string
         * @param max_matches    the maximum number of matches returned
         */
        vector<string> find_matches(string input, unsigned int max_matches=32);
    private:
        /**
         * The POSIX data structure for the constructed POSIX regular expression.
         */
        regex_t c_regex_;
    };
}

#endif

