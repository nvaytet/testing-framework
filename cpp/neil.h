#ifndef NEIL_H_
#define NEIL_H_


namespace Neil {

int num_threads = 1;

// _OPENMP is automatically defined if openMP support is enabled in the
// compiler.
#ifdef _OPENMP

#include <omp.h>

#pragma omp parallel
{
  num_threads = omp_get_num_threads();
}

// #else //_OPENMP

// num_threads = 1;

#endif

}
#endif // MANTID_KERNEL_MULTITHREADED_H_
