shellDo
=======

Shell-based browser / UI automation for Linux and Mac OS


## Table of Contents

- [ShellDo](#shelldo)
  * [What does (will) it do?](#what-does--will--it-do-)
  * [Modes of Operation](#modes-of-operation)
    + [Transpile](#transpile)
    + [Transpile and execute](#transpile-and-execute)
  + [Runtime macros](#runtime-macros)
  * [Commands](#commands)
    + [Imports](#imports)
    + [Control flow](#control-flow)
    + [Simulate keyboard events](#simulate-keyboard-events)
    + [Browser automation](#browser-automation)
    + [Terminal automation](#terminal-automation)
    + [Dialogs and popups](#dialogs-and-popups)
    + [File manipulations](#file-manipulations)
  * [Configuration](#configuration)
  * [Third party dependencies](#third-party-dependencies)


## Idea - What does (will) it do?

ShellDo is a superset of shell script, providing commands geared towards 
cross-platform browser / UI and system automation.  

This project is a compiler for transpiling and running ShellDo scripts.  

ShellDo aims at providing a unified cross-platform option
for scripting non-headless browser automation, helpful e.g.
for End-to-End testing, infoSec reconnaisance and for creating
productivity macros. 
ShellDo's abilities intersect with tools like selenium, puppeteer,
userscripts or browser extensions, but with a less traceable footprint. 


## Modes of Operation

### Transpile

Running ``shdo``, the compiler will find all ``*.do.sh`` files within the 
current working path, including its sub-directories, and 
transpile them into ``*.do.x.sh`` files in the same path.
``*.do.x.sh`` are doShell executable files, that can contain shellDo specific
runtime macros and calls to shell tools, built-in into the shellDo binary, 
these files can be executed via the shellDo interpreter. 


### Transpile and run

Running ``shdo -r script.do.sh``, the compiler will transpile the given 
file and execute it. Also already transpiled ``*.do.x.sh`` scripts can
be executed. 

## Runtime macros

The following macros are only replaced at runtime by generic content.  

| Macro             | Replaced by                                                      |
| ----------------- | ---------------------------------------------------------------- |
| ``__DATE__``      | Current date in preferred format                                 |
| ``__PWD__``       | Working directory path                                           |
| ``__TIMESTAMP__`` | Current UNIX timestamp                                           |
| ``__OS__``        | ``linux`` or ``darwin``                                          |
| ``__LINE__``      | Line number in current file                                      |
| ``__FILE__``      | Absolute path of current file including the                      |
| ``__DIR__``       | Absolute path of current file                                    |


## Commands

### Imports

shellDo can import extracted/separated plaintext and/or scripts from given files via: ``#import another_file.do.sh;``  


### Control flow

| Command                    | Description                               |
| -------------------------- | ----------------------------------------- |
| ``#wait 1.5``              | Pause execution for 1.5 seconds           | 
| ``#wait for any keypress`` | Pause execution until any key was pressed | 


### Simulate keyboard events

**Hit single key:**  

| Command            | Description                            |
| ------------------ | -------------------------------------- |  
| ``#hit backspace`` |                                        |
| ``#hit enter``     |                                        |
| ``#hit esc``       |                                        |
| ``#hit f1``        |                                        |
| ``#hit tab``       |                                        |
| ``#hit space``     |                                        |


**Stroke key combination:**

| Command       | Description             |
| ------------- | ----------------------- |  
|``#copy``      | Hit CTRL+C or CMD+c     |
|``#cut``       | Hit CTRL+X or CMD+x     |
|``#paste``     | Hit CTRL+V or CMD+V     |
|``#selectAll`` | Hit CTRL+A or CMD+A     |

**Type text:**

| Command            | Description                            |
| ------------------ | -------------------------------------- |  
| ``#type "TEXT"``   | Simulate typing given text on keyboard | 


### Web Browser automation

**Activate and toggle browser and its panels:**

| Command                        | Description                                       |
| ------------------------------ | ------------------------------------------------- |
| ``#activate browser``          | Launch or bring preferred browser window to front | 
| ``#close browserTab``          | Hits CTRL+W or CMD+W                              |
| ``#focus browserURL``          | Hits CTRL+L or CMD+L                              |
| ``#focus next browserTab``     | Hits CTRL+TAB or CMD+TAB                          |
| ``#focus previous browserTab`` | Hits CTRL+SHIFT+TAB or CMD+OPT+TAB                |
| ``#open browserDevConsole``    | Hits CTRL+SHIFT+J or CMD+SHIFT+J                  |
| ``#open browserDevTools``      | Hits CTRL+SHIFT+I or CMD+OPT+I                    |
| ``#open browserSettings;``     | Hits CTRL+Comma or CMD+Comma                      |
| ``#open new browserTab``       | Hits CTRL+T or CMD+T                              |
| ``#reopen browserTab``         | Hits CTRL+SHIFT+W or CMD+SHIFT+W                  |

**General browser control**

| Command                        | Description                                       |
| ------------------------------ | ------------------------------------------------- |
| ``#open "URL" inBrowser``      | Load given URL in new browser tab                 |
| ``#find inBrowser "..."``       | Hits CTRL+F or CMD+F                              |


**Actions upon elements in current browser page**

| Command                                         | Description                                       |
| ----------------------------------------------- | ------------------------------------------------- |
| ``#click domElement by id "someId"``            | Invokes mouse click on given element              |
| ``#click domElement by query "#id .someClass"`` | Invokes mouse click on given element              |
| ``#click button containing text "Hit me!"``     | Invokes mouse click on given button               |


### Terminal automation

| Command                     | Description                    |
| --------------------------- | ------------------------------ |
| ``#open newTerminal``       |                                |
| ``#edit inTerminal FILE``   | Open given file in bash editor | 


### Dialogs and popups

| Command                     | Description            |
| --------------------------- | ---------------------- |
| ``#notify "MESSAGE"``       |                        |
| ``#alert "MESSAGE"``        |                        |
| ``#confirm "MESSAGE"``      | Yes/No Dialog          |
| ``#prompt "MESSAGE"``       | Popup with input field |


### File manipulations

All file manipulations allow as optional last argument a destination file path, if not given, they overwrite the
given source file.

| Command                                                           | Description                                             |
| ----------------------------------------------------------------- | ------------------------------------------------------- |
| ``#replaceAll in file path/file search replace``                  | Replace all occurrences of given string                 |
| ``#replaceFirst in file path/file search replace``                | Replace first occurrence of given string                |
| ``#replaceLast in file path/file search replace``                 | Replace last occurrence of given string                 |
| ``#replaceBetween in file path/file before after replacement ``   | Remove text including and between "before" and "after"  |
| ``#extractBetween in file path/file before after``                | Extract text excluding but between "before" and "after" |


## Configuration

Via an optional ``.shdo.ini`` file, the following optional settings can be
given:

| Config                               | Description                                                      |
| ------------------------------------ | ---------------------------------------------------------------- |
| ``bash_editor=nano``                 | Text editor to be used in terminal, e.g. ``vim``, ``nano``, etc. |
| ``browser=firefox``                  | Web browser to be targeted                                       |
| ``date_format=Ymn`` ...              | Date format in printf() syntax                                   |


## Third party dependencies

Automation is ultimately performed using existing tools from third parties, 
and some shellDo built-in tools.

### Linux

* [xddotool](http://manpages.ubuntu.com/manpages/trusty/man1/xdotool.1.html)
* [wmctrl](http://tripie.sweb.cz/utils/wmctrl/)
* [xsel](https://linux.die.net/man/1/xsel)
* xdialog
* Shell script
* Shell-Do executable


### Mac OS

* AppleScript (osascript) - **Note:** Assistive access must be enabled
* Shell script
* shellDo executable
