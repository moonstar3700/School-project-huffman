#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include "data/frequency-table.h"

std::vector<char> charvector = { 'a' ,'b', 'b', 'c', 'c', 'c' , 'd', 'd' , 'd' , 'd' };
std::vector<int> intvector = { 1 ,2, 2, 3, 3, 3 , 4, 4 , 4 , 4 };
std::vector<char> LongNull = { NULL,NULL,NULL,NULL,NULL, NULL,NULL,NULL,NULL,NULL, NULL,NULL,NULL,NULL,NULL, NULL,NULL,NULL,NULL,NULL, NULL,NULL,NULL,NULL,NULL, NULL,NULL,NULL,NULL,NULL, };

TEST_CASE("FrequencyTable tests") {


    data::FrequencyTable<char> charfreq;
    charfreq.increment('a');
    REQUIRE(charfreq['a'] == 1);
    charfreq.increment('a');
    REQUIRE(charfreq['a'] == 2);
    REQUIRE(charfreq['b'] == 0);
    charfreq.increment('b');
    REQUIRE(charfreq['b'] == 1);

    REQUIRE(charfreq.values().size() == 2);

    charfreq = data::count_frequencies(charvector);
    REQUIRE(charfreq['a'] == 1);
    REQUIRE(charfreq['b'] == 2);
    REQUIRE(charfreq['c'] == 3);
    REQUIRE(charfreq['d'] == 4);


    data::FrequencyTable<int> intfreq;

    REQUIRE(intfreq[1] == 0);
    REQUIRE(intfreq[2] == 0);
    REQUIRE(intfreq[3] == 0);
    intfreq.increment(1);
    REQUIRE(intfreq[1] == 1);
    intfreq.increment(1);
    REQUIRE(intfreq[1] == 2);
    intfreq.increment(2);
    REQUIRE(intfreq[2] == 1);
    REQUIRE(intfreq[3] == 0);

    REQUIRE(intfreq.values().size() == 3);


    intfreq = data::count_frequencies(intvector);
    REQUIRE(intfreq[1] == 1);
    REQUIRE(intfreq[2] == 2);
    REQUIRE(intfreq[3] == 3);
    REQUIRE(intfreq[4] == 4);

    data::FrequencyTable<std::string> stringfreq;

    REQUIRE(stringfreq.values().size() == 0);

    REQUIRE(stringfreq["a"] == 0);
    REQUIRE(stringfreq["A"] == 0);
    REQUIRE(stringfreq["AA"] == 0);
    REQUIRE(stringfreq["aa"] == 0);
    REQUIRE(stringfreq["a "] == 0);
    REQUIRE(stringfreq[" a"] == 0);
    stringfreq.increment("a");
    REQUIRE(stringfreq["a"] == 1);

    REQUIRE(stringfreq.values().size() == 6);

    data::FrequencyTable<char> freqnull = data::count_frequencies(LongNull);
    REQUIRE(freqnull[NULL] == 30);


}