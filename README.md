doShell
=======

## Table of Contents

- [DoShell](#doshell)
  * [What does it do?](#idea---wat-does-(will)-it-do?)
  * [Functional Flow](#functional-flow)
    + [Transpile](#transpile) 
    + [Transpile and/or run](#transpile-and/or-run) 
  + [Runtime options within doShell scripts](#runtime-options-within-doShell-scripts)
    + [Runtime flags](#runtime-flags)
    + [Runtime macros](#runtime-macros)
    + [Conditional blocks](#conditional-blocks)
  * [Commands](#commands)
    + [Import](#import)
    + [Inline PHP](#inline-php) 
    + [String manipulation](#string-manipulation)
    + [Random values](#random-values)
    + [URL parsing](#url-parsing)
    + [File manipulation](#file-manipulation)
    + [Clipboard](#clipboard)
    + [Dialogs](#dialogs)
    + [Send keystrokes](#send-keyboard-events)
    + [Browser automation](#web-browser-automation)
      * [Toggle browser panels](#toggle-browser-panels)
      * [Load and manipulate URLs](#load-and-manipulate-urls)
      * [Interact with DOM elements](#interact-with-dom-elements)
    + [Terminal automation](#terminal-automation)
    + [Functions, iterations, conditions](#functions-iterations-conditions)
  * [Script Examples](#script-examples) 
  * [Configuration](#configuration)
  * [Third Party References](#third-party-references)
  * [Build Instructions](#build-instructions)
  * [Code Convention](#code-convention)
  * [License](#license)


## What does it do?

doShell is a scripting language, transpiler and runtime system for efficient 
**headfull interactive cross-platform automation** (foremost of browser and 
terminal operations).

This project is a source-to-source (S2S) transpiler and runtime system
for executing doShell scripts.  

Possible usecases are creation of productivity macros and  infoSec reconnaisance tools.  
**Note:** End-to-end browser testing should NOT be a doShell usecase, 
as [Selenium](https://www.selenium.dev/) based solutions prove much more effective.


### Features

* Automation of simulated user control (of foremost) web browser and 
  terminal operations
* Built-in shorthand-commands to ease various operations that are overly
  complicated or simply not easily memorable in plain shell script
  (string-manipulation in variables, files and clipboard; randomization etc.)
* doShell provides cross-platform commands for easily using GUI dialogs 
  from within scripts
* The transpiler targets 3rd party tools, that vary by platform:
  Automation works with the same doShell script on Linux and Mac OS
* doShell scripts can be parameterized via JSON passed at execution time
* Separation of Concerns/DRY: doShell can import code from other files
* As all browser automation is done by simulated user controls, 
  a completely regular, unsuspicious "vanilla" browser useragent and -footprint 
  (no traces of Selenium in JS window object) is sent while performing automated
  browser operations


### Mission targets

1. Ease scripted automation of controlling web browser and terminal
   in- and output and injection of sub-scripts and variables, supporting 
   the same language on linux and mac os. 
2. Make it concise: 
   1. Commands should be short, but self-explanatory
   2. To avoid 50% of doShell scripts being ``sleep`` commands,
   automation commands imply a plausible successive minimum delay 
3. Don't reinvent the wheel:  
   1. Reuse and integrate existing tools  (shell script, xdotool / applescript, 
      php, ...)  
   2. While there is no dedicated editor, linter or syntax highlightning
   for doShell: Enable IDEs to identify doShell as shell script 
   (mask doShell commands as shell script comments)   


## Functional Flow

![Transpiler](/images/doshell_diagram.png)


### Transpile

Running ``shdo -t script.do.sh`` transpiles the given doShell
script to a new file ``script.do.x.sh``


### Transpile and/or run

Running ``shdo -r script.do.sh``, the given file is transpiled and run.  
When running an already transpiled ``*.do.x.sh`` script, the translation is 
skipped.

doShell transpiles to intermediary shell script files: additional to 
conventional shell script code, they can contain runtime macros: 
placeholder-strings for generic content, and runtime variables. The doShell 
runtime system replaces runtime macros and declares runtime variables, before 
the eventual execution in a sandboxed shell-thread. 

### Communication from browser to runtime system

For communication from web browser back to the runtime sytem, the system 
clipboard and file IO can be used. doShell provides built-in commands for 
manipulation and import / export of text from/to the clipboard. 


## Runtime options within doShell scripts

### Runtime flags

Runtime flags can be used to override doShell options 
(which all can also be passed to the doShell executable from the shell / terminal e.g. via ``--browser=chromium``)

| Flag                   | Description                                                      |
| ---------------------- | ---------------------------------------------------------------- |
| ``#BROWSER=chromium``  | Sets the browser to be used, e.g. ``chromium`` or ``firefox``    |

### Runtime macros

The following predefined macros are replaced at runtime by generic content.  

| Macro             | Replaced by                                                      |
| ----------------- | ---------------------------------------------------------------- |
| ``__OS__``        | ``linux`` or ``darwin``                                          |
| ``__LINE__``      | Line number in current file                                      |
| ``__FILE__``      | Absolute path of current file including the filename             |
| ``__DIR__``       | Absolute path of current file w/o filename                       |

### Conditional blocks

Though its own commands are cross-platform compatible, doShell provides shorthand commands
to easily implement platform specific script variations.

**Example:**

````
#IF(LINUX)
  echo "hello linux"
#ELSEIF(MAC)
  echo "hello mac"
#ENDIF
````

### Runtime variables

Arbitrary user-defined runtime variables can be passed JSON-formatted 
when invoking the doShell interpreter to run a ``*.do.x.sh`` file. 

**Example**

Replace all occurences of ``__FOO__`` by ``bar`` before
running the given file:  
``shdo -r script.do.x.sh "{\"__FOO__\":\"bar\"}"``  

**Rules:**  
* Variables enclosed in ``__`` are replaced
* Variables not enclosed in ``__`` are declared: 
  * If a given variable is declared already within a script, the declaration
    is replaced at its original place
  * If a given variable is NOT declared, a declaration is added at the beginning
    of the transpiled runtime script  


## Commands

### Import

Import a specified file: ``#import another_file.do.sh``  


### Inline PHP

doShell script can contain inlined PHP (processed during pre-execution parsing, 
see functional flow) 

like:  
``#<?php echo time() ?>``  


### String manipulation

| Command                                           | Description                                                                   |
| ------------------------------------------------- | ----------------------------------------------------------------------------- |
| ``#extractBetween $VAR before after``             | Extract text excluding but between "before" and "after"                       |
| ``#replaceAfter $VAR search replace``             | Replace everything after and including the first occurrences of given string  |
| ``#replaceAll $VAR search replace``               | Replace all occurrences of given string                                       |
| ``#replaceBefore $VAR search replace``            | Replace everything before and including the first occurrences of given string |
| ``#replaceBetween $VAR before after replacement`` | Replace text including and between "before" and "after"                       |
| ``#replaceFirst $VAR search replace``             | Replace first occurrence of given string                                      |
| ``#replaceLast $VAR search replace``              | Replace last occurrence of given string                                       |


### Random values

| Command                           | Description                                          |
| --------------------------------- | ---------------------------------------------------- |
| ``myvar=#rand 0 100``             | Assign ``var`` a random value between 0 and 100      |
| ``myvar=#rand foo bar baz qux``   | Assign ``var`` a random value from the given options |


### URL parsing

| Command                                | Description                                                      |
| -------------------------------------- | ---------------------------------------------------------------- |
| ``#getSchemeFromUrl $URL``             | Extract scheme from given URL, e.g. ``http`` or ``https``        |
| ``#getHostFromUrl $URL``               | Extract host from given URL, e.g. ``www.example.com``            |
| ``#getPathFromUrl $URL``               | Extract path from given URL, e.g. ``/foo/bar``                   |
| ``#getQueryFromUrl $URL``              | Extract query from given URL, e.g. ``hat=bowler&accessory=cane`` |


### File manipulation

All file manipulations allow as optional last argument a destination file path,
if not given, they overwrite the given source file.


| Command                                                         | Description                                             |
| --------------------------------------------------------------- | ------------------------------------------------------- |
| ``#replaceAllInFile path/file search replace``                  | Replace all occurrences of given string                 |
| ``#replaceFirstInFile path/file search replace``                | Replace first occurrence of given string                |
| ``#replaceLastInFile path/file search replace``                 | Replace last occurrence of given string                 |
| ``#replaceBetweenInFile path/file before after replacement ``   | Remove text including and between "before" and "after"  |
| ``#extractBetweenInFile path/file before after``                | Extract text excluding but between "before" and "after" |


### Clipboard 

| Command                                 | Description                             |
| --------------------------------------- | --------------------------------------- |
| ``#appendClipboardToFile "clip.txt"``   | Append clipboard-text to given file     |
| ``#setClipboard $value``                | Copy text to clipboard                  |
| ``#copyAll``                            | Select all, than copy                   |
| ``#copyPaste "foo"``                    | Copy text to clipboard and invoke paste |
| ``#copyPaste $VAR``                     | Copy text to clipboard and invoke paste |
| ``#copyPasteInTerminal "foo"``          | Copy text to clipboard and invoke paste |
| ``#copyPasteInTerminal $VAR``           | Copy text to clipboard and invoke paste |
| ``#cutAll``                             | Select all, than cut                    |
| ``$value=#getClipboard``                |                                         |
| ``#saveClipboardToFile "clip.txt"``     | Save clipboard-text to given file       |
| ``#copyCurrentUrl``                     |                                         |
| ``#copyInTerminal``                     | Varies by OS                            |
| ``#pasteInTerminal``                    | Varies by OS                            |


| Command                                                      | Description            |
| ------------------------------------------------------------ | ---------------------- |
| ``#replaceAllInClipboard search replace``                  | Replace all occurrences of given string                 |
| ``#replaceFirstInClipboard search replace``                | Replace first occurrence of given string                |
| ``#replaceLastInClipboard search replace``                 | Replace last occurrence of given string                 |
| ``#replaceBetweenInClipboard before after replacement ``   | Remove text including and between "before" and "after"  |
| ``#extractBetweenInClipboard before after``                | Extract text excluding but between "before" and "after" |


### Dialogs

| Command                                                  | Description                       |
| -------------------------------------------------------- | --------------------------------- |
| ``#notify "MESSAGE"``                                    |                                   |
| ``#alert "MESSAGE"``                                     |                                   |
| ``var=#confirm "MESSAGE"``                               | Yes/No Dialog                     |
| ``var=#prompt "MESSAGE"``                                | Popup with input field            |
| ``var=#select "MESSAGE" "option1" "option2" "option3"``  | Popup with options to select from |


### Send keystrokes

**Hit single key:**  

| Command           | Description                            |
| ----------------- | -------------------------------------- |  
| ``#hitBackspace`` |                                        |
| ``#hitEnter``     |                                        |
| ``#hitEsc``       |                                        |
| ``#hitF1``        |                                        |
| ``#hitTab``       |                                        |
| ``#hitSpace``     |                                        |


**Stroke key combination:**

| Command                 | Description                    |
| ----------------------- | ------------------------------ |   
| ``#hitCopy``            | Hit CTRL+C or CMD+c            |
| ``#hitFindInTerminal``  | Hit CTRL+SHIFT+F or CMD+F      | 
| ``#hitFind``            | Hit CTRL+F or CMD+F            | 
| ``#copyInTerminal``     | Varies by OS                   |
| ``#cut``                | Hit CTRL+X or CMD+x            |
| ``#paste``              | Hit CTRL+V or CMD+V            |
| ``#pasteInTerminal``    | Varies by OS                   |
| ``#selectAll``          | Hit CTRL+A or CMD+A            |


**Type text:**

| Command               | Description                                    |
| --------------------- | ---------------------------------------------- |  
| ``#type "TEXT"``      | Simulate typing given text on keyboard         |
| ``#copyPaste "foo"``  | Copy text to clipboard and invoke paste. ``*`` |

``* Oftentimes a faster alternative over typing``  


### Web Browser automation  

**Note:** At the time being doShell was tested using Firefox, but should be 
easily adaptable to other web browsers. 


#### Toggle browser panels

| Command                      | Description                                                                                 |
| ---------------------------- | ------------------------------------------------------------------------------------------- |
| ``#activateBrowser``         | Launch or bring browser window to front                                                     | 
| ``#closeBrowserTab``         | Hits CTRL+W or CMD+W                                                                        |
| ``#focusBrowserURL``         | Hits CTRL+L or CMD+L                                                                        |
| ``#focusNextBrowserTab``     | Hits CTRL+TAB or CMD+TAB                                                                    |
| ``#focusPreviousBrowserTab`` | Hits CTRL+SHIFT+TAB or CMD+OPT+TAB                                                          |
| ``#openBrowserDevConsole``   | Hits CTRL+SHIFT+J or CMD+SHIFT+J (firefox) or CTRL+SHIFT+P / CMD+SHIFT+P in Chrome/Chromium |
| ``#openBrowserDevTools``     | Hits CTRL+SHIFT+I or CMD+OPT+I                                                              |
| ``#openBrowserSettings``     | Hits CTRL+Comma or CMD+Comma                                                                |
| ``#openNewBrowserTab``       | Hits CTRL+T or CMD+T                                                                        |
| ``#reopenBrowserTab``        | Hits CTRL+SHIFT+W or CMD+SHIFT+W                                                            |


#### Load and manipulate URLs

| Command                                               | Description                                          |
| ----------------------------------------------------- | ---------------------------------------------------- |
| ``$var=#get browserUrl``                              | Get current URL                                      |
| ``$var=#get browserReferrer``                         | Get referrer URL                                     |
| ``#openUrlInNewBrowserTab "https://duckduckgo.com/"`` | Load given URL in new browser tab                    |


#### Use devTools and devConsole

| Command                        | Description                                                                                 |
| ------------------------------ | ------------------------------------------------------------------------------------------- |
| ``#openBrowserDevConsole``     | Hits CTRL+SHIFT+J or CMD+SHIFT+J (firefox) or CTRL+SHIFT+P / CMD+SHIFT+P in Chrome/Chromium |
| ``#openBrowserDevTools``       | Hits CTRL+SHIFT+I or CMD+OPT+I                                                              |
| ``#runJs "alert('hello')"``    | Open and focus devConsole, paste and execute given script                                   |
| ``#execDevConsole``            | Hits CTRL+ENTER or CMD+ENTER                                                                |
| ``#clearDevConsole``           | Clears current commands from devConsole                                                     |


#runJsInDevConsole

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

| Command                           | Description                             |
| --------------------------------- | --------------------------------------- |
| ``#openNewTerminal``              |                                         |
| ``#openNewTerminalTab``           | Hit CTRL+SHIT+T or CMD+T                |
| ``#editInTerminal FILE``          | Open given file in bash editor          | 
| ``#hitFindInTerminal``            | Hit CTRL+SHIFT+F or CMD+F               |
| ``#copyPasteInTerminal "foo"``    | Copy text to clipboard and invoke paste | 
| ``#copyPasteInTerminal $VAR``     | Copy text to clipboard and invoke paste |
| ``#runInNewTerminal "ls"``        | Run given shell script in new terminal  | 


### Functions, iterations, conditions

doShell is a superset of shell script:  
All language constructs of regular shell script can be
used within doShell script. 


## Script Examples

The following example scripts can be found under [/examples](/examples):

| File                                                                                       | Description                                                                         |
| ------------------------------------------------------------------------------------------ | ----------------------------------------------------------------------------------- |
| [001_import.do.sh](/examples/001_import.do.sh)                                            | Importing external doShell- or shell scripts from other files                        |
| [002_using_macros.do.sh](/examples/001_import.do.sh)                                      | Using runtime macros                                                                 |
| [003_load_url_in_new_browser_tab.do.sh](/examples/003_load_url_in_new_browser_tab.do.sh)  | Opening a new browser tab and than loading a URL in it                               |
| [004_search_with_duckduckgo.do.sh](/examples/004_search_with_duckduckgo.do.sh)            | Form fill-out and submission                                                         |
| [005_use_dev_console.do.sh](/examples/005_use_dev_console.do.sh)                          | Opening of the dev console, inserting and running script in it                       |
| [006_store_clipboard_to_file.do.sh](/examples/006_store_clipboard_to_file.do.sh)          | Copy text in the browser, than save the clipboard content to a file                  |
| [007_export_all_script_tags.do.sh](/examples/007_export_all_script_tags.do.sh)            | Extract all <script> tags from a page loaded in the browser and save them to a file  |
| [008_parse_php.do.sh](/examples/008_parse_php.do.sh)                                      | Using PHP within doShell script                                                      |
| [009_export_html_comments.do.sh](/examples/009_export_html_comments.do.sh)                | Export all commented-out html from a web page                                        |
| [010_export_urls.do.sh](/examples/010_export_urls.do.sh)                                  | Export all URLs from HTML and all scripts of a web page                              |
| [011_export_form.do.sh](/examples/011_export_form.do.sh)                                  | Export all form fields w/ (and w/o) values                                           |
| [012_export_img_urls.do.sh](/examples/012_export_img_urls.do.sh)                          | Search in Wikipedia, open article, export image URLs                                 |
| [013_swop_domain.do.sh](/examples/013_swop_domain.do.sh)                                  | Replace any domain loaded in browser by localhost, maintain rest of URL, invoke load |
| [014_prompt.do.sh](/examples/014_prompt.do.sh)                                            | Open dialog to enter a term, than perform duckduckgo search for it                   |
| [015_notify.do.sh](/examples/015_notify.do.sh)                                            | Display a notification                                                               |
| [016_string_replace.do.sh](/examples/016_string_replace.do.sh)                            | Various string replacement examples                                                  |
 

## Configuration

The following optional settings can be given as environment vars:

| Config                               | Description                                                         | Default     |
| ------------------------------------ | ------------------------------------------------------------------- | ----------- |
| ``bash_editor=nano``                 | Text editor to be used in terminal, e.g. ``vim``, ``nano``, etc.    | ``nano``    | 
| ``browser=firefox``                  | Web browser to be targeted **NOTE**: at the time being only firefox | ``firefox`` |
| ``remove_code_after_run=0``          | Remove ``.do.x.sh``after execution                                  | ``1``       |

See also [settings.sh](/bin/settings.sh)


Third Party References
----------------------

## Runtime tools 

doShell uses a list of existing tools from third parties (and some doShell 
built-in tools) to peform automation, display dialogs, etc.
The third party tools vary by platform, not all tools are mandatory (depending 
on functionalities used within doShell scripts). 

### Runtime tools on Linux 

| Tool                                          | Description                                                         | License                                                                              |
| --------------------------------------------- | ------------------------------------------------------------------- | ------------------------------------------------------------------------------------ |
| [xddotool](http://manpages.ubuntu.com/manpages/trusty/man1/xdotool.1.html) |                                        |                                                                                      |
| [gxMessage](https://trmusson.dreamhosters.com/programs.html#gxmessage)     | GTK-based dialog windows interface for any terminal program | [GNU General Public License version 2](https://directory.fsf.org/wiki/License:GPLv2) |
| [wmctrl](http://tripie.sweb.cz/utils/wmctrl/)         |                                                             |                                                                                      |
| [xclip](https://linux.die.net/man/1/xclip)            |                                                             |                                                                                      |
| [xsel](https://linux.die.net/man/1/xsel)              |                                                             |                                                                                      |
| [PHP](https://www.php.net/)                           |                                                             |                                                                                      |
                                                        
### Runtime tools on Mac 

| Tool                                         | Description                                | License                                                              |
| -------------------------------------------- | ------------------------------------------ | -------------------------------------------------------------------- |
| AppleScript (osascript)                      | **Note:** Assistive access must be enabled |                                                                      |               
| [PHP](https://www.php.net/)                  |                                      |                                                                                      |

## Build tools and libraries

doShell was built using the following third party libraries and tools:

| Library                                       | Description                                                        | License                                                          |
| --------------------------------------------- | ------------------------------------------------------------------ | ---------------------------------------------------------------- |
| [Clip Library](https://github.com/dacap/clip) | Library to copy/retrieve content to/from the clipboard/pasteboard. | [MIT License](https://opensource.org/licenses/MIT)               |

| Tool                                                            | Description                                                                | License                                                                                                   |
| --------------------------------------------------------------- | -------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------- |
| [Clang](https://clang.llvm.org)                                 | A C language family frontend for LLVM                                      | [Apache License](https://www.apache.org/licenses/)                                                        |      
| [Cmake](https://cmake.org)                                      | Family of tools designed to build, test and package software               | [New BSD License](https://en.wikipedia.org/wiki/New_BSD_License)                                          |      
| [Cppcheck](http://cppcheck.sourceforge.net/)                    | Static analysis tool for C/C++ code                                        | [GNU General Public License version 3](https://www.gnu.org/licenses/gpl-3.0.html)                         |      
| [cpplint](https://github.com/cpplint/cpplint)                   | Static code checker for C++                                                | [BSD-3 Clause](https://opensource.org/licenses/BSD-3-Clause)                                              |      
| [GCC](https://gcc.gnu.org)                                      | GCC, the GNU Compiler Collection                                           | [GNU General Public License version 3](https://gcc.gnu.org/onlinedocs/libstdc++/manual/appendix_gpl.html) |      

Thanks a lot!


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
