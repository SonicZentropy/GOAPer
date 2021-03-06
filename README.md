# GOAPer

A simple STRIPS-like Goal Oriented Action Planning Framework for UE4

This branch is built on UnrealEngine 4.15.0. See branches for previous engine versions.

C++ plugin designed to be used in Blueprints (although can be used in C++). Includes editor customisations and per-project state configuration.

Based on:

http://alumni.media.mit.edu/~jorkin/goap.html

https://en.wikipedia.org/wiki/STRIPS

Includes a sample project with a (very) basic shooter agent. Otherwise follow the intructions for install and use.

Using a very crude forward search planning algorithm starting from current state at present. Needs work.

##Instructions 

1. Install the GOAPer Plugin
2. Create a project
3. Go to Project Settings -> Plugins -> GOAPer
4. Here you configure all the state atoms you want to use
5. Create Blueprints based on GOAPAction for each action
  1. Set the PreConditions and Effects in the blueprint defaults (you will see the values from the plugin settings)
  2. Set other parameters such as tick rate, interaction radius etc.
  3. Override the 'Execute' method. This should return false until the action completes, then return true
  4. Remember to set the GOAPState effects before returning true
6. Create a Blueprint based on GOAPAIController
  1. Set the AvailableActions, consisting of the GOAPActions you have created
  2. Set the Starting State
  3. Set the default Goal

##Todo

1. Add more comprehensive and robust planning algorithms
2. Continue building out demo project
