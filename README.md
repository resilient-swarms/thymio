#Thymio
Is an open source simulator based on ARGoS for Thymio robot platform.

##To install:
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



