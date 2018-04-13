//
// Created by Kuba on 07.04.2018.
//

#include "SimpleJson.h"

nets::JsonValue::JsonValue(int a) {
    value1=a;
    type=1;
}

nets::JsonValue::JsonValue(double a) {
    value2=a;
    type=2;
}

nets::JsonValue::JsonValue(string a) {
    value3=a;
    type=3;
}

nets::JsonValue::JsonValue(bool a) {
    value4=a;
    type=4;
}

nets::JsonValue::JsonValue(vector<nets::JsonValue> a) {
    value5=a;
    type=5;
}

nets::JsonValue::JsonValue(map<string, nets::JsonValue> a) {
    value6=a;
    type=6;
}

nets::JsonValue::~JsonValue() {

}

std::experimental::optional<nets::JsonValue> nets::JsonValue::ValueByName(const std::string &name) const {

    return std::experimental::optional<nets::JsonValue>();
}

std::string nets::JsonValue::ToString() const {
    string result;
    switch (type) {
        case 1:
            result = std::to_string(value1);
            break;
        case 2:
            result = std::to_string(value2);
            while (result.back()=='0'){
                result=result.substr(0,result.length()-1);
            }
            break;
        case 3:
            result=raw_string(value3);
            break;
        case 4:
            if (value4) {
                result = "true";
            } else {
                result = "false";
            }
            break;
        case 5:
            result = "[";
            bool first;
            first = true;
            for (auto n : value5) {
                if (!first) {
                    result.append(", ");
                } else {
                    first = false;
                }
                result.append(n.ToString());
            }
            result += ']';
            break;
        case 6:
            result+="{";
            first = true;
            for (const auto &str : value6){
                if (!first){
                    result+=", ";
                }
                else{
                    first= false;
                }
                result.append(raw_string(str.first));
                result+=": ";
                result.append(str.second.ToString());
            }
            result+="}";
            break;
        default:
            return result;
    }
    return result;
}
// "\"\\\"abc\\\"\""
// "\"\"abc\"\""
std::string nets::raw_string(std::string to_copy) {
    std::string result = "\"";
    for (int i=0; i<to_copy.length(); ++i){
        if (to_copy[i]=='\\'){
            result += "\\";
        }
        if (to_copy[i]=='\"'){
            result+="\\";
        }
        result+=to_copy[i];
    }
    result+="\"";
    return result;
}

