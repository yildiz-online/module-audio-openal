# Yildiz-Engine module-audio-openal.

This is the official repository of the OpenAl Module, part of the Yildiz-Engine project.
The openAl module is an implementation of the audio-module, based on OpenAl-soft library.

## Features

* Ogg streaming.
* FLAC streaming.
* Wav sound file reading.
* 3D audio position.
* ...

## Requirements

To build this module, you will need the latest java JDK, and Maven 3.

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

	mvn clean install
	


This will compile the source code, then run the unit tests, and finally build a jar file and DLL/SO for the environment you chose.

	
To build the windows artifact, prebuilt libraries are provided.

## Usage

In your maven project, add the dependency

```xml
<dependency>
    <groupId>be.yildiz-games</groupId>
    <artifactId>module-audio-openal</artifactId>
    <version>LATEST</version>
</dependency>
```

## Contact
Owner of this repository: Grégory Van den Borre
