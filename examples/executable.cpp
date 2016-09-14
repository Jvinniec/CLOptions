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
