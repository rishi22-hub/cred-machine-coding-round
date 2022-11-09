#ifndef FLIGHTBOOKINGMANAGER_HPP
#define FLIGHTBOOKINGMANAGER_HPP

#include "models/FlightDetails.hpp"
#include "models/ClassSeatAvailability.hpp"
#include "models/Seat.hpp"
#include "models/SearchResponse.hpp"
#include "constants/FlightBooking.hpp"

#include <string>

class FlightBookingManager
{
public:
    /**
     * Add flight detail
     *
     * @return bool, true if add is successful else false
     **/
    virtual bool add(const FlightDetails &flightDetails) = 0;

    /**
     * Add {@ClassSeatAvailability} to given fightId
     *
     * @return bool, true if add is successful else false
     **/
    virtual bool addClassSeatAvailability(const std::string flightId, ClassSeatAvailability classSeatAvailability) = 0;

    /**
     * Update {@ClassSeatAvailability} to given fightId
     *
     * @return bool, true if update is successful else false
     **/
    virtual bool updateClassSeatAvailability(const std::string flightId, ClassSeatAvailability classSeatAvailability) = 0;

    /**
     * Remove {@ClassSeatAvailability} to given fightId
     *
     * @return bool, true if remove is successful else false
     **/
    virtual bool removeClassSeatAvailability(const std::string flightId, ClassSeatAvailability classSeatAvailability) = 0;

    /**
     * bookSeat does the booking of a seat for given class type and flight ID
     *
     * @return true if booking is successful else false
     **/
    virtual bool bookSeat(const std::string flightId, FlightBooking::ClassType classType) = 0;

    /**
     * Search function searches direct flight details from source to destination
     * <p>
     * Returns the {@SearchResponse} which matches the criteria
     **/
    virtual SearchResponse search(FlightBooking::Location source, FlightBooking::Location destination) = 0;

private:
};

#endif