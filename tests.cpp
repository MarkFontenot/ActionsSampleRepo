#include "catch.hpp"

#include <cstring>
#include "DSVector.h"
#include "DSString.h"


TEST_CASE("Vector class", "[vector]") {

    DSVector<DSString> vector1;
    vector1.append(DSString((char *) "testString"));
    vector1.append(DSString((char *) "a test string"));
    vector1.append(DSString((char *) ""));
    vector1.append(DSString((char *) "THIS IS AN UPPERCASE STRING"));
    vector1.append(DSString((char *) "this is an uppercase string"));
    vector1.append(DSString((char *) "\n"));
    vector1.append(DSString((char *) ""));
    vector1.append(DSString((char *) "  split  split  split  "));
    vector1.append(DSString((char *) "                          "));
    vector1.append(DSString((char *) "testString"));

    DSVector<DSString> vector2;
    vector2.append(DSString((char *) "testString"));
    vector2.append(DSString((char *) "a test string"));
    vector2.append(DSString((char *) ""));
    vector2.append(DSString((char *) "THIS IS AN UPPERCASE STRING"));
    vector2.append(DSString((char *) "this is an uppercase string"));
    vector2.append(DSString((char *) "\n"));
    vector2.append(DSString((char *) ""));
    vector2.append(DSString((char *) "  split  split  split  "));
    vector2.append(DSString((char *) "                          "));
    vector2.append(DSString((char *) "testString"));
    vector2.append(DSString((char *) "An extra string"));


    DSVector<int> vector3;
    vector3.append(1);
    vector3.append(2);
    vector3.append(5);
    vector3.append(10);
    vector3.append(100);
    vector3.append(23);
    vector3.append(13241);
    vector3.append(3);
    vector3.append(65);
    vector3.append(76);

    DSVector<char *> vector4;
    vector4.append((char *) "testString");
    vector4.append((char *) "a test string");
    vector4.append((char *) "");
    vector4.append((char *) "THIS IS AN UPPERCASE STRING");
    vector4.append((char *) "this is an uppercase string");
    vector4.append((char *) "\n");
    vector4.append((char *) "");
    vector4.append((char *) " split split split ");
    vector4.append((char *) "                          ");
    vector4.append((char *) "testString");

//    SECTION("Equality operators") {
//        REQUIRE((s[0] == DSString((char *) "testString")));
//        REQUIRE((s[0] == s[9]));
//        REQUIRE((s[2] == (char *) ""));
//        REQUIRE((s[1] == (char *) "a test string"));
//        REQUIRE((!(s[3] == s[4])));
//    }
//
//    SECTION("Assignment operators") {
//        DSString str;
//        str = "a test string";
//        REQUIRE((str == s[1]));
//        str = DSString((char *) "testString");
//        REQUIRE((str == s[0]));
//        str = "";
//        REQUIRE((str == s[6]));
//        str = DSString((char *) "\n");
//        REQUIRE((str == s[5]));
//    }
//
//    SECTION("Addition operator") {
//        REQUIRE((DSString((char *) "testStringtestString") == s[0] + s[9]));
//        REQUIRE((s[6] + s[6] == (char *) ""));
//        REQUIRE((s[5] + s[6] == DSString((char *) "\n")));
//        REQUIRE((s[0] + s[1] + s[2] == (char *) "testStringa test string"));
//    }

//    SECTION("Greater than operator") {
//        REQUIRE(s[0] > s[1]);
//        REQUIRE(s[4] > s[3]);
//        REQUIRE(s[9] > s[6]);
//        REQUIRE(s[7] > s[6]);
//    }

    SECTION("Is Empty"){
        DSVector<DSString> temp;
        REQUIRE(temp.isEmpty() == true);
        DSString x((char *)"hello");
        temp.append(x);
        REQUIRE(temp.isEmpty() == false);
        temp.removeAt(0);
        REQUIRE(temp.isEmpty() == true);
    }

    SECTION("Clear all"){
        vector1.clear();
        REQUIRE(vector1.isEmpty() == true);
        REQUIRE(vector1.getSize() == 0);
        vector2.clear();
        REQUIRE(vector2.isEmpty() == true);
        REQUIRE(vector2.getSize() == 0);
        vector3.clear();
        REQUIRE(vector3.isEmpty() == true);
        REQUIRE(vector3.getSize() == 0);
        vector4.clear();
        REQUIRE(vector4.isEmpty() == true);
        REQUIRE(vector4.getSize() == 0);

        DSVector<DSString> temp;
        temp.clear();
        REQUIRE(temp.isEmpty() == true);
        REQUIRE(temp.getSize() == 0);
    }

    SECTION("Find") {
        DSString str;

        str = "testString";
        REQUIRE((vector1.find(str) == true));
        str = "hello";
        REQUIRE((vector1.find(str) == false));

        str = "Stringtest";
        REQUIRE((vector1.find(str) == false));

        str = "a test strin";
        REQUIRE((vector1.find(str) == false));

        REQUIRE((vector3.find(3) == true));
        REQUIRE((vector3.find(23) == true));
        REQUIRE((vector3.find(76) == true));
        REQUIRE((vector3.find(1) == true));

        REQUIRE((vector4.find((char*)"testString") == true));
        REQUIRE((vector4.find((char*)"hello") == false));
        REQUIRE((vector4.find((char*)"Stringtest") == false));
        REQUIRE((vector4.find((char*)"a test strin") == false));
    }

        //DONE
    SECTION("[] Operator") {
        DSString temp((char *) "testString");
        REQUIRE((vector1[0] == temp));
        REQUIRE((vector2[0] == temp));
        char * temp2 = (char *)"testString";

        REQUIRE((vector4[0] == temp2));

        temp = (char *)"testString";
        REQUIRE((vector1[vector1.getSize() - 1] == temp));
        temp2 = (char *)"testString";
        REQUIRE((vector4[vector4.getSize() - 1]  == temp2));
        temp = (char *)"An extra string";
        REQUIRE((vector2[vector2.getSize() - 1] == temp));


        REQUIRE((vector3[0] == 1));
        REQUIRE((vector3[5] == 23));
        REQUIRE((vector3[vector3.getSize() - 1] == 76));
    }


    SECTION("== operator"){
        DSVector<DSString> temp;
        temp = vector1;
        REQUIRE((vector1 == temp));
    }
    //DONE
    SECTION("getLength function") {
        REQUIRE((vector1.getSize() == 10));
        REQUIRE((vector2.getSize() == 11));
        REQUIRE((vector3.getSize() == 10));
        REQUIRE((vector4.getSize() == 10));
    }

    SECTION("Sort"){
        vector1.sort();
        vector2.sort();
        vector3.sort();
        vector4.sort();
        DSString temp;
        temp = "";

        REQUIRE((vector1[0] == temp));

        REQUIRE((vector1[1] == temp));
        temp = "\n";
        REQUIRE((vector1[2] == temp));
        temp = "                          ";
        REQUIRE((vector1[3] == temp));
        temp = "  split  split  split  ";
        REQUIRE((vector1[4] == temp));
        temp = "THIS IS AN UPPERCASE STRING";
        REQUIRE((vector1[5] == temp));
        temp = "a test string";
        REQUIRE((vector1[6] == temp));
        temp = "testString";
        REQUIRE((vector1[7] == temp));
        temp = "testString";
        REQUIRE((vector1[8] == temp));
        temp = "this is an uppercase string";
        REQUIRE((vector1[9] == temp));
        char * temp2;
        temp2 = (char *)"";

        REQUIRE((vector1[0] == temp2));

        REQUIRE((vector1[1] == temp2));
        temp2 = (char *)"\n";
        REQUIRE((vector1[2] == temp2));
        temp2 = (char *)"                          ";
        REQUIRE((vector1[3] == temp2));
        temp2 = (char *)"  split  split  split  ";
        REQUIRE((vector1[4] == temp2));
        temp2 = (char *)"THIS IS AN UPPERCASE STRING";
        REQUIRE((vector1[5] == temp2));
        temp2 = (char *)"a test string";
        REQUIRE((vector1[6] == temp2));
        temp2 = (char *)"testString";
        REQUIRE((vector1[7] == temp2));
        temp2 = (char *)"testString";
        REQUIRE((vector1[8] == temp2));
        temp2 = (char *)"this is an uppercase string";
        REQUIRE((vector1[9] == temp2));


        REQUIRE(vector3[0] == 1);
        REQUIRE(vector3[1] == 2);
        REQUIRE(vector3[2] == 3);
        REQUIRE(vector3[3] == 5);
        REQUIRE(vector3[4] == 10);
        REQUIRE(vector3[5] == 23);
        REQUIRE(vector3[6] == 65);
        REQUIRE(vector3[7] == 76);
        REQUIRE(vector3[8] == 100);
        REQUIRE(vector3[9] == 13241);

        DSVector<DSString> tempVec;
        tempVec.sort();
        REQUIRE(tempVec.isEmpty() == true);

    }

    SECTION("Remove at"){
        vector2.removeAt(vector2.getSize() - 1);
        REQUIRE((vector1 == vector2));

        DSVector<int> temp;
        temp.append(1);
        temp.removeAt(0);
        REQUIRE((temp.isEmpty() == true));


        vector4.removeAt(3);
        REQUIRE((vector4.getSize() == 9));
        REQUIRE((vector4[3] == (char *)"this is an uppercase string"));
        REQUIRE((vector4[4] == (char *)"\n"));
        REQUIRE((vector4[5] == (char *)""));
        REQUIRE((vector4[6] == (char *)" split split split "));
        REQUIRE((vector4[7] == (char *)"                          "));
        REQUIRE((vector4[8] == (char *)"testString"));
    }

//    SECTION("Substring function") {
//        REQUIRE((s[0].substring(0, 5) == (char *) "testS"));
//        REQUIRE((s[4].substring(0, 4) == (char *) "this"));
//        REQUIRE((s[4].substring(1, 4) == (char *) "his"));
//    }
//
//    SECTION("c_str function") {
//        REQUIRE(strcmp(s[0].c_str(), "testString") == 0);
//        REQUIRE(strcmp(s[9].c_str(), s[0].c_str()) == 0);
//        REQUIRE(strcmp(s[2].c_str(), "") == 0);
//    }
//
//    SECTION("Find"){
//        DSString str;
//        str = "testString";
//        REQUIRE((s.find(str) == true));
//        str = "ring";
//        REQUIRE((s.find(str) == false));
//    }

        //DONE
    SECTION("Edit"){

        DSString str;
        str = "changed";
        vector1.edit(str,0);
        REQUIRE((vector1[0] == str));

        str = "changed";
        vector2.edit(str,vector2.getSize() - 1);
        REQUIRE((vector2[vector2.getSize() - 1] == str));

        int x = 813;
        vector3.edit(x,2);
        REQUIRE((vector3[2] == x));

        char * temp = (char *)"this element was changed";
        vector4.edit(temp, 6);
        REQUIRE((vector4[6] == temp));
    }

//    SECTION("Get Size"){
//        REQUIRE(s.getSize() == 10);
//    }
//
//
//        //NEEDS to get done
//    SECTION("Clear all"){
//        REQUIRE((s.isEmpty() == false));
//        s.clear();
//        REQUIRE((s.isEmpty() == true));
//    }
//
//    SECTION("Clear"){
//        s.clear();
//        REQUIRE(s.getSize() == 0);
//    }
}

TEST_CASE("String class", "[string]"){
    DSString s[11];
    s[0] = DSString((char *)"testString");
    s[1] = DSString((char *)"a test string");
    s[2] = DSString((char *)"");
    s[3] = DSString((char *)"THIS IS AN UPPERCASE STRING");
    s[4] =DSString((char *)"this is an uppercase string");
    s[5] =DSString((char *)"\n");
    s[6] =DSString((char *)"");
    s[7] =DSString((char *)"   split   split   split   ");
    s[8] =DSString((char *)"                          ");
    s[9] =DSString((char *)"testString");
    s[10] =DSString((char *)"test, String, is,here,");

    SECTION("Equality operators"){
        REQUIRE((s[0] == DSString((char *)"testString")));
        REQUIRE((s[0] == s[9]));
        REQUIRE((s[2] == (char *)""));
        REQUIRE((s[1] == (char *)"a test string"));
        REQUIRE((!(s[3] == s[4])));
    }

    SECTION("Assignment operators"){
        DSString str;
        str = "a test string";
        REQUIRE((str == s[1]));
        str =DSString((char *)"testString");
        REQUIRE((str == s[0]));
        str = "";
        REQUIRE((str == s[6]));
        str = DSString((char *)"\n");
        REQUIRE((str == s[5]));

        str = 5;
        REQUIRE((str == (char *)"5"));
        str = 10;
        REQUIRE((str == (char *)"10"));
        str = 0;
        REQUIRE((str == (char *)"0"));
    }

    SECTION("Addition operator"){
        REQUIRE((DSString((char *)"testStringtestString") == s[0]+s[9]));
        REQUIRE((s[6] + s[6] == (char *)""));
        REQUIRE((s[5] + s[6] ==DSString((char *)"\n")));
        REQUIRE((s[0] + s[1] + s[2] == (char *)"testStringa test string"));

        //char
        char c;
        //c = ' ';
        //REQUIRE(((s[4] + c) == (char *)"this is an uppercase string "));
        //c = 'h';
        //REQUIRE((s[4] + c == (char *)"this is an uppercase stringh"));
    }

    SECTION("Greater than operator"){
        REQUIRE(s[0] > s[1]);
        REQUIRE(s[4] > s[3]);
        REQUIRE(s[9] > s[6]);
        REQUIRE(s[7] > s[6]);
    }

    SECTION("Contains"){
        DSString str;
        DSString str2;
        str = "ring";
        REQUIRE((s[0].contains(str) == 6));
        str = "hello";
        REQUIRE((s[0].contains(str) == -1));
        REQUIRE((s[0].contains(s[9]) == 0));
        str = "Stringtest";
        REQUIRE((s[0].contains(str) == -1));
        str = "helloljher23re";
        str2 = "ljher";
        REQUIRE((str.contains(str2) == 5));
    }

    SECTION("[] Operator"){
        REQUIRE(s[0][1] == 'e');
        REQUIRE(s[4][4] == ' ');
        REQUIRE(s[6][0] == 0);
        REQUIRE(s[0][100] == 'g');
    }

    SECTION("getLength function"){
        REQUIRE(s[9].getLength() == 10);
        REQUIRE(s[2].getLength() == 0);
        REQUIRE(s[8].getLength() == 26);
        REQUIRE(s[3].getLength() == 27);
    }

    SECTION("Substring function"){
        REQUIRE((s[0].substring(0, 5) == (char *)"testS"));
        REQUIRE((s[4].substring(0, 4) == (char *)"this"));
        REQUIRE((s[4].substring(1, 4) == (char *)"his"));
    }

    SECTION("c_str function"){
        REQUIRE(strcmp(s[0].c_str(), "testString") == 0);
        REQUIRE(strcmp(s[9].c_str(), s[0].c_str()) == 0);
        REQUIRE(strcmp(s[2].c_str(), "") == 0);
    }

    SECTION("lowercase"){
        s[3].lowercase();
        REQUIRE((s[3] == s[4]));

        s[4].lowercase();
        REQUIRE((s[4] == s[4]));

        s[6].lowercase();
        REQUIRE((s[6] == s[6]));
    }

    SECTION("Split"){
        char *spliter = (char *)" ";
        DSVector<DSString> y;
        DSString x;
        x = "split";
        y.append(x);
        y.append(x);
        y.append(x);
        DSVector<DSString> temp;
        temp = s[7].split(spliter);
        REQUIRE((y == temp));
        y.clear();
        x = "test";
        y.append(x);
        x = "String";
        y.append(x);
        x = "is";
        y.append(x);
        x = "here";
        y.append(x);
        char * spliter2 = (char *)", ";
        REQUIRE((y == s[10].split(spliter2)));
        y.clear();
        REQUIRE((y == s[6].split(spliter2)));
        REQUIRE((y == s[6].split(spliter)));
        y.append(s[0]);
        char * spliter3 = (char *)"";
        REQUIRE((y == s[0].split(spliter3)));





    }

    //DSString int constructor


}
