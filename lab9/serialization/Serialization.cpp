//
// Created by dell on 09.05.2018.
//

#include "Serialization.h"

academia::Serializer::Serializer(std::ostream *out) : out_(out){}


//Room

academia::Room::Room(int id, std::string name, academia::Room::Type type) {
    id_=id;
    name_=name;
    type_=type;
}

void academia::Room::Serialize(academia::Serializer *ser) const {
    ser->Header("Room");
    ser->IntegerField("id", id_);
    ser->StringField("type", enum_to_string.at(type_));
    ser->StringField("name", name_);
    ser->Footer("Room");
}

void academia::Room::Serialize(academia::JsonSerializer *js) const {
    js->setFirst_(true);
    js->Header("Room");
    js->IntegerField("id", id_);
    js->StringField("name", name_);
    js->StringField("type", enum_to_string.at(type_));
    js->Footer("Room");
}

void academia::Room::Serialize(academia::XmlSerializer *xs) const {
    xs->Header("room");
    xs->IntegerField("id", id_);
    xs->StringField("name", name_);
    xs->StringField("type", enum_to_string.at(type_));
    xs->Footer("room");
}




// Building

academia::Building::Building(int id, std::string name,
                             const std::vector<Room> &rooms) {
    id_ = id;
    name_ = name;
    rooms_ = rooms;
}

void academia::Building::Serialize(academia::Serializer *ser) const {

}

void academia::Building::Serialize(academia::JsonSerializer *js) const {
    js->setFirst_(true);
    js->Header("Building");
    js->IntegerField("id", id_);
    js->StringField("name", name_);
    std::vector<std::reference_wrapper<const Serializable>> to_array_field;
    for (auto &room:rooms_){
        to_array_field.emplace_back(std::cref(room));
    }
    js->ArrayField("rooms", to_array_field);
    js->Footer("Building");
}

void academia::Building::Serialize(academia::XmlSerializer *xs) const {
    xs->Header("building");
    xs->IntegerField("id", id_);
    xs->StringField("name", name_);
    std::vector<std::reference_wrapper<const Serializable>> to_array_field;
    for (auto &room:rooms_){
        to_array_field.emplace_back(std::cref(room));
    }
    xs->ArrayField("rooms", to_array_field);
    xs->Footer("building");
}

int academia::Building::Id() const {
    return id_;
}



//JsonSerializer

academia::JsonSerializer::JsonSerializer(std::ostream *out): Serializer(out), first_(true){}

void academia::JsonSerializer::First() {
    if (!first_){
        *out_<<", ";
    }else{
        first_= false;
    }
}

void academia::JsonSerializer::IntegerField(const std::string &field_name, int value) {
    First();
    *out_<<"\""<<field_name<<"\": "<<value;
}

void academia::JsonSerializer::DoubleField(const std::string &field_name, double value) {

}

void academia::JsonSerializer::StringField(const std::string &field_name, const std::string &value) {
    First();
    *out_<<"\""<<field_name<<"\": \""<<value<<"\"";
}

void academia::JsonSerializer::BooleanField(const std::string &field_name, bool value) {

}

void academia::JsonSerializer::SerializableField(const std::string &field_name, const academia::Serializable &value) {

}

void academia::JsonSerializer::ArrayField(const std::string &field_name,
                                          const std::vector<std::reference_wrapper<const academia::Serializable>> &value) {
    First();
    first_=true;
    *out_<<"\""<<field_name<<"\": [";
    bool first=true;
    for (auto &room:value){
        if (first){
            first=false;
        }else{
            *out_<<", ";
        }
        room.get().Serialize(this);
    }
    *out_<<"]";
    first_= false;
}

void academia::JsonSerializer::Header(const std::string &object_name) {
    *(out_)<<"{";
}

void academia::JsonSerializer::Footer(const std::string &object_name) {
    *(out_)<<"}";
}

void academia::JsonSerializer::setFirst_(bool first_) {
    JsonSerializer::first_ = first_;
}




//XmlSerializer

academia::XmlSerializer::XmlSerializer(std::ostream *out) :Serializer(out){}

void academia::XmlSerializer::IntegerField(const std::string &field_name, int value) {
    *out_<<"<"<<field_name<<">"<<value<<"<\\"<<field_name<<">";
}

void academia::XmlSerializer::DoubleField(const std::string &field_name, double value) {

}

void academia::XmlSerializer::StringField(const std::string &field_name, const std::string &value) {
    *out_<<"<"<<field_name<<">"<<value<<"<\\"<<field_name<<">";
}

void academia::XmlSerializer::BooleanField(const std::string &field_name, bool value) {

}

void academia::XmlSerializer::SerializableField(const std::string &field_name, const academia::Serializable &value) {

}

void academia::XmlSerializer::ArrayField(const std::string &field_name,
                                         const std::vector<std::reference_wrapper<const academia::Serializable>> &value) {
    *out_<<"<"<<field_name<<">";
    for (auto &room:value){
        room.get().Serialize(this);
    }
    *out_<<"<\\"<<field_name<<">";
}

void academia::XmlSerializer::Header(const std::string &object_name) {
    *out_<<"<"<<object_name<<">";
}

void academia::XmlSerializer::Footer(const std::string &object_name) {
    *out_<<"<\\"<<object_name<<">";
}





void academia::BuildingRepository::StoreAll(academia::Serializer *serializer) const {
    serializer->Header("building_repository");
    std::vector<std::reference_wrapper<const Serializable>> to_array_field;
    for (auto &building:buildings_){
        to_array_field.emplace_back(std::cref(building));
    }
    serializer->ArrayField("buildings",to_array_field);
    serializer->Footer("building_repository");
}

void academia::BuildingRepository::Add(const academia::Building building_to_add) {
    buildings_.emplace_back(building_to_add);
}

academia::BuildingRepository::BuildingRepository(const academia::Building &first_building) {
    Add(first_building);
}

std::experimental::optional<academia::Building> academia::BuildingRepository::operator[](int id) const {
    for (auto &building:buildings_){
        if (id == building.Id()){
            return building;
        }
    }
}
