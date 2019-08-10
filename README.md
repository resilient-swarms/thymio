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

IMPORTANT: character encoding must be US-UTF8. Can be changed using [raspi-config](https://www.raspberrypi.org/documentation/configuration/raspi-config.md).

First install all dependencies for [ARGoS](https://github.com/ilpincy/argos3), [ASEBA](https://github.com/aseba-community/aseba):

	sudo apt-get install
                            cmake\
                            g++ \
                            git \
                            make \
                            libxml2-dev \
                            libudev-dev \
                            libdashel-dev \

It is necessary to build Aseba from source on Rasberry Pi (on Debian it is sufficient to do sudo apt-get install aseba)

First clone the 1.6.x Aseba release:

	git clone -b release-1.6.x --single-branch https://github.com/aseba-community/aseba.git

change to the cloned repository

	cd aseba

Create the build directory:

	mkdir build_aseba\
	cd build_aseba

Execute cmake:

	cmake ..

Then make and install:

	sudo make install

Aseba is now installed on the Raspberry Pi



To build ARGoS on Raspberry Pi specifically for Thymio:

First clone ARGoS from its repository:

	git clone https://github.com/ilpincy/argos3

Change directory to the cloned repository and create a build_thymio directory:

	cd argos3 \
	mkdir build_thymio\
	cd build_thymio

Execute cmake using following options:

	cmake -DARGOS_BUILD_FOR=thymio -DARGOS_DYNAMIC_LIBRARY_LOADING=OFF -DARGOS_DOCUMENTATION=OFF ../src 

Then build and install ARGoS. This will only compile and build necessary libraries for the execution of the controller codes.

	sudo make install


For Thymio:
First clone this repository:

	git clone https://github.com/resilient-swarms/thymio

Change the current directory to the cloned directory again and create a build_thymio directory there.

	cd thymio /
	mkdir build_thymio /
	cd build_thymio

Now run cmake with the following options:

	cmake -DARGOS_BUILD_FOR=thymio -DThymio_LIBS=<Path to the build_thymio directory inside the ARGoS repository> ..

Then build and install Thymio.

	sudo make install

## Running Experiments on the Raspberry Pi:

To run Thymio_diffusion example or any other example follow the following procedure.

Make sure you are in the thymio directory then execute it using:

    build/src/testing/Thymio_diffusion/Thymio_diffusion -c src/testing/Thymio_diffusion/realtestexperiment.argos -i thymio

The first argument is the path to the experiment's configuration file (.argos). The second argument is the controller's name, which is specified as a tag in the [configuration file](https://github.com/daneshtarapore/Thymio/src/testing/Thymio_diffusion/realtestexperiment.argos#L19).

