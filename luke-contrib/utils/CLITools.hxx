#ifndef SEEN_PUREGEN_CLITOOLS_HXX
#define SEEN_PUREGEN_CLITOOLS_HXX

#include <string>
#include <functional>

#include <vector>
#include <iostream>

namespace CLIArgs {

struct Option {
  std::string ShortName;
  std::string LongName;
  std::string ValueIdent;
  bool HasVal;
  bool Required;
  bool Used;
  std::function<bool(std::string const &opt)> CallBack;
  std::function<void()> Default;

  Option();
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

void AddArguments(int argc, char const * argv[]);

bool GetOpts();

std::string GetArg(size_t i);
size_t GetNArg();

extern std::vector<Option> OptSpec;
//I feel that this should work, but it doesn't seem to.
//You can just do OptSpec.emplace_back manually.
template<class... arguments>
void AddToOptSpec(arguments&&... args){
    OptSpec.emplace_back(&args...);
}

void SayRunLike();

}
#endif
