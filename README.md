# BaseBot [![CodeFactor](https://www.codefactor.io/repository/github/frc5024/basebot/badge)](https://www.codefactor.io/repository/github/frc5024/basebot) [![GitHub license](https://img.shields.io/github/license/frc5024/BaseBot.svg)](https://github.com/frc5024/BaseBot/blob/master/LICENSE) [![DOI](https://zenodo.org/badge/159041740.svg)](https://zenodo.org/badge/latestdoi/159041740)

BaseBot is a complete rewrite of [BarebonesFRC](https://github.com/ewpratten/barebonesfrc) with 2 goals. Do it right, and do it fast. The entire codebase is written in pure c/c++ and some components are being optimized further with the help of assembly analysis.

## Installation
This code can be "installed" in one of two ways. First, is via an official release:

These are the steps:
 - Get the latest release from github
 - Unpack the compressed archive
 - Open it as a folder in vscode
 - Set your team number in wpilib
 - Deploy using wpilib

The second way is to use rolling release / waterfall. Just do the steps above, but use git to clone the master branch instead of grabbing the latest release.

NOTE: 5024 members should always use the second method.


## Deployment
When deploying code to our robots we have a problem where, on the first few tries, the deployment fails due to not being able to find the RIO. Just keep trying, and it will eventually work.

## DriverMenu
This codebase has a modified version of 2018's offseason DriverMenu.

| Action | Controller | When | What it Does |
| -- | -- | -- | -- |
| Hold Y button | Driver's controller | While enabling the robot | Switches to TriggerDrive |

## Building the documentation
To build the documentation, make sure you have doxygen installed, then run:
```sh
doxygen ./doxygen.config 
```
The documentation will the be automattically pushed to the website for this repo.

5024 members should not worry about this because the documentation is automatically built during our code review process.

## Who Made This?
BaseBot is a rewrite of [barebonesFRC](https://github.com/Ewpratten/barebonesFRC) which was based off of the [2017](https://github.com/frc5024/SteamWorks) and [2018](Https://github.com/frc5024/PowerUp) codebases from Team [5024](Https://github.com/frc5024)

BarebonesFRC was originally designed by:
 - [@ewpratten](Https://github.com/ewpratten)
 - [@slownie](Https://github.com/slownie)

And was tested by:
 - [@ewpratten](Https://github.com/ewpratten)
 - [@slownie](Https://github.com/slownie)
 - [@b3alzach1n](https://github.com/b3alzach1n)
 - Ethan (non-githubber)
 - Josh (non-githubber)
 - [@retrax24](Https://github.com/retrax24)
 - [@Volxz](Https://github.com/Volxz)
 - Nick (non-githubber)

BaseBot is developed by the [5024 Programming Team](https://github.com/orgs/frc5024/people) and has been tested by:
 - Aidan
 - Andrea
 - Jeremy
 - Josh
 - Mark
 - Nick

From our drive team

Special thanks to our awesome mentors:
 - [@johnlownie](https://github.com/johnlownie)
 - [@LordMichaelmort](https://github.com/LordMichaelmort)
 - [@awpratten](https://github.com/awpratten)
