#ifndef PROJAED2_AIRPORT_H
#define PROJAED2_AIRPORT_H

#include <string>
#include <vector>
#include "Graph.h"
using namespace std;

class Airport {
public:
    ///Default constructor for class Airport
    Airport() = default;
    ///Creates an Airport with the code, name, city, country, latitude and longitude given
    Airport(string& code, string& name, string& city, string& country, float latitude, float longitude);
    ///Creates an Airport only with the code given
    Airport(string& code);

    ///
    /// \return the Airport code
    string getCode() const;
    ///
    /// \return the Airport name
    string getName();
    ///
    /// \return the Airport city
    string getCity();
    ///
    /// \return the Airport country
    string getCountry();
    ///
    /// \return the Airport latitude
    float getLatitude();
    ///
    /// \return the Airport longitude
    float getLongitude();

    /// Changes the Airport code to the code given
    /// \param code Airport code
    void setCode(string& code);
    /// Changes the Airport name to the name given
    /// \param name Airport name
    void setName(string& name);
    /// Changes the Airport city to the city given
    /// \param city Airport city
    void setCity(string& city);
    /// Changes the Airport country to the country given
    /// \param country Airport country
    void setCountry(string& country);
    /// Changes the Airport latitude to the latitude given
    /// \param latitude Airport latitude
    void setLatitude(float latitude);
    /// Changes the Airport longitude to the longitude given
    /// \param longitude Airport longitude
    void setLongitude(float longitude);

    ///Overload of the operator '<' for class Airport
    /// \param other Airport given
    /// \return true if the Airport code in comparison is smaller than the code of the Airport given
    bool operator<(const Airport& other) const;
    ///Overload of the operator '==' for class Airport
    /// \param other Airport given
    /// \return true if the Airport code in comparison is equal to the code of the Airport given
    bool operator==(const Airport& other) const;
private:
    /// Airport code
    string code;
    /// Airport name
    string name;
    /// Airport city
    string city;
    /// Airport country
    string country;
    /// Airport latitude
    float latitude;
    /// Airport longitude
    float longitude;
};

#endif //PROJAED2_AIRPORT_H
