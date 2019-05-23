//
//  multipleinputfiles_cloptions.cpp
//  CLOptions
//
//  Created by Josh Cardenzana on 9/16/16.
//  Copyright © 2016-2019 JCardenzana. All rights reserved.
//
//  Compile with:
//      g++ -std=c++11 -I../include multipleinputfiles_cloptions.cpp -o multipleinputfiles_cloptions
//
//  Description:
//      This serves as an example of how to create a single executable
//      that is capable of taking two command line options '--input' and
//      '--output' from the user. Specifically it shows how to do it
//      using the CLOptions tools. For an example that demonstrates how
//      to use the GetOpt tools see 'multipleinputfiles_getopt.cpp'.
//

#include <iostream>
#include "CLOptions.h"

int main(int argc, char** argv)
{
    // Define the command line options
    CLOptions options ;
    options.AddStringParam("i,input",
                           "This is the inputfile.",
                           "default_in") ;
    options.AddStringParam("o,output",
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