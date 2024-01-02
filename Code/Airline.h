#ifndef PROJAED2_AIRLINE_H
#define PROJAED2_AIRLINE_H

#include <string>
using namespace std;

class Airline {
public:
    ///Default constructor for class Airline
    Airline() = default;
    /// Creates a Airline with the code, name, callsign and country given
    /// \param code Airline code
    /// \param name Airline name
    /// \param callSign Airline callsign
    /// \param country Airline country
    Airline(const string& code, const string& name, const string& callSign, const string& country);
    /// Creates a Airline only with the code given
    /// \param code Airline code
    Airline(const string& code);

    ///
    /// \return Airline code
    string getCode() const;
    ///
    /// \return Airline name
    string getName() const;
    ///
    /// \return Airline callsign
    string getCallsign() const;
    ///
    /// \return Airline country
    string getCountry() const;
    /// Changes the name of the Airline to the one given
    /// \param name Airline name
    void setName(string name);
    /// overload of the operator '<' for class Airline
    /// \param other Airline given
    /// \return true if the code of the Airline in comparison is smaller than the code of the Airline given
    bool operator<(const Airline& other) const;

private:
    /// Airline code
    string code;
    /// Airline name
    string name;
    /// Airline callsign
    string callSign;
    /// Airline country
    string country;
};


#endif //PROJAED2_AIRLINE_H
