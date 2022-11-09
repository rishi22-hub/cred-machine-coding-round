#ifndef CLASSSEATAVAILABILITY_HPP
#define CLASSSEATAVAILABILITY_HPP

#include "constants/FlightBooking.hpp"
#include "models/Seat.hpp"

#include <vector>

class ClassSeatAvailability
{
public:
    ClassSeatAvailability();

    ClassSeatAvailability(FlightBooking::ClassType classType, const std::vector<Seat> &availableSeats, const std::vector<Seat> &bookedSeats);

    FlightBooking::ClassType getClassType() const;

    std::vector<Seat> getAvailableSeats() const;

    std::vector<Seat> getBookedSeats() const;

    void setAvailableSeats(std::vector<Seat> &seats);

    void setBookedSeats(std::vector<Seat> &seats);

private:
    FlightBooking::ClassType classType;

    std::vector<Seat> availableSeats;

    std::vector<Seat> bookedSeats;
};

#endif