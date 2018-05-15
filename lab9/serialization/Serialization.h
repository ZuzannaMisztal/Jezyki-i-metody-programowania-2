//
// Created by dell on 09.05.2018.
//

#ifndef JIMP_EXERCISES_ACADEMIASERIALIZER_H
#define JIMP_EXERCISES_ACADEMIASERIALIZER_H

#include <ostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <experimental/optional>

namespace academia{
    class Serializer;
    class JsonSerializer;
    class XmlSerializer;

    class Serializable{
    public:
        virtual void Serialize(Serializer *ser)const =0;
        virtual void Serialize(JsonSerializer *js)const =0;
        virtual void Serialize(XmlSerializer *xs)const =0;
    };

    class Serializer{
    protected:
        std::ostream *out_;
    public:
        Serializer(std::ostream*);
        virtual void IntegerField(const std::string &field_name, int value)=0;
        virtual void DoubleField(const std::string &field_name, double value)=0;
        virtual void StringField(const std::string &field_name, const std::string &value)=0;
        virtual void BooleanField(const std::string &field_name, bool value)=0;
        virtual void SerializableField(const std::string &field_name, const academia::Serializable &value)=0;
        virtual void ArrayField(const std::string &field_name,
                        const std::vector<std::reference_wrapper<const academia::Serializable>> &value)=0;
        virtual void Header(const std::string &object_name)=0;
        virtual void Footer(const std::string &object_name)=0;
    };



    class Room:public Serializable{
    public:
        enum class Type{
            COMPUTER_LAB,
            LECTURE_HALL,
            CLASSROOM
        };
        Room(int, std::string, Type);
        void Serialize(Serializer *ser)const override;
        void Serialize(JsonSerializer *js) const override;
        void Serialize(XmlSerializer *xs) const override;

    private:
        int id_;
        std::string name_;
        Type type_;
        std::map<Type, std::string> enum_to_string {{Type::COMPUTER_LAB, "COMPUTER_LAB"}, {Type::LECTURE_HALL, "LECTURE_HALL"}, {Type::CLASSROOM, "CLASSROOM"}};
    };

    class Building:public Serializable{
    private:
        int id_;
        std::string name_;
        std::vector<Room> rooms_;
    public:
        Building()= default;
        Building(int id, std::string name, const std::vector<Room> &rooms);
        ~Building() =  default;
        void Serialize(Serializer *ser) const override;
        void Serialize(JsonSerializer *js) const override;
        void Serialize(XmlSerializer *xs) const override;
        int Id() const;
    };



    class JsonSerializer : public Serializer{
    private:
        bool first_;
    public:
        JsonSerializer(std::ostream*);
        void IntegerField(const std::string &field_name, int value) override;
        void DoubleField(const std::string &field_name, double value) override;
        void StringField(const std::string &field_name, const std::string &value) override;
        void BooleanField(const std::string &field_name, bool value) override;
        void SerializableField(const std::string &field_name, const academia::Serializable &value) override;
        void ArrayField(const std::string &field_name,
                        const std::vector<std::reference_wrapper<const academia::Serializable>> &value) override;
        void Header(const std::string &object_name) override;
        void Footer(const std::string &object_name) override;
        void First();
        void setFirst_(bool first_);
    };

    class XmlSerializer : public Serializer{
    public:
        XmlSerializer(std::ostream*);
        void IntegerField(const std::string &field_name, int value) override;

        void DoubleField(const std::string &field_name, double value) override;

        void StringField(const std::string &field_name, const std::string &value) override;

        void BooleanField(const std::string &field_name, bool value) override;

        void SerializableField(const std::string &field_name, const academia::Serializable &value) override;

        void ArrayField(const std::string &field_name,
                        const std::vector<std::reference_wrapper<const academia::Serializable>> &value) override;

        void Header(const std::string &object_name) override;

        void Footer(const std::string &object_name) override;
    };


    class BuildingRepository{
    private:
        std::vector<Building> buildings_;
    public:
        BuildingRepository()= default;
        BuildingRepository(const Building &);
        ~BuildingRepository()= default;
        void StoreAll(Serializer *serializer) const;
        void Add(const Building);
        std::experimental::optional<Building> operator[](int id) const;
    };
}


#endif //JIMP_EXERCISES_ACADEMIASERIALIZER_H
