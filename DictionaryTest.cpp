//-----------------------------------------------------------------------------
// DictionaryTest.cpp
// D test client for Dictionary ADT
// jovigil
// pa7
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <stdexcept>
#include "Dictionary.h"
#define NUM_TESTS 15
using namespace std;

enum Tests{
    START,

    SET_VALUE,
    SIZE,
    CONTAINS,
    GET_VALUE,
    CLEAR,
    TO_STR,
    PRE_STR,
    REMOVE,
    BEGIN,
    END,
    NEXT,
    PREV,
    OP_INS,
    OP_EQ,
    OP_ASGN,

    FINISH
};

enum TestRetCodes{
    SET_VALUE_F = -NUM_TESTS,
    SIZE_F,
    CONTAINS_F,
    GET_VALUE_F,
    CLEAR_F,
    TO_STR_F,
    PRE_STR_F,
    REMOVE_F,
    BEGIN_F,
    END_F,
    NEXT_F,
    PREV_F,
    OP_INS_F,
    OP_EQ_F,
    OP_ASGN_F,
    
    SUCCESS
};

void printMsg(const char* str);
void err(int code);
int test(int testCase, Dictionary D, int* score);


void err(int code){
    switch (code){
        case SET_VALUE_F:{
            cout << "setValue() FAILURE" << endl;
            break;
        }
        case SIZE_F:{
            cout << "size() FAILURE" << endl;
            break;
        }
        case CONTAINS_F:{
            cout << "contains() FAILURE" << endl;
            break;
        }
        case GET_VALUE_F:{
            cout << "getValue() FAILURE" << endl;
            break;
        }
        case CLEAR_F:{
            cout << "clear() FAILURE" << endl;
            break;
        }
        case TO_STR_F:{
            cout << "to_string() FAILURE" << endl;
            break;
        }
        case PRE_STR_F:{
            cout << "pre_string() FAILURE" << endl;
            break;
        }
        case REMOVE_F:{
            cout << "remove() FAILURE" << endl;
            break;
        }
        case BEGIN_F:{
            cout << "begin() FAILURE" << endl;
            break;
        }
        case END_F:{
            cout << "end() FAILURE" << endl;
            break;
        }
        case NEXT_F:{
            cout << "end() FAILURE" << endl;
            break;
        }
        case PREV_F:{
            cout << "prev() FAILURE" << endl;
            break;
        }
        case OP_INS_F:{
            cout << "insertion operator \"<<\" FAILURE" << endl;
            break;
        }
        case OP_EQ_F:{
            cout << "comparison operator \"==\" FAILURE" << endl;
            break;
        }
        case OP_ASGN_F:{
            cout << "assignment operator \"=\" FAILURE" << endl;
            break;
        }
    }
}


void printMsg(const char* str){
    cout << str << endl;
}


int test(int testCase, Dictionary D, int* score){
    switch (testCase){
        
        case SET_VALUE:{
            D.setValue("baby's first key", 90);
            D.setValue("baby's second key", 85);
            D.setValue("i know u want me freak", 1);
            D.setValue("i know u want me freak", 2);
            int two = D.getValue("i know u want me freak");
            if ( two != 2 ){
                printMsg("Error: failed to set key:val pair properly");
                *score = *score - 1; 
                return SET_VALUE_F;
            }
            break;
        }

        case SIZE:{
            int i;
            for ( i=0; i<30; i++ ){
                D.setValue(to_string(i), i);
            }
            if ( D.size() != 30 ){
                printMsg("Error: returned incorrect value");
                *score = *score - 1; 
                return SIZE_F;
            }
            break;
        }

        case CONTAINS:{
            int i;
            for ( i=0; i<30; i++ ){
                D.setValue(to_string(i), i);
            }
            if ( D.contains("30") ){
                printMsg("Error: returned incorrect value");
                *score = *score - 1; 
                return CONTAINS_F;
            }
            break;
        }
        
        case GET_VALUE:{
            int i;
            for ( i=0; i<30; i++ ){
                D.setValue(to_string(i), i);
            }
            int twenty = D.getValue("20");
            if ( twenty != 20 ){
                printMsg("Error: returned incorrect value");
                *score = *score - 1; 
                return GET_VALUE_F;
            }
            break;
        }

        case CLEAR:{
            int i;
            for ( i=0; i<30; i++ ){
                D.setValue(to_string(i), i);
            }
            D.clear();
            if ( D.size() != 0 ){
                printMsg("Error: nodes remain");
                *score = *score - 1; 
                return CLEAR_F;
            }
            break;
        }

        case TO_STR:{
            int i;
            for ( i=0; i<8; i++ ){
                D.setValue(to_string(i), i);
            }
            string exp = "0 : 0\n1 : 1\n2 : 2\n3 : 3\n4 : 4\n5 : 5\n6 : 6\n7 : 7\n";
            string act = D.to_string();
            if ( act != exp ){
                printMsg("Error: incorrect string");
                cout << "actual:\n" << D << endl;
                cout << "expected:\n" << exp << endl;
                *score = *score - 1; 
                return TO_STR_F;
            }
            break;
        }

        case PRE_STR:{
            D.setValue("6", 6);
            D.setValue("4", 4);
            D.setValue("8", 8);
            D.setValue("2", 2);
            D.setValue("5", 5);
            D.setValue("7", 7);
            D.setValue("9", 9);
            D.setValue("1", 1);
            D.setValue("3", 3);
            string exp = "6\n4\n2\n1\n3\n5\n8\n7\n9\n";
            string act = D.pre_string();
            if ( act != exp ){
                printMsg("Error: incorrect string");
                cout << "actual:\n" << act << endl;
                cout << "expected:\n" << exp << endl;
                *score = *score - 1; 
                return PRE_STR_F;
            }
            break;
        }

        case REMOVE:{
            D.setValue("6", 6);
            D.setValue("4", 4);
            D.setValue("8", 8);
            D.setValue("2", 2);
            D.setValue("5", 5);
            D.setValue("7", 7);
            D.setValue("9", 9);
            D.setValue("1", 1);
            D.setValue("3", 3);
            D.remove("6");
            string exp = "7\n4\n2\n1\n3\n5\n8\n9\n";
            string act = D.pre_string();
            if ( act != exp || D.size() != 8 ){
                printMsg("Error: incorrect string");
                cout << "actual:\n" << act << endl;
                cout << "expected:\n" << exp << endl;
                cout << "size after remove():\n" << D.size() << endl;
                *score = *score - 1; 
                return REMOVE_F;
            }
            break;
        }

        case BEGIN:{
            int i;
            for ( i=0; i<8; i++ ){
                D.setValue(to_string(i), i);
            }
            D.begin();
            string zero = D.currentKey();
            if ( zero != "0" ){
                printMsg("Error: failed to place cursor at first element");
                *score = *score - 1; 
                return BEGIN_F;
            }
            break;
        }

        case END:{
            int i;
            for ( i=0; i<8; i++ ){
                D.setValue(to_string(i), i);
            }
            D.end();
            string seven = D.currentKey();
            if ( seven != "7" ){
                printMsg("Error: failed to place cursor at last element");
                *score = *score - 1; 
                return END_F;
            }
            break;
        }

        case NEXT:{
            int i;
            for ( i=0; i<8; i++ ){
                D.setValue(to_string(i), i);
            }
            D.begin();
            D.next();
            D.next();
            D.next();
            int three = D.currentVal();
            if ( three != 3 ){
                printMsg("Error: failed to place cursor at next element");
                *score = *score - 1; 
                return NEXT_F;
            }
            break;
        }

        case PREV:{
            int i;
            for ( i=0; i<8; i++ ){
                D.setValue(to_string(i), i);
            }
            D.end();
            D.prev();
            D.prev();
            D.prev();
            int four = D.currentVal();
            if ( four != 4 ){
                printMsg("Error: failed to place cursor at previous element");
                *score = *score - 1; 
                return PREV_F;
            }
            break;
        }

        case OP_INS:{
            int i;
            for ( i=0; i<8; i++ ){
                D.setValue(to_string(i), i);
            }
            string exp = "0 : 0\n1 : 1\n2 : 2\n3 : 3\n4 : 4\n5 : 5\n6 : 6\n7 : 7\n";
            cout << "insertion operator visual test: " << endl;
            cout << D << endl;
            cout << "expected: \n" << exp << endl;
            break;
        }

        case OP_EQ:{
            int i;
            Dictionary E;
            for ( i=0; i<8; i++ ){
                D.setValue(to_string(i), i);
                E.setValue(to_string(i), i);
            }
            if ( !(D == E) ){
                printMsg("Error: incorrect comparison");
                *score = *score - 1; 
                return OP_EQ_F;
            }
            break;
        }

        case OP_ASGN:{
            int i;
            for ( i=0; i<8; i++ ){
                D.setValue(to_string(i), i);
            }
            Dictionary F = D;
            if ( !(D == F) ){
                printMsg("Error: improper assignment");
                *score = *score - 1; 
                return OP_ASGN_F;
            }
            break;
        }

        default:
            break;
    }
    return SUCCESS;
}





int main(){
    int TEST =  START;
    int score = NUM_TESTS;
    printMsg("jovigil's Dictionary ADT test harness");
    printMsg("Beginning tests\n");
    while ( TEST < FINISH ){
        Dictionary D;
        int result = test(TEST, D, &score);
        if ( result != SUCCESS ){
            err(result);
        }
        TEST++;
    }
    cout << "Tests complete.\nScore: " << score << "/" << NUM_TESTS << endl;
    return 0;
}