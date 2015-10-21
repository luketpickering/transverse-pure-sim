#include <stdexcept>

#include "PureGenUtils.hxx"


namespace PGUtils {

long MakeNuclearPDG(int Z, int A){
  // 100%03d%03d0 % Z, A
  return 1000000000L + Z*10000L + A*10L;
}

///Converts a string to a long, checking for errors.
///See STR2INT_ERROR for error codes.
STR2INT_ERROR str2int (long &i, char const *s, int base) {
  char *end;
  long  l;
  (void)errno;
  l = strtol(s, &end, base);
  if ((errno == ERANGE && l == LONG_MAX) || l > LONG_MAX) {
      return STRINT_OVERFLOW;
  }
  if ((errno == ERANGE && l == LONG_MIN) || l < LONG_MIN) {
      return STRINT_UNDERFLOW;
  }
  if (*s == '\0' || *end != '\0') {
      return STRINT_INCONVERTIBLE;
  }
  i = l;
  return STRINT_SUCCESS;
}

///Converts a string to a int, checking for errors.
///See STR2INT_ERROR for error codes.
STR2INT_ERROR str2int (int &i, char const *s, int base) {
  long holder;
  STR2INT_ERROR retC = str2int(holder,s,base);
  if(retC != STRINT_SUCCESS){
    return retC;
  }
  if(holder > INT_MAX) {
    return STRINT_OVERFLOW;
  } else if (holder < INT_MIN){
    return STRINT_UNDERFLOW;
  }
  i = holder;
  return retC;
}

std::string int2str(int i){
  std::stringstream ss("");
  ss << i;
  return ss.str();
}

bool str2bool(std::string const &str, bool &retC){
  if(str == "1" || str == "true" ){
    retC = true;
    return true;
  }
  if(str == "0" || str == "false" ){
    retC = true;
    return false;
  }
  retC = false;
  return false;
}

bool str2bool(std::string const &str){
  bool dummy;
  return str2bool(str,dummy);
}

std::vector<std::string> SplitStringByDelim(std::string const &inp,
  char const *delim){

  size_t nextOccurence = 0;
  size_t prevOccurence = 0;
  std::vector<std::string> outV;
  bool AtEnd = false;
  // std::cout << inp << std::endl;
  while(!AtEnd){
    // std::cout << "[SplitStringByDelim] prevOccurence: " << prevOccurence << std::endl;
    nextOccurence = inp.find_first_of(delim,prevOccurence);
    // std::cout << "[SplitStringByDelim] nextOccurence: " <<
      // ((nextOccurence == std::string::npos)?-1:nextOccurence) << std::endl;
    if(nextOccurence == std::string::npos){
      if(prevOccurence == inp.length()){
        // std::cout << "[SplitStringByDelim] Found trailing delimiter." << std::endl;
        break;
      }
      AtEnd = true;
    }
    outV.push_back(inp.substr(prevOccurence,(nextOccurence-prevOccurence)));
    // std::cout << "[SplitStringByDelim] Added string: " << outV.back()
      // << std::endl;
    prevOccurence = nextOccurence+1;
  }
  return outV;
}

std::vector<float> StringVToFloatV(
  std::vector<std::string> const &stringV){

  std::vector<float> outV;
  for(auto const & str : stringV){
    float flt = 0.0;
    try{
      flt = std::stof(str);
    } catch (const std::invalid_argument& ia) {
      std::cout << "Couldn't parse str: \"" << str << "\"\n\t"
        << ia.what() << std::endl;
      throw;
    }
    outV.push_back(flt);
  }
  return outV;
}

std::vector<int> StringVToIntV(
  std::vector<std::string> const &stringV){

  std::vector<int> outV;
  for(auto const & str : stringV){
    int ihldr = 0.0;
    try{
      ihldr = std::stoi(str);
    } catch (const std::invalid_argument& ia) {
      std::cout << "Couldn't parse str: \"" << str << "\"\n\t"
        << ia.what() << std::endl;
      throw;
    }
    outV.push_back(ihldr);
  }
  return outV;
}

}
