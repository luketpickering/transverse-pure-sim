#include "CLITools.hxx"

namespace CLIArgs {
std::vector<Option> OptSpec;
std::vector<std::string> Args;

  Option::Option(){
    ShortName = "";
    LongName = "";
    HasVal = false;
    Required = false;
    Used = false;
    CallBack = [](std::string const &) -> bool { return false; };
    Default = [](){};
  }

  Option::Option(std::string shortname,std::string longname, bool hasval,
    std::function<bool(std::string const &opt)> callback,
    bool required,
    std::function<void()> def,
    std::string valString){
    ShortName = shortname;
    LongName = longname;
    HasVal = hasval;
    CallBack = callback;
    Required = required;
    Default = def;
    ValueIdent=valString;
  }

  bool Option::IsOpt(std::string const &optname) const{
    return ((optname == ShortName) || (optname == LongName));
  }

  std::ostream& operator<<(std::ostream& os, Option const &opt){
    return os << "(" << opt.ShortName << "|" << opt.LongName << ")"
      << "  " << opt.ValueIdent
      << (opt.Required?" [Required]":"");
  }



void AddArguments(int argc, char const * argv[]){
  for(int i = 0; i < argc; ++i){
    Args.emplace_back(argv[i]);
  }
}

bool GetOpts(){
  bool skipNextArg = false;
  for(auto arg_it = std::next(Args.cbegin());
    arg_it < Args.cend(); std::advance(arg_it,1)){

    if(skipNextArg){ skipNextArg = false; continue; } //Allows args with values

    std::string const & arg = *arg_it;

    for(auto &opt : OptSpec){
      if(!opt.IsOpt(arg)) { continue; }

      if(opt.HasVal){
        skipNextArg = true;
        auto next_it = std::next(arg_it);
        if(next_it == Args.cend()){
          std::cout << "Didn't find expected value for Option " << opt.LongName
            << std::endl;
          return false;
        }

        std::string const & val = *next_it;

        if(!opt.CallBack(val)){
          std::cout << "Error Option: " << opt.LongName
            << ": doesn't understand value: \"" << val << "\"" << std::endl;
          return false;
        }

      } else {
        if(!opt.CallBack("")){ //C++11 lambdas cant have default arguments
          std::cout << "Invalid option: " << opt.LongName << std::endl;
          return false;
        }
      }
      opt.Used = true;
    }
  }
  bool AllGood = true;
  for(auto const &opt : OptSpec){
    if(opt.Required && !opt.Used){
      std::cout << "Didn't find and option for " << opt.LongName << std::endl;
      AllGood = false;
    }
    if(!opt.Used){
      opt.Default();
    }
  }
  return AllGood;
}

std::string GetArg(size_t i){ return Args[i]; }
size_t GetNArg(){ return Args.size(); }

void SayRunLike(){
  std::cout << "Run like:\n " << Args.front() << std::flush;
  for(auto const & opt: OptSpec){
    if(opt.Required){
      std::cout << " " << opt.ShortName
        << " " << opt.ValueIdent << std::flush;
    }
  }
  for(auto const & opt: OptSpec){
    if(!opt.Required){
      std::cout << " [" << opt.ShortName
        << " " << opt.ValueIdent << "]" << std::flush;
    }
  }
  std::cout << "\n\n-----------------------------------\n" << std::endl;
  for(auto const & opt: OptSpec){
    std::cout << "[Arg]: " << opt << std::endl;
  }
}

}
