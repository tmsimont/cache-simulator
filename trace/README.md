## Trace

This folder contain all of the files necessary for working with the actual simulation layer.

Please see the [UML](https://github.com/tmsimont/cache-simulator/tree/master/uml)

### Compililing

Tested on GCC 4.8.1:
```
g++ -std=c++11 -o trace *.cc *.cpp
```

This should also compile on Windows

### Running

You'll need some trace files:
```
wget https://www.cs.utexas.edu/users/fussell/courses/cs352.fall98/Homework/cc1.din.Z
wget https://www.cs.utexas.edu/users/fussell/courses/cs352.fall98/Homework/spice.din.Z
wget https://www.cs.utexas.edu/users/fussell/courses/cs352.fall98/Homework/tex.din.Z
```

Unzip these files by running the following command:

```
gunzip *.din.Z
```


#### Arguments
```
[executable] [configuration] < [trace file]
```

Optionally you can redirect the output:
```
[executable] [configuration] < [trace file] > [ouput file]
```

The configuration should be in the format of the c1.txt file in the `/configurations/` directory.



