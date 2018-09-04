#include <iostream>

int main() {

  int nThreads = 4;
  int dist = 1110;
  
  for (int idThread = 0; idThread < nThreads; idThread++) {
  
  // Compute loop start and end
//     int nchunk = dist / nThreads;
//     int nstart = nchunk * idThread;
//     int nextra = dist % nchunk;
//     if (nextra > 0) {
//       if (idThread < nextra)
//         nchunk++;
//       int k = idThread % nThreads;
//       nstart += std::min(k,nextra);
//     }
//     int nstop = nstart + nchunk;
    
    int nchunk = dist / nThreads;
    int nstart = nchunk * idThread;
    int nextra = dist % nchunk;
    if (idThread < nextra)
      nchunk++;
    nstart += std::min(idThread % nThreads,nextra);
    int nstop = nstart + nchunk;
  
    std::cout << "Thread number " << idThread << " has: " << nstart << " " << nstop << " " << nchunk << std::endl;
    std::cout << "Nextra is: " << nextra << std::endl;
  }
  
  
  
  return 0;

}
