#ifndef PROJAED2_AIRLINE_H
#define PROJAED2_AIRLINE_H

#include <string>
using namespace std;

class Airline {
public:
    Airline(const string& code, const string& name, const string& callSign, const string& country);

    string getCode() const;
    string getName() const;
    string getCallsign() const;
    string getCountry() const;

    bool operator<(const Airline& other) const;

private:

    string code;
    string name;
    string callSign;
    string country;
};


#endif //PROJAED2_AIRLINE_H
