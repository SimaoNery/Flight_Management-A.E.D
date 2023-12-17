#ifndef PROJAED2_AIRPORT_H
#define PROJAED2_AIRPORT_H

#include <string>
#include <vector>
#include "Graph.h"
using namespace std;


class Airport {
public:
    Airport() = default;
    Airport(string& code, string& name, string& city, string& country, float latitude, float longitude);

    string getCode();
    string getName();
    string getCity();
    string getCountry();
    float getLatitude();
    float getLongitude();


    bool operator<(const Airport& other) const;
    bool operator==(const Airport& other) const;
private:

    string code;
    string name;
    string city;
    string country;
    float latitude;
    float longitude;
};


#endif //PROJAED2_AIRPORT_H
