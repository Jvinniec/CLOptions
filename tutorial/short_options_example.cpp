//
//  short_options_example.cpp
//  CLOptions
//
//  Created by Josh Cardenzana on 1/27/17.
//  Copyright © 2017 JCardenzana. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "CLOptions.h"

/********************************************
 * Forward declarations
 ********************************************/
void PrintDetails(std::string name, int age, double weight) ;
CLOptions DefineOptions() ;

/********************************************
 * Main
 ********************************************/
int main(int argc, char** argv)
{
    // Define the command line options and parse the command line
    CLOptions options = DefineOptions() ;
    if (options.ParseCommandLine(argc, argv)) return 0 ;
    
    // Print the persons details
    PrintDetails(options.AsString("Name"),
                 options.AsInt("Age"),
                 options.AsDouble("Weight")) ;
    
    return 0 ;
}

/********************************************
 * Define the command line options
 ********************************************/
CLOptions DefineOptions()
{
    // Define the command line arguments
    CLOptions options ;
    options.AddStringParam("N,Name","This is the person's name.","") ;
    options.AddIntParam("A,Age","The age of the person in years",0) ;
    options.AddDoubleParam("W,Weight","The weight of the person in pounds.",0.0);
    options.AddVersionInfo("personaldetails v6") ;
    return options ;
}

/********************************************
 * Print the results
 ********************************************/
void PrintDetails(std::string name, int age, double weight)
{
    std::cout << "Name  : " << name << std::endl;
    std::cout << "Age   : " << age << std::endl;
    std::cout << "Weight: " << weight << std::endl;
    return ;
}