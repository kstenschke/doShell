shellDo
=======

Shell-based UI automation for Linux and Mac OS


## Table of Contents

- [ShellDo](#shelldo)
  * [What does (will) it do?](#what-does--will--it-do-)
  * [Modes of Operation](#modes-of-operation)
    + [Transpile](#transpile)
    + [Transpile and execute](#transpile-and-execute)
    + [Run built-in actions](#run-built-in-actions)
      + [File manipulations](#file-manipulations)
  * [Configuration](#configuration)
  * [Syntax general](#syntax-general)
  * [Comments](#comments)
  * [Runtime macros](#runtime-macros)
  * [Commands](#commands)
    + [Imports](#imports)
    + [Control flow](#control-flow)
    + [Simulate keyboard events](#simulate-keyboard-events)
    + [Browser automation](#browser-automation)
    + [Terminal automation](#terminal-automation)
    + [Dialogs and popups](#dialogs-and-popups)
  * [Third party dependencies](#third-party-dependencies)


## Idea - What does (will) it do?

This project is a compiler for transpiling and running ShellDo scripts.  

ShellDo script is a superset of shell script, providing commands geared towards 
cross-platform browser / UI and system automation.  

Possible automations are: launching and switching among applications and 
windows, simulating mouse- and keyboard- events, running terminal commands, 
and more. Focus of shellDo are simulated user interactions to control and manipulate
web browsers by scripted interaction with the web browser's developer tools. 


## Modes of Operation

### Transpile

Running ``shdo``, the compiler will find all ``*.do.sh`` files within the 
current working path, including its sub-directories, and 
create ``*.sh`` files with the same basename at the same path.

### Transpile and run

Running ``shdo -r script.do.sh``, the compiler will transpile the given 
file and execute it. Also already transpiled scripts or plain shell scripts,
not containing any shellDo commands, can be executed. 

### Run built-in actions

Helpful shell tools, built-in and executable via the shellDo binary: 

#### File manipulations

All file manipulations allow as optional last argument a destination file path, if not given, they overwrite the
given source file.

| Command                                          | Description                                             |
| ------------------------------------------------ | ------------------------------------------------------- |
| ``shdo replaceAllInFile file search replace``    | Replace all occurrences of given string                 |
| ``shdo replaceFirstInFile file search replace``  | Replace first occurrence of given string                |
| ``shdo replaceLastInFile file search replace``   | Replace last occurrence of given string                 |
| ``shdo removeBetweenInFile file before after``   | Remove text including and between "before" and "after"  |
| ``shdo extractBetweenInFile file before after``  | Extract text excluding but between "before" and "after" |


## Configuration

Via an optional ``.shdo.ini`` file, the following optional settings can be
given:

| Config                                           | Description                                                      |
| ------------------------------------------------ | ---------------------------------------------------------------- |
| ``bash_editor=nano``                             | Text editor to be used in terminal, e.g. ``vim``, ``nano``, etc. |
| ``browser=firefox``                              | Web browser to be targeted                                       |
| ``date_format=Ymn`` ...                          | Date format in printf() syntax                                   |


## Language / syntax

* ShellDo script is a superset of shell script, 
  scripts can contain all possible shell commands.
* Shell-Do commands look similar to comments containig pseudo-code
* Shell-Do commands are prefixed by #, allowing editors
  to use existing shell script highlightning 
* Every command is expected to be ended by: ";\n"
* Comments must be prefixed by ``//``


## Runtime macros

The following macros are only replaced at runtime by generic content.  
**Note:** Scripts making use of runtime macros require the shellDo binary fro being executed 
(they cannot be run just by using the plain shell).

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

Before any other transposing and processing, shellDo imports extracted/separated 
plaintext and/or scripts from given files:

``#import another_file.do.sh;``  


### Control flow

``#wait 1.5 SECONDS;``  
``#wait for any keypress;``  


### Simulate keyboard events


**Hit single key:**  
``#keystroke backspace;``  
``#keystroke enter;``   
``#keystroke esc;``  
``#keystroke f1;``  
``#keystroke tab;``  
``#keystroke space;``


**Stroke key combination:**  
``#key combo copy;`` = Hit CTRL+C or CMD+c  
``#key combo cut;``  
``#keystroke paste;`` Hit CTRL+V or CMD+V   
``#keystroke selectAll;`` Hit CTRL+A or CMD+A  

**Type text:**  
``#type [string "TEXT"];`` Simulate typing given text on keyboard  


### Browser automation

``#activate browser;`` Launch or bring preferred browser window to front  
``#close browserTab;`` Hits CTRL+W or CMD+W  
``#focus nextBrowserTab;`` Hits CTRL+TAB or CMD+TAB  
``#focus BrowserURL;`` Hits CTRL+L or CMD+L  
``#focus prevBrowserTab;`` Hits CTRL+SHIFT+TAB or CMD+OPT+TAB  
``#open UrlInBrowser [string "URL"];`` Load given URL in new browser tab  
``#open findInBrowser;`` Hits CTRL+F or CMD+F  
``#open browserDevTools;`` Hits CTRL+SHIFT+I or CMD+OPT+I  
``#open browserDevConsole;`` Hits CTRL+SHIFT+J or CMD+SHIFT+J  
``#open browserSettings;`` Hits CTRL+Comma or CMD+Comma  
``#open newBrowserTab;`` Hits CTRL+T or CMD+T  
``#reopen browserTab;`` Hits CTRL+SHIFT+W or CMD+SHIFT+W  

### Terminal automation

``#open newTerminal;``  
``#edit inTerminal [string "FILE"];`` Open given file in bash editor  


### Dialogs and popups

``#alert [string "TEXT"];``  
``#notify [string "TEXT"];``  
``#confirm [string "TEXT"];``  - Yes/No Dialog
``#prompt [string "TEXT"];``  - Popup with input field


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

* AppleScript (osascript)
* Shell script
* shellDo executable
