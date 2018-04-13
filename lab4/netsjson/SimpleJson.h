//
// Created by Kuba on 07.04.2018.
//

#ifndef JIMP_EXERCISES_SIMPLEJSON_H
#define JIMP_EXERCISES_SIMPLEJSON_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "SimpleJson.h"
#include <experimental/optional>

using ::std::vector;
using ::std::map;
using ::std::cout;
using ::std::endl;
using ::std::string;
using ::std::literals::operator""s;

namespace nets{
    class JsonValue {
        int value1;
        double value2;
        string value3;
        bool value4;
        vector<JsonValue> value5;
        map<string, JsonValue> value6;
        int type;

    public:
        JsonValue(int);
        JsonValue(double);
        JsonValue(string);
        JsonValue(bool);
        JsonValue(vector<JsonValue>);
        JsonValue(map<string, JsonValue>);
        ~JsonValue();
        std::experimental::optional<JsonValue> ValueByName(const std::string &name) const;
        std::string ToString() const;
    };
    std::string raw_string(std::string);
}


#endif //JIMP_EXERCISES_SIMPLEJSON_H
