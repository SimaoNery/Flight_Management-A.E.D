#include "Airline.h"

Airline::Airline(const string& code, const string& name, const string& callSign, const string& country){
    this->code_ = code;
    this->name_ = name;
    this->callSign_ = callSign;
    this->country_ = country;
}

string Airline::getCode() const{
    return code_;
}

string Airline::getName() const{
    return name_;
}

string Airline::getCallsign() const{
    return callSign_;
}

string Airline::getCountry() const{
    return country_;
}