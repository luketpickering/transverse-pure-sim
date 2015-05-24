#include "PureGenUtils.hxx"

namespace PGUtils {
///Converts a string to a long, checking for errors.
///See STR2INT_ERROR for error codes.
STR2INT_ERROR str2int (long &i, char const *s, int base) {
  char *end;
  long  l;
  errno;
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

}
