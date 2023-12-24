#include "Airline.h"

Airline::Airline(const string& code, const string& name, const string& callSign, const string& country){
    this->code= code;
    this->name = name;
    this->callSign = callSign;
    this->country = country;
}

Airline::Airline(const string& code){
    this->code = code;
}

string Airline::getCode() const{
    return code;
}

string Airline::getName() const{
    return name;
}

string Airline::getCallsign() const{
    return callSign;
}

string Airline::getCountry() const{
    return country;
}

void Airline::setName(string name) {
    this->name = name;
}

bool Airline::operator<(const Airline &other) const {
    return code < other.code;
}