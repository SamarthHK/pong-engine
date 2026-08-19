//Header files tell program the function declaration (Inputs, outputs)
#include <iostream>
//Using a namespace is same in C#, means i can use the programs from this lib (Or directory)
using namespace std;

//Function declaration
int main() {
    //Printing hello world in the console
    std::cout << "Hello world!!!\n"; //cout stands for see-out (Proper pronunciation)  or charecter out
    // << in couts context just means feed what comes after << into the function before it
    //Here im feeding 3 different strings into cout's stream
    std::cout << "Print no.1" << "Print no.2" << "Print no.3";
    //Just like C, telling the program everything shut down fine
    return 0;
}