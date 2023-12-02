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

private:

    string code_;
    string name_;
    string callSign_;
    string country_;
};


#endif //PROJAED2_AIRLINE_H
