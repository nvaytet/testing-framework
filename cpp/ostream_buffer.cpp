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

std::string original(int prec, int n, const std::string separator) {

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

std::string method1(int prec, int n, const std::string separator) {

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


std::string omp(int prec, int n, const std::string separator) {

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








std::string omp_iter(int prec, int n, const std::string separator) {

  std::vector<double> vec;
  for (int i = 0; i < n; i++) {
    vec.push_back(static_cast<double>(i));
  }

  int nt = 0;
  #pragma omp parallel
  {
    nt = omp_get_num_threads();
  }
  std::cout << nt;
  
  
  
//   std::vector<double>::iterator it;
  std::vector<double>::iterator begin = vec.begin();
  std::vector<double>::iterator end = vec.end();
  
  std::vector<std::ostringstream> omp_out(nt);
//   for (int i = 0; i < nt; i++){
//     omp_
//   }
  
//   #pragma omp parallel default(shared) private(tid,nthreads) 
  
  // Get the distance between begining and end
  int dist = std::distance(begin, end);
  
  #pragma omp parallel
  {
    int tid = omp_get_thread_num();
//     int nthreads = omp_get_num_threads();
    
//     int step = n / nthreads;
//     int istart = tid * step;
//     int iend   = istart + step;
//     std::cout << "thread " << tid << "has istart " << istart << std::endl;
    
//     std::ostringstream output;
    
    std::vector<double>::iterator it;
    
    
    
    #pragma omp for
//     for (it = begin; it != end;) {
    for (int i = 0; i < dist; i++) {
//       omp_out[tid] << std::setprecision(prec) << std::scientific << vec[i] << separator;
      omp_out[tid] << separator << *(begin + i);
//       it++;
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
  
  
//   for (int i = 0; i < nt; i++){
//     std::cout << omp_out[i].str() << std::endl;
//   }
  
  
  
  for (int i = 1; i < nt; i++){
    omp_out[0] << omp_out[i].str();
    
  }
  
  int sep_len = separator.length();
  
  return omp_out[0].str().erase(0,sep_len);
//   return " ";
}























int main() {

  int prec = 10;
  int n = 1000000;
  const std::string separator = ",";

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
  ms2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
  std::cout << "OMP : " << (ms2 - ms1).count() << "\n";
  
  ms1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
  std::string s4 = omp_iter(prec, n, separator);
  ms2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
  std::cout << "OMP_ITER : " << (ms2 - ms1).count() << "\n";
//   std::cout << s4;
  
//   std::string message = fmt::format("The answer is {}", 42);

  return 0;
}































// // In Strings.h

// template <typename ITERATOR_TYPE>
// DLLExport std::string join(ITERATOR_TYPE begin, ITERATOR_TYPE end,
//                            const std::string &separator) {
//   
//   int nThreads = PARALLEL_NUMBER_OF_THREADS;
// //   #pragma omp parallel
// //   {
// //     nThreads = PARALLEL_NUMBER_OF_THREADS;
// //   }
// 
// //   if (nThreads == 0) {
// //     
// //     std::ostringstream output;
// //     ITERATOR_TYPE it;
// //     for (it = begin; it != end;) {
// //       output << *it;
// //       it++;
// //       if (it != end)
// //         output << separator;
// //     }
// //     return output.str();
// //     
// //   } else {
//   
//   std::vector<std::ostringstream> output(nThreads);
//   
//   // Get the distance between begining and end
//   long int dist = std::distance(begin, end);
//     
//   #pragma omp parallel
//   {
//     int idThread = PARALLEL_THREAD_NUMBER;
//     ITERATOR_TYPE it;
//     
//     
//     #pragma omp for
//     for (int i = 0; i < dist; i++) {
//       output[idThread] << separator << *(begin + i);
//     }
//   }
//   
//   for (int i = 1; i < nThreads; i++){
//     output[0] << output[i].str();
//   }
//   
// //   int sep_len = separator.length();
//   
//   return output[0].str().erase(0,separator.length());
//     
// //   }
// 
// }
