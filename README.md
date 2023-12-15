# Assignment: Do My Brackets Match?

**Objectives:**

* Implement a templated list data structure.
* Developing tests and automated code testing using the catch2 framework.
* Implement a stack interface.


## Time Line 
You have about three weeks to complete the assignment. Start right away! **The lab TA will expect that you already have most of that week's work completed. Come with prepared questions and
be prepared to answer the TA's questions about your code.**

* Week 1: DSList class with CATCH2 tests and memory leak debugging using `valgrind/asan`. **Deliverables:** `DSList` implementation + test. DSList already has a stack interface (`push_front()`, `pop_front()`)
* Week 2: DSStack class based on an array with CATCH2 tests and memory leak debugging using `valgrind/asan`. **Deliverables:** `DSStack` implementation + test.
* Week 3: Bracket checking function for a single file and driver program with command line interface. Improve the code and the documentation comments. **Deliverables:** completed project.


## Introduction
Writing code is fun... Well, most of the time. Sometimes I mess up
brackets (i.e., `"[]", "()", "{}"`). 
I have a library of hundreds of
source code files and do not want to manually open each one up in VS Code,
so I need a program to do the checking for me.

The program should be called in the following way:

```
check_brackets <input_files>
```

It should produce the following output:

1. If no error is found: `<input_file>: OK` and return 0 (meaning the program executed successfully)
2. If an error is found: `<input_file>: Bracket mismatch detected` and return 1 (meaning there was a problem).

   Also print debugging information that is as specific as possible. For example:
     - What type of bracket is the issue.
     - The line number of the `input_file` where the issue was detected.
     - The text of the line where the issue was detected.
     - Any information that would help me to fix the issue.

## The Algorithm
Check code for balanced brackets: push `({[` on the stack and take them off when the corresponding `)`, `}`, or `)` is seen. Any error or a non-empty stack at the end of the code indicates a problem.

## The Data
 You can get some source code (e.g., from the examples in this class) and check them. Then introduce some mistakes and check again. The `data` directory contains example files.

## Implementation Requirements
Write good, well documented code!

You **cannot use STL containers for the stack.**
You need to implement two versions of the stack. 

For strings, you can use the STL class`std::string`. Reading STL strings is a 
lot easier than c-strings. See the C++ section of this [IO example](https://github.com/mhahsler/CS2341/blob/main/Chapter1_Programming/io/). 

1. A stack based on your own list class implementation.
2. A stack based on an array. Make sure to use proper memory management. 

Write two programs (add another executable to the `CMakeLists.txt`), one based on a list and one based on a vector/array and compare the runtime on some larger source code files. Your programs should report the runtime every time. See [the code examples in Chapter2 Algorithm Analysis](https://github.com/mhahsler/CS2341/tree/main/Chapter2_Algorithm_Analysis) for examples of how to measure runtime in C++.


## Additional Work (Bonus; max. 5 points)
* Make sure that unbalanced brackets in comments (`//`, and `/*`) and character or string definitions (i.e., in single and double quotation marks) do not produce an error. This means you also can check `\*` and `*\` and string delimiters `"` and `'` for consistency. [up to +2]
* Check all the `clang` source code from [llvm project](https://github.com/llvm/llvm-project) in the directories `clang/include/` and `clang/lib/` to report timing differences between data different structures. [up to +2]
* How would you check `<>` in C++ since it is used in templates, 
but can also be used as comparison operators? [up to +3]
* Better testing: Can you generate a long text file that randomly nested brackets to a specified depth that you can use to test your code better? [+1]
* Can your program make a recommendation of where to place missing brackets? How would it do that. [up to  +2]
* You could use the function call stack as the "stack" in your program and implement the checker as a recursive program. [up to +3] 

## Grading Rubric

|                             | Points Possible | Points Awarded |
| :------------------         | --------------: | -------------: |
| DSList Class                | 20              |                |
| CATCH2 tests DSList         |  5              |                |
| DSStack Class (List)        | 10              |                |
| DSStack Class (Array)       |  5              |                |
| Bracket checker (OK/not OK) | 15              |                |
| Test checker                |  5              |                |
| Runtime comparison          |  5              |                |
| Detailed errors for checker | 10              |                |
| Answer to questions         |  5              |                |
| Proper Memory Management    | 10              |                |
| Formatting, Comments, etc.  |  5              |                |
| Proper use of GitHub        |  5              |                |
| Additional Work             | up to +5        |                |
| 48hr early submission bonus |  + 5            |                |

