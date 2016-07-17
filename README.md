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

	mvn clean install -Denv=win64
	
for linux:

	mvn clean install -Denv=linux64

This will compile the source code, then run the unit tests, and finally build a jar file and DLL/SO for the environment you chose.

## Usage

To use the snapshot versions, please add the following repository
https://oss.sonatype.org/content/repositories/snapshots/

Released version are retrieved from maven central.

In your maven project, add the dependency

for windows:

```xml
<dependency>
    <groupId>be.yildiz-games</groupId>
    <artifactId>module-audio-openal</artifactId>
    <version>1.0.0-0-SNAPSHOT</version>
	<classifier>win64</classifier>
</dependency>
```

for linux:

```xml
<dependency>
    <groupId>be.yildiz-games</groupId>
    <artifactId>module-audio-openal</artifactId>
    <version>1.0.0-0-SNAPSHOT</version>
	<classifier>linux64</classifier>
</dependency>
```
## Contact
Owner of this repository: Grégory Van den Borre