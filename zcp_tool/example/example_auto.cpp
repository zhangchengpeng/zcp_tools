#include <iostream>
#include <map>
#include <typeinfo>
#include <vector>
#include "zcp_tool/comm/printf_utils.h"
using namespace std;

template <typename T>
void print_vector(T& t) {
    for (auto it = t.begin(); it < t.end(); it++) {
        cout << *it << endl;
    }
}

template <typename T>
void print_map(T& t) {
    for (auto it = t.begin(); it != t.end(); it++) {
        cout << it->first << ":" << it->second << endl;
    }
}

/*
map<string, string> record;
map<string, string>::iterator it;
PRINTF_MAP(record, it);

template <typename T1, typename T2, typename T3>
void PRINTF_MAP(map<T1, T2> &record, T3 &it) {
        it = record.begin();
        while (it != record.end()) {
                cout << it->first << ":" << it->second << endl;
                it++;
        }
}
*/

int main(int argc, char* argv[]) {
    int i;
    decltype(i) j         = 10;
    const type_info& info = typeid(j);
    cout << info.name() << endl;

    vector<string> vec;
    vec.push_back("ab");
    vec.push_back("ac");
    vec.push_back("ad");
    print_vector(vec);

    map<int, string> record;
    record.insert(pair<int, string>(1, "ab"));
    record.insert(pair<int, string>(2, "ac"));
    record.insert(pair<int, string>(3, "ad"));
    print_map(record);

    return 0;
}