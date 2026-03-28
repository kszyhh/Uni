# Calculator for Electronics Engineers

Author: Krzysztof Szczepański
Course Project: Object-Oriented Programming Languages (JPO), Electronics and Telecommunications, AGH University of Krakow
About the Project

This document is a summary of a final university project aimed at learning proper software design and implementation methodologies. The application is a calculator that performs basic mathematical operations, specifically tailored for electronics engineers. The program operates in a continuous mode, meaning it constantly stores the last result of the performed operations in its memory.
Features

    Basic mathematical operations: The application supports addition, subtraction, multiplication, and division. It also includes a safeguard against division by zero, which automatically cancels the invalid operation.

    Decibel conversion: Ability to convert values to a logarithmic scale for power, using the formula 10⋅log10​(x). Conversion for voltage is also available based on the formula 20⋅log10​(x). These functions work exclusively for positive numbers (x>0).

    Numeral system switching: The user can change how the current result is displayed in the header. Supported systems include decimal (DEC), binary (BIN), hexadecimal (HEX), and octal (OCT). Note that for BIN, HEX, and OCT modes, the fractional part of the result is ignored (rounded down).

Requirements and Installation

    Language and Standard: C++14 or newer

    Compilers: GCC, Visual Studio

    Build System: CMake

    Operating System: Windows / Linux

Compilation Instructions:
To build the project, open the build_x directory, launch a terminal in that location, and type the cmake .. command. The compiled, ready-to-run project files will be generated in this directory.
User Manual

Upon launching the calculator, the main window is displayed, divided into two sections:

    Information Panel (Header): Located at the top of the screen, it displays the currently selected numeral system (DEC by default) and the current operation result.

    Main Menu: Contains a list of available options numbered from 1 to 9. To select an option, type the corresponding digit and press ENTER. After each operation, the screen is cleared and refreshed to display the latest result.

Architecture and Main Classes

The project was designed using Object-Oriented Programming (OOP) principles, implementing the Strategy design pattern to handle different numeral systems:

    CalculatorEngine: Acts as the core engine of the calculator. It stores the current result, executes mathematical operations, and manages the currently selected display system.

    ConsoleInterface: Handles user interactions. It displays the menu, reads user input, and communicates with the CalculatorEngine object.

    ISystemWyswietlania (DisplaySystem Interface): An abstract interface that defines common methods (strategies) for all numeral systems supported by the calculator.

    Derived Classes (SystemDec, SystemHex, SystemBin, SystemOct): Concrete classes responsible for formatting the calculated numeric result into a text string appropriate for their respective numeral systems.

Used Libraries

    Logic implementation: <cmath> (math functions, logarithms), <bitset> (bitwise operations), <string>, <memory>.

    I/O handling: <iostream>, <sstream>, <iomanip>, <cstdlib>.

    Testing: <gtest/gtest.h> (Google Test framework for unit testing).
