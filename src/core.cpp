#include <iostream>
#include <string>
#include <vector>
using std::cout, std::endl, std::string, std::vector, std::to_string;

// Function to print debug messages
template <typename T>
void print(const T& item) {
    cout << item << endl;
}

template <typename T>
string stringify(const T& item){
    return to_string(item);
}

template <typename T>
string stringify(const vector<T>& vec) {
    string finalString = "";
    finalString += "[";
    for (const auto& item : vec) {
        finalString += stringify(item) + " ";
    }
    finalString += "]";
    return finalString;
}
