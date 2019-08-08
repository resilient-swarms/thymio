# Thymio

Is an open source simulator based on ARGoS framework for Thymio robotic platform. It uses an interface, which is developed using core libraries from ASEBA and DaSHEL.

## Installing Thymio on a desktop computer:
This version of Thymio on a desktop computer is mainly used for simulation.
First clone this repository:

	git clone https://github.com/resilient-swarms/thymio

Then change directory to the repository you have cloned and create "build" directory using:

    mkdir build
    
Then move to this directory:

    cd build
    
Now execute:

    cmake -DCMAKE_BUILD_TYPE=Release ..
    
Now compile the code using:

    make
    
Now install from binaries using:

    sudo make install
    
You have now installed Thymio's simulator

To execute the examples:
Go to the parent directory of "build".

execute:

    argos3 -c src/testing/Thymio_diffusion/testexperiment.argos

Or any other example present inside the testing directory.

## For A Raspberry Pi :
First you should prepare the environment. You need internet connection and to configure WLAN use information from the [official documentation](https://www.raspberrypi.org/documentation/configuration/wireless/wireless-cli.md)

First install all dependencies for [ARGoS](https://github.com/ilpincy/argos3), [ASEBA](https://github.com/aseba-community/aseba) and [DaSHEL](https://github.com/aseba-community/dashel):

	sudo apt-get install
                            cmake\ 
                            libxml2-dev \
                            g++ \
                            git \
                            make \
                            libenki-dev \
                            libdashel-dev \
                            aseba 

To build ARGoS on Raspberry Pi specifically for Thymio:

First clone ARGoS from its repository:

	git clone https://github.com/ilpincy/argos3

Change directory to the cloned repository and create a build_thymio directory:

	mkdir build_thymio\
	cd build_thymio

Execute cmake using following options:

    cmake -DARGOS_BUILD_FOR=thymio -DARGOS_DYNAMIC_LIBRARY_LOADING=OFF -DARGOS_DOCUMENTATION=OFF ../src 

Then build and install ARGoS. This will only compile and build necessary libraries for the execution of the controller codes.


For Thymio:
First clone this repository:

	git clone https://github.com/resilient-swarms/thymio

Change the current directory to the cloned directory again and create a build_thymio directory there. Then run cmake with the following options:

    cmake -DARGOS_BUILD_FOR=thymio -DThymio_LIBS=<Path to the build_thymio directory inside the ARGoS repository> ..

Then build and install Thymio.

IMPORTANT: character encoding must be changed to US-UTF8 using [raspi-config](https://www.raspberrypi.org/documentation/configuration/raspi-config.md).

## Running Experiments on the Raspberry Pi:

To run Thymio_diffusion example or any other example follow the following procedure.

Make sure you are in the build/testing/Thymio_diffusion directory and the executable file is available then execute it using:

    sudo ./Thymio_diffusion -c "/home/pi/Thymio/src/testing/Thymio_diffusion/realtestexperiment.argos" -i thymio

The first argument is the path to the experiment's configuration file (.argos). The second argument is the controller's name, which is specified as a tag in the [configuration file](https://github.com/daneshtarapore/Thymio/blob/6ab255c84a1a258e4a0cf1bd8c7dead4feb64bf1/src/testing/Thymio_diffusion/testexperiment.argos#L19).

