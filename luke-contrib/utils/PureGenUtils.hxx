#ifndef SEEN_PUREGEN_UTILS_HXX
#define SEEN_PUREGEN_UTILS_HXX
#include <cstdlib>
#include <cerrno>
#include <climits>

#include <string>
#include <sstream>
#include <vector>
#include <iostream>

namespace PGUtils {

long MakeNuclearPDG(int Z, int A);

enum STR2INT_ERROR { STRINT_SUCCESS,
                     STRINT_OVERFLOW,
                     STRINT_UNDERFLOW,
                     STRINT_INCONVERTIBLE };

///Converts a string to a long, checking for errors.
///See STR2INT_ERROR for error codes.
STR2INT_ERROR str2int (long &i, char const *s, int base=10);

///Converts a string to a int, checking for errors.
///See STR2INT_ERROR for error codes.
STR2INT_ERROR str2int (int &i, char const *s, int base=10);

std::string int2str(int i);

bool str2bool(std::string const &str, bool &retC);
bool str2bool(std::string const &str);

template<typename T, size_t N>
void ClearArray(T (&arr)[N]){
  for(size_t i = 0; i < N; ++i){
    arr[i] = 0;
  }
}

template<typename T>
void ClearPointer(T * &arr, size_t N){
  for(size_t i = 0; i < N; ++i){
    arr[i] = 0;
  }
}

template<typename T, size_t N, size_t M>
void ClearArray2D(T (&arr)[N][M]){
  for(size_t i = 0; i < N; ++i){
    for(size_t j = 0; j < M; ++j){
      arr[i][j] = 0;
    }
  }
}

template<typename T, size_t N>
std::string PrintArray(T const (&arr)[N]){
  std::stringstream ss("");
  ss << "[ ";
  for(size_t i = 0; i < N; ++i){
    ss << arr[i] << (((i+1)==N)?"":", ");
  }
  ss << " ]";
  return ss.str();
}

template<typename T>
std::string PrintArray(const T* arr, size_t N){
  std::stringstream ss("");
  ss << "[ ";
  for(size_t i = 0; i < N; ++i){
    ss << arr[i] << (((i+1)==N)?"":", ");
  }
  ss << " ]";
  return ss.str();
}

//I guess that the pointer array in a statically
//allocated 2D array shouldn't be changed by TTree::GetEntry,
//this is probably alright.
template<typename T, size_t N, size_t M>
T** NewPPOf2DArray(T (&arr)[N][M]){
  T** DynArrOfP = new T*[N];
  for(size_t i =0; i < N; ++i){
    DynArrOfP[i] = arr[i];
  }
  return DynArrOfP;
}

std::vector<std::string> SplitStringByDelim(std::string const &inp,
  char const *delim);
std::vector<float> StringVToFloatV(
  std::vector<std::string> const &stringV);

std::vector<int> StringVToIntV(
  std::vector<std::string> const &stringV);
}

#endif
