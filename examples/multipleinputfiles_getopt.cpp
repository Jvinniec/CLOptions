//
//  multipleinputfiles.cpp
//  CLOptions
//
//  Created by Josh Cardenzana on 9/16/16.
//  Copyright © 2016 JCardenzana. All rights reserved.
//

#include <iostream>
#include <getopt.h>
#include <map>
#include <string>

int main (int argc, char** argv)
{
    // Create the variables to store your parameters
    std::map<std::string, std::string> input_parameters ;
    input_parameters["input"] = "default_in" ;   // Storage for input
    input_parameters["output"] = "default_out" ; // Storage for output
    
    // Create variables to hold your parameters
    const struct option longopts[] =
    {
        {"input", required_argument, 0, 'i'},
        {"output", required_argument, 0, 'o'},
        {0,0,0,0} // This tells getopt that this is the end
    };
    
    // Some parameters for getopt_long
    int c(0);
    
    // Get the options from the command line
    while (c != -1) {
        int option_index(-1) ;
        
        // Read the next command line option
        // Note here that the ':' after the 'i' and 'o' denotes that
        // it requires an argument
        c = getopt_long(argc, argv, "i:o:", longopts, &option_index) ;
        
        // If the option is valid, fill the corresponding value
        if ((c>0)&&(option_index>=0)) {
            input_parameters[longopts[option_index].name] = optarg ;
        }
        
        switch (c) {
            case 'i':
                // Fill input option
                input_parameters["input"] = optarg ;
            case 'o':
                // Fill output option
                input_parameters["output"] = optarg ;
            case '?':
                // getopt_long printed an error message
                break ;
        }
    }
    
    std::cout << "input  = " << input_parameters["input"] << std::endl;
    std::cout << "output = " << input_parameters["output"] << std::endl;
    
    return 0 ;
}