doShell
=======

Headful browser and terminal automation for Linux and Mac OS

## Table of Contents

- [DoShell](#doshell)
  * [What does it do?](#idea---wat-does-(will)-it-do?)
  * [Functional Flow](#functional-flow)
    + [Transpile](#transpile) 
    + [Transpile and/or run](#transpile-and/or-run) 
  + [Runtime macros and variables](#runtime-macros-and-variables)
  + [Inline PHP](#inline-php) 
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
  * [Script Examples](#script-examples) 
  * [Configuration](#configuration)
  * [Dependencies](#dependencies)
  * [Build Instructions](#build-instructions)
  * [Code Convention](#code-convention)
  * [Third Party References](#third-party-references)
  * [License](#license)


## Idea - What does it do?

doShell is a superset of shell script, providing commands geared towards 
non-headless cross-platform browser and terminal automation.  
Possible usecases are end-to-end testing, infoSec reconnaisance and creation of productivity macros.  

This project is a source-to-source (S2S) transpiler and runtime system
for executing doShell scripts.


### Mission targets

1. Ease scripted automation of controlling web browser and terminal
   in- and output and injection of extracted sub-scripts and
   variables, supporting the same language on linux and mac os. 
2. Make it concise: 
   1. Commands should be short, but self-explanatory
   2. To avoid 50% of doShell scripts being ``sleep`` commands,
   automation commands imply a plausible successive minimum delay 
3. Don't reinvent the wheel:  
   1. Reuse and integrate existing tools  (shell script, xdotool / applescript, php, ...)  
   2. While there is no dedicated editor, linter or syntax highlightning
   for doShell: Enable IDEs to identify doShell as shell script 
   (mask doShell commands as shell script comments)   


## Functional Flow

![Transpiler](/images/doshell_diagram.png)


### Transpile

Running ``shdo -t script.do.sh`` transpiles the given doShell
script to a new file ``script.do.x.sh``


### Transpile and/or run

Running ``shdo -r script.do.sh``, the transpiler will translate the given 
file and the runtime system will execute it.  
When running an already transpiled ``*.do.x.sh`` script, the translation is 
skipped.

doShell transpiles to intermediary shell script files, which additionally to conventional 
shell script code can contain runtime macros: placeholder-strings for generic 
content, and runtime variables. The doShell runtime system replaces runtime macros and 
declares runtime variables, from optional variable-value tuples that can be given as 
associative JSON as execution arguments, before the eventual execution in a sandboxed 
shell-thread. 

### Communication from browser to runtime system

For communication from web browsers back to the runtime sytem, the system 
clipboard is used. doShell has some built-in commands for manipulation and 
import / export of text from/to the clipboard. 


## Runtime macros and variables

The following predefined macros are replaced at runtime by generic content.  

| Macro             | Replaced by                                                      |
| ----------------- | ---------------------------------------------------------------- |
| ``__OS__``        | ``linux`` or ``darwin``                                          |
| ``__LINE__``      | Line number in current file                                      |
| ``__FILE__``      | Absolute path of current file including the                      |
| ``__DIR__``       | Absolute path of current file                                    |

Arbitrary user-defined runtime variables can be passed JSON-formatted 
when invoking the doShell interpreter to run a ``*.do.x.sh`` file. 

**Example**

Replace all occurences of ``__FOO__`` by ``bar`` before
running the given file:  
``shdo -r script.do.x.sh "{\"__FOO__\":\"bar\"}"``  

**Rules:**  
* Variables enclosed in ``__`` are replaced
* Variables not enclosed in ``__`` are declared: 
  * If a given variable is declared already within a script, the declaration at
    is replaced at its original place
  * If a given variable is NOT declared, a declaration is added at the beginning
    of the transpiled runtime script  

## Inline PHP

doShell script can contain inlined PHP (see functional flow) 
like:  
``#<?php echo time() ?>``  


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

| Command                                           | Description                                                              |
| ------------------------------------------------- | ------------------------------------------------------------------------ |
| ``#extractBetween $VAR before after``             | Extract text excluding but between "before" and "after"                  |
| ``#replaceAfter $VAR search replace``             | Replace every before and including the first occurrences of given string |
| ``#replaceAll $VAR search replace``               | Replace all occurrences of given string                                  |
| ``#replaceBefore $VAR search replace``            | Replace every before and including the first occurrences of given string |
| ``#replaceBetween $VAR before after replacement`` | Remove text including and between "before" and "after"                   |
| ``#replaceFirst $VAR search replace``             | Replace first occurrence of given string                                 |
| ``#replaceLast $VAR search replace``              | Replace last occurrence of given string                                  |


### Send keystrokes

**Hit single key:**  

| Command            | Description                            |
| ------------------ | -------------------------------------- |  
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


### Web Browser automation  

**Note:** At the time being doShell was tested using Firefox, but should be easily adaptable
to other web browsers. 


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


### Functions, iterations, conditions

As doShell is a superset of shell script, 
all language constructs of regular shell script
can also be used within doShell script. 


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

| Config                               | Description                                                      |
| ------------------------------------ | ---------------------------------------------------------------- |
| ``bash_editor=nano``                 | Text editor to be used in terminal, e.g. ``vim``, ``nano``, etc. |
| ``browser=firefox``                  | Web browser to be targeted                                       |

See also [settings.sh](/bin/settings.sh)


## Dependencies

Automation is ultimately performed using existing tools from third parties, 
and some doShell built-in tools.

### Optional dependencies

* When using PHP within doShell scripts, [PHP](https://www.php.net/) must be 
  installed


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


Third Party References
----------------------

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


License
-------

doShell is licensed under
[The MIT License (MIT)](https://opensource.org/licenses/MIT)
