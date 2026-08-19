//Header files tell program the function declaration (Inputs, outputs)
#include <iostream>
#include <string>
//Using a namespace is same in C#, means i can use the programs from this lib (Or directory)
using namespace std;

//Function declaration
int main() {
    //Data types:
    bool temp_bool;    //1 byte
    char temp_char;    //1 byte
    int temp_int;      //2 or 4 byte
    float temp_float;  //4 bytes
    double temp_double;//8 bytes

    //Just like C you can assign chars ints using ascii
    char x = 69, y = 70, z = 71;
    cout << x << y << z << endl;

    //Just like C, strings arent a part of the language itself and need to be added
    string name = "Samarth Harish Kumar";
    cout << name << endl;

    //C++ has something like var from java and C#, its called auto
    auto number = 5;
    cout << typeid(number).name() << endl;
}