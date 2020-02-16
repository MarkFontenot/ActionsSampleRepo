#include "catch.hpp"

#include <cstring>
#include "DSVector.h"
#include "DSString.h"


TEST_CASE("Vector class", "[vector]") {

    DSVector<DSString> s;
    s.append(DSString((char *) "testString"));
    s.append(DSString((char *) "a test string"));
    s.append(DSString((char *) ""));
    s.append(DSString((char *) "THIS IS AN UPPERCASE STRING"));
    s.append(DSString((char *) "this is an uppercase string"));
    s.append(DSString((char *) "\n"));
    s.append(DSString((char *) ""));
    s.append(DSString((char *) "  split  split  split  "));
    s.append(DSString((char *) "                          "));
    s.append(DSString((char *) "testString"));

    SECTION("Equality operators") {
        REQUIRE((s[0] == DSString((char *) "testString")));
        REQUIRE((s[0] == s[9]));
        REQUIRE((s[2] == (char *) ""));
        REQUIRE((s[1] == (char *) "a test string"));
        REQUIRE((!(s[3] == s[4])));
    }

    SECTION("Assignment operators") {
        DSString str;
        str = "a test string";
        REQUIRE((str == s[1]));
        str = DSString((char *) "testString");
        REQUIRE((str == s[0]));
        str = "";
        REQUIRE((str == s[6]));
        str = DSString((char *) "\n");
        REQUIRE((str == s[5]));
    }

    SECTION("Addition operator") {
        REQUIRE((DSString((char *) "testStringtestString") == s[0] + s[9]));
        REQUIRE((s[6] + s[6] == (char *) ""));
        REQUIRE((s[5] + s[6] == DSString((char *) "\n")));
        REQUIRE((s[0] + s[1] + s[2] == (char *) "testStringa test string"));
    }

    SECTION("Greater than operator") {
        REQUIRE(s[0] > s[1]);
        REQUIRE(s[4] > s[3]);
        REQUIRE(s[9] > s[6]);
        REQUIRE(s[7] > s[6]);
    }

    SECTION("Contains") {
        DSString str;
        DSString str2;

        str = "ring";
        REQUIRE((s[0].contains(str) != -1));
        str = "hello";
        REQUIRE((s[0].contains(str) == -1));
        //REQUIRE((s[0].contains(s[9]) != -1));
        str = "Stringtest";
        REQUIRE((s[0].contains(str) == -1));
        str = "helloljher23re";
        str2 = "ljher";
        REQUIRE(str.contains(str2) != -1);
    }

    SECTION("[] Operator") {
        REQUIRE(s[0][1] == 'e');
        REQUIRE(s[4][4] == ' ');
        REQUIRE(s[6][0] == 0);
        REQUIRE(s[0][100] == 'g');
    }

    SECTION("getLength function") {
        REQUIRE(s[9].getLength() == 10);
        REQUIRE(s[2].getLength() == 0);
        REQUIRE(s[8].getLength() == 26);
        REQUIRE(s[3].getLength() == 27);
    }

    SECTION("Substring function") {
        REQUIRE((s[0].substring(0, 5) == (char *) "testS"));
        REQUIRE((s[4].substring(0, 4) == (char *) "this"));
        REQUIRE((s[4].substring(1, 4) == (char *) "his"));
    }

    SECTION("c_str function") {
        REQUIRE(strcmp(s[0].c_str(), "testString") == 0);
        REQUIRE(strcmp(s[9].c_str(), s[0].c_str()) == 0);
        REQUIRE(strcmp(s[2].c_str(), "") == 0);
    }

    SECTION("Find"){
        DSString str;
        str = "testString";
        REQUIRE((s.find(str) == true));
        str = "ring";
        REQUIRE((s.find(str) == false));
    }

    SECTION("Edit"){
        DSString str;
        str = "changed";
        s.edit(str,0);
        REQUIRE((s[0] == str));
    }

    SECTION("Get Size"){
        REQUIRE(s.getSize() == 10);
    }

    SECTION("Is Empty"){
        REQUIRE((s.isEmpty() == false));
        s.clear();
        REQUIRE((s.isEmpty() == true));
    }

    SECTION("Clear"){
        s.clear();
        REQUIRE(s.getSize() == 0);
    }
}