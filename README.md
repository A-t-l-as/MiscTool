# MiscTool
A program for decompiling less important files from the KnightShift game, such as `.dat`, `.int`, etc. <br>

Exporting data from a binary file to a `.cpp` file:
```
MiscTool.exe -e <Path to the input file> -<File type>
```

Supported file types:
* `KsTerrainDat` -- `.dat` terrain file from KnightShift.

Compiling a .cpp file into a binary file with a new extension:
```
MiscTool.exe -c <Path to the source .cpp file> <output format>
```

# Examples of operations

Example of exporting the `teren5.dat` file:
```
MiscTool.exe -e teren5.dat -KsTerrainDat
```

An example of compiling the `teren5.cpp` file into `teren5.dat`:
```
MiscTool.exe -c teren5.cpp dat
```
