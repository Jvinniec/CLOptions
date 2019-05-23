/*************************************************************************
 * File: short_options_example.cpp (CLOptions)
 * Copyright © 2017-2019 JCardenzana. All rights reserved.
 * 
 * Description:
 *      Same as personaldetails_6, but adds the short form of the options that
 *      can also be used to set a parameter from the command line.
 * 
 * Compile with:
 *      g++ -std=c++11 -I../include short_options_example.cpp -o short_opts
 * 
 * Execute with:
 *      ./short_opts --Name Sally --Age 56 --Weight 345.678
 *      ./short_opts -n Sally -a 56 -w 345.678
 *      ./short_opts --Name Sally -a 56 -w 345.678
 ************************************************************************/

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
    options.AddStringParam("n,Name","This is the person's name.","") ;
    options.AddIntParam("a,Age","The age of the person in years",0) ;
    options.AddDoubleParam("w,Weight","The weight of the person in pounds.",0.0);
    options.AddVersionInfo("short_opt v1") ;
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