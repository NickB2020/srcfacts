# Build

Create a build directory and move into it:

```console
mkdir build
cd build
```

Once in your build directory (~/srcFacts/build), run cmake:

```console
cmake ..
```

An example input file is provided. To run with make:

```console
make run
```

To run on the command line:

```console
./srcFacts < libxml2.xml
```

You can also time it:

```console
time ./srcFacts < libxml2.xml
```

By default, cmake assumes aCMAKE_BUILD_TYPE of Debug.
For a (much) faster program:

```console
cmake .. -DCMAKE_BUILD_TYPE=Release
```
