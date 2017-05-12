# Yildiz-Engine module-audio-openal.

This is the official repository of the OpenAl Module, part of the Yildiz-Engine project.
The openAl module is an implementation of the audio-module, based on OpenAl-soft library.

## Features

* Ogg streaming.
* Wav sound file reading.
* ...

## Requirements

To build this module, you will need a java 8 JDK, Mingw64, and Maven 3.

## Coding Style and other information

Project website:
http://www.yildiz-games.be

Issue tracker:
https://yildiz.atlassian.net

Wiki:
https://yildiz.atlassian.net/wiki

Quality report:
https://sonarqube.com/overview?id=be.yildiz-games:module-audio-openal

## License

All source code files are licensed under the permissive MIT license
(http://opensource.org/licenses/MIT) unless marked differently in a particular folder/file.

## Build instructions

Go to your root directory, where you POM file is located.

Then invoke maven

for windows:

	mvn clean install -Denv=win32 -Pnative
	
for linux:

	mvn clean install -Denv=linux64 -Pnative


This will compile the source code, then run the unit tests, and finally build a jar file and DLL/SO for the environment you chose.

This can only be done on linux, window does not support cross compilation.

To build the linux artifact, some libraries must be installed:

	apt-get install openal-dev
	apt-get install physfs-dev
	apt-get install libsndfile-dev
	
To build the windows artifact, prebuilt libraries are provided.

## Usage

In your maven project, add the dependency

for windows:

```xml
<dependency>
    <groupId>be.yildiz-games</groupId>
    <artifactId>module-audio-openal</artifactId>
    <version>1.0.6</version>
	<classifier>win32</classifier>
</dependency>
```

for linux:

```xml
<dependency>
    <groupId>be.yildiz-games</groupId>
    <artifactId>module-audio-openal</artifactId>
    <version>1.0.6</version>
	<classifier>linux64</classifier>
</dependency>
```
## Contact
Owner of this repository: Grégory Van den Borre
