# MBVM

## About
+ See the doc/ directory.

## Building
### Prerequisites
+ CMake >= 3.10
    + `sudo yum install cmake3` or `sudo apt install cmake` (also available via cygwin)
+ CUnit (if testing) (http://cunit.sourceforge.net/)
    + `sudo yum install CUnit CUnit-devel` or `sudo apt install libcunit1 libcunit1-dev`

### Building with CMake
+ Run CMake in the project's root directory
    + `cmake .`
+ Run the appropriate make target depending on if you want to test or not
    + `make mbvm`
    + `make mbvm_test`

## Running
+ TODO

## Testing
### Unit tests
The unit tests are built into a separate executable using CUnit. They will all
run at once, there is currently not a way to run them individually.
+ Make sure the test executable has been built (see above)
+ Run the test make target
    + `make test`
+ Alternatively for detailed test output execute the tests directly
    + `./exec/mbvm_test`
### Blackbox tests
The blackbox test script executes the programs in the test_programs/ directory
and verifies their output against known expected output.
+ Make sure the main executable has been built (see above)
+ Run the 'test_programs.py' python script via `python test_programs.py` or
`./test_programs.py`
    + This won't work on Windows currently