#include "Airport.h"

Airport::Airport(string& code, string& name, string& city, string& country ,float latitude, float longitude){
    this->code_ = code;
    this->name_ = name;
    this->city_ = city;
    this->country_ = country;
    this->latitude_ = latitude;
    this->longitude_ = longitude;
}

string Airport::getCode(){
    return code_;
}

string Airport::getName(){
    return name_;
}

string Airport::getCity(){
    return city_;
}

string Airport::getCountry() {
    return country_;
}

float Airport::getLatitude(){
    return latitude_;
}

float Airport::getLongitude(){
    return longitude_;
}