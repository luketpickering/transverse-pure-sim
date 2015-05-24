#include <iostream>
#include <assert.h>

#include "PureGenUtils.hxx"

using namespace PGUtils;

void Str2Int_Tests(){
/************************************str2int***********************************/
  char const * word = "hello";
  char const * neg = "-53";
  char const * zero = "0";
  char const * posit = "+748";
  char const * small = "-21474836470";
  char const * decimal = "0.576";
  char const * large = "21474836470";
  char const * good = "16";

  int test = 0;
  assert(str2int(test, word) == STRINT_INCONVERTIBLE);
  std::cout << "[PASSED] str2int test #1" << std::endl;
  assert(str2int(test, neg) == STRINT_SUCCESS); assert(test == -53);
  std::cout << "[PASSED] str2int test #2" << std::endl;
  assert(str2int(test, zero) == STRINT_SUCCESS); assert(test == 0);
  std::cout << "[PASSED] str2int test #3" << std::endl;
  assert(str2int(test, posit) == STRINT_SUCCESS); assert(test == 748);
  std::cout << "[PASSED] str2int test #4" << std::endl;
  assert(str2int(test, small) == STRINT_UNDERFLOW);
  std::cout << "[PASSED] str2int test #5" << std::endl;
  assert(str2int(test, decimal) ==STRINT_INCONVERTIBLE);
  std::cout << "[PASSED] str2int test #6" << std::endl;
  assert(str2int(test, large) == STRINT_OVERFLOW);
  std::cout << "[PASSED] str2int test #7" << std::endl;
  assert(str2int(test, good) == STRINT_SUCCESS); assert(test == 16);
  std::cout << "[PASSED] str2int test #8" << std::endl;

  std::cout <<
"*******************************************************************************"
"**\n"
"******************************PASSED str2int tests*****************************"
"**\n"
"*******************************************************************************"
"**"  << std::endl;
/******************************************************************************/
}

int main(){
  std::cout <<
"*******************************************************************************"
"**\n"
"*******************************************************************************"
"**\n"
"**********************************TESTS****************************************"
"**\n"
"*******************************************************************************"
"**\n"
"*******************************************************************************"
"**"  << std::endl;
  Str2Int_Tests();
  return 0;
}
