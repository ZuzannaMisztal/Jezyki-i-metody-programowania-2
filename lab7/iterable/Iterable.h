//
// Created by dell on 05.05.2018.
//

#ifndef JIMP_EXERCISES_ITERABLE_H
#define JIMP_EXERCISES_ITERABLE_H


#include <string>
#include <memory>

namespace utility {
    class IterableIterator {
    protected:
        std::vector<int>::const_iterator l_b;
        std::vector<std::string>::const_iterator r_b;
        std::vector<int>::const_iterator l_e;
        std::vector<std::string>::const_iterator r_e;
    public:
        IterableIterator(std::vector<int>::const_iterator left_begin,
                         std::vector<std::string>::const_iterator right_begin,
                         std::vector<int>::const_iterator left_end,
                         std::vector<std::string>::const_iterator right_end);
        virtual std::pair<int, std::string> Dereference() const =0;
        virtual IterableIterator &Next()=0;
        virtual bool NotEquals(const std::unique_ptr<IterableIterator>&) const =0;
        std::vector<int>::const_iterator GetL_B();
        std::vector<std::string>::const_iterator GetR_B();
        ~IterableIterator()= default;
    };

    class ZipperIterator : public IterableIterator{
    public:
        explicit ZipperIterator(std::vector<int>::const_iterator left_begin,
                                std::vector<std::string>::const_iterator right_begin,
                                std::vector<int>::const_iterator left_end,
                                std::vector<std::string>::const_iterator right_end);
        std::pair<int, std::string> Dereference() const override;
        IterableIterator &Next() override;
        bool NotEquals(const std::unique_ptr<IterableIterator>&)const override;
    };

    class EnumerateIterator : public IterableIterator{public:
        explicit EnumerateIterator(std::vector<int>::const_iterator left_begin,
        std::vector<std::string>::const_iterator right_begin,
                std::vector<int>::const_iterator left_end,
        std::vector<std::string>::const_iterator right_end);
        std::pair<int, std::string> Dereference() const override;
        IterableIterator &Next() override;
        bool NotEquals(const std::unique_ptr<IterableIterator>&) const override;
    };

    class ProductIterator : public IterableIterator{public:
        explicit ProductIterator(std::vector<int>::const_iterator left_begin,
                                   std::vector<std::string>::const_iterator right_begin,
                                   std::vector<int>::const_iterator left_end,
                                   std::vector<std::string>::const_iterator right_end);
        std::pair<int, std::string> Dereference() const override;
        IterableIterator &Next() override;
        bool NotEquals(const std::unique_ptr<IterableIterator>&) const override;
    };

    class IterableIteratorWrapper{
    private:
        std::unique_ptr<IterableIterator> it;
    public:
        IterableIteratorWrapper(std::unique_ptr<IterableIterator> iterator);
        bool operator!=(const IterableIteratorWrapper &other) const;
        std::pair<int, std::string> operator*() const ;
        IterableIteratorWrapper &operator++();
    };

    class Iterable{
    protected:
        std::vector<int> int_vector;
        std::vector<std::string> string_vector;
    public:
        virtual std::unique_ptr<IterableIterator> ConstBegin() const=0;
        virtual std::unique_ptr<IterableIterator> ConstEnd() const =0;
        IterableIteratorWrapper cbegin() const;
        IterableIteratorWrapper cend() const;
        IterableIteratorWrapper begin() const;
        IterableIteratorWrapper end() const;
    };

    class Zipper : public Iterable{
    public:
        Zipper(std::vector<int> vi, std::vector<std::string> vs);
        std::unique_ptr<IterableIterator> ConstBegin() const override;
        std::unique_ptr<IterableIterator> ConstEnd() const override;
    };

    class Enumerate : public Iterable{
    public:
        Enumerate(std::vector<std::string> vs);
        std::unique_ptr<IterableIterator> ConstBegin() const override;
        std::unique_ptr<IterableIterator> ConstEnd() const override;
    };

    class Product : public Iterable{
    public:
        Product(std::vector<int> vi, std::vector<std::string> vs);
        std::unique_ptr<IterableIterator> ConstBegin() const override;
        std::unique_ptr<IterableIterator> ConstEnd() const override;
    };
}

#endif //JIMP_EXERCISES_ITERABLE_H
