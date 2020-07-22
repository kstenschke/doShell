autolang
========

Desktop automation language for Linux and Mac OS.


## Table of Contents

- [autolang](#autolang)
  * [What does (will) it do?](#what-does--will--it-do-)
  * [Compiler modes](#compiler-modes)
    + [Transpile](#transpile)
    + [Transpile and execute](#transpile-and-execute)
  * [Configuration](#configuration)
  * [Syntax general](#syntax-general)
  * [Comments](#comments)
  * [Commands](#commands)
    + [Control flow](#control-flow)
    + [Simulate keyboard events](#simulate-keyboard-events)
    + [Browser automation](#browser-automation)
    + [Terminal automation](#terminal-automation)
    + [Dialogs and popups](#dialogs-and-popups)


## What does (will) it do?

The autolang compiler transpiles .atl files to shell scripts, 
executable on bash.  Resulting scripts can than start applications, 
activate/switch windows, perform simulated mouse- and keyboard- events 
and more. 

All actual automation is performed using existing third party tools:

* Linux: 
  * [xddotool](http://manpages.ubuntu.com/manpages/trusty/man1/xdotool.1.html)
  * [wmctrl](http://tripie.sweb.cz/utils/wmctrl/)
  * [xsel](https://linux.die.net/man/1/xsel)
* Mac OS:
  * AppleScript (osascript)


## Compiler modes

### Transpile

Running ``alc``, the compiler will find all ``.atl`` files within the 
current working path, including its sub-directories at any level, and 
create ``.sh`` files with the same basename at the same path.

### Transpile and execute

Running ``alc -r script.atl``, the compiler will transpile the given 
file and execute it (no transpiled file is saved).


## Configuration

Via an optional ``.aml.ini`` file the following optional settings can be
given:

``bash_editor=nano`` "editor" being e.g. ``vim``, ``nano``, etc.  
``browser=firefox`` browser to be targeted  


## Syntax general

* Empty lines are ignored.
* Whitespace preceding a comment, used e.g. for indenting is allowed
* Each line is expected to contain no more than one command
* Every command is expected to be ended by: ";\n"
* Whitespace at the end of lines is NOT allowed
* Comments must be written on separate lines


## Comments

There are only single-line, no block comments.
Comments are prefixed either by: ``#`` or ``//``.


## Commands

### Control flow

``sleep [float SECONDS];``  


### Simulate keyboard events

** Hit single key:**  
``keyStrokeBackspace;`` Hit BACKSPACE key  
``keyStrokeEnter;`` Hit ENTER key  
``keyStrokeEsc;`` Hit ESC key  
``keyStrokeTab;`` Hit TAB key  

** Stroke key combination:**  
``keyStrokeCopy;`` Hit CTRL+C or CMD+C  
``keyStrokeCut;`` Hit CTRL+X or CMD+X  
``keyStrokePaste;`` Hit CTRL+V or CMD+V  
``keyStrokeSelectAll;`` Hit CTRL+A or CMD+A  

** Type Text:**  
``type [string "TEXT"];`` Simulate typing given text on keyboard
``type [string "TEXT"] [float SECONDS];`` Type text with given delay between characters
``type [string "TEXT"] [float MIN_SECONDS] [float MAX_SECONDS];`` Type text with random delay within given range between characters


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
