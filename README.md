# CERN_GEM_DAQ

To execute a script:

1. c++ --std=c++11 < filename >.cpp $(pkg-config --cflags --libs libmongocxx) -Wl,-rpath,/usr/local/lib

2. ./a.out