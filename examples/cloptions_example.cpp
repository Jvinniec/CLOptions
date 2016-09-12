//
//  main.cpp
//  CLOptions
//
//  Created by Josh Cardenzana on 9/9/16.
//  Copyright © 2016 JCardenzana. All rights reserved.
//

#include <iostream>

#include "CLOptions.h"

//_______________________________________________
CLOptions DefineOptions()
{
    CLOptions options = CLOptions() ;
    
    // Define a couple of parameters
    options.AddIntParam("IntParam1",                                // This is the command line name
                         "This is the first integer parameter!",    // This is a description of the parameter
                         1) ;                                       // This is the default value
    options.AddDoubleParam("ValueOfPi",
                         "This is a nonprecise value of Pi!",
                         3.14159) ;
    options.AddStringParam("Long_definition",
                           "This is a string parameter that has a very long definition so that when you pass the help option as '-h' or '-help' at run time you can see how the help message will be printed out. You can actually control how wide the padding for this help text is and how wide the help text will be when printed to the screen.", "") ;
    
    return options ;
}

//_______________________________________________
int main(int argc, const char * argv[]) {
    // Define options upfront
    CLOptions options = DefineOptions() ;
    
    // Fill the parameter options from the provided command line options
    // If this method returns false, then the help command was requested
    // This was done to allow quiting the program without doing anything
    if (options.ParseCommandLine(argc, const_cast<char**>(argv))) {
        return 0 ;
    }
    
    // You can now access the values using the parameter names
    std::cout << "------------------------------------" << std::endl;
    std::printf("Simple print of parameter values\n") ;
    std::cout << "------------------------------------" << std::endl;
    options.PrintSimple() ;
    
    std::cout << "\n------------------------------------" << std::endl;
    std::cout << "More detailed description of parameter values" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    options.PrintDetailed() ;
    
    // Now we want to actually use the values that are stored
    std::string value = options["ValueOfPi"] ;
    
    return 0;
}
