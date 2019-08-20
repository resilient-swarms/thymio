# Thymio

This branch makes a Neural Network controller available for the Raspberry Pi installation. This branch identical to the master branch when using it with ARGoS simulations, so it is recommended to use that branch when simulating.

## For A Raspberry Pi :
This readme assumes you've already followed the steps for installing this repository on a Raspberry Pi in the master branch [here](https://github.com/resilient-swarms/thymio/blob/master/README.md)

First install all dependencies for [SFERES NN](https://github.com/sferes2/nn2):

	sudo apt-get install
                            libboost-serialization-dev \
                            libboost-graph-dev
                            libeigen3-dev \

Change the current directory to the root of the thymio repository i.e.

	cd ~/thymio
	
Now change the repository to be on the nn_controller branch

	git checkout nn_controller

Now download sferes2 which won't need compilation:

    	git clone https://github.com/sferes2/sferes2.git

Now download the neural network module for sferes in the modules directory:

	cd sferes2/modules
	git clone https://github.com/sferes2/nn2.git

Now return to the root of the thymio repository:

	cd ~/thymio

create a build_thymio directory there. If you already have a build_thymio directory after following the master branch instructions it is recommended to delete that build_thymio directory first:

	mkdir build_thymio
	cd build_thymio

Now run cmake with the following options:

	cmake -DARGOS_BUILD_FOR=thymio -DThymio_LIBS=<Path to the build_thymio directory inside the ARGoS repository> ..

Then build and install Thymio.

	sudo make install

## Running Experiments on the Raspberry Pi:

To run thymio_diffusion example or any other example follow the following procedure.

Make sure you are in the thymio directory then execute it using:

    build_thymio/src/testing/thymio_diffusion/thymio_diffusion -c src/testing/thymio_diffusion/realtestexperiment.argos -i thymio

The first argument is the path to the experiment's configuration file (.argos). The second argument is the controller's name, which is specified as a tag in the [configuration file](https://github.com/resilient-swarms/thymio/blob/master/src/testing/thymio_diffusion/realtestexperiment.argos#L19).

If a neural network is available to load it can be run using:

    bash run_thymio.sh

The neural network must be a text archive called BOOST_SERIALIZATION_NVP which can be created and transmitted to a thymio over a network with the [real thymio experiment](https://github.com/resilient-swarms/real-thymio-exp) repository.

