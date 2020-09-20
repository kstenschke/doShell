doShell
=======

## Table of Contents

- [DoShell](#doshell)
  * [What does it do?](#idea---wat-does-(will)-it-do?)
  * [Functional Flow](#functional-flow)
    + [Transpile](#transpile) 
    + [Transpile and/or run](#transpile-and/or-run) 
  + [Runtime options](#runtime-options)
    + [Runtime flags](#runtime-flags)
    + [Conditional blocks](#conditional-blocks)
  * [Macros](#macros)  
  * [Commands](#commands)
    + [Import](#import)
    + [Inline PHP](#inline-php) 
    + [String manipulation](#string-manipulation)
    + [URL parsing](#url-parsing)
    + [Random values](#random-values)
    + [File manipulation](#file-manipulation)
    + [Clipboard](#clipboard)
    + [Dialogs](#dialogs)
    + [Send keystrokes](#send-keyboard-events)
    + [Browser automation](#web-browser-automation)
      * [Toggle browser panels](#toggle-browser-panels)
      * [Load and manipulate URLs](#load-and-manipulate-urls)
      * [Interact with DOM elements](#interact-with-dom-elements)
    + [Terminal automation](#terminal-automation)
    + [Enable/Disable Devices](#enable-disable-devices)
    + [Functions, iterations, conditions](#functions-iterations-conditions)
  * [Script Examples](#script-examples) 
  * [Third Party References](#third-party-references)
  * [Build Instructions](#build-instructions)
  * [Code Convention](#code-convention)
  * [License](#license)


## What does it do?

doShell script is a superset of shell script, geared towards efficient 
**headfull interactive UI automation** on Linux and Mac OS, foremost but not limited
to operations involving web browsing and shell.

This project is a source-to-source (S2S) transpiler and runtime system.  

To rapidly get an idea of doShell's syntax and some of it's abilities, 
also have a glance at the included /examples/. 

**What about Windows?**
On Windows, i recommend using the excellent [AutoHotKey](https://www.autohotkey.com/) 

### Features

* Automation of mimicked user control of (foremost) web browser and 
  terminal operations
* Built-in shorthand commands to ease operations that differ per
  platform or are not easily memorable in plain shell script
* Commands for easily using GUI dialogs from within scripts
* doShell scripts can be parameterized via JSON passed at execution time
* Separation of Concerns/DRY: doShell can import code from other files
* Browser automation is done by fake user interaction, 
  therefor a completely unsuspicious "vanilla" browser useragent and -footprint 
  (no traces of Selenium in JS window object) is sent while performing automated
  browser operations


### Mission targets

1. Ease (shell) scripting of interactive cross-platform compatible automation
2. Make it concise: 
   1. Commands should be short, but self-explanatory
   2. To avoid automation scripts being bloated with ``sleep`` commands,
   automation commands imply a plausible successive minimum delay 
3. Don't reinvent the wheel:  
   1. Use and combine existing tools  (shell script, xdotool / applescript, 
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

**Run:** ``shdo -r script.do.sh`` transpiles and runs the given script.  
When running an already transpiled ``*.do.x.sh`` script, the transpilation is 
skipped.  

**Run-Clean:** ``shdo -rc script.do.sh`` transpiles and runs the given script,
if existing, an already transpiled intermediary file is overwritten.  

doShell transpiles to intermediary shell script files: additional to 
conventional shell script code, they can contain runtime macros: 
placeholder-strings for generic content, and runtime variables.
The doShell runtime system replaces runtime macros, -variables and -conditional
blocks before the eventual execution in a sandboxed shell-thread.  


## Runtime options

### Runtime flags

| Flag                                  | Description                                                                                                        |
| ------------------------------------- | ------------------------------------------------------------------------------------------------------------------ |
| ``#!browser chromium``                | Sets the browser to be used, e.g. ``chromium`` or ``firefox``                                                      |
| ``#!keep_runtime_file``               | By default, doShell removes the temporary execution code, this flag instructs the runtime system to keep that file |
| ``#!mouse "ETP/2 Elantech Touchpad"`` | Declares primary mouse device to doShell (named as listed via ``xinput list``) (ATM: Linux only)                   |


### Conditional blocks

Though its own commands are cross-platform compatible, doShell provides shorthand commands
to easily implement platform specific script variations.

**Example:**

````
#!/usr/bin/env bash

#if_is_linux
  #!browser chromium
#endif_is_linux

#if_is_mac
  #!browser firefox
#endif_is_mac
# ... 

````


### Runtime variables

Arbitrary string replacements to be done at runtime, can be passed
JSON-formatted when invoking the doShell interpreter to run a ``*.do.x.sh`` file. 

**Example**

Replace all occurences of ``::FOO::`` by ``bar`` before
running the given file:  
``shdo -r script.do.x.sh "{\"::FOO::\":\"bar\"}"``  



### Macros

| Macro               | Replaced by                                            | Replaced during  |
| ------------------- | ------------------------------------------------------ | ---------------- |
| ``::DIR::``         | Absolute path of current file w/o filename             | Transpilation    |
| ``::FILE::``        | Absolute path of current file including the filename   | Transpilation    |
| ``::LINE::``        | Line number in current file                            | Transpilation    |
| ``::OS::``          | ``linux`` or ``mac``                                   | Runtime          |
| ``::TIMESTAMP::``   | Current UNIX timestamp                                 | Runtime          |


## Commands

### Import

Import a specified file: ``#import another_file.do.sh``  


### Inline PHP

doShell script can contain inlined PHP (processed during pre-execution parsing, 
see [functional flow diagram](#functional-flow)) 

like:  
``#!php echo time() ?>``  


### String manipulation

| Command                                           | Description                                                                   |
| ------------------------------------------------- | ----------------------------------------------------------------------------- |
| ``#extractBetween $VAR before after``             | Extract text excluding but between "before" and "after".**\***                |
| ``#replaceAfter $VAR search replace``             | Replace everything after and including the first occurrences of given string  |
| ``#replaceAll $VAR search replace``               | Replace all occurrences of given string                                       |
| ``#replaceBefore $VAR search replace``            | Replace everything before and including the first occurrences of given string |
| ``#replaceBetween $VAR before after replacement`` | Replace text including and between "before" and "after"                       |
| ``#replaceFirst $VAR search replace``             | Replace first occurrence of given string                                      |
| ``#replaceLast $VAR search replace``              | Replace last occurrence of given string                                       |


### URL parsing

| Command                    | Description                                                      |
| -------------------------- | ---------------------------------------------------------------- |
| ``#getSchemeFromUrl $URL`` | Extract scheme from given URL, e.g. ``http`` or ``https``        |
| ``#getHostFromUrl $URL``   | Extract host from given URL, e.g. ``www.example.com``            |
| ``#getPathFromUrl $URL``   | Extract path from given URL, e.g. ``/foo/bar``                   |
| ``#getQueryFromUrl $URL``  | Extract query from given URL, e.g. ``hat=bowler&accessory=cane`` |
| ``#urlEncode $URL``        | Encode given URL                                                 |
| ``#urlDecode $URL``        | Decode given URL                                                 |


### Random values

| Command                           | Description                                      |
| --------------------------------- | ------------------------------------------------ |
| ``myvar=#rand 0 100``             | Assign ``var`` a random value between 0 and 100  |


### File manipulation

All file manipulation commands output the manipulated file contents. To over/write results back to files, 
you can use the shell redirection operator ``>``. 


| Command                                                           | Description                                             |
| ----------------------------------------------------------------- | ------------------------------------------------------- |
| ``#extractBetweenFromFile path/file before after``                | Extract text excluding but between "before" and "after" |
| ``#replaceAfterFromFile path/file search replace``                |                                                         |
| ``#replaceAllFromFile path/file search replace``                  | Replace all occurrences of given string                 |
| ``#replaceBeforeFromFile path/file search replace``               |                                                         |
| ``#replaceBetweenFromFile path/file before after replacement ``   | Replace text including and between "before" and "after" |
| ``#replaceFirstFromFile path/file search replace``                | Replace first occurrence of given string                |
| ``#replaceLastFromFile path/file search replace``                 | Replace last occurrence of given string                 |


### Clipboard 

| Command                                 | Description                             |
| --------------------------------------- | --------------------------------------- |
| ``#setClipboard $value``                | Copy text to clipboard                  |
| ``#copyAll``                            | Select all, than copy                   |
| ``#copyPaste "foo"``                    | Copy text to clipboard and invoke paste |
| ``#copyPaste $VAR``                     | Copy text to clipboard and invoke paste |
| ``#copyPasteInTerminal "foo"``          | Copy text to clipboard and invoke paste |
| ``#copyPasteInTerminal $VAR``           | Copy text to clipboard and invoke paste |
| ``#cutAll``                             | Select all, than cut                    |
| ``#getClipboard``                       |                                         |
| ``#copyCurrentUrl``                     |                                         |
| ``#copyInTerminal``                     | Varies by OS                            |
| ``#pasteInTerminal``                    | Varies by OS                            |


**Manipulate strings from clipboard**  

All manipulation commands on strings from the clipboard output the resulting string.  
To over/write the result back to files, you can use the shell redirection operator ``>``. 

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
| ``myVar=#getBrowserUrl``                               | Get current URL                                      |
| ``myVar=#getBrowserReferrer``                          | Get referrer URL                                     |
| ``#openUrlInNewBrowserTab "https://duckduckgo.com/"`` | Load given URL in new browser tab                    |


#### Use devTools and devConsole

| Command                              | Description                                                                                 |
| ------------------------------------ | ------------------------------------------------------------------------------------------- |
| ``#openBrowserDevConsole``           | Hits CTRL+SHIFT+J or CMD+SHIFT+J (firefox) or CTRL+SHIFT+P / CMD+SHIFT+P in Chrome/Chromium |
| ``#openBrowserDevTools``             | Hits CTRL+SHIFT+I or CMD+OPT+I                                                              |
| ``#runJs alert('hello') #end_runJs`` | Open and focus devConsole, paste and execute given script                                   |
| ``#execDevConsole``                  | Hits CTRL+ENTER or CMD+ENTER                                                                |
| ``#clearDevConsole``                 | Clears current commands from devConsole                                                     |


#### Interact with DOM elements

| Command                                        | Description                            |
| ---------------------------------------------- | -------------------------------------- |
| ``#focusDomElementById "someId"``              |                                        |
| ``#focusDomElementByQuery "#id .someClass"``   |                                        |
| ``#clickDomElementById "someId"``              | Invokes mouse click on given element   |
| ``#clickDomElementByQuery "#id .someClass"``   | Invokes mouse click on given element   |
| ``#clickButtonContainingText "Hit me!"``       | Invokes mouse click on given button    |
| ``#clickLinkContainingText "Hit me!"``         | Invokes mouse click on given link      |


#### Communication from browser to runtime system

For communication from web browser back to the runtime system, the system 
clipboard and file IO can be used. doShell provides built-in commands for 
manipulation and import / export of text from/to the clipboard.


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


### Enable/Disable Devices

**ATM:** Implemented on Linux only.

| Command                               | Description                                                       |
| ------------------------------------- | ----------------------------------------------------------------- |
| ``#disableMouse``                     | Disable primary mouse device (see [Runtime flags](#runtime-flags) |
| ``#enableMouse``                      | Enable primary mouse device                                       |
| ``#disableDevice "Some device name"`` | Disable given device (Find out device names via ``xinput list``)  |
| ``#enableDevice "Some device name"``  | Enable given device                                               |


### Functions, iterations, conditions

doShell is a superset of shell script:  
All language constructs of regular shell script can be
used within doShell script. 


## Script Examples

The following example scripts can be found under [/examples](/examples):

| File                                                                                        | Description                                                                          |
| ------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------ |
| [001_import.do.sh](/examples/001_import.do.sh)                                              | Importing external doShell- or shell scripts from other files                        |
| [002_macros.do.sh](/examples/002_macros.do.sh)                                              | Using runtime macros                                                                 |
| [003_platform_conditions.do.sh](/examples/003_platform_conditions.do.sh)                    | Varying code per platform                                                            |
| [004_random.do.sh](/examples/004_random.do.sh)                                              | Shorthand commands for random value generation                                       |
| [005_strings.do.sh](/examples/005_strings.do.sh)                                            | String manipulation commands                                                         |
| [006_strings_from_files.do.sh](/examples/006_strings_from_files.do.sh)                      | Manipulation of strings from files                                                   |
| [007_clipboard_strings.do.sh](/examples/007_clipboard_strings.do.sh)                        | Clipboard manipulation commands                                                      |
| [008_parse_url.do.sh](/examples/008_parse_url.do.sh)                                        | Parsing and encoding/decoding URL parts                                              |
| [009_parse_php.do.sh](/examples/009_parse_php.do.sh)                                        | Using PHP within doShell script                                                      |
| [010_dialogs.do.sh](/examples/010_dialogs.do.sh)                                            | Various dialogs / GUI popup windows                                                  |
| [011_dialogs-open_bash_in_container.do.sh](/examples/011_dialogs-open_bash_in_container.sh) | Display selection popup of docker containers, open bash in selected one              |
| [012_load_url_in_new_browser_tab.do.sh](/examples/012_load_url_in_new_browser_tab.do.sh)    | Opening a new browser tab and than loading a URL in it                               |
| [013_search_with_duckduckgo.do.sh](/examples/013_search_with_duckduckgo.do.sh)              | Html form fill-out and submission                                                    |
| [014_store_clipboard_to_file.do.sh](/examples/014_store_clipboard_to_file.do.sh)            | Copy text from browser, than save the clipboard content to a file                    |
| [015_use_dev_console.do.sh](/examples/015_use_dev_console.do.sh)                            | Opening the dev console, inserting and running script in it                          |
| [016_export_all_script_tags.do.sh](/examples/016_export_all_script_tags.do.sh)              | Extract all <script> tags from a page loaded in browser and save them to a file      |
| [017_export_html_comments.do.sh](/examples/017_export_html_comments.do.sh)                  | Export all commented-out HTML from a web page                                        |
| [018_export_urls.do.sh](/examples/018_export_urls.do.sh)                                    | Export all URLs from HTML and all scripts of a web page                              |
| [019_swop_domain.do.sh](/examples/019_swop_domain.do.sh)                                    | Replace any domain loaded in browser by localhost, maintain rest of URL, invoke load |
| [020_iterate_url.do.sh](/examples/020_iterate_url.do.sh)                                    | Open iterated values of an URL parameter in new browser tabs                         |


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

The source code of the doShell transpiler and interpreter follows the 
[Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).  


License
-------

doShell is licensed under
[The MIT License (MIT)](https://opensource.org/licenses/MIT)
