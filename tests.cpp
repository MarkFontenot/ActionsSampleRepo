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

    SECTION("Append"){
        DSVector<DSString> temp;
        DSString x;
        x = "hello";
        temp.append(x);
        REQUIRE((temp[0] == x));
        x = "another test";
        temp.append(x);
        REQUIRE((temp[1] == x));


        DSVector<int> temp2;
        temp2.append(3);
        REQUIRE(temp2[0] == 3);
        temp2.append(-23);
        REQUIRE(temp2[1] == -23);


        DSVector<char *> temp3;
        temp3.append((char *)"hello");
        REQUIRE(temp3[0] == (char *)"hello");
        temp3.append((char *)"hello again");
        REQUIRE(temp3[1] == (char *)"hello again");
    }

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

        try{
            vector1[vector1.getSize()];
        }catch(exception & e){
            REQUIRE(strcmp(e.what(),(char *)"out of range in [] function") == 0);
        }
        try{
            vector1[-1];
        }catch(exception & e){
            REQUIRE(strcmp(e.what(),(char *)"out of range in [] function") == 0);
        }
    }

    SECTION("== operator"){
        DSVector<DSString> temp;
        DSVector<DSString> temp1;
        temp = temp1;
        REQUIRE((temp1 == temp));

        temp = vector1;
        REQUIRE((vector1 == temp));
        temp = vector2;
        REQUIRE((vector2 == temp));

        DSVector<int> temp2;
        temp2 = vector3;
        REQUIRE((vector3 == temp2));
        DSVector<char *> temp3;
        temp3 = vector4;
        REQUIRE((vector4 == temp3));
    }

    SECTION("Get size function") {
        REQUIRE((vector1.getSize() == 10));
        REQUIRE((vector2.getSize() == 11));
        REQUIRE((vector3.getSize() == 10));
        REQUIRE((vector4.getSize() == 10));
        vector4.clear();
        REQUIRE((vector4.getSize() == 0));
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

        try{
            vector4.removeAt(-1);
        }catch(exception & e){
            REQUIRE(strcmp(e.what(),(char *)"out of range in removeAt function") == 0);
        }
        try{
            vector4.removeAt(1000);
        }catch(exception & e){
            REQUIRE(strcmp(e.what(),(char *)"out of range in removeAt function") == 0);
        }
    }

    SECTION("= operator"){
        vector1 = vector2;
        for(int x = 0; x < vector1.getSize();x++){
            REQUIRE((vector1[x] == vector2[x]));
        }
        vector2.clear();
        vector1 = vector2;
        REQUIRE((vector1.isEmpty() == true));
        REQUIRE((vector1.getSize() == 0));

        DSVector<int> vectInt;
        vectInt = vector3;
        for(int x = 0; x < vectInt.getSize();x++){
            REQUIRE((vectInt[x] == vector3[x]));
        }
        vector3.clear();
        vectInt = vector3;
        REQUIRE((vectInt.isEmpty() == true));
        REQUIRE((vectInt.getSize() == 0));

        DSVector<char *> vectChar;
        vectChar = vector4;
        for(int x = 0; x < vectChar.getSize();x++){
            REQUIRE((vectChar[x] == vector4[x]));
        }
        vector4.clear();
        vectChar = vector4;
        REQUIRE((vectChar.isEmpty() == true));
        REQUIRE((vectChar.getSize() == 0));
    }

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
        try{
            vector4.edit(temp, 1000);
        }catch(exception & e){
            REQUIRE(strcmp(e.what(),(char *)"out of range in edit function") == 0);
        }
        try{
            vector4.edit(temp, -1);
        }catch(exception & e){
            REQUIRE(strcmp(e.what(),(char *)"out of range in edit function") == 0);
        }
    }

}

TEST_CASE("String class", "[string]"){
    DSString s[16];
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
    s[11] = DSString((char *)"123");
    s[12] = DSString((char *)"0");
    s[13] = DSString((char *)"-5");
    s[14] = DSString((char *)"-5a");
    s[15] = DSString((char *)"a5");

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
        str = -5;
        REQUIRE((str == (char *)"-5"));

    }

    SECTION("Addition operator"){
        REQUIRE((DSString((char *)"testStringtestString") == s[0]+s[9]));
        REQUIRE((s[6] + s[6] == (char *)""));
        REQUIRE((s[5] + s[6] ==DSString((char *)"\n")));
        REQUIRE((s[0] + s[1] + s[2] == (char *)"testStringa test string"));
    }

    SECTION("Greater than operator"){
        REQUIRE(s[0] > s[1]);
        REQUIRE(s[4] > s[3]);
        REQUIRE(s[9] > s[6]);
        REQUIRE(s[7] > s[6]);
    }
    SECTION("Less than operator"){
        REQUIRE(s[1] < s[0]);
        REQUIRE(s[3] < s[4]);
        REQUIRE(s[6] < s[9]);
        REQUIRE(s[6] < s[7]);
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
        try{
            s[0][-1];
        }catch(exception & e){
            REQUIRE(strcmp(e.what(),(char *)"Index out of range in [] method") == 0);
        }
        try{
            s[0][1000];
        }catch(exception & e){
            REQUIRE(strcmp(e.what(),(char *)"Index out of range in [] method") == 0);
        }
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
        try{
            s[4].substring(-1, 4);
        }catch(exception & e){
            REQUIRE(strcmp(e.what(),(char *)"First index out of range in substring method") == 0);
        }
        try{
            s[4].substring(1, 1000);
        }catch(exception & e){
            REQUIRE(strcmp(e.what(),(char *)"Second index out of range in substring method") == 0);
        }
        try{
            s[4].substring(4, 1);
        }catch(exception & e){
            REQUIRE(strcmp(e.what(),(char *)"Invalid indexes in substring method") == 0);
        }
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

    SECTION("Get int"){
        REQUIRE(s[11].getInt() == 123);
        REQUIRE(s[12].getInt() == 0);
        REQUIRE(s[13].getInt() == -5);
        try{
            s[0].getInt();
        }catch(exception & e){
            REQUIRE(strcmp(e.what(),(char *)"DSString is not an integer") == 0);
        }
    }

    SECTION("Get int"){
        REQUIRE(s[11].isNum() == true);
        REQUIRE(s[12].isNum() == true);
        REQUIRE(s[13].isNum() == true);
        REQUIRE(s[0].isNum() == false);
        REQUIRE(s[14].isNum() == false);
        REQUIRE(s[15].isNum() == false);
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

    SECTION("Remove"){
        char temp []= " ";
        DSString temp2;
        temp2 = (char *)"splitsplitsplit";
        REQUIRE((s[7].remove(temp) == temp2));
        temp[0] = ',';
        temp2 = ((char *)"test String ishere");
        REQUIRE((s[10].remove(temp) == temp2));
        REQUIRE((s[1].remove(temp) == s[1]));
    }
}
