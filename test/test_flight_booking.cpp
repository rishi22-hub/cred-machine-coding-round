#define BOOST_TEST_MODULE flight_booking_tests

#include <boost/test/unit_test.hpp>
#include "services/FlightBookingManager.hpp"
#include "services/FlightBookingManagerImpl.hpp"

BOOST_AUTO_TEST_SUITE(tests_suite)

BOOST_AUTO_TEST_CASE(AddFlightDetailsSuccess)
{
  FlightBookingManager *manager = new FlightBookingManagerImpl();
  FlightDetails flightDetails("id1", "flight1", FlightBooking::indigo, FlightBooking::delhi, FlightBooking::chennai, std::vector<ClassSeatAvailability>());
  BOOST_CHECK_EQUAL(manager->add(flightDetails), 1);
  SearchResponse searchResponse = manager->search(FlightBooking::delhi, FlightBooking::chennai);
  std::vector<FlightDetails> results = searchResponse.getResults();
  BOOST_CHECK_EQUAL(searchResponse.getTotalCount(), 1);
  for (int i = 0; i < results.size(); i++)
  {
    BOOST_CHECK_EQUAL(results[i].getId() == "id1", 1);
  }
}

BOOST_AUTO_TEST_CASE(AddFlightDetailsFailure)
{
  FlightBookingManager *manager = new FlightBookingManagerImpl();
  FlightDetails flightDetails("id1", "flight1", FlightBooking::goair, FlightBooking::ahmedabad, FlightBooking::chennai, std::vector<ClassSeatAvailability>());
  BOOST_CHECK_EQUAL(manager->add(flightDetails), 1);
  BOOST_CHECK_EQUAL(manager->add(flightDetails), 0);
  SearchResponse searchResponse = manager->search(FlightBooking::ahmedabad, FlightBooking::chennai);
  std::vector<FlightDetails> results = searchResponse.getResults();
  BOOST_CHECK_EQUAL(searchResponse.getTotalCount(), 1);
  for (int i = 0; i < results.size(); i++)
  {
    BOOST_CHECK_EQUAL(results[i].getId() == "id1", 1);
  }
}

BOOST_AUTO_TEST_CASE(AddAvailabilitySuccess)
{
  FlightBookingManager *manager = new FlightBookingManagerImpl();
  FlightDetails flightDetails("id1", "flight1", FlightBooking::goair, FlightBooking::ahmedabad, FlightBooking::chennai, std::vector<ClassSeatAvailability>());
  BOOST_CHECK_EQUAL(manager->add(flightDetails), 1);
  ClassSeatAvailability classSeatAvailability(FlightBooking::economy, std::vector<Seat>({Seat("s1", 1233.0), Seat("s2", 1233.0)}), std::vector<Seat>({Seat("s3", 4233.0), Seat("s4", 4233.0)}));
  BOOST_CHECK_EQUAL(manager->addClassSeatAvailability("id1", classSeatAvailability), 1);
  SearchResponse searchResponse = manager->search(FlightBooking::ahmedabad, FlightBooking::chennai);
  std::vector<FlightDetails> results = searchResponse.getResults();
  BOOST_CHECK_EQUAL(searchResponse.getTotalCount(), 1);
  for (int i = 0; i < results.size(); i++)
  {
    BOOST_CHECK_EQUAL(results[i].getId() == "id1", 1);
  }
}

BOOST_AUTO_TEST_CASE(AddAvailabilityFailure)
{
  FlightBookingManager *manager = new FlightBookingManagerImpl();
  FlightDetails flightDetails("id1", "flight1", FlightBooking::goair, FlightBooking::ahmedabad, FlightBooking::chennai, std::vector<ClassSeatAvailability>());
  BOOST_CHECK_EQUAL(manager->add(flightDetails), 1);
  ClassSeatAvailability classSeatAvailability1(FlightBooking::economy, std::vector<Seat>({Seat("s1", 1233.0), Seat("s2", 1233.0)}), std::vector<Seat>({Seat("s3", 4233.0), Seat("s4", 4233.0)}));
  ClassSeatAvailability classSeatAvailability2(FlightBooking::business, std::vector<Seat>({Seat("s1", 1233.0), Seat("s2", 1233.0)}), std::vector<Seat>({Seat("s3", 4233.0), Seat("s4", 4233.0)}));
  ClassSeatAvailability classSeatAvailability3(FlightBooking::business, std::vector<Seat>({Seat("s5", 1233.0), Seat("s6", 1233.0)}), std::vector<Seat>({Seat("s7", 4233.0), Seat("s8", 4233.0)}));
  BOOST_CHECK_EQUAL(manager->addClassSeatAvailability("id1", classSeatAvailability1), 1);
  BOOST_CHECK_EQUAL(manager->addClassSeatAvailability("id1", classSeatAvailability1), 0);
  BOOST_CHECK_EQUAL(manager->addClassSeatAvailability("id1", classSeatAvailability2), 1);
  BOOST_CHECK_EQUAL(manager->addClassSeatAvailability("id1", classSeatAvailability3), 0);
}

BOOST_AUTO_TEST_CASE(UpdateAvailabilityFailure)
{
  FlightBookingManager *manager = new FlightBookingManagerImpl();
  FlightDetails flightDetails("id1", "flight1", FlightBooking::goair, FlightBooking::ahmedabad, FlightBooking::chennai, std::vector<ClassSeatAvailability>());
  ClassSeatAvailability classSeatAvailability1(FlightBooking::economy, std::vector<Seat>({Seat("s1", 1233.0), Seat("s2", 1233.0)}), std::vector<Seat>({Seat("s3", 4233.0), Seat("s4", 4233.0)}));
  ClassSeatAvailability classSeatAvailability2(FlightBooking::business, std::vector<Seat>({Seat("s1", 1233.0), Seat("s2", 1233.0)}), std::vector<Seat>({Seat("s3", 4233.0), Seat("s4", 4233.0)}));
  ClassSeatAvailability classSeatAvailability3(FlightBooking::business, std::vector<Seat>({Seat("s5", 1233.0), Seat("s6", 1233.0)}), std::vector<Seat>({Seat("s7", 4233.0), Seat("s8", 4233.0)}));
  BOOST_CHECK_EQUAL(manager->updateClassSeatAvailability("id1", classSeatAvailability1), 0);
  BOOST_CHECK_EQUAL(manager->add(flightDetails), 1);
  BOOST_CHECK_EQUAL(manager->updateClassSeatAvailability("id1", classSeatAvailability1), 0);
  BOOST_CHECK_EQUAL(manager->addClassSeatAvailability("id1", classSeatAvailability2), 1);
  BOOST_CHECK_EQUAL(manager->updateClassSeatAvailability("id1", classSeatAvailability3), 1);
  SearchResponse searchResponse = manager->search(FlightBooking::ahmedabad, FlightBooking::chennai);
  std::vector<FlightDetails> results = searchResponse.getResults();
  BOOST_CHECK_EQUAL(searchResponse.getTotalCount(), 1);
  for (int i = 0; i < results.size(); i++)
  {
    BOOST_CHECK_EQUAL(results[i].getId() == "id1", 1);
  }
}

BOOST_AUTO_TEST_CASE(UpdateAvailabilitySuccess)
{
  FlightBookingManager *manager = new FlightBookingManagerImpl();
  FlightDetails flightDetails("id1", "flight1", FlightBooking::goair, FlightBooking::ahmedabad, FlightBooking::chennai, std::vector<ClassSeatAvailability>());
  ClassSeatAvailability classSeatAvailability1(FlightBooking::economy, std::vector<Seat>({Seat("s1", 1233.0), Seat("s2", 1233.0)}), std::vector<Seat>({Seat("s3", 4233.0), Seat("s4", 4233.0)}));
  ClassSeatAvailability classSeatAvailability2(FlightBooking::business, std::vector<Seat>({Seat("s1", 1233.0), Seat("s2", 1233.0)}), std::vector<Seat>({Seat("s3", 4233.0), Seat("s4", 4233.0)}));
  ClassSeatAvailability classSeatAvailability3(FlightBooking::business, std::vector<Seat>({Seat("s5", 1233.0), Seat("s6", 1233.0)}), std::vector<Seat>({Seat("s7", 4233.0), Seat("s8", 4233.0)}));
  BOOST_CHECK_EQUAL(manager->updateClassSeatAvailability("id1", classSeatAvailability1), 0);
  BOOST_CHECK_EQUAL(manager->add(flightDetails), 1);
  BOOST_CHECK_EQUAL(manager->addClassSeatAvailability("id1", classSeatAvailability2), 1);
  BOOST_CHECK_EQUAL(manager->updateClassSeatAvailability("id1", classSeatAvailability3), 1);
}

BOOST_AUTO_TEST_CASE(RemoveAvailabilityFailure)
{
  FlightBookingManager *manager = new FlightBookingManagerImpl();
  FlightDetails flightDetails("id1", "flight1", FlightBooking::goair, FlightBooking::ahmedabad, FlightBooking::chennai, std::vector<ClassSeatAvailability>());
  ClassSeatAvailability classSeatAvailability1(FlightBooking::economy, std::vector<Seat>({Seat("s1", 1233.0), Seat("s2", 1233.0)}), std::vector<Seat>({Seat("s3", 4233.0), Seat("s4", 4233.0)}));
  ClassSeatAvailability classSeatAvailability2(FlightBooking::business, std::vector<Seat>({Seat("s1", 1233.0), Seat("s2", 1233.0)}), std::vector<Seat>({Seat("s3", 4233.0), Seat("s4", 4233.0)}));
  ClassSeatAvailability classSeatAvailability3(FlightBooking::business, std::vector<Seat>({Seat("s5", 1233.0), Seat("s6", 1233.0)}), std::vector<Seat>({Seat("s7", 4233.0), Seat("s8", 4233.0)}));
  BOOST_CHECK_EQUAL(manager->removeClassSeatAvailability("id1", classSeatAvailability1), 0);
  BOOST_CHECK_EQUAL(manager->add(flightDetails), 1);
  BOOST_CHECK_EQUAL(manager->addClassSeatAvailability("id1", classSeatAvailability1), 1);
  BOOST_CHECK_EQUAL(manager->removeClassSeatAvailability("id1", classSeatAvailability3), 0);
}

BOOST_AUTO_TEST_CASE(RemoveAvailabilitySuccess)
{
  FlightBookingManager *manager = new FlightBookingManagerImpl();
  FlightDetails flightDetails("id1", "flight1", FlightBooking::goair, FlightBooking::ahmedabad, FlightBooking::chennai, std::vector<ClassSeatAvailability>());
  ClassSeatAvailability classSeatAvailability1(FlightBooking::economy, std::vector<Seat>({Seat("s1", 1233.0), Seat("s2", 1233.0)}), std::vector<Seat>({Seat("s3", 4233.0), Seat("s4", 4233.0)}));
  ClassSeatAvailability classSeatAvailability2(FlightBooking::business, std::vector<Seat>({Seat("s1", 1233.0), Seat("s2", 1233.0)}), std::vector<Seat>({Seat("s3", 4233.0), Seat("s4", 4233.0)}));
  ClassSeatAvailability classSeatAvailability3(FlightBooking::business, std::vector<Seat>({Seat("s5", 1233.0), Seat("s6", 1233.0)}), std::vector<Seat>({Seat("s7", 4233.0), Seat("s8", 4233.0)}));
  BOOST_CHECK_EQUAL(manager->removeClassSeatAvailability("id1", classSeatAvailability1), 0);
  BOOST_CHECK_EQUAL(manager->add(flightDetails), 1);
  BOOST_CHECK_EQUAL(manager->addClassSeatAvailability("id1", classSeatAvailability1), 1);
  BOOST_CHECK_EQUAL(manager->removeClassSeatAvailability("id1", classSeatAvailability1), 1);
}

BOOST_AUTO_TEST_CASE(BookSeatAvailabilitySuccess)
{
  FlightBookingManager *manager = new FlightBookingManagerImpl();
  FlightDetails flightDetails("id1", "flight1", FlightBooking::goair, FlightBooking::ahmedabad, FlightBooking::chennai, std::vector<ClassSeatAvailability>());
  ClassSeatAvailability classSeatAvailability1(FlightBooking::economy, std::vector<Seat>({Seat("s1", 1233.0), Seat("s2", 1233.0)}), std::vector<Seat>({Seat("s3", 4233.0), Seat("s4", 4233.0)}));
  ClassSeatAvailability classSeatAvailability2(FlightBooking::business, std::vector<Seat>({Seat("s1", 1233.0), Seat("s2", 1233.0)}), std::vector<Seat>({Seat("s3", 4233.0), Seat("s4", 4233.0)}));
  ClassSeatAvailability classSeatAvailability3(FlightBooking::business, std::vector<Seat>({Seat("s5", 1233.0), Seat("s6", 1233.0)}), std::vector<Seat>({Seat("s7", 4233.0), Seat("s8", 4233.0)}));
  BOOST_CHECK_EQUAL(manager->add(flightDetails), 1);
  BOOST_CHECK_EQUAL(manager->addClassSeatAvailability("id1", classSeatAvailability2), 1);
  BOOST_CHECK_EQUAL(manager->bookSeat("id1", FlightBooking::business), 1);
  BOOST_CHECK_EQUAL(manager->bookSeat("id1", FlightBooking::business), 1);
}

BOOST_AUTO_TEST_CASE(BookSeatAvailabilityFailure)
{
  FlightBookingManager *manager = new FlightBookingManagerImpl();
  FlightDetails flightDetails("id1", "flight1", FlightBooking::goair, FlightBooking::ahmedabad, FlightBooking::chennai, std::vector<ClassSeatAvailability>());
  ClassSeatAvailability classSeatAvailability1(FlightBooking::economy, std::vector<Seat>({Seat("s1", 1233.0), Seat("s2", 1233.0)}), std::vector<Seat>({Seat("s3", 4233.0), Seat("s4", 4233.0)}));
  ClassSeatAvailability classSeatAvailability2(FlightBooking::business, std::vector<Seat>({Seat("s1", 1233.0), Seat("s2", 1233.0)}), std::vector<Seat>({Seat("s3", 4233.0), Seat("s4", 4233.0)}));
  ClassSeatAvailability classSeatAvailability3(FlightBooking::business, std::vector<Seat>({Seat("s5", 1233.0), Seat("s6", 1233.0)}), std::vector<Seat>({Seat("s7", 4233.0), Seat("s8", 4233.0)}));
  BOOST_CHECK_EQUAL(manager->add(flightDetails), 1);
  BOOST_CHECK_EQUAL(manager->addClassSeatAvailability("id2", classSeatAvailability2), 0);
  BOOST_CHECK_EQUAL(manager->bookSeat("id2", FlightBooking::business), 0);
  BOOST_CHECK_EQUAL(manager->bookSeat("id2", FlightBooking::business), 0);
  BOOST_CHECK_EQUAL(manager->addClassSeatAvailability("id2", classSeatAvailability1), 0);
  BOOST_CHECK_EQUAL(manager->bookSeat("id1", FlightBooking::economy), 0);
}

BOOST_AUTO_TEST_CASE(BookSeatNonExistent)
{
  FlightBookingManager *manager = new FlightBookingManagerImpl();
  FlightDetails flightDetails("id1", "flight1", FlightBooking::goair, FlightBooking::ahmedabad, FlightBooking::chennai, std::vector<ClassSeatAvailability>());
  ClassSeatAvailability classSeatAvailability1(FlightBooking::economy, std::vector<Seat>({Seat("s1", 1233.0), Seat("s2", 1233.0)}), std::vector<Seat>({Seat("s3", 4233.0), Seat("s4", 4233.0)}));
  ClassSeatAvailability classSeatAvailability2(FlightBooking::business, std::vector<Seat>({Seat("s1", 1233.0), Seat("s2", 1233.0)}), std::vector<Seat>({Seat("s3", 4233.0), Seat("s4", 4233.0)}));
  ClassSeatAvailability classSeatAvailability3(FlightBooking::business, std::vector<Seat>({Seat("s5", 1233.0), Seat("s6", 1233.0)}), std::vector<Seat>({Seat("s7", 4233.0), Seat("s8", 4233.0)}));
  BOOST_CHECK_EQUAL(manager->add(flightDetails), 1);
  BOOST_CHECK_EQUAL(manager->addClassSeatAvailability("id1", classSeatAvailability2), 1);
  BOOST_CHECK_EQUAL(manager->bookSeat("id1", FlightBooking::business), 1);
  BOOST_CHECK_EQUAL(manager->bookSeat("id1", FlightBooking::business), 1);
  BOOST_CHECK_EQUAL(manager->bookSeat("id1", FlightBooking::business), 0);
  BOOST_CHECK_EQUAL(manager->bookSeat("id1", FlightBooking::business), 0);
}

BOOST_AUTO_TEST_CASE(SearchNonExistent)
{
  FlightBookingManager *manager = new FlightBookingManagerImpl();
  FlightDetails flightDetails("id1", "flight1", FlightBooking::goair, FlightBooking::ahmedabad, FlightBooking::chennai, std::vector<ClassSeatAvailability>());
  ClassSeatAvailability classSeatAvailability3(FlightBooking::business, std::vector<Seat>({Seat("s5", 1233.0), Seat("s6", 1233.0)}), std::vector<Seat>({Seat("s7", 4233.0), Seat("s8", 4233.0)}));
  BOOST_CHECK_EQUAL(manager->add(flightDetails), 1);
  BOOST_CHECK_EQUAL(manager->addClassSeatAvailability("id1", classSeatAvailability3), 1);
  BOOST_CHECK_EQUAL(manager->search(FlightBooking::bangalore, FlightBooking::delhi).getTotalCount(), 0);
}

BOOST_AUTO_TEST_CASE(SearchOnlySourcePresentSuccess)
{
  FlightBookingManager *manager = new FlightBookingManagerImpl();
  FlightDetails flightDetails("id1", "flight1", FlightBooking::goair, FlightBooking::ahmedabad, FlightBooking::chennai, std::vector<ClassSeatAvailability>());
  ClassSeatAvailability classSeatAvailability3(FlightBooking::business, std::vector<Seat>({Seat("s5", 1233.0), Seat("s6", 1233.0)}), std::vector<Seat>({Seat("s7", 4233.0), Seat("s8", 4233.0)}));
  BOOST_CHECK_EQUAL(manager->add(flightDetails), 1);
  BOOST_CHECK_EQUAL(manager->addClassSeatAvailability("id1", classSeatAvailability3), 1);
  BOOST_CHECK_EQUAL(manager->search(FlightBooking::ahmedabad, FlightBooking::delhi).getTotalCount(), 0);
}

BOOST_AUTO_TEST_CASE(SearchOnlyDestinationPresentSuccess)
{
  FlightBookingManager *manager = new FlightBookingManagerImpl();
  FlightDetails flightDetails("id1", "flight1", FlightBooking::goair, FlightBooking::ahmedabad, FlightBooking::chennai, std::vector<ClassSeatAvailability>());
  ClassSeatAvailability classSeatAvailability3(FlightBooking::business, std::vector<Seat>({Seat("s5", 1233.0), Seat("s6", 1233.0)}), std::vector<Seat>({Seat("s7", 4233.0), Seat("s8", 4233.0)}));
  BOOST_CHECK_EQUAL(manager->add(flightDetails), 1);
  BOOST_CHECK_EQUAL(manager->addClassSeatAvailability("id1", classSeatAvailability3), 1);
  BOOST_CHECK_EQUAL(manager->search(FlightBooking::chennai, FlightBooking::ahmedabad).getTotalCount(), 0);
}

BOOST_AUTO_TEST_CASE(SearchFailureTest)
{
  FlightBookingManager *manager = new FlightBookingManagerImpl();
  FlightDetails flightDetails("id1", "flight1", FlightBooking::goair, FlightBooking::ahmedabad, FlightBooking::chennai, std::vector<ClassSeatAvailability>());
  ClassSeatAvailability classSeatAvailability3(FlightBooking::business, std::vector<Seat>({Seat("s5", 1233.0), Seat("s6", 1233.0)}), std::vector<Seat>({Seat("s7", 4233.0), Seat("s8", 4233.0)}));
  BOOST_CHECK_EQUAL(manager->search(FlightBooking::chennai, FlightBooking::ahmedabad).getTotalCount(), 0);
  BOOST_CHECK_EQUAL(manager->add(flightDetails), 1);
  BOOST_CHECK_EQUAL(manager->addClassSeatAvailability("id1", classSeatAvailability3), 1);
  BOOST_CHECK_EQUAL(manager->search(FlightBooking::chennai, FlightBooking::chennai).getTotalCount(), 0);
}

BOOST_AUTO_TEST_CASE(SearchSuccessTest)
{
  FlightBookingManager *manager = new FlightBookingManagerImpl();
  FlightDetails flightDetails1("id1", "flight1", FlightBooking::goair, FlightBooking::ahmedabad, FlightBooking::chennai, std::vector<ClassSeatAvailability>());
  FlightDetails flightDetails2("id2", "flight2", FlightBooking::goair, FlightBooking::ahmedabad, FlightBooking::chennai, std::vector<ClassSeatAvailability>());
  FlightDetails flightDetails3("id3", "flight1", FlightBooking::goair, FlightBooking::delhi, FlightBooking::jaipur, std::vector<ClassSeatAvailability>());
  FlightDetails flightDetails4("id4", "flight2", FlightBooking::goair, FlightBooking::kolkata, FlightBooking::chennai, std::vector<ClassSeatAvailability>());
  ClassSeatAvailability classSeatAvailability3(FlightBooking::business, std::vector<Seat>({Seat("s5", 1233.0), Seat("s6", 1233.0)}), std::vector<Seat>({Seat("s7", 4233.0), Seat("s8", 4233.0)}));
  BOOST_CHECK_EQUAL(manager->add(flightDetails1), 1);
  BOOST_CHECK_EQUAL(manager->add(flightDetails2), 1);
  BOOST_CHECK_EQUAL(manager->add(flightDetails3), 1);
  BOOST_CHECK_EQUAL(manager->add(flightDetails4), 1);
  BOOST_CHECK_EQUAL(manager->addClassSeatAvailability("id1", classSeatAvailability3), 1);
  BOOST_CHECK_EQUAL(manager->addClassSeatAvailability("id2", classSeatAvailability3), 1);
  SearchResponse searchResponse = manager->search(FlightBooking::ahmedabad, FlightBooking::chennai);
  BOOST_CHECK_EQUAL(searchResponse.getTotalCount(), 2);
  std::vector<FlightDetails> results = searchResponse.getResults();
  for (int i = 0; i < results.size(); i++)
  {
    BOOST_CHECK_EQUAL(results[i].getId() == "id1" || results[i].getId() == "id2", 1);
  }
  SearchResponse searchResponse2 = manager->search(FlightBooking::kolkata, FlightBooking::chennai);
  std::vector<FlightDetails> results2 = searchResponse2.getResults();
  BOOST_CHECK_EQUAL(searchResponse2.getTotalCount(), 1);
  for (int i = 0; i < results2.size(); i++)
  {
    BOOST_CHECK_EQUAL(results2[i].getId() == "id4", 1);
  }
}

BOOST_AUTO_TEST_SUITE_END()