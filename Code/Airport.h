#ifndef PROJAED2_AIRPORT_H
#define PROJAED2_AIRPORT_H

#include <string>
#include <vector>
#include "Graph.h"
using namespace std;


class Airport {
public:
    Airport(string& code, string& name, string& city, string& country, float latitude, float longitude);

    string getCode();
    string getName();
    string getCity();
    string getCountry();
    float getLatitude();
    float getLongitude();

private:

    string code_;
    string name_;
    string city_;
    string country_;
    float latitude_;
    float longitude_;
};


#endif //PROJAED2_AIRPORT_H
