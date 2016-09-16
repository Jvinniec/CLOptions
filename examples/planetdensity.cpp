//
// planetdensity.cpp
//
// Author: J. V. Cardenzana
//
// Computes the density of some planet providing
// command line options of 'Mass' and 'Radius' 
// for describing the planet.
// Available Options:
//   -Mass        Mass (kg)
//   -Radius      Radius (meters)
//   -PlanetName  Planet name

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
  // Define a name for the planet
  options.AddStringParam("PlanetName",
			 "This is some generic name for the planet",
			 "Planet Bob") ;
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
    // Note that the '[]' operator returns the value as a string
    std::cout << "Details about " << options["PlanetName"] <<  std::endl;
    std::cout << "   Mass  : " << options["Mass"] << " kg" << std::endl;
    std::cout << "   Radius: " << options["Radius"] << " m" << std::endl;
    // Compute the volume of the planet
    double volume = (4.0/3.0) * 3.14159 * std::pow(options.AsDouble("Radius"),3.0) ;
    // Compute the density as (Mass/volume)
    std::cout << "   Density: " << options.AsDouble("Mass") / volume << " kg/m^3" << std::endl;
  }

  return 0 ;
}
