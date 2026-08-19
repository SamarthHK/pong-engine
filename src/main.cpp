//Header files tell program the function declaration (Inputs, outputs)
#include <iostream>
//Using a namespace is same in C#, means i can use the programs from this lib (Or directory)
using namespace std;

//Function declaration
int main() {
    //Variable creation and assignment are just like C
    int age;
    age = 15;
    //You can print multiple datatypes!!!
    std::cout << "My age happens to be... " << age << std::endl;
    //Multi-variable creation and assignment
    int x = 21, y = 16, z = 40;
    std::cout << "Before Values:\n" << "x: " << x << " Y: " << y << " Z: " << z << std::endl;
    //Chained assignment
    x = y = z = 10;
    std::cout << "After Values:\n" << "X: " << x << " Y: " << y << " Z: " << z << std::endl;
    //Way to assign a final or constant value, just like C#
    const int fav_number = 69;
    std::cout << "Favorite number: " << fav_number << std::endl;

}