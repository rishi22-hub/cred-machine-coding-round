#include "SearchResponse.hpp"

SearchResponse::SearchResponse(int totalCount, const std::vector<FlightDetails> &results)
{
    this->totalCount = totalCount;
    this->results = results;
}

int SearchResponse::getTotalCount()
{
    return this->totalCount;
}

std::vector<FlightDetails> SearchResponse::getResults(){
    return this->results;
}