# Pipita-pacs_project
Repository for PACS project 2019-2020

This repository will contain both the project code and the project documentation.

The chosen project is project #50, "Development of an interactive 2D application with OpenFrameworks"

I have implemented a simple application in which the user uses a Kinect (model 1414) to interact with a game similar to Breakout/Arkanoid: the player will control the moving bar with his/her hands.
Both the graphics and the interaction with the Kinect hardware are handled via the libraries provided by openframeworks, using the ofxKinect addon to manage the kinect interaction specifically. 

At the current stage the application grants the possibility to, first, regulate the kinect elevation and then play using motion controls. Once the game has ended, the player can either choose to play another round or to exit the application.

All levels are generated randomly. Further informations on how to play are provided in-game.

In order for the application to work openframeworks is needed, as well as the ofxKinect addon (https://openframeworks.cc/), follow the instruction provided in the website to install it.
In order for ofxKinect to work the libraries and drivers provided by Openkinect (https://openkinect.org/wiki/Getting_Started) are required.

Once openframeworks and the needed drivers have been installed, in order to be able to compile the sources modify the makefile as indicated in the makefile itself.

In order to compile the sources open the directory in a terminal and execute the command "sudo make". If sudo is missing openframeworks will not be able to create the needed folders.

To run the application execute the command "make RunRelease" or enter the bin directory and execute the command "./break_kinect". 

Note that the application has been developed for the usage of the kinect model 1414, thus I cannot guarantee anything about wether it works with more recent models or not. 

Currently the project is being developed in the VSCode editor within an Ubuntu environment

