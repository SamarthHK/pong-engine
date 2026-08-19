//Header files tell program the function declaration (Inputs, outputs)
#include <iostream>
//Using a namespace is same in C#, means i can use the programs from this lib (Or directory)
using namespace std;

//Function declaration
int main() {
    //Creating a basic calculator
    int x, y, opperand, output;
    cout << "Enter 2 numbers number" << endl;
    //Cin restricts input to the type of x and y
    cin >> x >> y;

    cout << "Enter number for thy function of choice:\n" << "\t-1 for addition\n" << "\t-2 for subtraction\n" << "\t-3 for multiplication\n" << "\t-4 for division\n";
    cin >> opperand;

    //I do now >:)
    switch (opperand) {
        case 1:
            output = x + y;
            break;
        case 2:
            output = x - y;
            break;
        case 3:
            output = x * y;
            break;
        case 4:
            output = x / y;
            break;
        default:
            return 1;
    }

    cout << "Thou result is: " << output << endl;
    return 0;
}