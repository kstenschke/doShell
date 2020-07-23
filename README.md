Shell-Do
========

Shell-based automation for Linux and Mac OS.


## Table of Contents

- [Shell-Do](#shell-do)
  * [What does (will) it do?](#what-does--will--it-do-)
  * [Triggered automation tools](#triggered-automation-tools)
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
    + [Control flow](#control-flow)
    + [Simulate keyboard events](#simulate-keyboard-events)
    + [Browser automation](#browser-automation)
    + [Terminal automation](#terminal-automation)
    + [Dialogs and popups](#dialogs-and-popups)


## Idea - What does (will) it do?

Shell-Do script is a superset of shell script, providing additional commands 
geared towards cross-platform UI automation.  
Shell-Do scripts can be transpiled and run as shell scripts.  

Possible automations are: launching and switching among applications and 
windows, simulating mouse- and keyboard- events, running terminal commands, 
controlling a web browser, some advanced file manipulations and more. 


## Triggered automation tools

Automation is ultimately performed using existing tools from third parties, 
and some built-in tools:

* **Linux:**
  * [xddotool](http://manpages.ubuntu.com/manpages/trusty/man1/xdotool.1.html)
  * [wmctrl](http://tripie.sweb.cz/utils/wmctrl/)
  * [xsel](https://linux.die.net/man/1/xsel)
  * Shell script
  * Shell-Do executable
* **Mac OS:**
  * AppleScript (osascript)
  * Shell script
  * Shell-Do executable


## Modes of Operation

The Do-Shell executable is a compiler, 
can execute Do-Shell scripts and provides some built-in tools that can
be run from the shell:

### Transpile

Running ``shdo``, the compiler will find all ``*.do.sh`` files within the 
current working path, including its sub-directories, and 
create ``*.sh`` files with the same basename at the same path.

### Transpile and execute

Running ``shdo -r script.do.sh``, the compiler will transpile the given 
file and execute it.

### Run built-in actions

A collection of shell tools, executable via the
Shell-Do binary. 

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

* Shell-Do script is a superset of sbell script, 
  scripts can contain all possible shell commands.
* Shell-Do commands look similar to comments containig pseudo-code
* Shell-Do commands are prefixed by #, allowing editors
  to use existing shell script highlightning 
* Shell-Do commands can use any amount of lines
* Every command is expected to be ended by: ";\n"
* Comments must be prefixed by ``//``


## Runtime macros

The following strings are replaced at runtime:  

``__date__`` - current date in preferred format  

``__pwd__`` - working directory path  

``__timestamp__`` - current UNIX timestamp  

``__os__`` - ``linux`` or ``darwin``  

... 


## Commands

### Control flow

``#wait 1.5 SECONDS;``  
``#wait for any keypress;``  


### Simulate keyboard events


**Hit single key:**  
``# keystroke backspace;``  
``# keystroke enter;``   
``# keystroke esc;``  
``# keystroke f1;``
``# keystroke tab;``  
``# keystroke space;``


**Stroke key combination:**  
``# key combo copy;`` = Hit CTRL+C or CMD+c  
``# key combo cut;``  
``keyStrokePaste;`` Hit CTRL+V or CMD+V   
``keyStrokeSelectAll;`` Hit CTRL+A or CMD+A  

**Type text:**  
``type [string "TEXT"];`` Simulate typing given text on keyboard  
``type [string "TEXT"] [float SECONDS];`` Type text with given delay
  between characters  
``type [string "TEXT"] [float MIN_SECONDS] [float MAX_SECONDS];``
  Type text with random delay within given range between characters  


### Browser automation

``activateBrowser;`` Launch or bring preferred browser window to front  
``closeBrowserTab;`` Hits CTRL+W or CMD+W  
``focusNextBrowserTab;`` Hits CTRL+TAB or CMD+TAB  
``focusBrowserURL;`` Hits CTRL+L or CMD+L  
``focusPrevBrowserTab;`` Hits CTRL+SHIFT+TAB or CMD+OPT+TAB  
``openUrlInBrowser [string "URL"];`` Load given URL in new browser tab  
``openFindInBrowser;`` Hits CTRL+F or CMD+F  
``openBrowserDevTools;`` Hits CTRL+SHIFT+I or CMD+OPT+I  
``openBrowserDevConsole;`` Hits CTRL+SHIFT+J or CMD+SHIFT+J  
``openBrowserSettings;`` Hits CTRL+Comma or CMD+Comma  
``openNewBrowserTab;`` Hits CTRL+T or CMD+T  
``reopenBrowserTab;`` Hits CTRL+SHIFT+W or CMD+SHIFT+W  

### Terminal automation

``openNewTerminal;``  
``editInTerminal [string "FILE"];`` Open given file in bash editor  


### Dialogs and popups

``alert [string "TEXT"];``  
``notify [string "TEXT"];``  
