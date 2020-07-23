DoSH (do shell) 
===============

Shell-based automation for Linux and Mac OS.


## Table of Contents

- [DoSH](#dosh-do-shell)
  * [What does (will) it do?](#what-does--will--it-do-)
  * [Compiler modes](#compiler-modes)
    + [Transpile](#transpile)
    + [Transpile and execute](#transpile-and-execute)
    + [Run built-in action] 
  * [Configuration](#configuration)
  * [Syntax general](#syntax-general)
  * [Comments](#comments)
  * [Runtime macros] 
  * [Commands](#commands)
    + [Control flow](#control-flow)
    + [Simulate keyboard events](#simulate-keyboard-events)
    + [Browser automation](#browser-automation)
    + [Terminal automation](#terminal-automation)
    + [Dialogs and popups](#dialogs-and-popups)


## Idea - What does (will) it do?

DoSH is a superset of shell script, providing additional commands 
geared towards cross-platform system automation.
DoSH can be transpiled into executable shell scripts.  

Possible automations are: launching and switching among applications and 
windows, simulating mouse- and keyboard- events, running terminal commands, 
controlling a web browser, some advanced file manipulations and more. 

Automation is ultimately performed using existing third party and some built-in
tools:

* **Linux:**
  * [xddotool](http://manpages.ubuntu.com/manpages/trusty/man1/xdotool.1.html)
  * [wmctrl](http://tripie.sweb.cz/utils/wmctrl/)
  * [xsel](https://linux.die.net/man/1/xsel)
  * Shell script
  * atl executable
* **Mac OS:**
  * AppleScript (osascript)
  * Shell script
  * atl executable


## Compiler modes

### Transpile

Running ``dosh``, the compiler will find all ``.do.sh`` files within the 
current working path, including its sub-directories, and 
create ``.sh`` files with the same basename at the same path.

### Transpile and execute

Running ``dosh -r script.do.sh``, the compiler will transpile the given 
file and execute it.

### Run built-in action

A collection of shell tools, executable from the
DoSH binary. 


``atl replaceInFile file search replace;``
...  

## Configuration

Via an optional ``.dosh.ini`` file, the following optional settings can be
given:

``bash_editor=nano`` "editor" being e.g. ``vim``, ``nano``, etc.  
``browser=firefox`` browser to be targeted  
``date_format=Ymn`` ... 


## Language / syntax

* DoSH is a superset of SHell script, 
  scripts can contain all possible shell commands.
* DoSH commands look similar to comments containig pseudo-code
* DoSH commands are prefixed by #, allowing editors
  to use existing shell script highlightning 
* DoSH commands can use any amount of lines
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

``#sleep 1.5 SECONDS;``  


### Simulate keyboard events

**Hit single key:**  
``# keystroke backspace;``  
``# keystroke enter;``   
``# keystroke esc;``  
``# keystroke tab;``   

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
