#ifndef SEARCHRESPONSE_HPP
#define SEARCHRESPONSE_HPP

#include "models/FlightDetails.hpp"

class SearchResponse
{
public:
    SearchResponse(int totalCount, const std::vector<FlightDetails> &results);

    int getTotalCount();

    std::vector<FlightDetails> getResults();

private:
    int totalCount;

    std::vector<FlightDetails> results;
};

#endif