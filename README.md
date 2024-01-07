# Order Book
# About
A data structure to maintain price point levels of bid & ask orders.

## File Structure
- `dependencies` sub directory has all the third party libraries used. They are either pre built or are built by the project.
- `scripts` has 4 scripts
  - `build.sh` is to build the code. No args required
  - `run_benchmarks.sh` is to run the code along with the benchmark suite.
  - `run_memory_check_and_tests.sh` is to run the tests along with a memory profile tool.
  - `run_tests.sh` is to run the 
- `src` has all the source code
  - Has its own `CMakeLists.txt` and can be added to an external project.
- `tests` has just one file with tests in it. More can be added there and run `run_benchmarks.sh` or `run_memory_check_and_tests.sh` to test. Add details in the comments within the file. Code will have to be rebuilt after the changes are made.
- `benchmarks.cpp` has the benchmarks and more can be added there. Add details in the comments within the file.  Code will have to be rebuilt after the changes are made.

## Usage
- Run the build script `scripts/build.sh` and run the corresponding scripts from the directory to test.
- To add tests or benchmarks, visit the `tests/tests.cpp` or `benchmarks.cpp` respectively. Follow the comments to add the tests or benchmarks and rebuild the project.

## Assumptions
- Snapshot sample in the task description did not have the 'symbol' key. I have added it for being able to test better.
- No filtering is to be done based on the values of price and volume even if they are non positive since no range was mentioned in the task description.
- Datatype of price and volume will be double.
- State of the order book is not to be stored when the program terminates. Example: Store the data into a database at termination of the program.

## Comments and Thougths
- Even though latency is critical, I have implemented the order book to be dynamically allocated rather than storing it on stack memory which is much faster. This is for the reason that many object creations might have given a memory overflow.
- Choosing a contiguous container (e.g. vector) for the data structure might have made operations faster but keeping it sorted and reordering is much easier through a map.
- Logs not implemented intentionally.
- Shortcomings in this implementation:
  - Multi threading can be added here but I believe it is better to implement at the user application level invoking this library and hence did not think that it is required here. Not sure if you were expecting that. 
  - Tests should have been passed at runtime through a file so that the code wouldn't have to be re-built after each test case edit.
  - There are some functions written in the source code specifically for the purpose of testing. It is not the best practice but since the order_book class is private, there was no better way to test those functions and implement dummy functions within the class.
  Alternate option would have been to implement tests within the source code as some people on the forums have done. It would have made the source code equally ugly.
  - Templates should have been implemented. I did not feel the need here, though it would have made the data structure a little more generic without adding any runtime overhead.
