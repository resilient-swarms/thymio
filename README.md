# Thymio

Is an open source simulator based on ARGoS for Thymio robot platform.

## To install:

first create "build" directory using:

    mkdir build
    
Then move to this directory:

    cd build
    
Now execute:

    cmake -DCMAKE_BUILD_TYPE=Release ../src
    
Now compile the code using:

    make
    
Now install from binaries using:

    sudo make install
    
You have now installed Thymio's simulator

To execute the examples:
Go to the parent directory of "build".

execute:

    argos3 -c src/testing/testexperiment.argos


## For A Raspberry Pi :

First install all dependencies for ARGoS, ASEBA and DaSHEL, then build them from source. When building ARGoS from source on a Raspberry Pi QtOpenGL is now required and also the build must be specifically for Thymio robot. 

When building ASEBA, disable Enki from the cmake file by commenting [this](https://github.com/aseba-community/aseba/blob/85c2b3a679cb4137e24afaf88c55067c0f65eac7/CMakeLists.txt#L22) line out:

    include(CMakeModules/enki.cmake)


To build ARGoS on Raspberry Pi specifically for Thymio:

Create a build_thymio directory

First execute cmake using following options:

    cmake –DARGOS_BUILD_FOR=thymio ../src 

Then build and install ARGoS. This will only compile and build necessary libraries for the execution of the controller codes.

###For DaSHEL
normal build and install is enough.

###For Thymio:
First create a build_thymio directory in Thymio’s directory. Then run cmake with following options:

    Cmake –DARGOS_BUILD_FOR=Thymio –Dthymio_LIBS=<Path to the build_thymio directory inside ARGoS repository> ../src

Then build and install Thymio.



