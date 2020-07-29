doShell
=======

Shell-based browser / UI automation for Linux and Mac OS


## Table of Contents

- [DoShell](#doshell)
  * [What does (will) it do?](#idea---what-does-(will)-it-do?)
  * [Modes of Operation](#modes-of-operation)
    + [Transpile](#transpile)
    + [Transpile and/or run](#transpile-and/or-run)
  + [Runtime macros](#runtime-macros)
  * [Commands](#commands)
    + [Import](#import)
    + [Control flow](#control-flow)
    + [Send keyboard events](#send-keyboard-events)
    + [Browser automation](#web-browser-automation)
      * [Toggle browser panels](#toggle-browser-panels)
      * [Load and manipulate URLs](#load-and-manipulate-urls)
      * [Interact with DOM elements](#interact-with-dom-elements)
      * [Miscellaneous](#miscellaneous)
    + [Terminal automation](#terminal-automation)
    + [Clipboard](#clipboard)
    + [Dialogs and popups](#dialogs-and-popups)
    + [File manipulations](#file-manipulations)
  * [Configuration](#configuration)
  * [Dependencies](#dependencies)
  * [Build Instructions](#build-instructions)
  * [Code Convention](#code-convention)
  * [License](#license)


## Idea - What does (will) it do?

doShell is a superset of shell script, providing commands geared towards 
cross-platform browser / UI and system automation.  

This project is a transpiler and an interpreter
for running doShell scripts.  

Some possible usecases for doShell are End-to-End testing, 
infoSec reconnaisance and creation of productivity macros. 


### Mission targets

1. Ease scripted automation of controlling web browser in- and output
2. Support the same language on linux and mac os
3. Make the language concise: commands should be as short as possible, 
  while as much self-explanatory as possible
4. Don't reinvent the wheel: invoke and reference existing tools
5. (following 4.) While there is no editor, linter or syntax highlightning:
   Enable editors to identify doShell as shell script 
   (mask doShell commands as shell script comments) 


## Modes of Operation

### Transpile

Running ``shdo``, the compiler will find all ``*.do.sh`` files within the 
current working path, including its sub-directories, and 
transpile them into ``*.do.x.sh`` files in the same path.
``*.do.x.sh`` are doShell executable files, that can contain doShell specific
runtime macros and calls to [third party tools](#dependencies) and calls to 
shell tools, built-in into the doShell binary. 
These files can be executed via the doShell interpreter. 


### Transpile and/or run

Running ``shdo -r script.do.sh``, the compiler will transpile the given 
file and execute it. Also already transpiled ``*.do.x.sh`` scripts can
be executed. 

## Runtime macros

The following predefined macros are replaced at runtime by generic content.  

| Macro             | Replaced by                                                      |
| ----------------- | ---------------------------------------------------------------- |
| ``__DATE__``      | Current date in preferred format                                 |
| ``__PWD__``       | Working directory path                                           |
| ``__TIMESTAMP__`` | Current UNIX timestamp                                           |
| ``__OS__``        | ``linux`` or ``darwin``                                          |
| ``__LINE__``      | Line number in current file                                      |
| ``__FILE__``      | Absolute path of current file including the                      |
| ``__DIR__``       | Absolute path of current file                                    |

Arbitrary user-defined runtime macros can be passed JSON-formatted 
when invoking the doShell interpreter to run a ``*.do.x.sh`` file. 

**Example**

Replace all occurences of ``__FOO__`` by ``bar`` before
running the given file:  
``shdo -r script.do.x.sh "{\"__FOO__\":\"bar\"}"`` 


## Commands

### General

All commands accept an optional last argument for pausing execution after having
invoked that command.  

**Example:** Type: "hello", wait 0.5 seconds, type: " world"  

``#type "hello" 0.5`` 
``#type " word"`` 

### Import

doShell can import extracted/separated plaintext
and/or scripts from given files via:  
``#import another_file.do.sh;``  


### Control flow

| Command                    | Description                                                        |
| -------------------------- | ------------------------------------------------------------------ |
| ``sleep 1.5``              | Pause execution for 1.5 seconds (Shell script command)             | 
| ``#wait for any keypress`` | Display notification and pause execution until any key was pressed | 


### Send keyboard events

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

#### Toggle browser panels

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


#### Load and manipulate URLs

| Command                                                     | Description                                          |
| ----------------------------------------------------------- | ---------------------------------------------------- |
| ``$var=#get browserUrl``                                    | Get current URL                                      |
| ``$var=#get browserReferrer``                               | Get referrer URL                                     |
| ``##open url in new browsertab: "https://duckduckgo.com/"`` | Load given URL in new browser tab                    |


#### Interact with DOM elements

| Command                                            | Description                            |
| -------------------------------------------------- | -------------------------------------- |
| ``#focus domElement by id: "someId"``              |                                        |
| ``#focus domElement by query: "#id .someClass"``   |                                        |
| ``#click domElement by id: "someId"``              | Invokes mouse click on given element   |
| ``#click domElement by query: "#id .someClass"``   | Invokes mouse click on given element   |
| ``#click button containing text: "Hit me!"``       | Invokes mouse click on given button    |
| ``#click link containing text: "Hit me!"``         | Invokes mouse click on given link      |


#### Miscellaneous

| Command                         | Description                                          |
| ------------------------------- | ---------------------------------------------------- |
| ``#find inBrowser: "..."``      | Hits CTRL+F or CMD+F, enters given text, hits return |


### Terminal automation

| Command                     | Description                    |
| --------------------------- | ------------------------------ |
| ``#open new terminal``      |                                |
| ``#open new terminalTab``   | Hit CTRL+SHIT+T or CMD+T       |
| ``#edit inTerminal: FILE``  | Open given file in bash editor | 


### Clipboard

| Command                        | Description            |
| ------------------------------ | ---------------------- |
| ``#setClipboard: $value``      |                        |
| ``$value=#getClipboard``       |                        |


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


## Dependencies

Automation is ultimately performed using existing tools from third parties, 
and some doShell built-in tools.

### Linux

* [xddotool](http://manpages.ubuntu.com/manpages/trusty/man1/xdotool.1.html)
* [wmctrl](http://tripie.sweb.cz/utils/wmctrl/)
* [xsel](https://linux.die.net/man/1/xsel)
* xdialog
* Shell script
* doShell executable


### Mac OS

* AppleScript (osascript) - **Note:** Assistive access must be enabled
* Shell script
* doShell executable



Build Instructions
------------------

`cmake CMakeLists.txt; make`


Code Convention
---------------

It is recommended to write doShell scripts according to 
[Google Shell Style Guide](https://google.github.io/styleguide/shell.xml)
where applicable.

The source code of the doShell transpiler and interpreter follows the 
[Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).  


License
-------

doShell is licensed under
[The MIT License (MIT)](https://opensource.org/licenses/MIT)
