//
// Created by dell on 18.04.2018.
//

#ifndef JIMP_EXERCISES_ARRAYFILL_H
#define JIMP_EXERCISES_ARRAYFILL_H


#include <vector>
#include <random>
#include <memory>

namespace arrays {
    class Filler{
    public:
        virtual int GetValue(size_t index) const =0;
    };

    class UniformFill:public Filler {
    private:
        int fillerValue;
    public:
        int GetValue(size_t index) const override;

        UniformFill(int value = 0);
    };

    class IncrementalFill:public Filler{
    private:
        int startValue, stepValue;
    public:
        int GetValue(size_t index) const override;

        IncrementalFill(int start, int step=1);
    };

    class SquaredFill:public Filler{
    private:
        int aValue, bValue;
    public:
        int GetValue(size_t index) const override;

        SquaredFill(int a=1, int b=0);
    };

    void FillArray(size_t size, const Filler &filler, std::vector<int> *v);
}
#endif //JIMP_EXERCISES_ARRAYFILL_H
