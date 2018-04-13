//
// Created by Kuba on 07.04.2018.
//

#include "SimpleJson.h"

nets::JsonValue::JsonValue(int a) {
    value1=a;
    type=1;
}

nets::JsonValue::JsonValue(float a) {
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
            break;
        case 3:
            result = "\"" + value3 + "\"";
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
            bool first = true;
            for (auto n : value5) {
                if (!first) {
                    result.append(", ");
                } else {
                    first = false;
                }
                result.append(n.ToString());
            }
            result += "]";
            break;
        default:
            return result;
    }
    return std::string();
}
