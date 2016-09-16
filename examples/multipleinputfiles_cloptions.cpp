//
//  multipleinputfiles_cloptions.cpp
//  CLOptions
//
//  Created by Josh Cardenzana on 9/16/16.
//  Copyright © 2016 JCardenzana. All rights reserved.
//

#include <iostream>
#include "CLOptions.h"

int main(int argc, char** argv)
{
    // Define the command line options
    CLOptions options ;
    options.AddStringParam("input",
                           "This is the inputfile.",
                           "default_in") ;
    options.AddStringParam("output",
                           "This is the output filename.",
                           "default_out") ;
    
    // Parse the command line options
    // Note this returns true if requesting the help information
    if (options.ParseCommandLine(argc, argv)) {
        return 0 ;
    }
    
    std::cout << "input  = " << options["input"] << std::endl;
    std::cout << "output = " << options["output"] << std::endl;
    
    return 0;
}