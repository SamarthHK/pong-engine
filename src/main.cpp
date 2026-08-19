//Header files tell program the function declaration (Inputs, outputs)
#include <iostream>
//Using a namespace is same in C#, means i can use the programs from this lib (Or directory)
using namespace std;

//Function declaration
int main() {
    //Memory management:
    string food = "Pizza";
    string* ref = &food;
    cout << *ref << " Mem address: " << ref << endl;
    *ref = "Heh"; //Setting value (Not reference, but actually value) to heh from pizza
    cout << food << " Mem address: " << &food << endl;
    //They both will have the same memory address!!!

    //Allocating and de-allocating memory:
    int* ptr = new int; //Allocating, can only allocate to a pointer
    cout << *ptr << " Mem address: " << ptr << endl;
    delete ptr; // de-allocating

}