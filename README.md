# KCLib
## Project Overview
A simple C++ static library for working on school projects at Washington State University.

Developed by Kace Cottam.

## Usage
In the [Latest Releases](https://github.com/KaceCottam/KCLib/releases), you will find a zip file. 
Download and unzip that, and extract the `include` and `lib` folders into your project folder.

Make sure that the `include` folder is registered as an additional include directory 
and that the `lib` folder is registered as an additional library directory.

_Make sure to link the `.lib` files!_

Then, you can use
```C++
#include <KCModuleName.hpp>
/* ... */
```
to start using the library.

All definitions are in the `KC` namespace.

## List of Modules
__**TODO: Link**__
- KCConsole
- KCStateMachine
- KCQueues
- KCLinkedLists
- KCNodes

## Copyright Information
**This project is licensed under the [GPL-3.0 License](https://github.com/KaceCottam/KCLib/blob/master/LICENSE)!**

All users must abide by this license.

## Known Bugs

## Troubleshooting

## Credits
A big thanks to [Javidx9](https://github.com/OneLoneCoder) (and [youtube](https://www.youtube.com/javidx9)) for your tutorials! 
I used your tutorials for reference and some of your source code for my `KCConsole` module.

Another big thanks to [TheChernoProject on youtube](https://www.youtube.com/user/TheChernoProject) for your C++ tutorials.
You made it really easy to understand the information about syntax and modern conventions.

A few more thanks to my father, and my professor at Washington State University.

## CHANGELOG
  Version 3.3:
  - Added KCCSVParser, which parses CSV files.

  Version 3.2:
  - Added KCQueues, KCStacks, KCBinarySearchTree
  - Made KCStateMachine transitions into identifiers. Updated the code so it is now an std::unordered_map instead of std::map
  
  Version 3.1b "CMakeRemake":
  - Reformatted entire library to use CMake.
  - Removed KCCore, KCColors, KCController in favor of the new KCConsole module.
