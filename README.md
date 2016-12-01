# HTTPOverTCP

[![Build Status](https://travis-ci.org/caiomcg/HTTPOverTCP.svg?branch=master)](https://travis-ci.org/caiomcg/HTTPOverTCP)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/caiomcg/HTTPOverTCP/master/LICENSE)

A C++ implementation of the HTTP protocol over TCP under Unix environment.

## Requirements ##

* An Unix Environment.
* C++ Compiler with support for standard 11.

## Build Instructions ##

* Clone the project.
* Move to the debug folder.
* Invoke the makefile.

```
$> git clone https://github.com/caiomcg/HTTPOverTCP.git
$> cd debug
$> make all VERBOSE=true
```

## Execution Instructions ##
* Move to the debug folder.
* Run the created executable file followed by the desired port.

```
$> cd debug
$> ./WebServer 8888
```
