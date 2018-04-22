//
// Created by dell on 18.04.2018.
//

#include "ArrayFill.h"

arrays::UniformFill::UniformFill(int value) {
    fillerValue=value;
}



int arrays::UniformFill::GetValue(size_t index) const {
    return fillerValue;
}

void arrays::FillArray(size_t size, const Filler &filler, std::vector<int> *v) {
    v->clear();
    v->reserve(size);
    for (size_t i=0; i<size; ++i){
        v->emplace_back(filler.GetValue(i));
    }
}

int arrays::IncrementalFill::GetValue(size_t index) const {
    return (startValue+index*stepValue);
}

arrays::IncrementalFill::IncrementalFill(int start, int step) {
    startValue=start;
    stepValue=step;
}

int arrays::SquaredFill::GetValue(size_t index) const {
    const size_t value = aValue * index *index + bValue;
    return value;
}

arrays::SquaredFill::SquaredFill(int a, int b) {
    aValue=a;
    bValue=b;
}
