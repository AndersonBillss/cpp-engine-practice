#pragma once

#include <iostream>
#include <string>
#include <vector>
using std::cout, std::endl, std::string, std::vector, std::to_string;

inline string stringify(const char * item) {
    return string(item);
}
inline string stringify(const string& item) {
    return item;
}
inline string stringify(const int& item) {
    return "\033[33m" + to_string(item) + "\033[0m";
}
inline string stringify(const float& item) {
    return "\033[33m" + to_string(item) + "\033[0m";
}
inline string stringify(const double& item) {
    return "\033[33m" + to_string(item) + "\033[0m";
}
template <typename T>
inline string stringify(const vector<T>& vec) {
    string finalString = "";
    finalString += "[";
    for(auto i=0; i<vec.size(); i++){
        auto item = vec[i];
        bool isLast = i == vec.size()-1;
        finalString += stringify(item);
        if(!isLast){
        finalString += ", ";
        }
    }
    finalString += "]";
    return finalString;
}
template <typename T>
inline string stringify(const T& item){
    return to_string(item);
}

template <typename T>
inline void print(const T& item) {
    cout << stringify(item) << endl;
}