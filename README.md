# CLOptions

The header file in 'include/CLOptions.h' can be included in your
simple executable script for defining and using command line
options in your script. It also provides the functionality of
printing help text and setting default values for those parameters.

 * **Wiki page:** https://github.com/Jvinniec/CLOptions/wiki
 * **Tutorial:** https://github.com/Jvinniec/CLOptions/wiki/Tutorial

#### Disclaimer ####
This code is built on top of the 'getopt' framework. If you find CLOptions useful, please give us a shoutout in your README.

# Example #
Imagine creating some executable, in which you want the user to be able to provide you with some options on the command line. For the sake of this example, lets say you want them to provide you with one integer, boolean, double, and string. The code below demonstrates how you would do this with CLOptions.

<b>executable.cpp</b></br>
*This file is also available in the 'examples' directory.*
```c++
#include <iostream>
#include "CLOptions.h"

CLOptions DefineOptions() 
{
  // Create a CLOptions object
  CLOptions options ;
  
  // Add some parameters of different types
  // The format for each parameter definition is:
  //    1 - Command line option name
  //    2 - Description of parameter
  //    3 - Default value
  options.AddIntParam("i,IntegerParam",
                      "This is a simple integer parameter.",
                      1)   ;
  options.AddDoubleParam("d,DoubleParam",
                         "This is a simple double parameter.",
                         123.456) ;
  options.AddBoolParam("b,BooleanParam",
                       "This is a simple boolean parameter",
                       false) ;
  options.AddStringParam("s,StringParam",
                         "This is a simple string parameter",
                         "just a string") ;

  // Add text to be printed with '-v' or '--version' options
  options.AddVersionInfo("executable v1.0");

  // Add detailed description of program to be printed
  // when '-h' or '--help' options are used
  options.AddProgramDescription("Executable demonstrating CLOptions usage.");

  return options ;
}

int main(int argc, const char* argv[])
{
  // Initialize the options parameter
  CLOptions options = DefineOptions() ;
  
  // Now fill the options from the command line arguements.
  // Note that the 'ParseCommandLine()' method returns a bool
  // which specifies when the '-h','-help', or a problem has occured.
  // This allows you to quit when this happens.
  if (options.ParseCommandLine(argc, const_cast<char**>(argv))) {
    return 0;
  }

  // Now we can access the parameters which have been set
  int         some_int  = options.AsInt("IntegerParam") ;
  double      some_dbl  = options.AsDouble("DoubleParam") ;
  bool        some_bool = options.AsBool("BooleanParam") ;
  std::string some_str  = options.AsString("StringParam") ;
  
  // Now lets print out the values as an example
  std::cout << "\nPrinting options individualy:" << std::endl;
  std::cout << "IntegerParam " << options.AsInt("IntegerParam") << std::endl;
  std::cout << "DoubleParam " << options.AsDouble("DoubleParam") << std::endl;
  std::cout << "BooleanParam " << options.AsBool("BooleanParam") << std::endl;
  std::cout << "StringParam " << options.AsString("StringParam") << std::endl;
  
  // Note that we can also get the above behavior directly from 'CLOptions::PrintSimple()'
  std::cout << "\nPrinting options directly:" << std::endl;
  options.PrintSimple() ;
  
  return 0;
}
```
This executable is easily compiled via:
```
$ g++ -std=c++11 -I[CLOptions-install-directory]/include executable.cpp -o executable
```
The help text can be printed as follows:
```
$ ./executable -h
executable v1.0

USAGE: ./executable [options]

DESCRIPTION:
  Executable demonstrating CLOptions usage. 

AVAILABLE OPTIONS:
  -h, --help [no argument]
               Prints out this help information. 
  -v, --version [no argument]
               Print version information and exit. 
  -b, --BooleanParam [bool, default=0]
               This is a simple boolean parameter 
  -d, --DoubleParam [double, default=123.456000]
               This is a simple double parameter. 
  -i, --IntegerParam [int, default=1]
               This is a simple integer parameter. 
  -s, --StringParam [string, default=just a string]
               This is a simple string parameter
```
The code can be executed with the following results:
```
$ ./executable --DoubleParam 3.14159 --BooleanParam 1

Printing options individualy:
IntegerParam 123
DoubleParam 3.14159
BooleanParam 1
StringParam just a string

Printing options directly:
BooleanParam 1
DoubleParam 3.14159
IntegerParam 123
StringParam just a string
```
## ABOUT ##
Author: J. V. Cardenzana (Jvinniec)

## Future Improvements ##
If there are people out there who happen to find this code useful, please let me know! I would be more than happy to continue expanding on it to include things like:
* Exception throwing when a string is passed to a parameter expecting a number type.
* Definitions for vector parameters with a specific delimiter
* Definitions for parameters which are required vs. those that are optional
* Ability to pass a given parameter more than once and fill the values into a list.
* ~~Definitions of both long and short forms of an argument (for instance setting the parameter `Param` with either `-P` or `-Param`).~~ Implemented as of v1.2.1.
* ~~Ability to pass options from a configuration file, and overwrite them with commands submitted on the command line.~~   Implemented as of v1.1.0. See 'examples/configfile_example.cpp' for an example.
* ~~Ability to specify version information using `-v` or `-version` command line option~~  
Implemented as of v1.2.0.

If any of these sound like they would benefit you, LET ME KNOW by submitting an [issue](https://github.com/Jvinniec/CLOptions/issues) and I'll see what I can do to get them implemented.
