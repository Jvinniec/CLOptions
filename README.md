         ____  _________    ____  __  _________
        / __ \/ ____/   |  / __ \/  |/  / ____/
       / /_/ / __/ / /| | / / / / /|_/ / __/   
      / _, _/ /___/ ___ |/ /_/ / /  / / /___   
     /_/ |_/_____/_/  |_/_____/_/  /_/_____/                                      

The header file in 'include/CLOptions.h' can be included in your
simple executable script for defining and using command line
options in your script. It also provides the functionality of
printing help text and setting default values for those parameters.

#Example#
You could imagine creating some executable, in which you want the
user to be able to provide you with some options.
<b>executable.cpp</b>
This file is also available in the 'examples' directory.
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
  options.AddIntParam("IntegerParam",
      "This is a simple integer parameter.",
      123) ;
  options.AddDoubleParam("DoubleParam",
      "This is a simple double parameter.",
      123.456) ;
  options.AddBoolParam("BooleanParam",
      "This is a simple boolean parameter",
      false) ;
  options.AddStringParam("StringParam",
      "This is a simple string parameter",
      "just a string") ;
      
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
  int some_int = options.AsInt("IntegerParam") ;
  double some_dbl = options.AsDouble("DoubleParam") ;
  bool some_bool = options.AsBool("BooleanParam") ;
  std::string some_str = options.AsString("StringParam") ;
  
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

USAGE: ./executable [options]

AVAILABLE OPTIONS:
  -BooleanParam [bool, default=0]
               This is a simple boolean parameter 
  -DoubleParam [double, default=123.456000]
               This is a simple double parameter. 
  -IntegerParam [int, default=123]
               This is a simple integer parameter. 
  -StringParam [string, default=just a string]
               This is a simple string parameter
```
The code can be executed with the following results:
```
$ ./executable -DoubleParam 3.14159 -BooleanParam 1

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
#Extras#
If there are people out there who happen to find this code useful, please let me know! I would be more than happy to continue expanding on it to include things like:
* Definitions for vector parameters with a specific delimiter
* Definitions for parameters which are required vs. those that are optional
