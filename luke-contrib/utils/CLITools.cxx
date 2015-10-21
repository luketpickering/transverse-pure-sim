#include <set>
#include <numeric>
#include <utility>

#include "CLITools.hxx"

namespace CLIArgs {
std::vector<Option> OptSpec;
std::vector<std::string> Args;

Option::Option(){
  IsValid = false;
}

Option::Option(
  std::string shortname,
  std::string longname,
  bool hasval,
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
  ValueIdent = valString;
  Used = false;
  IsValid = true;
}

Option::Option(Option &from){

  ShortName = from.ShortName;
  LongName = from.LongName;
  ValueIdent = from.ValueIdent;

  HasVal = from.HasVal;
  CallBack = from.CallBack;
  Required = from.Required;
  Default = from.Default;
  Used = from.Used;
  IsValid = from.IsValid;
}

Option::Option(Option &&from) :
  ShortName( std::move(from.ShortName) ),
  LongName( std::move(from.LongName) ),
  ValueIdent( std::move(from.ValueIdent) ){

  HasVal = from.HasVal;
  CallBack = from.CallBack;
  Required = from.Required;
  Default = from.Default;
  Used = from.Used;
  IsValid = from.IsValid;
}

bool Option::IsOpt(std::string const &optname) const{
  return ((optname == ShortName) || (optname == LongName));
}

std::ostream& operator<<(std::ostream& os, Option const &opt){
  return os << "(" << opt.ShortName << "|" << opt.LongName << ")"
    << (opt.HasVal?" " + opt.ValueIdent:std::string(""))
    << (opt.Required?" [Required]":"");
}

Option GetOpt(std::string const &profopt){
  for(auto &opt : OptSpec){
    if(!opt.IsOpt(profopt)) {
      continue;
    }
    return opt;
  }
  return Option();
}

void AddHelp(){
  AddOpt("-h","--help", false,
  [&] (std::string const &opt) -> bool {
    SayRunLike();
    exit(0);
  });
}

void AddArguments(int argc, char const * argv[]){
  AddHelp();
  for(int i = 0; i < argc; ++i){
    Args.emplace_back(argv[i]);
  }
}

void AddArgumentsAndGetUnexpecteds(int argc, char * argv[], int& retArgc,
  char ** &retArgv){
  AddHelp();
  std::set<int> Unexpecteds;
  //The first argument is the invocation command, we always want this.
  Args.emplace_back(argv[0]);
  for(int i = 1; i < argc; ++i){

    Option const & opt = GetOpt(argv[i]);
    if(!opt){
      //if we didn't find it, then it is 'unexpected and should be handed back.'
      Unexpecteds.insert(i);
      continue;
    }
    Args.emplace_back(argv[i]);
    if(opt.HasVal){
      ++i;
      Args.emplace_back(argv[i]);
    }
  }
  //Anyone else will also, likely, always want this.
  retArgv = new char *[Unexpecteds.size()+1];
  retArgc = 1;
  retArgv[0] = argv[0];

  //Add other unexpecteds to the out array.
  for(const int & ux : Unexpecteds){
    retArgv[retArgc] = argv[ux];
    retArgc++;
  }
}

bool HandleArgs(){
  bool skipNextArg = false;

  for(auto arg_it = std::next(Args.cbegin());
    arg_it < Args.cend(); std::advance(arg_it,1)){

    if(skipNextArg){ skipNextArg = false; continue; } //Allows args with values

    std::string const & arg = *arg_it;

    Option opt = GetOpt(arg);

    if(!opt){
      std::cout << "Unexpected Option: " << arg << std::endl;
      return false;
    }

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

  for(auto const &opt : OptSpec){
    if(!opt.Used){
      opt.Default();
    }
  }

  //Check that all that should have been used, were used.
  return std::accumulate(OptSpec.begin(),OptSpec.end(), true,
  [] (bool const &acc, Option const & opt) -> bool {
    if(!acc){ return acc; }
    if(opt.Required && !opt.Used){
      std::cout << "Didn't find an option for " << opt.LongName << std::endl;
      return false;
    }
    return true;
  });
}

std::string GetArg(size_t i){ return Args[i]; }
size_t GetNArg(){ return Args.size(); }

void SayRunLike(){
  std::cout << "Run like:\n " << Args.front() << std::flush;
  for(auto const & opt: OptSpec){
    if(opt.Required){
      std::cout << " " << opt.ShortName
        << (opt.HasVal?" " +opt.ValueIdent:std::string("")) << std::flush;
    }
  }
  for(auto const & opt: OptSpec){
    if(!opt.Required){
      std::cout << " [" << opt.ShortName
        << (opt.HasVal?" " + opt.ValueIdent:std::string("")) << "]"
        << std::flush;
    }
  }
  std::cout << "\n\n-----------------------------------\n" << std::endl;
  for(auto const & opt: OptSpec){
    std::cout << "[Arg]: " << opt << std::endl;
  }
}

void _PushOption(Option &&opt){
  OptSpec.push_back( std::move(opt) );
}

}
