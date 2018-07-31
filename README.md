MBVM
===

About
---
+ See the doc/ directory.

Prerequisites
---
+ CMake
+ CUnit (if testing) (http://cunit.sourceforge.net/)

Building
---
+ Run CMake in the project's root directory
    + `cmake .`
+ Run the appropriate make target depending on if you want to test or not
    + `make mbvm`
    + `make mbvm_test`

Running
---
+ TODO

Testing
---
+ Make sure the test executable has been built (see above)
+ Run the test make target
    + `make test`
+ Alternatively for detailed test output execute the tests directly
    + `./exec/mbvm_test`