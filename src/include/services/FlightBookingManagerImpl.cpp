#include "FlightBookingManagerImpl.hpp"

/**
     * Add flight detail
     *
     * @return bool, true if add is successful else false
     **/
bool FlightBookingManagerImpl::add(const FlightDetails &flightDetails)
{
     auto id=flightDetails.getId();
    if(flightMap.find(id)!=flightMap.end())
    return false;
   
    flightMap[id]=flightDetails;
    return true;
}

/**
     * Add {@ClassSeatAvailability} to given fightId
     *
     * @return bool, true if add is successful else false
     **/
bool FlightBookingManagerImpl::addClassSeatAvailability(const std::string flightId, ClassSeatAvailability classSeatAvailability)
{

    auto flight_details = flightMap[flightId];
   auto add_seats=flight_details.getClassSeatAvailability();
    auto get_available_seats=classSeatAvailability.getAvailableSeats();
    for(auto &i:add_seats){
        for(auto &j:get_available_seats){
            auto available_seats=i.getAvailableSeats();
            available_seats.push_back(j);
        }
    }
    return true;
}

/**
     * Update {@ClassSeatAvailability} to given fightId
     *
     * @return bool, true if update is successful else false
     **/
bool FlightBookingManagerImpl::updateClassSeatAvailability(const std::string flightId, ClassSeatAvailability classSeatAvailability)
{
   auto flight_details = flightMap[flightId];
    auto add_seats=flight_details.getClassSeatAvailability();
    auto get_available_seats=classSeatAvailability.getAvailableSeats();
    for(auto &i:add_seats){
        
            i.setAvailableSeats(get_available_seats);
        
    }
    return true;
}

/**
     * Remove {@ClassSeatAvailability} to given fightId
     *
     * @return bool, true if remove is successful else false
     **/
bool FlightBookingManagerImpl::removeClassSeatAvailability(const std::string flightId, ClassSeatAvailability classSeatAvailability)
{
    auto flight_details = flightMap[flightId];
    auto add_seats=flight_details.getClassSeatAvailability();
    auto get_available_seats=classSeatAvailability.getAvailableSeats();
    for(auto &i:add_seats){
        for(auto &j:get_available_seats){
            auto available_seats=i.getAvailableSeats();
            remove(available_seats.begin(),available_seats.end(),j);
        }
    }
    return true;
}

/**
     * bookSeat does the booking of a seat for given class type and flight ID
     *
     * @return true if booking is successful else false
     **/
bool FlightBookingManagerImpl::bookSeat(const std::string flightId, FlightBooking::ClassType classType)
{
   auto flight_details = flightMap[flightId];
    auto available_seats=flight_details.getClassSeatAvailability();

    for(auto &i:available_seats){
        if((i.getClassType()==classType)&&((i.getAvailableSeats().size()>0))){
            auto it=i.getAvailableSeats().back();
            i.getAvailableSeats().pop_back();
            i.getBookedSeats().push_back(it);
            return true;
        }
    }
    return false;
}

/**
     * Search function searches direct flight details from source to destination
     * <p>
     * Returns the {@SearchResponse} which matches the criteria
     **/
SearchResponse FlightBookingManagerImpl::search(FlightBooking::Location source, FlightBooking::Location destination)
{
    std::vector<FlightDetails>ans;
    for(auto i:flightMap){
        auto details=i.second;
        if((details.getSource()==source)&&(details.getDestination()==destination)){
            ans.push_back(details);
        }
    }
    auto count=ans.size();
    return SearchResponse(count,ans);
}