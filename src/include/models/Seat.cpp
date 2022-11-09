#include "Seat.hpp"

Seat::Seat(const std::string &id, double cost)
{
    this->cost = cost;
    this->id = id;
}

Seat::Seat()
{
}