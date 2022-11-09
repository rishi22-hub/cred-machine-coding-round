#ifndef SEAT_HPP
#define SEAT_HPP

#include <string>

class Seat
{
public:
    Seat(const std::string &id, double cost);
    
    Seat();
private:
    std::string id;

    double cost;
};

#endif