# Spacify
### *Currently under development*
## Overview
VST3 audio effect plugin to turn your sample into a "spacey" sound featuring three different options:

*Far Out*

*Lift Off*

*Other Worldly*
## Effects
### Far Out - Heavy use of reverb and chorus to create a sound as if you are far out in outer space.
### Lift Off - Heavy use of distortion and chorus to create a distorted sound as if you had just lift off to mars.
### Other Worldly - Heavy use of multiple different effects to create an other worldly sound.
## Concepts
This project was written in C++ using the Juce framework.
### Object Oriented Programming
The project is entirely written in an object oriented C++ (other than the framework) which I coded in Visual Studios.
The frontend user application was a combination of slider and button objects with text to create an appealing menu of options for the user.
The source code for this part of the project is within the PluginEditor files.
### Algorithms
The algorithms used to create the different effects were made by mathematical changes within the input audio that is stored in a 2-dimensional buffer array.
These effects were made by tweaking previously created effect algorithms to create a specifically desired sound.
The source code for this part of the project is within the PluginProcessor files, with the bulk of the work in the processBlock method.
## Visulization
*Images of the final product and demonstration video will appear here*
