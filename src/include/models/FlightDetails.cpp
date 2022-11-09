#include "FlightDetails.hpp"

FlightDetails::FlightDetails()
{
}

FlightDetails::FlightDetails(const std::string &id, const std::string &name, FlightBooking::Airline airline, FlightBooking::Location source, FlightBooking::Location destination,
                             const std::vector<ClassSeatAvailability> &seatAvailabilities)
{
    this->id = id;
    this->name = name;
    this->airline = airline;
    this->source = source;
    this->destination = destination;
    this->seatAvailabilities = seatAvailabilities;
}

std::string FlightDetails::getId() const
{
    return this->id;
}

std::vector<ClassSeatAvailability> FlightDetails::getClassSeatAvailability() const
{
    return this->seatAvailabilities;
}

void FlightDetails::setClassSeatAvailability(std::vector<ClassSeatAvailability> &seatAvailabilities)
{
    this->seatAvailabilities = seatAvailabilities;
}

FlightBooking::Location FlightDetails::getSource()
{
    return this->source;
}

FlightBooking::Location FlightDetails::getDestination()
{
    return this->destination;
}
