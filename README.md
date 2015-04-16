# The Chewable Framework

Chewable is designed to make your life easier for game development. It is a C++ component-based framework that aims to serve as a solid foundation for getting a game up and running quicker.

It is as minimal as a library can be and does not require any dependencies to compile (uses gtest for unit tests). It does <b>NOT</b> include features for windowing, input, graphics, audio but the framework's design allows these systems to be plugged in easily.

For some of the features mentioned above and others such as level management and data format specific serialization, check the <a href="https://github.com/chryan/delectable">Delectable Engine</a>.

NOTE: This framework was originally hosted on Google Code, and is used by the game <a href="http://www.deity-game.com/">Deity</a>.

# Chewable Features
Chewable implements the following key features:
* Component-based architecture
* Reflection & serialization utilities (including an extensible serialization system)
* Fast event/delegate system
* Object, game state, and resource management
* Math and various utilities
* Debugging tools: logging, profiling, assertions
* Utilities: math, high-precision timers, threading

The project is currently only supported on Windows (with projects files for MSVC2010). If you are interested in porting the framework to Mac/Linux, please drop me an email.

Unit tests have been written for almost all features/utilities for the project. Technical documentation and tutorials will be added as soon as I have time to write some. In the meantime, http://dev.chryan.com/ has some articles related to implementation details of Chewable.
