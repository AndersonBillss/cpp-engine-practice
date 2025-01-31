#include "core.h"
#include <vector>
using std::string;

int main(){
    vector<string> v1 = {"hello", "12", "2"};
    vector<string> v2 = {"34", "56", "HI"};
    vector<string> v3 = {"Sample", "String", "98765"};
    vector<vector<string>> myStringVector = {v1, v2, v3};
    print(myStringVector);

    vector<int> myVector = {1,2,3,4,5};
    print(myVector);

    vector<int> v4 = {1, 4, 5};
    vector<int> v5 = {9, 7, 5};
    vector<int> v6 = {6, 1, 7};
    vector<vector<int>> myIntVector = {v4, v5, v6};
    print(myIntVector);

    print(string("ABC"));
    print("ABC");
    print(1);
    print(1.2f);
    return 0;
}