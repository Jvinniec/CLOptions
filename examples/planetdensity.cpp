#include <iostream>
#include <cmath>
#include "CLOptions.h"

CLOptions DefineOptions()
{
  CLOptions options ;

  // Define a mass parameter
  options.AddDoubleParam("Mass",
			 "This is the planet's mass (in kg).",
			 0.0) ;
  // Define a radius parameter
  options.AddDoubleParam("Radius",
			 "This is the planet's radius (in meters)",
			 1.0) ;

  return options ;
}

int main (int argc, const char* argv[])
{
  // Define the command line options
  CLOptions options = DefineOptions() ;

  // Fill the options from the command line
  if (options.ParseCommandLine(argc, const_cast<char**>(argv))) {
    return 0 ;
  }

  // Do some checks on the parameters
  if (options.AsDouble("Mass") <= 0.0) {
    std::cout << "[ERROR] Mass must be greater than 0!" << std::endl;
  } else if (options.AsDouble("Radius") <= 0.0) {
    std::cout << "[ERROR] Radius must be greater than 0!" << std::endl;
  } else {
    // Now print out the value of the planet:
    std::cout << "Planet parameters:" << std::endl;
    std::cout << "   Mass  : " << options.AsDouble("Mass") << " kg" << std::endl;
    std::cout << "   Radius: " << options.AsDouble("Radius") << " m" << std::endl;
    std::cout << "   Density: " << options.AsDouble("Mass") / std::pow(options.AsDouble("Radius"), 3.0) << " kg/m^3" << std::endl;
  }

  return 0 ;
}
