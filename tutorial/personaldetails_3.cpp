// personaldetails_3.cpp

// compile with:
// g++ -std=c++11 -I../include personaldetails_3.cpp -o personaldetails_3
#include <iostream>
#include <string>
#include "CLOptions.h"

void PrintDetails(std::string name, int age, double weight)
{
    std::cout << "Name  : " << name << std::endl;
    std::cout << "Age   : " << age << std::endl;
    std::cout << "Weight: " << weight << std::endl;
    return ;
}

int main (int argc, char** argv)
{
    // Define the command line arguments
    CLOptions options ;
    options.AddStringParam("Name",
                           "This is the person's name.",
                           "") ;
    options.AddIntParam("Age",
                            "The age of the person in years",
                            0) ;
    options.AddDoubleParam("Weight",
                            "The weight of the person in pounds.",
                            0.0);
    
    // Parse the command line options
    if (options.ParseCommandLine(argc, argv)) {
        return 0 ;
    }
    
    // Print the persons details
    PrintDetails(options.AsString("Name"),
                 options.AsInt("Age"),
                 options.AsDouble("Weight")) ;
    
    return 0 ;
}