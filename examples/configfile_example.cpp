//
//  configfile_example.cpp
//  CLOptions
//
//  Created by Josh Cardenzana on 9/19/16.
//  Copyright © 2016 JCardenzana. All rights reserved.
//
// Compile with:
//    g++ -std=c++11 -I../include configfile_example.cpp -o configfile_example

#include <iostream>
#include "CLOptions.h"

//__________________________________________________
CLOptions DefineOptions()
{
    CLOptions options ;

    // Make the options parameter know that this could get passed
    // a configuration file option (this ability is off by default)
    // The passed parameters to this method are:
    //    1. Parameter Name - Default is "ConfigFile"
    //    2. Description    - Tell your users what this does
    //    3. Default        - Give a default file name to be used
    //    4. Comment ID (#) - Some string that identifies when a line is to be
    //                        interpreted as a comment in the config file.
    // There are defaults for all of these values, but you can customize
    // it to suit your programing style.
    options.AddConfigFileParam("", "", "configfile_example.txt") ;
    
    // Define some parameters
    options.AddDoubleParam("Pi", "An very inaccurate value of Pi!", 3.14) ;
    options.AddBoolParam("ILikePi", "Do you like pi?", true) ;
    
    return options ;
}


//__________________________________________________
int main (int argc, char** argv)
{
    // Get the command line options
    CLOptions options = DefineOptions() ;
    
    // Parse the options from the command line
    if (options.ParseCommandLine(argc, argv)) {
        // Something went wrong
        return 0 ;
    }
    
    // Print the values that were given
    std::cout << "Options Passed:" << std::endl;
    std::cout << "   Pi     : " << options.AsDouble("Pi") << std::endl;
    std::cout << "   ILikePi: " << options.AsBool("ILikePi") << std::endl;
    
    // Just for fun
    if (options.AsBool("ILikePi")) {
        std::cout << "Who doesnt love Pi?" << std::endl;
    } else {
        std::cout << "YOU MONSTER! How could you not like pi!?!?!?" << std::endl;
    }
    
    return 0 ;
}
