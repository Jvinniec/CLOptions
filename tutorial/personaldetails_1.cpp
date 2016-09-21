// personaldetails_1.cpp

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
    // Define some personal details
    std::string name = "Dave" ;
    int age = 33 ;
    double weight = 167.5 ;
    
    // Print the persons details
    PrintDetails(name, age, weight) ;
    
    return 0 ;
}