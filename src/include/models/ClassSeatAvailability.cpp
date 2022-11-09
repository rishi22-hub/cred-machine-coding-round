#include "ClassSeatAvailability.hpp"

ClassSeatAvailability::ClassSeatAvailability()
{
}

ClassSeatAvailability::ClassSeatAvailability(FlightBooking::ClassType classType, const std::vector<Seat> &availableSeats, const std::vector<Seat> &bookedSeats)
{
    this->classType = classType;
    this->availableSeats = availableSeats;
    this->bookedSeats = bookedSeats;
}

FlightBooking::ClassType ClassSeatAvailability::getClassType() const
{
    return this->classType;
}

std::vector<Seat> ClassSeatAvailability::getAvailableSeats() const
{
    return this->availableSeats;
}

std::vector<Seat> ClassSeatAvailability::getBookedSeats() const
{
    return this->bookedSeats;
}

void ClassSeatAvailability::setAvailableSeats(std::vector<Seat> &seats)
{
    this->availableSeats = seats;
}

void ClassSeatAvailability::setBookedSeats(std::vector<Seat> &seats)
{
    this->bookedSeats = seats;
}
