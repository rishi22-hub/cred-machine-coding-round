#ifndef FLIGHTDETAILS_HPP
#define FLIGHTDETAILS_HPP

#include "constants/FlightBooking.hpp"
#include "models/ClassSeatAvailability.hpp"

#include <string>
#include <vector>

class FlightDetails
{
public:
    //TODO: Add Constructor, Getter and Setters

    FlightDetails();

    FlightDetails(const std::string &id, const std::string &name, FlightBooking::Airline airline, FlightBooking::Location source, FlightBooking::Location destination,
                  const std::vector<ClassSeatAvailability> &seatAvailabilities);

    std::string getId() const;

    std::vector<ClassSeatAvailability> getClassSeatAvailability() const;

    void setClassSeatAvailability(std::vector<ClassSeatAvailability> &seatAvailabilities);

    FlightBooking::Location getSource();

    FlightBooking::Location getDestination();

private:
    std::string id;

    std::string name;

    FlightBooking::Airline airline;

    FlightBooking::Location source;

    FlightBooking::Location destination;

    std::vector<ClassSeatAvailability> seatAvailabilities;
};

#endif