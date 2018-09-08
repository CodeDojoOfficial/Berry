<h1 align="center">
  <a href="/blob/master/README.md"><img src="/images/logo.png" alt="" width="200"></a>
  <br>
  Berry Programming Language
  <br>
  <br>
</h1>

<p align="center">
  <a href="/LICENSE"><img src="https://img.shields.io/github/license/CodeDojoOfficial/Berry.svg?style=for-the-badge" alt="license - MIT"></a>
  <a href="../../releases/latest"><img src="https://img.shields.io/badge/release-1.0.0__0-blue.svg?style=for-the-badge" alt="release - 1.0.0_0"></a>
  <a href="../../releases/latest"><img src="https://img.shields.io/badge/BDK-0-red.svg?style=for-the-badge" alt="BDK 0"></a>
</p>

<p align="center"><i>One of the simplest languages in existance!</i></p>

## A Simple Syntax

Berry has a whopping 8 characters that aren't ignored by it's compiler! No special syntax for comments! You can make your programs as confusing/compact, or as readable/expanded as possible! As the compiler ignores all spaces, comments, and newline characters!

Berry is one of the simplest languages to learn in the entire programming industry!

## Table of Contents

- [Preface: What is an esoteric language?](#preface-what-is-an-esoteric-language)
- [Quick Start](#quick-start)
  - [Installation](#installation)
  - [First Program: Bang!](#first-program-bang)

## Preface: What is an esoteric language?

An esoteric programming language is a language that is made as a joke, and/or is very difficult to comprehend its syntax. Berry is an esoteric language because of it's simple yet complex syntax patterns.

## Quick Start

This section will show you the utmost basics of how to operate the Berry system on your computer.

## Installation

To install Berry, go to the [`latest release`](https://github.com/CodeDojoOfficial/Berry/releases/latest) page and download the zip file.

Once you move it to your desired location, open up a terminal and navigate to it using `cd`.

```bash
$ cd ${YOUR_PATH}
$ unzip ${ZIPFILE}
```

Good! Now you have installed Berry on your computer! You can delete the zip and start programming!

## First Program: Bang!

In this tutorial, you will learn how to print a bang (!) in Berry!

> File: bang.bry

```
+++++ +++++ +++++ +++++ +++++ +++++ +++ .
>>>>> >> .
```

Then enter the terminal and enter the commands.

```bash
$ berry -o bang bang.bry
$ ./bang
!
$ 
```

As you can see, the bang is printed to the terminal, along with a newline. So in this program, all cells (8) are set to 0, except for the last one, which is a newline. You can think of the value in each cell as two things at once. A number, and a character that follows the ASCII and ASCIIE tables.

Each plus increases its value, and each minus decreases its value. You can switch to different cells by using the `<` and `>` characters. This wraps around too. So if you are on cell 8, enter `>`, and you will be on cell 1. ASCII code 33 is a bang. When we had the 33 pluses (see /stylerules for why it is spaced apart), we got to code 33, and printed it with `.`.

We then moved over to the final cell, cell 8. This cell, if you will recall, is always initialized with a newline character, though it can still be edited. We print our newline, and we are done!
