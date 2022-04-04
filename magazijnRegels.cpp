#ifndef MAGAZIJNREGEL
#define MAGAZIJNREGEL

#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <map>
#include <unistd.h>

class magazijnRegels {
    private:

        typedef std::map<int, std::vector<int>> aangrenzendeLocaties;
        aangrenzendeLocaties _tegels;

    
    public:
        magazijnRegels() {
            std::cout << "[CONSTRUCTED][magazijnHerindeler]\n";
            _tegels.insert(std::make_pair(0, std::vector<int>{1,3}));
            _tegels.insert(std::make_pair(1, std::vector<int>{0,2,4}));
            _tegels.insert(std::make_pair(2, std::vector<int>{1,5}));
            _tegels.insert(std::make_pair(3, std::vector<int>{4,0,6}));
            _tegels.insert(std::make_pair(4, std::vector<int>{3,5,1,7}));
            _tegels.insert(std::make_pair(5, std::vector<int>{4,2,8}));
            _tegels.insert(std::make_pair(6, std::vector<int>{7,3}));
            _tegels.insert(std::make_pair(7, std::vector<int>{6,8,4}));
            _tegels.insert(std::make_pair(8, std::vector<int>{7,5}));
        }

        int uiteindelijkeContainerLocaties[9] = {1,2,3,4,5,6,7,8,0};

        const std::vector<int>& haalAangrenzendOp(int id) const {
            aangrenzendeLocaties::const_iterator itr(_tegels.find(id));
            if (itr != _tegels.end()) return itr->second;
            static std::vector<int> s;
            return s;
        }
};

#endif