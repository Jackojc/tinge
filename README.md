# tinge
**a simple, fast, header-only library for C++ which enables pretty colours on the terminal.**

### Requirements
- Only supports terminals which have support for ANSI escape sequences.
- C++17 compiler needed.
- Works on Linux and Windows 10.

### Examples
![example1](pics/example1.png)


### Code
```cpp
// Core functions.
tinge::print("printing!\n");
tinge::log("logging!\n");
tinge::err("errors!\n");

// Logging.
tinge::notice("notice!\n");
tinge::warn("warning!\n");
tinge::error("error!\n");
tinge::success("success!\n");

// All of the above have newline versions. i.e. `println();`


// Use styles.
tinge::println(tinge::bold, "emphasis");


// Use indentation.
tinge::warnln(tinge::before{tinge::tab(2)}, "2 tabs");
```
