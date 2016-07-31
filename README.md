# Connect Four in C
README

Revision History:
6/12/2015 (JB): initial version
6/13/2015 (JB): added .h format
11/07/2015 (JV): Added Compile and Run.

(JV) = Joshua Villasenor
(JB) = Jason Berneberg

### Compile and Run:
dowload and install x11 from http://www.xquartz.org.
Log out and back in.
In this directory type
open terminal and cd to this directory.
% make
% ./ConnectFour

### General program notes:
##### IMPORTANT: The Computer portion of the game has not been implemented and will cause bugs in the program when clicked.

-All code should use 4 space indents and never use tabs.
-Every file should start with a comment that contains the file name.
-Every function made should have a comment before it with file name a a spot for revision history.
-All functions should/files should be cammel case. aka start with lowercase and no underscores.
-All defines should be all caps with underscores.
-All enums will have the suffix Enum in the name. ex: colorEnum
-All structs with have the suffix Struct in the name. ex: rgbStruct
-All code blocks should have the { on the same line as the instruction.
  ex:
  // this is valid
  if (1) {

  // this is  not valid
  if (1)
  {
#### The format of the .h files should be as follows
\#ifndef
\#include
\#define
enum/struct
extern
function prototypes

