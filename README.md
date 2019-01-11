# DeepSpace [![CodeFactor](https://www.codefactor.io/repository/github/frc5024/deepspace/badge)](https://www.codefactor.io/repository/github/frc5024/deepspace) [![DOI](https://zenodo.org/badge/162623857.svg)](https://zenodo.org/badge/latestdoi/162623857)

Our DeepSpace code is built on top of [BaseBot](https://github.com/frc5024/basebot). The documentation can be found [HERE](https://frc5024.github.io/DeepSpace/)

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

## Building Documentation
To build the c++ documentation, we use a custom Doxygen config. To use this config, run this command on a linux machine:
```sh
doxygen ./doxygen.config
```

To build the Controller Layout files, run this command (`python3` may need to be changed to `python`):
```sh
python3 ./buildcml.py ./controller_layout.cml.json
```

NOTE: Linux is required for the doxygen documents due to our use of unix-style path notation.

## Pull requests
Pull requests is our prefered method of merging code. For a PR to be merged, it must:
 - Pass style checking
 - Be approved by a mentor or team lead
 - Compile without any errors or warnings

## Deployment
When deploying code to our robots we have a problem where, on the first few tries, the deployment fails due to not being able to find the RIO. Just keep trying, and it will eventually work.

## The team
This codebase is built and tested by the [5024 programming team](https://github.com/frc5024) with help from our mentors:
 - [@johnlownie](https://github.com/johnlownie)
 - [@LordMichaelmort](https://github.com/LordMichaelmort)
 - [@awpratten](https://github.com/awpratten)