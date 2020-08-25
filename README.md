# Pipita-pacs_project
Repository for PACS project 2019-2020

This repository will contain both the project code and the project documentation.

The chosen project is project #50, "Development of an interactive 2D application with OpenFrameworks"

I will implement a simple application in which the user will use a Kinect ( model 1414) to interact with a game similar to Breakout: the player will control the moving bar with his/her hands.
Both the graphics and the interaction with the Kinect hardware will be handled via the libraries provided by openframeworks, using the ofxKinect addon to manage the kinect interaction specifically. 

At the current stage the application grants the possibility to, first, regulate the kinect elevation and then play using motion controls.

Currently I am working on the possibility to play again without exiting from the application and on optimization issues.

In order for the application to work openframeworks is needed, as well as the ofxKinect addon (https://openframeworks.cc/), follow the instruction provided in the website to install it.
In order for ofxKinect to work the libraries and drivers provided by Openkinect (https://openkinect.org/wiki/Getting_Started).

Note that the application has been developed for the usage of the kinect model 1414, thus I cannot guarantee anything about wether it works with more recent models or not. 

Currently the project is being developed in the VSCode editor within an Ubuntu environment

