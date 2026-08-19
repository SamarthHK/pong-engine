//Header files tell program the function declaration (Inputs, outputs)
#include <functional>
#include <iostream>
//Using a namespace is same in C#, means i can use the programs from this lib (Or directory)
using namespace std;

void funct(function<int(int a, int b)> f);

//Function declaration
int main() {
    //Lambda
    int x = 10;
    /*
     *THe [x] Just means im passing in a reference of a object outside the lambda called state capture
     *(int a, int b) is just the input params
     *{}; contains the code
     *Auto is needed because it created a unique type for the lambda
     */
    auto add = [x](int a, int b) {
        return (a + b)*x;
    };
    //Passing the refernce of the lambda in
    funct(add);

}
/*
 *Creating a function that takes a function that returns int: function<int()>
 *and saying that function takes (int, int) as input
 */
void funct(function<int(int, int)> f) {
    cout << f(10,10) << endl;
}