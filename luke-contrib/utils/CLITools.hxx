#ifndef SEEN_PUREGEN_CLITOOLS_HXX
#define SEEN_PUREGEN_CLITOOLS_HXX

#include <string>
#include <functional>

#include <vector>
#include <iostream>

namespace CLIArgs {

///Describes a CLI option.
struct Option {
  ///Shorter name usable to invoke on the command line.
  std::string ShortName;
  ///Longer name usable to invoke on the command line.
  std::string LongName;
  ///Value type description used in usage output.
  std::string ValueIdent;
  ///Whether this option is followed by a value.
  bool HasVal;
  ///Whether this option must appear for successful configuration.
  bool Required;
  ///Whether this option has been used.
  bool Used;
  ///The function to invoke when handling this option.
  std::function<bool(std::string const &opt)> CallBack;
  ///The function to invoke when this option was not used.
  std::function<void()> Default;
  ///Whether this instance is a valid option.
  bool IsValid;

  Option();
  Option(Option &from);
  Option(Option &&from);
  Option(std::string shortname,
    std::string longname,
    bool hasval,
    std::function<bool(std::string const &opt)> callback,
    bool required=false,
    std::function<void()> def=[](){},
    std::string valString="Value");

  bool IsOpt(std::string const &optname) const;

  friend std::ostream& operator<<(std::ostream& os, Option const &opt);
};

inline bool operator!(Option const & opt){
  return (!opt.IsValid);
}

///Adds all passed in arguments to the argument list
void AddArguments(int argc, char const * argv[]);
///\brief Adds known arguments and values to argument list, returns array of
///unexpected arguments for external use.
///
///\note The zeroth entry of argv is added to both the internal argument list
/// and the returned array of unexpecteds.
void AddArgumentsAndGetUnexpecteds(int argc, char * argv[], int& retArgc,
  char ** &retArgv);

///Invokes options for found arguments and defaults for unused options.
bool HandleArgs();

///Returns the value of a specific argument.
std::string GetArg(size_t i);
///Returns the number of arguments that have been added.
size_t GetNArg();

///Writes usage options to stdout.
void SayRunLike();

///Attempts to get an option by either ShortName or LongName.
///
///Returns a default option if none is found.
Option GetOpt(std::string const &profopt);

///IMPLEMENTATION:Function which adds a new option to the list of known options.
///
///\note This function is not for external use.
///\todo If AddOpt were not a template then this could be moved to the
///implementation file.
void _PushOption(Option &&opt);

///Checks the validity of and a new CLIArgs::Option.
///
///Parameter pack is expanded into the CLIArgs::Option constructor so for
///relevant arguments, see there.
///returns true if option was added.
template<class ... Args>
bool AddOpt(Args... args){
  Option newopt(args...);

  if(!!GetOpt(newopt.ShortName) || !!GetOpt(newopt.LongName)){
    std::cout << "[ERROR]: Attempting to add option: " << newopt << ", however "
    " the " << ((!!GetOpt(newopt.ShortName))?" Short name: " + newopt.ShortName:
                                             " Long name: " + newopt.LongName)
    << " is already in use by: " << GetOpt(newopt.LongName) << std::endl;
    return false;
  }
  _PushOption(std::move(newopt));
  return true;
}

}
#endif
