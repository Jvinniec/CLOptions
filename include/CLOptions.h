//
//  CLOptions.h
//  CLOptions
//
//  Created by Josh Cardenzana on 9/9/16.
//  Copyright © 2016 JCardenzana. All rights reserved.
//
//--------------------------------------------------------
// This header file is designed to serve as a simple method
// for producing command line options within a small
// executable. Please note the following:
//  - The user is responsible for making sure parameters do
//    not conflict with each other in their program
//  - ALL parameters defined require a value to be passed on
//    the command line.
//  - A string version of set parameters can be returned using
//    '[<param_name>]'.
//  - To get a 'double' or 'bool' or 'int' or 'string'
//    value specifically, use the 'AsBool','AsDouble', etc..
//    methods. Note that if a variable is not defined as an
//    object of the type you are trying to return, you will
//    not be able to return that object. For example:
//
//       CLOptions options ;
//       options.AddDouble("DblParam","Generic double parameter", 123.456) ;
//
//    The following will happen:
//
//       double dbl       = options.AsDouble("DblParam") ; // GOOD
//       bool bool        = options.AsBool("DblParam") ;   // BAD, will produce error msg
//       int integer      = options.AsInt("DblParam") ;    // BAD, will produce error msg
//       std::string str1 = options.AsString("DblParam") ; // BAD, will produce error msg
//       std::string str2 = options["DblParam"] ;          // GOOD, will put "DblParam" value into a string
//
// (legal stuff)
//
// The original author releases this code with the under-
// standing that it is provided as is with no guarantees.
//--------------------------------------------------------

#ifndef CLOptions_h
#define CLOptions_h

#include <fstream>
#include <getopt.h>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// Some defines when printing parameter descriptions
#define max_description_width 80    // Controls the maximum # of characters to print in description
#define pad_description_width 15    // Controls how many spaces are printed before each line of the description

// This parameter prevents the case where 'max_descriptoin_width' < 'pad_description_width'
#define max_width ((max_description_width>pad_description_width) ? max_description_width : pad_description_width + 1)

//enum CLParamType {BOOL, DOUBLE, INT, STRING} ;

namespace CLOptionsHelper {
    /***************************************
     * Methods for splitting strings on some delimeter
     ***************************************/
    // Method for splitting a string based on some delimiter into a vector of strings
    inline std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
        std::stringstream ss(s);
        std::string item=std::string();
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }
    // Method for splitting a string based on some delimiter into a vector of strings
    inline std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, elems);
        return elems;
    }
    
    // Tests whether a file is accessible
    static inline bool file_exists (const std::string& name, bool hard_check=true) {
        std::ifstream f( name.c_str() );
        if ( !f.good() && hard_check ) {
            // note that the name is put in quotes to show when
            // extra white space has been added
            std::cout << "[ERROR] File does not exist:\n   \"" << name << "\"" << std::endl;
        }
        return f.good();
    }
}

/***************************************
 * CLParam
 * Parent class for all command line parameter objects
 ***************************************/
template <typename T>
class CLParam {
public:
    CLParam<T>() {};
    CLParam<T>(const std::string& param_name,
                     const std::string& info,
                     T default_val) :
    parameter_name(param_name), description(info), value(default_val), default_value(default_val)
    {
        if (description.empty()) description="No description for " + parameter_name + ".";
    }
    virtual ~CLParam() {}
    virtual CLParam<T>& operator=(const T& other) {
        value = other ;
        return *this ;
    }
    inline operator T() {return value;}
    T getDefault() {return default_value;}
    T getValue() {return value;}
    std::string getParamName() {return parameter_name;}
    std::string getDescription() {return description;}
    void setValue(T new_value) {value = new_value;}
    void Print() {
        std::cout << "# " << description << std::endl ;
        std::cout << "# [Default = " << default_value << "]" << std::endl;
        PrintSimple() ;
    }
    void PrintSimple() {
        std::cout << parameter_name << " " << value << std::endl ;
    }
protected:
    std::string parameter_name ;
    std::string description ;
    T value ;
    T default_value ;
private:
};

/************************************************
 * Bool parameter
 ************************************************/
class CLBool : public CLParam<bool> {
public:
    CLBool() : CLParam<bool>() {};
    CLBool(const std::string& param_name,
                 const std::string& info,
                 bool default_val,
                 std::map<std::string, CLBool*> &bool_map) :
    CLParam<bool>(param_name, info, default_val)
    {
        bool_map[parameter_name] = this ;
    }
    CLBool& operator=(std::string& other) {
        value = std::stoi(other);
        return *this ;
    }
    CLBool& operator=(bool other) {
        value = other ;
        return *this ;
    }
protected:
private:
};

/************************************************
 * String parameter
 ************************************************/
class CLString : public CLParam<std::string> {
public:
    CLString(const std::string& param_name,
                   const std::string& info,
                   const std::string& default_val,
                   std::map<std::string, CLString*> &str_map) :
    CLParam<std::string>(param_name, info, default_val)
    {
        str_map[parameter_name] = this ;
    }
    CLString& operator=(std::string other) {
        value = other ;
        return *this ;
    }
    
    // Some methods relating to std::string. There's probably a better way to do this..
    const char* c_str()
        {return value.c_str() ;}
    int compare(const std::string& str)
        {return value.compare(str) ;}
    size_t find(const std::string& str, size_t pos=0)
        {return value.find(str, pos) ;}
    bool empty() const
        {return value.empty();}
    std::string operator+(const std::string& other) {
        std::string new_str = value + other ;
        return new_str ;
    }
protected:
private:
};

/************************************************
 * Double parameter
 ************************************************/
class CLDouble : public CLParam<double> {
public:
    CLDouble(const std::string& param_name,
                   const std::string& info,
                   double default_val,
                   std::map<std::string, CLDouble*> &dbl_map) :
    CLParam<double>(param_name, info, default_val)
    {
        dbl_map[parameter_name] = this ;
    }
    CLDouble& operator=(const std::string& other) {
        value = std::stod(other);
        return *this ;
    }
    CLDouble& operator=(double other) {
        value = other ;
        return *this ;
    }
protected:
private:
};

/************************************************
 * Int parameter
 ************************************************/
class CLInt : public CLParam<int> {
public:
    CLInt(const std::string& param_name,
                const std::string& info,
                int default_val,
                std::map<std::string, CLInt*> &int_map) :
    CLParam<int>(param_name, info, default_val)
    {
        int_map[parameter_name] = this ;
    }
    CLInt& operator=(const std::string& other) {
        value = std::stoi(other);
        return *this ;
    }
    CLInt& operator=(int other) {
        value = other ;
        return *this ;
    }
protected:
private:
};


/***************************************
 * CLOptions
 * Parent class for all command line parameter objects
 ***************************************/
class CLOptions {
public:
    // Basic constructor
    CLOptions() {} ;
    // Destructor
    virtual ~CLOptions()
    {
        // Loop through each storage map and delete all objects
        std::map<std::string, CLBool*>::iterator bool_itr ;
        for (bool_itr=params_bools.begin(); bool_itr!=params_bools.end(); ++bool_itr)
            if (bool_itr->second != nullptr) delete bool_itr->second ;
        
        std::map<std::string, CLDouble*>::iterator dbl_itr;
        for (dbl_itr=params_doubles.begin(); dbl_itr!=params_doubles.end(); ++dbl_itr)
            if (dbl_itr->second != nullptr) delete dbl_itr->second ;
        
        std::map<std::string, CLInt*>::iterator int_itr;
        for (int_itr=params_ints.begin(); int_itr!=params_ints.end(); ++int_itr)
            if (int_itr->second != nullptr) delete int_itr->second ;
        
        std::map<std::string, CLString*>::iterator str_itr ;
        for (str_itr=params_strings.begin(); str_itr!=params_strings.end(); ++str_itr)
            if (str_itr->second != nullptr) delete str_itr->second ;
    } ;
    
    
    // Methods for adding parameters of a specific type
    void AddBoolParam(const std::string& param_name,
                    const std::string& param_descrip,
                    bool default_val)
        {
            new CLBool(param_name, param_descrip, default_val, params_bools) ;
        }
    void AddDoubleParam(const std::string& param_name,
                    const std::string& param_descrip,
                    double default_val)
        {
            new CLDouble(param_name, param_descrip, default_val, params_doubles) ;
        }
    void AddIntParam(const std::string& param_name,
                    const std::string& param_descrip,
                    int default_val)
        {
            new CLInt(param_name, param_descrip, default_val, params_ints) ;
        }
    void AddStringParam(const std::string& param_name,
                    const std::string& param_descrip,
                    std::string default_val)
        {
            new CLString(param_name, param_descrip, default_val, params_strings) ;
        }
    
    // Here are some additional parameters that fall outside the typical parameters...
    
    // Add configuration file option
    void AddConfigFileParam(const std::string& param_name = std::string(),
                            const std::string& param_descrip = std::string(),
                            const std::string& default_val = std::string(),
                            const std::string& comment_var = "#")
        {
            // Set the value for the configuration file option
            configfile_opt_name = (param_name.empty()) ? "ConfigFile" : param_name ;
            std::string configfile_opt_desc = (param_descrip.empty()) ?
                    "Configuration file containing options (will be overridden by values passed on the command line)." :
                    param_descrip ;
            configfile_comment = comment_var ;
            
            // Add an option for the configuration file parameter
            AddStringParam(configfile_opt_name, configfile_opt_desc, default_val) ;
        }
    
    // Add version information
    void AddVersionParam(const std::string& param_name = "",
                         const std::string& param_descrip = "Print version information and exit.",
                         const std::string& text_to_be_printed = "version text not set")
        {
            // Set the name of the parameter
            version_opt_name = (param_name.length()>0) ? param_name : "version" ;
            // Set the actual parameter
            AddStringParam(param_name, param_descrip, text_to_be_printed) ;
        }
    
    // This method actually sets the options from the passed command line arguements
    bool ParseCommandLine(int argc, char ** argv) ;
    
    // Overload operator for getting objects as strings
    std::string operator[](std::string param_name) ;
    bool        AsBool  (const std::string& param_name) ;
    double      AsDouble(const std::string& param_name) ;
    int         AsInt   (const std::string& param_name) ;
    std::string AsString(const std::string& param_name) ;
    
    // Print the values
    void PrintDetailed() ;  // With description
    void PrintSimple() ;    // Without description
    void PrintBools(bool detailed=false) ;      // Print only the bools
    void PrintDoubles(bool detailed=false) ;    // Print only the doubles
    void PrintInts(bool detailed=false) ;       // Print only the integers
    void PrintStrings(bool detailed=false) ;    // Print only the strings
    
    // Print the help information (i.e. all of the parameters and their descriptions)
    void PrintHelp(const std::string& executable_name) ;
    void PrintDescription(const std::string& param_description) ;
    
    // Set the name of the configuration file option
    void SetConfigFileOption(const std::string& new_configfile_opt)
        {configfile_opt_name = new_configfile_opt ;}
    
protected:
    // The variable used for storing the parameters
    std::vector<struct option> longopts ;
    
    // Storage objects for the different parameter types
    std::map<std::string, CLBool*> params_bools ;
    std::map<std::string, CLDouble*> params_doubles ;
    std::map<std::string, CLInt*> params_ints ;
    std::map<std::string, CLString*> params_strings ;
    
    // This method puts together the full list of parameters into
    // the longopts vector so that it can be used by getopt
    void DefineParams() ;
    bool SetParam(const std::string& param_name,
                  std::vector<std::string> param_value) ;
    
    // Fill the options from a configuration file
    bool FillFromFile(const std::string& filename) ;
    
    // Default configuration file option name
    std::string configfile_opt_name = std::string() ;
    std::string configfile_comment ;  // Lines in the config file beginning with this will be ignored
    std::string version_opt_name = std::string() ;
    
private:
    
};



/***************************************
 * CLOptions
 * More complicated method definitions
 ***************************************/
//__________________________________________________________
bool CLOptions::ParseCommandLine(int argc, char** argv)
{
    // Establish the actual parameters
    DefineParams() ;

    // If we've defined a configuration file parameter, do a pre-loop to see if
    // the user has passed that parameter
    if (configfile_opt_name.size() > 0) {
        // Loop until we find the config file name
        bool use_default_configfile(true) ;
        while(1) {
            int c(0), options_index(-1) ;
            
            c = getopt_long_only(argc, argv, "",
                                 &longopts[0], &options_index) ;
            if (c==-1) break;
            if (c==0) continue ;
            if (std::string(longopts[options_index].name).compare(configfile_opt_name)==0) {
                if (FillFromFile(optarg)) return true ;
                use_default_configfile = false ;
                break ;
            }
        }
        // If the config file info wasnt filled AND if the default filename isnt empty
        // fill the config options from the default file
        if ((use_default_configfile)&&(!(*this)[configfile_opt_name].empty())) {
            if (FillFromFile((*this)[configfile_opt_name])) return true ;
        }
    }
    
    optind = 0 ;
    
    // Loop through all the passed options
    while (1)
    {
        int c(0) ;
        /* getopt_long stores the option index here. */
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
                break;
            case 'h':
                // Print the help message and quit
                PrintHelp(argv[0]) ;
                return true ;
            case '?':
                // getopt_long_omly already printed an error message.
                // This will most typically happen when then an unrecognized
                // option has been passed.
                return true ;
            default:
                std::string opt_name( longopts[option_index].name ) ;
                std::string opt_val ( optarg ) ;
                std::vector<std::string> values = CLOptionsHelper::split( optarg, ' ') ;
                SetParam(opt_name, values) ;
                
                break ;
        }
    }
    // Note that it is up to the user to handle conflicts between parameters
    return false ;
}

//__________________________________________________________
// Note that the vector-ness of 'opt_vals' will allow for passing
// values to options which take a list of values
bool CLOptions::SetParam(const std::string& opt_name,
              std::vector<std::string> opt_vals)
{
    // Special check for the version parameter
    
    
    // Fill in the correct variable
    if (params_bools.count(opt_name) > 0) {
        *params_bools[opt_name] = std::stoi(std::string(opt_vals.front())) ;
    } else if (params_doubles.count(opt_name) > 0) {
        *params_doubles[opt_name] = std::stod(opt_vals.front()) ;
    } else if (params_ints.count(opt_name) > 0) {
        *params_ints[opt_name] = std::stoi(opt_vals.front()) ;
    } else if (params_strings.count(opt_name) > 0) {
        *params_strings[opt_name] = opt_vals.front() ;
    } else {
        return false ;
    }

    return true ;
}

//__________________________________________________________
std::string CLOptions::operator[](std::string param_name)
{
    // Create a default return value of an empty string
    std::string param_val = "" ;
    
    // Loop through the bools
    if (params_bools.count(param_name) > 0) {
        param_val = std::to_string(params_bools[param_name]->getValue()) ;
    }
    
    // Loop through the doubles
    else if (params_doubles.count(param_name) > 0) {
        param_val = std::to_string(params_doubles[param_name]->getValue()) ;
    }
    
    // Loop through the ints
    else if (params_ints.count(param_name) > 0) {
        param_val = std::to_string(params_ints[param_name]->getValue()) ;
    }
    
    // Loop through the strings
    else if (params_strings.count(param_name) > 0) {
        param_val = params_strings[param_name]->getValue() ;
    }
    
    else {
        std::cerr << "[ERROR] Unknown command line parameter: " << param_name << std::endl;
    }
    
    return param_val ;
}

//__________________________________________________________
bool CLOptions::AsBool(const std::string& param_name)
{
    if (params_bools.count(param_name) == 0) {
        std::cerr << "[ERROR] CLOptions::AsBool() :: Parameter \"" << param_name << "\" is not a bool!" << std::endl;
        return false ;
    } else {
        return params_bools[param_name]->getValue();
    }
}

//__________________________________________________________
double CLOptions::AsDouble(const std::string& param_name)
{
    if (params_doubles.count(param_name) == 0) {
        std::cerr << "[ERROR] CLOptions::AsDouble() :: Parameter \"" << param_name << "\" is not a double!" << std::endl;
        return 0 ;
    } else {
        return params_doubles[param_name]->getValue();
    }
}

//__________________________________________________________
int CLOptions::AsInt(const std::string& param_name)
{
    if (params_ints.count(param_name) == 0) {
        std::cerr << "[ERROR] CLOptions::AsInt() :: Parameter \"" << param_name << "\" is not an integer!" << std::endl;
        return 0 ;
    } else {
        return params_ints[param_name]->getValue();
    }
}

//__________________________________________________________
std::string CLOptions::AsString(const std::string& param_name)
{
    if (params_strings.count(param_name) == 0) {
        std::cerr << "[ERROR] CLOptions::AsString() :: Parameter \"" << param_name << "\" is not a string!" << std::endl;
        return 0 ;
    } else {
        return params_strings[param_name]->getValue();
    }
}

//__________________________________________________________
void CLOptions::PrintDetailed()
{
    // Print the values of the parameters in detail
    PrintBools(true) ;
    PrintDoubles(true) ;
    PrintInts(true) ;
    PrintStrings(true) ;
}

//__________________________________________________________
void CLOptions::PrintSimple()
{
    // Print the values of the parameters without descriptions
    PrintBools(false) ;
    PrintDoubles(false) ;
    PrintInts(false) ;
    PrintStrings(false) ;
}

//__________________________________________________________
void CLOptions::PrintBools(bool detailed)
{
    // Dont do anything if the map is emtpy
    if (params_bools.empty()) return ;
    
    // Print a parameter header if doing detailed
    if (detailed) {
        std::printf("*****************\n") ;
        std::printf("  BOOLEANS\n") ;
        std::printf("*****************\n") ;
    }
    
    // Now loop through each of the parameters
    std::map<std::string, CLBool*>::iterator iter ;
    for (iter=params_bools.begin(); iter!=params_bools.end(); ++iter) {
        if (detailed) {iter->second->Print() ;}
        else          {iter->second->PrintSimple() ;}
    }
}

//__________________________________________________________
void CLOptions::PrintDoubles(bool detailed)
{
    // Dont do anything if the map is emtpy
    if (params_doubles.empty()) return ;
    
    // Print a parameter header if doing detailed
    if (detailed) {
        std::printf("*****************\n") ;
        std::printf("  DOUBLES\n") ;
        std::printf("*****************\n") ;
    }
    
    // Now loop through each of the parameters
    std::map<std::string, CLDouble*>::iterator iter ;
    for (iter=params_doubles.begin(); iter!=params_doubles.end(); ++iter) {
        if (detailed) {iter->second->Print() ;}
        else          {iter->second->PrintSimple() ;}
    }
}

//__________________________________________________________
void CLOptions::PrintInts(bool detailed)
{
    // Dont do anything if the map is emtpy
    if (params_ints.empty()) return ;
    
    // Print a parameter header if doing detailed
    if (detailed) {
        std::printf("*****************\n") ;
        std::printf("  INTEGERS\n") ;
        std::printf("*****************\n") ;
    }
    
    // Now loop through each of the parameters
    std::map<std::string, CLInt*>::iterator iter ;
    for (iter=params_ints.begin(); iter!=params_ints.end(); ++iter) {
        if (detailed) {iter->second->Print() ;}
        else          {iter->second->PrintSimple() ;}
    }
}

//__________________________________________________________
void CLOptions::PrintStrings(bool detailed)
{
    // Dont do anything if the map is emtpy
    if (params_strings.empty()) return ;
    
    // Print a parameter header if doing detailed
    if (detailed) {
        std::printf("*****************\n") ;
        std::printf("  STRINGS\n") ;
        std::printf("*****************\n") ;
    }
    
    // Now loop through each of the parameters
    std::map<std::string, CLString*>::iterator iter ;
    for (iter=params_strings.begin(); iter!=params_strings.end(); ++iter) {
        if (detailed) {iter->second->Print() ;}
        else          {iter->second->PrintSimple() ;}
    }
}

//__________________________________________________________
void CLOptions::PrintHelp(const std::string& executable_name)
{
    std::cout << "\nUSAGE: " << executable_name << " [options]" << std::endl;
    std::cout << "\nAVAILABLE OPTIONS:" << std::endl;
    
    // Specify the help information
    std::printf("  -h, -help [no argument]\n") ;
    PrintDescription("Prints out this help information.") ;
    
    // Loop through the parameters and print their current values
    
    // BOOLEANS
    std::map<std::string, CLBool*>::iterator bool_itr ;
    for (bool_itr=params_bools.begin(); bool_itr!=params_bools.end(); ++bool_itr) {
        std::printf("  -%s [bool, default=%d]\n",
                    bool_itr->second->getParamName().c_str(),
                    bool_itr->second->getDefault()) ;
        PrintDescription(bool_itr->second->getDescription()) ;
    }
    // DOUBLES
    std::map<std::string, CLDouble*>::iterator dbl_itr ;
    for (dbl_itr=params_doubles.begin(); dbl_itr!=params_doubles.end(); ++dbl_itr) {
        std::printf("  -%s [double, default=%f]\n",
                    dbl_itr->second->getParamName().c_str(),
                    dbl_itr->second->getDefault()) ;
        PrintDescription(dbl_itr->second->getDescription()) ;
    }
    // INTEGERS
    std::map<std::string, CLInt*>::iterator int_itr ;
    for (int_itr=params_ints.begin(); int_itr!=params_ints.end(); ++int_itr) {
        std::printf("  -%s [int, default=%d]\n",
                    int_itr->second->getParamName().c_str(),
                    int_itr->second->getDefault()) ;
        PrintDescription(int_itr->second->getDescription()) ;
    }
    // STRINGS
    std::map<std::string, CLString*>::iterator str_itr ;
    for (str_itr=params_strings.begin(); str_itr!=params_strings.end(); ++str_itr) {
        std::printf("  -%s [string, default=%s]\n",
                    str_itr->second->getParamName().c_str(),
                    str_itr->second->getDefault().c_str()) ;
        PrintDescription(str_itr->second->getDescription()) ;
    }
    std::cout << std::endl;
}

//__________________________________________________________
void CLOptions::PrintDescription(const std::string& param_description)
{
    // Split the description into individual words
    std::vector<std::string> desc_words = CLOptionsHelper::split(param_description, ' ') ;
    std::vector<std::string>::iterator word ;
    
    int current_length(0) ;
    
    for (word=desc_words.begin(); word!=desc_words.end(); ++word) {
        // If there are no words on this line, print the next word
        if (current_length == 0) {
            for (int s=0; s<pad_description_width; s++) std::cout << " " ;
            std::cout << (*word) << " " ;
            current_length = pad_description_width + word->length() + 1 ;
        }
        // Else, if the next word would send us over the limit of the
        // line, print a new line and then print the word
        else if (current_length+word->length() > max_width) {
            std::cout << std::endl ;
            for (int s=0; s<pad_description_width; s++) std::cout << " " ;
            std::cout << (*word) << " " ;
            current_length = pad_description_width + word->length() + 1 ;
        }
        // Else, just print the word
        else {
            std::cout << (*word) << " " ;
            current_length += word->length() + 1 ;
        }
    }
    std::cout << std::endl;
}

//__________________________________________________________
void CLOptions::DefineParams()
{
    // Clear out the longopts object
    longopts.clear() ;
    
    // Resize it to hold exactly the number of variables we need
    int options_count = params_bools.size() +
                        params_doubles.size() +
                        params_ints.size() +
                        params_strings.size() + 2 ;
    longopts.resize(options_count) ;
    int opt_num(0) ;
    
    // Add the help option
    longopts[opt_num++] = {"help", no_argument, 0, 'h'} ;
    
    // Add the bool options
    std::map<std::string, CLBool*>::iterator biter ;
    for (biter=params_bools.begin(); biter!=params_bools.end(); ++biter)
        longopts[opt_num++] = {biter->first.c_str(), required_argument, 0, 'b'} ;
    
    // Add the double options
    std::map<std::string, CLDouble*>::iterator diter ;
    for (diter=params_doubles.begin(); diter!=params_doubles.end(); ++diter)
        longopts[opt_num++] = {diter->first.c_str(), required_argument, 0, 'd'} ;
    
    // Add the int options
    std::map<std::string, CLInt*>::iterator iiter ;
    for (iiter=params_ints.begin(); iiter!=params_ints.end(); ++iiter)
        longopts[opt_num++] = {iiter->first.c_str(), required_argument, 0, 'i'} ;
    
    // Add the string options
    std::map<std::string, CLString*>::iterator siter ;
    for (siter=params_strings.begin(); siter!=params_strings.end(); ++siter)
        longopts[opt_num++] = {siter->first.c_str(), required_argument, 0, 's'} ;
    
    // Add the terminating options
    longopts.back() = {0,0,0,0} ;
}

//__________________________________________________________
// Note this method returns true when there has been an error reading
// from the file
bool CLOptions::FillFromFile(const std::string& filename)
{
    std::cout << "Filling from " << filename << std::endl;
    // First make sure that the file can actually be opened for reading
    if (!CLOptionsHelper::file_exists(filename)) {
        return true ;
    }
    
    // Open the supplied file
    std::ifstream configFile(filename) ;
    std::string line ;
    while (std::getline(configFile, line)) {
        // Skip if the line is empty
        if (line.empty()) continue ;
        // Skip if the line is a comment
        if (line.find(configfile_comment) == 0) continue ;
        
        // Split the line on spaces
        std::vector<std::string> param = CLOptionsHelper::split(line, ' ') ;
        
        // Create a separate string vector that represents the user
        // defined values for this parameter
        std::vector<std::string> values(param.begin()+1, param.end()) ;
        if (values.size() == 0) continue ;
        
        // Now actually set the parameter
        if (!SetParam(param.front(), values)) return false ;
    }
    
    return false ;
}

#endif /* CLOptions_h */
