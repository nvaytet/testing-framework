#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <strstream>
#include <vector>
// #include "core.h"
#include <omp.h>

using namespace std::chrono;

std::string original(int prec, int n, const char separator) {

  std::vector<double> vec;
  for (int i = 0; i < n; i++) {
    vec.push_back(static_cast<double>(i));
  }

  std::vector<double>::iterator it;
  std::vector<double>::iterator begin = vec.begin();
  std::vector<double>::iterator end = vec.end();

  std::ostringstream output;
  for (it = begin; it != end;) {
    output << std::setprecision(prec) << std::scientific << *it;
    it++;
    if (it != end)
      output << separator;
  }

  return output.str();
}

std::string method1(int prec, int n, const char separator) {

  std::vector<double> vec;
  for (int i = 0; i < n; i++) {
    vec.push_back(static_cast<double>(i));
  }

  std::vector<double>::iterator it;
  std::vector<double>::iterator begin = vec.begin();
  std::vector<double>::iterator end = vec.end();

  int len = n * (prec + 7) - 1;
  char *arr = new char[len];

  std::ostrstream output(arr, len, std::ios_base::out);
  output << std::setprecision(prec) << std::scientific << vec[0];
  it = begin;
  it++;
  while (it != end) {
    output << separator << std::setprecision(prec) << std::scientific << *it;
    it++;
  }
  //     delete[] arr;
  return output.str();
}


std::string omp(int prec, int n, const char separator) {

  std::vector<double> vec;
  for (int i = 0; i < n; i++) {
    vec.push_back(static_cast<double>(i));
  }

  int nt;
  #pragma omp parallel
  {
    nt = omp_get_num_threads();
  }
//   std::cout << nt;
  
  
  std::vector<std::ostringstream> omp_out(nt);
//   for (int i = 0; i < nt; i++){
//     omp_
//   }
  
//   #pragma omp parallel default(shared) private(tid,nthreads) 
  #pragma omp parallel
  {
    int tid = omp_get_thread_num();
    int nthreads = omp_get_num_threads();
    
//     int step = n / nthreads;
//     int istart = tid * step;
//     int iend   = istart + step;
//     std::cout << "thread " << tid << "has istart " << istart << std::endl;
    
//     std::ostringstream output;
    #pragma omp for
    for (int i = 0; i < n; i++) {
//       omp_out[tid] << std::setprecision(prec) << std::scientific << vec[i] << separator;
      omp_out[tid] << vec[i] << separator;
    }
//     std::vector<double>::iterator it;
//     std::vector<double>::iterator begin = vec.begin();
//     std::vector<double>::iterator end = vec.end();

//     std::ostringstream output;
//     for (it = begin; it != end;) {
//       output << std::setprecision(prec) << std::scientific << *it;
//       it++;
//       if (it != end)
//         output << separator;
//     }

//      std::cout << "thread: " << tid << " " << output.str() << std::endl;
  }
  
  for (int i = 1; i < nt; i++){
    omp_out[0] << omp_out[i].str();
  }
  
  return omp_out[0].str();
//   return " ";
}








std::string omp(int prec, int n, const char separator) {

  std::vector<double> vec;
  for (int i = 0; i < n; i++) {
    vec.push_back(static_cast<double>(i));
  }

  int nt;
  #pragma omp parallel
  {
    nt = omp_get_num_threads();
  }
//   std::cout << nt;
  
  
  std::vector<std::ostringstream> omp_out(nt);
//   for (int i = 0; i < nt; i++){
//     omp_
//   }
  
//   #pragma omp parallel default(shared) private(tid,nthreads) 
  #pragma omp parallel
  {
    int tid = omp_get_thread_num();
    int nthreads = omp_get_num_threads();
    
//     int step = n / nthreads;
//     int istart = tid * step;
//     int iend   = istart + step;
//     std::cout << "thread " << tid << "has istart " << istart << std::endl;
    
//     std::ostringstream output;
    #pragma omp for
    for (int i = 0; i < n; i++) {
//       omp_out[tid] << std::setprecision(prec) << std::scientific << vec[i] << separator;
      omp_out[tid] << vec[i] << separator;
    }
//     std::vector<double>::iterator it;
//     std::vector<double>::iterator begin = vec.begin();
//     std::vector<double>::iterator end = vec.end();

//     std::ostringstream output;
//     for (it = begin; it != end;) {
//       output << std::setprecision(prec) << std::scientific << *it;
//       it++;
//       if (it != end)
//         output << separator;
//     }

//      std::cout << "thread: " << tid << " " << output.str() << std::endl;
  }
  
  for (int i = 1; i < nt; i++){
    omp_out[0] << omp_out[i].str();
  }
  
  return omp_out[0].str();
//   return " ";
}























int main() {

  int prec = 10;
  int n = 100000;
  char separator = ',';

  milliseconds ms1, ms2;

  ms1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
  std::string s1 = original(prec, n, separator);
  ms2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
  std::cout << "Original : " << (ms2 - ms1).count() << "\n";

  ms1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
  std::string s2 = method1(prec, n, separator);
  ms2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
  std::cout << "Method1 : " << (ms2 - ms1).count() << "\n";
  
  
  ms1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
  std::string s3 = omp(prec, n, separator);
//   std::cout << s3;
  ms2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
  std::cout << "OMP : " << (ms2 - ms1).count() << "\n";
  
//   std::string message = fmt::format("The answer is {}", 42);

  return 0;
}
