/*************************************************************************
 * File: personaldetails_2.cpp (CLOptions)
 * Copyright © 2017-2019 JCardenzana. All rights reserved.
 * 
 * Description:
 *      Demonstrates passing parameters as a space separated list.
 * 
 * Compile with:
 *      g++ -std=c++11 personaldetails_2.cpp -o personaldetails_2
 ************************************************************************/

#include <iostream>
#include <string>

void PrintDetails(std::string name, int age, double weight)
{
    std::cout << "Name  : " << name << std::endl;
    std::cout << "Age   : " << age << std::endl;
    std::cout << "Weight: " << weight << std::endl;
    return ;
}

int main (int argc, char** argv)
{
    // Print usage info
    if (argc < 4) {
        std::cout << "\nUSAGE: " << std::string(argv[0]) << " <name> <age> <weight>\n\n";
        return 0 ;
    }
    
    // Define some personal details
    std::string name   = std::string(argv[1]) ;
    int         age    = std::stoi(argv[2]) ;
    double      weight = std::stod(argv[3]) ;
    
    // Print the persons details
    PrintDetails(name, age, weight) ;
    
    return 0 ;
}