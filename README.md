doShell
=======

Browser UI and terminal automation for Linux and Mac OS


## Table of Contents

- [DoShell](#doshell)
  * [What does (will) it do?](#idea---wat-does-(will)-it-do?)
  * [Modes of Operation](#modes-of-operation)
    + [Transpile and/or run](#transpile-and/or-run)
    + [Communication between browsers and runtime system](#communication-between-browsers-and-runtime-system)
  + [Runtime macros](#runtime-macros)
  * [Commands](#commands)
    + [Import](#import)
    + [Dialogs](#dialogs)
    + [String manipulation](#string-manipulation)
    + [Send keystrokes](#send-keyboard-events)
    + [Clipboard](#clipboard)
    + [Browser automation](#web-browser-automation)
      * [Toggle browser panels](#toggle-browser-panels)
      * [Load and manipulate URLs](#load-and-manipulate-urls)
      * [Interact with DOM elements](#interact-with-dom-elements)
    + [Terminal automation](#terminal-automation)
    + [File manipulation](#file-manipulation)
    + [Functions, iterations, conditions](#functions-iterations-conditions) 
  * [Configuration](#configuration)
  * [Dependencies](#dependencies)
  * [Build Instructions](#build-instructions)
  * [Code Convention](#code-convention)
  * [License](#license)


## Idea - What does (will) it do?

doShell is a superset of shell script, providing commands geared towards 
non-headless cross-platform browser and terminal automation.  
Possible doShell usecases are end-to-end testing, 
infoSec reconnaisance and creation of productivity macros.  


This project is a source-to-source (S2S) transpiler and a runtime system
for executing doShell scripts.


### Mission targets

1. Ease scripted automation of controlling web browser in- and output
2. Support the same language on linux and mac os
3. Make it concise: 
   1. Commands should be short, but self-explanatory
   2. To avoid 50% of doShell scripts being ``sleep`` commands,
   automation commands imply a plausible successive minimum delay 
5. Don't reinvent the wheel:  
   1. Reuse existing tools  (shell script, xdotool / applescript, ...)  
   2. While there is no dedicated editor, linter or syntax highlightning
   for doShell: Enable IDEs to identify doShell as shell script 
   (mask doShell commands as shell script comments)   


## Modes of Operation

![Transpiler](/images/doshell_diagram.png)


### Transpile and/or run

Running ``shdo -r script.do.sh``, the transpiler will translate the given 
file and the runtime system will execute it.
When running an already transpiled ``*.do.x.sh`` script, the translation is skipped.

doShell transpiles to regular shell script, which additionally to conventional shell script code 
can contain runtime macros: placeholder-strings for generic content.  
The doShell runtime system replaces runtime macros before execution in a sandboxed shell-thread. 

### Communication between browsers and runtime system

For communication from web browsers back to the runtime sytem, the doShell runtime system in 
parallel to the shell for script execution, launches another shell thread which listens to 
a local network port and stores incoming data for further processing.  
Web browsers than can send-out data to the open port, via HTTP POST invoked by JavaScript 
run from the browser's devConsole.

#### Enable CORS in Firefox

Open Firefox, and on the address bar, type about:config. .
Click on I'll be careful,I promise!".  
Search for security.fileuri.strict_origin_policy.  
Right-click and select Toggle to change the value from true to false. .
Close the browser and launch it again.  

In Chrome, cross scripting is handled automatically


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

### Import

doShell can import extracted/separated plaintext
and/or scripts from given files via:  
``#import another_file.do.sh;``  


### Dialogs

| Command                     | Description            |
| --------------------------- | ---------------------- |
| ``#notify "MESSAGE"``       |                        |
| ``#alert "MESSAGE"``        |                        |
| ``#confirm "MESSAGE"``      | Yes/No Dialog          |
| ``#prompt "MESSAGE"``       | Popup with input field |


# String manipulation

| Command                                                   | Description                                             |
| --------------------------------------------------------- | ------------------------------------------------------- |
| ``#replaceAllInVar $VAR search replace``                  | Replace all occurrences of given string                 |
| ``#replaceFirstInVar $VAR search replace``                | Replace first occurrence of given string                |
| ``#replaceLastInVar $VAR search replace``                 | Replace last occurrence of given string                 |
| ``#replaceBetweenInVar $VAR before after replacement ``   | Remove text including and between "before" and "after"  |
| ``#extractBetweenInVar $VAR before after``                | Extract text excluding but between "before" and "after" |


### Send keystrokes

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

| Command             | Description             |
| ------------------- | ----------------------- |  
|``#copy``            | Hit CTRL+C or CMD+c     |
|``#copyInTerminal``  | Varies by OS            |
|``#cut``             | Hit CTRL+X or CMD+x     |
|``#paste``           | Hit CTRL+V or CMD+V     |
|``#pasteInTerminal`` | Varies by OS            |
|``#selectAll``       | Hit CTRL+A or CMD+A     |


**Type text:**

| Command               | Description                                    |
| --------------------- | ---------------------------------------------- |  
| ``#type "TEXT"``      | Simulate typing given text on keyboard         |
| ``#copyPaste "foo"``  | Copy text to clipboard and invoke paste. ``*`` |

``* Oftentimes a faster alternative over typing``  


### Clipboard 

| Command                        | Description                             |
| ------------------------------ | --------------------------------------- |
| ``#setClipboard $value``       | Copy text to clipboard                  |
| ``#copyPaste "foo"``           | Copy text to clipboard and invoke paste |
| ``$value=#getClipboard`        |                                         |

| Command                                                      | Description            |
| ------------------------------------------------------------ | ---------------------- |
| ``#replaceAllInClipboard search replace``                  | Replace all occurrences of given string                 |
| ``#replaceFirstInClipboard search replace``                | Replace first occurrence of given string                |
| ``#replaceLastInClipboard search replace``                 | Replace last occurrence of given string                 |
| ``#replaceBetweenInClipboard before after replacement ``   | Remove text including and between "before" and "after"  |
| ``#extractBetweenInClipboard before after``                | Extract text excluding but between "before" and "after" |


### Web Browser automation  

**Note:** At the time being doShell was tested using Chromium and Firefox.


#### Toggle browser panels

| Command                      | Description                                                                                 |
| ---------------------------- | ------------------------------------------------------------------------------------------- |
| ``#activateBrowser``         | Launch or bring preferred browser window to front                                           | 
| ``#closeBrowserTab``         | Hits CTRL+W or CMD+W                                                                        |
| ``#focusBrowserURL``         | Hits CTRL+L or CMD+L                                                                        |
| ``#focusNextBrowserTab``     | Hits CTRL+TAB or CMD+TAB                                                                    |
| ``#focusPreviousBrowserTab`` | Hits CTRL+SHIFT+TAB or CMD+OPT+TAB                                                          |
| ``#openBrowserDevConsole``   | Hits CTRL+SHIFT+J or CMD+SHIFT+J (firefox) or CTRL+SHIFT+P / CMD+SHIFT+P in Chrome/Chromium |
| ``#openBrowserDevTools``     | Hits CTRL+SHIFT+I or CMD+OPT+I                                                              |
| ``#openBrowserSettings;``    | Hits CTRL+Comma or CMD+Comma                                                                |
| ``#openNewBrowserTab``       | Hits CTRL+T or CMD+T                                                                        |
| ``#reopenBrowserTab``        | Hits CTRL+SHIFT+W or CMD+SHIFT+W                                                            |


#### Load and manipulate URLs

| Command                                               | Description                                          |
| ----------------------------------------------------- | ---------------------------------------------------- |
| ``$var=#get browserUrl``                              | Get current URL                                      |
| ``$var=#get browserReferrer``                         | Get referrer URL                                     |
| ``#openUrlInNewBrowserTab "https://duckduckgo.com/"`` | Load given URL in new browser tab                    |


#### Interact with DOM elements

| Command                                        | Description                            |
| ---------------------------------------------- | -------------------------------------- |
| ``#focusDomElementById "someId"``              |                                        |
| ``#focusDomElementByQuery "#id .someClass"``   |                                        |
| ``#clickDomElementById "someId"``              | Invokes mouse click on given element   |
| ``#clickDomElementByQuery "#id .someClass"``   | Invokes mouse click on given element   |
| ``#clickButtonContainingText "Hit me!"``       | Invokes mouse click on given button    |
| ``#clickLinkContainingText "Hit me!"``         | Invokes mouse click on given link      |


### Terminal automation

| Command                   | Description                    |
| ------------------------- | ------------------------------ |
| ``#openNewTerminal``      |                                |
| ``#openNewTerminalTab``   | Hit CTRL+SHIT+T or CMD+T       |
| ``#editInTerminal FILE``  | Open given file in bash editor | 


### File manipulation

All file manipulations allow as optional last argument a destination file path, if not given, they overwrite the
given source file.


| Command                                                         | Description                                             |
| --------------------------------------------------------------- | ------------------------------------------------------- |
| ``#replaceAllInFile path/file search replace``                  | Replace all occurrences of given string                 |
| ``#replaceFirstInFile path/file search replace``                | Replace first occurrence of given string                |
| ``#replaceLastInFile path/file search replace``                 | Replace last occurrence of given string                 |
| ``#replaceBetweenInFile path/file before after replacement ``   | Remove text including and between "before" and "after"  |
| ``#extractBetweenInFile path/file before after``                | Extract text excluding but between "before" and "after" |


### Functions, iterations, conditions

As doShell is a superset of shell script, 
all language constructs of regular shell script
can also be used within doShell script. 


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
* [xclip](https://linux.die.net/man/1/xclip)
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
