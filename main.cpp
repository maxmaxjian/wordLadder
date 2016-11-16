#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <iterator>
#include <algorithm>

class solution {
  public:
    std::vector<std::vector<std::string>> findLadders(const std::string & beginWord, const std::string & endWord, const std::unordered_set<std::string> & wordList) {
        std::vector<std::vector<std::string>> paths = getLadders(wordList, std::vector<std::string>{beginWord}, endWord);
        for (auto & path : paths) {
            std::copy(path.begin(), path.end(), std::ostream_iterator<std::string>(std::cout, " "));
            std::cout << std::endl;
        }
        return paths;
    }

  private:
    std::vector<std::vector<std::string>> getLadders(const std::unordered_set<std::string> & wordlist, const std::vector<std::string> & curr, const std::string & end) {
        std::vector<std::vector<std::string>> result;
        if (diffInOneLetter(curr.back(), end)) {
            auto cpy = curr;
            cpy.push_back(end);
            result.push_back(cpy);
        }
        else {
            std::vector<std::string> next;
            std::copy_if(wordlist.begin(), wordlist.end(), std::inserter(next, next.begin()),
                         [&](const std::string & s){
                             return diffInOneLetter(curr.back(),s);
                         });
            for (auto nx : next) {
                auto set_cpy = wordlist;
                set_cpy.erase(nx);
                auto cpy = curr;
                cpy.push_back(nx);
                auto temp = getLadders(set_cpy, cpy, end);
                std::copy(temp.begin(), temp.end(), std::inserter(result, result.end()));
            }
        }
        return result;
    }

    bool diffInOneLetter(const std::string & s1, const std::string & s2) {
        if (s1.size() != s2.size())
            return false;
        else {
            auto it = std::mismatch(s1.begin(), s1.end(), s2.begin());
            if (it.first == s1.end())
                return false;
            else {
                auto first = it.first, second = it.second;
                ++first;
                ++second;
                auto jt = std::mismatch(first, s1.end(), second);
                if (jt.first == s1.end())
                    return true;
            }
        }
        return false;
    }
};

int main() {
    std::string beginWord{"hit"}, endWord{"cog"};
    std::unordered_set<std::string> wordlist{"hot","dot","dog","lot","log"};

    solution soln;
    auto paths = soln.findLadders(beginWord, endWord, wordlist);
}
