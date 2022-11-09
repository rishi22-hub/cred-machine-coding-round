#ifndef FLIGHTBOOKINGMANAGERIMPL_HPP
#define FLIGHTBOOKINGMANAGERIMPL_HPP

#include "services/FlightBookingManager.hpp"

#include <map>

class FlightBookingManagerImpl : public FlightBookingManager
{
public:
    bool add(const FlightDetails &flightDetails);

    bool addClassSeatAvailability(const std::string flightId, ClassSeatAvailability classSeatAvailability);

    bool updateClassSeatAvailability(const std::string flightId, ClassSeatAvailability classSeatAvailability);

    bool removeClassSeatAvailability(const std::string flightId, ClassSeatAvailability classSeatAvailability);

    bool bookSeat(const std::string flightId, FlightBooking::ClassType classType);

    SearchResponse search(FlightBooking::Location source, FlightBooking::Location destination);

private:
    std::map<std::string, FlightDetails> flightMap;
};

#endif