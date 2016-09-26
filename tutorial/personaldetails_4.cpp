// personaldetails_4.cpp

// compile with:
// g++ -std=c++11 personaldetails_4.cpp -o personaldetails_4
#include <iostream>
#include <string>
#include <vector>
#include <getopt.h>

void PrintDetails(std::string name, int age, double weight)
{
    std::cout << "Name  : " << name << std::endl;
    std::cout << "Age   : " << age << std::endl;
    std::cout << "Weight: " << weight << std::endl;
    return ;
}

void PrintHelp(std::string command_name)
{
    std::cout << "\nUSAGE: " << command_name << " [options]\n\n";
    std::cout << "Available Options:\n" ;
    std::cout << "  -h, -help [no argument]\n" ;
    std::cout << "                 Prints this help text\n" ;
    std::cout << "  -Name [string, default=]\n" ;
    std::cout << "                 This is the persons name.\n" ;
    std::cout << "  -Age [int, default=0]\n" ;
    std::cout << "                 This is the persons age in years\n";
    std::cout << "  -Weight [double, default=0]\n" ;
    std::cout << "                 This is the persons weight in pounds\n\n" ;
}

int main (int argc, char** argv)
{
    
    std::string name = "" ;
    int age = 0 ;
    double weight = 0.0 ;
    
    // Setup the GetOpt long options.
    std::vector<struct option> longopts ;
    longopts.push_back({"help",  no_argument, 0, 'h'}) ;
    longopts.push_back({"Name",  required_argument, 0, 'N'}) ;
    longopts.push_back({"Age",   optional_argument, 0, 'A'}) ;
    longopts.push_back({"Weight",required_argument, 0, 'W'}) ;
    longopts.push_back({0,0,0,0}) ;
    
    // Now parse the options
    while (1)
    {
        int c(0) ;
        int option_index = -1;
        
        c = getopt_long_only (argc, argv, "h",
                              &longopts[0], &option_index);
        
        /* Detect the end of the options. */
        if (c == -1) break;
        
        // Now loop through all of the options to fill them based on their values
        switch (c)
        {
            case 0:
                /* If this option set a flag, do nothing else now. */
                break ;
            case 'h':
                // Print the help message and quit
                PrintHelp(argv[0]) ;
                return 0 ;
            case '?':
                // getopt_long_omly already printed an error message.
                // This will most typically happen when then an unrecognized
                // option has been passed.
                return 0 ;
            default:
                std::string opt_name( longopts[option_index].name ) ;
                if (opt_name.compare("help")==0) {
                    PrintHelp(argv[0]) ;
                } else if (opt_name.compare("Name")==0) {
                    name = std::string(optarg) ;
                } else if (opt_name.compare("Age")==0) {
                    age = std::stoi(optarg) ;
                } else if (opt_name.compare("Weight")==0) {
                    weight = std::stod(optarg) ;
                }
                break ;
        }
    }
    
    // Print the persons details
    PrintDetails(name, age, weight) ;

    return 0 ;
}
