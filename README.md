[![Platform](https://img.shields.io/badge/platform-osx%2Flinux-green)](#)
[![Written in C++](https://img.shields.io/badge/written%20in-C++-lightblue)](#)
[![License](https://img.shields.io/badge/License-MIT%20-yellowgreen)](https://github.com/kstenschke/doShell/blob/master/LICENSE.md)  
[![cpplint](https://github.com/kstenschke/doShell/workflows/cpplint/badge.svg)](https://github.com/kstenschke/doShell/actions)
[![cppcheck](https://github.com/kstenschke/doShell/workflows/cppcheck-action/badge.svg)](https://github.com/kstenschke/doShell/actions)
[![CodeFactor](https://www.codefactor.io/repository/github/kstenschke/doShell/badge)](https://www.codefactor.io/repository/github/kstenschke/doShell)


doShell
=======

Shell wrapper/macro language for rapid automation scripting on Linux and Mac OS  


## Table of Contents

- [DoShell](#doshell)
  * [What does it do?](#what-does-it-do?)
  * [Functional Flow](#functional-flow) 
  * [Runtime options](#runtime-options)
    + [Flags](#Flags)
    + [Conditional blocks](#conditional-blocks)
  * [Macros](#macros)  
  * [Commands](#commands)
    + [Mute output](#mute-output)
    + [Import](#import)
    + [Ivoke PHP and Node.js](#invoke-php-and-nodejs) 
    + [String manipulation](#string-manipulation)
      + [General](#general)
      + [URL parsing](#url-parsing)
    + [Random values](#random-values)
    + [Clipboard](#clipboard)
    + [Dialogs](#dialogs)
    + [Send keystrokes](#send-keystrokes)
    + [Browser automation](#browser-automation)
      * [Toggle browser panels](#toggle-browser-panels)
      * [Load and manipulate URLs](#load-and-manipulate-urls)
      * [Interact with DOM elements](#interact-with-dom-elements)
    + [Terminal automation](#terminal-automation)    
  * [Functions, iterations, conditions, extensions](#functions-iterations-conditions-extensions)
  * [Script Examples](#script-examples) 
  * [Third Party References](#third-party-references)
  * [Build Instructions](#build-instructions)
  * [Code Convention](#code-convention)
  * [License](#license)


## What does it do?

doShell provides a superset of shell script, geared towards rapid cross-platform 
(Linux and Mac OS) headfull UI automation.    
doShell is foremost targeted, but not limited, to automation of operations
involving browsing the web.

This project is a source-to-source (S2S) transpiler and runtime system.  

**What about Windows?**
On Windows, i recommend using the excellent [AutoHotKey](https://www.autohotkey.com/) 

### Features

* Mimick user-interaction / UI control of (foremost) web browsing operations
* Shorthand commands to ease operations that differ per platform or are not 
  easily memorable in plain shell script, xdoTool / appleScript, etc.
* Commands for invoking GUI dialogs (alert, notify, confirm, prompt, select)
* Scripts can be parameterized via JSON passed at execution time
* Separation of Concerns/DRY: doShell can import code from other files
* For infoSec researchers: Browser automation is done by fake user interaction, 
  therefor a completely unsuspicious "vanilla" browser useragent and -footprint 
  (no traces of Selenium in JS window object) is sent while performing automated
  browser operations
* As doShell transpiles scripts (instead of just being an interpreter) scripts can 
  also thereafter be improved and extended manually if needed


For quickly getting an idea of doShell's syntax and some of it's abilities, 
also have a glance at the included [script examples](#script-examples). 


### Mission targets

1. Ease scripting interactive cross-platform compatible automation
2. Make it concise: 
   1. Commands should be short, but self-explanatory
   2. To avoid bloating automation scripts with ``sleep`` commands,
   related commands imply a plausible successive minimum delay 
3. Don't reinvent the wheel:  
   1. Use and combine existing tools  (shell script, applescript / xdotool + wmCtrl + zenity, 
      php, node.js)  
   2. While there is no dedicated editor, linter or syntax highlightning
   for doShell: Enable IDEs to identify doShell as shell script 


## Functional Flow

![Transpiler](/images/doshell_diagram.png)


### Transpile

Running ``shdo -t script.do.sh`` transpiles the given doShell
script to a new intermediary file ``script.do.x.sh``

doShell transpiles to intermediary shell script files,
which are stored for better performance  when repeatedly running
the same script. Additional to conventional shell script code, they can contain 
runtime macros: placeholder-strings for generic content, and runtime variables.  
The doShell runtime system replaces runtime macros, -variables and -conditional
blocks before the eventual execution.  


### Transpile and/or run

**Run:** ``shdo -r script.do.sh`` transpiles and runs the given script.  
When running an already transpiled ``*.do.x.sh`` script, the transpilation is 
skipped.  

**Run-Clean:** ``shdo -rc script.do.sh`` transpiles and runs the given script,
if existing, an already transpiled intermediary file is overwritten.  


## Runtime options

### Flags

| Flag                                  | Description                                                                                                        |
| ------------------------------------- | ------------------------------------------------------------------------------------------------------------------ |
| ``#!browser chromium``                | Sets the browser to be used, e.g. ``chromium`` or ``firefox``. Default: ``firefox``                                |
| ``#!keep_runtime_file``               | By default, doShell removes the temporary execution code, this flag instructs the runtime system to keep that file |
| ``#!remove_transpilation``            | By default, doShell keeps the intermediary code, this flag instructs the runtime system to delete that file        |
| ``#!slow_motion``                     | Insert ``sleep`` commands after each line. Helpful for testing scripts in "slow-motion"                            |
| ``#!terminal xterm``                  | Linux only: on mac the default terminal is used. Sets the terminal to be used, default: ``gnome-terminal``         |


### Conditional blocks

Though its own commands are cross-platform compatible, doShell provides
shorthand commands to easily implement platform specific script variations.

**Example:**

````bash
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
JSON-formatted when invoking the doShell interpreter to run a ``*.do.x.sh`` 
file. 

**Example**

Replace all occurences of ``::FOO::`` by ``bar`` before
running the given file:  

````bash
shdo -r script.do.x.sh "{\"::FOO::\":\"bar\"}"
````  

**Note:** For an optimal ratio of performance and a small
file size of the doShell executable, doShell provides only
a very simple custom JSON parser: All keys and values 
therefor must be surrounded by single or double quotes.



### Macros

| Macro               | Replaced by                                                                  | Replaced during  |
| ------------------- | ---------------------------------------------------------------------------- | ---------------- |
| ``::DIR::``         | Absolute path of current file w/o filename                                   | Transpilation    |
| ``::DIR_DOSH::``    | Absolute path of current running doShell executable w/o filename             | Runtime          |
| ``::DIR_EXEC::``    | Directory path from where doShell was invoked                                | Runtime          |
| ``::FILE::``        | Absolute path of current file including the filename                         | Transpilation    |
| ``::LINE::``        | Line number in current file                                                  | Transpilation    |
| ``::MUTE::``        | ``&>/dev/null`` = silences the preceeding command's STDOUT and STDERR output | Runtime          |
| ``::MUTE_2::``      | ``2>/dev/null`` = silences the preceeding command's file descriptor output   | Runtime          |
| ``::OS::``          | ``linux`` or ``mac``                                                         | Runtime          |
| ``::TIMESTAMP::``   | Current UNIX timestamp                                                       | Runtime          |


## Commands


### Mute output

To prevent otherwise verbose commands, from printing their result
into the shell, the ```::MUTE::``` [modifier macro](#macros)
(which is simply a shorthand for ``&>/dev/null``). 
can be appended to otherwise verbose commands.

**Example:**  

````bash
_setClipboard "https://www.test.com/foo-bar-baz-qux"
_replaceBeforeFromClipboard // '' ::MUTE::
````


### Import

Import a specified file: 
````bash
_import another_file.do.sh
````  


### Invoke PHP and Node.js

**Inline PHP:**  

doShell script can contain inlined PHP (processed during pre-execution parsing, 
see [functional flow diagram](#functional-flow)) 

like: 

````bash
_php echo time() _/php
````  

Script example on embedding PHP with doShell: ``examples/09_parse_php.do.sh``

**Use node.js modules from within doShell:**  

Script example for embedding node.js modules within doShell:  
  ``examples/17_export_website_to_markdown.do.sh``  

Prior to using node modules from within doShell, install
the used dependencies, e.g. when using 
[turndown](https://github.com/domchristie/turndown) as in 
``examples/17_export_website_to_markdown.do.sh``:

````bash
npm init
npm install turndown
````


### String manipulation

#### General 

| Command                                           | Description                                                                   |
| ------------------------------------------------- | ----------------------------------------------------------------------------- |
| ``_extractBetween $VAR before after``             | Extract text excluding but between "before" and "after".**\***                |
| ``_replaceAfter $VAR search replace``             | Replace everything after and including the first occurrences of given string  |
| ``_replaceAll $VAR search replace``               | Replace all occurrences of given string                                       |
| ``_replaceBefore $VAR search replace``            | Replace everything before and including the first occurrences of given string |
| ``_replaceBetween $VAR before after replacement`` | Replace text including and between "before" and "after"                       |
| ``_replaceFirst $VAR search replace``             | Replace first occurrence of given string                                      |
| ``_replaceLast $VAR search replace``              | Replace last occurrence of given string                                       |


**Strings from files** 

| Command                                                           | Description                                             |
| ----------------------------------------------------------------- | ------------------------------------------------------- |
| ``_extractBetweenFromFile path/file before after``                | Extract text excluding but between "before" and "after" |
| ``_replaceAfterFromFile path/file search replace``                |                                                         |
| ``_replaceAllFromFile path/file search replace``                  | Replace all occurrences of given string                 |
| ``_replaceBeforeFromFile path/file search replace``               |                                                         |
| ``_replaceBetweenFromFile path/file before after replacement ``   | Replace text including and between "before" and "after" |
| ``_replaceFirstFromFile path/file search replace``                | Replace first occurrence of given string                |
| ``_replaceLastFromFile path/file search replace``                 | Replace last occurrence of given string                 |


#### URL parsing

| Command                    | Description                                                      |
| -------------------------- | ---------------------------------------------------------------- |
| ``_getSchemeFromUrl $URL`` | Extract scheme from given URL, e.g. ``http`` or ``https``        |
| ``_getHostFromUrl $URL``   | Extract host from given URL, e.g. ``www.example.com``            |
| ``_getPathFromUrl $URL``   | Extract path from given URL, e.g. ``/foo/bar``                   |
| ``_getQueryFromUrl $URL``  | Extract query from given URL, e.g. ``hat=bowler&accessory=cane`` |
| ``_urlEncode $URL``        | URL-Encode given string                                          |
| ``_urlDecode $URL``        | URL-Decode given string                                          |


### Random values

| Command                           | Description                                      |
| --------------------------------- | ------------------------------------------------ |
| ``myvar=#rand 0 100``             | Assign ``var`` a random value between 0 and 100  |


### Clipboard 

| Command                                    | Description                                 |
| ------------------------------------------ | ------------------------------------------- |
| ``_appendToClipboard $value``              | Add string to end of clipboard              |
| ``_getClipboard``                          | Output clipboard contents                   |
| ``_loadIntoClipboard filename.txt``        | Load file content into clipboard            |
| ``_prependToClipboard $value``             | Add string before start of clipboard        |
| ``_saveClipboard filename.txt``            | Store text from clipboard to file           |
| ``_setClipboard $value``                   | Copy string to clipboard                    |
| ``_setClipboardFromFile path/to/file.txt`` | Copy content of file to clipboard           |


**Invoke copy/paste related key combos**

| Command                                 | Description                             |
| --------------------------------------- | --------------------------------------- |
| ``_copyAll``                            | Select all, than copy                   |
| ``_copyLine``                           | Select caret line, than copy            |
| ``_copyLineInTerminal``                 | Select caret line, than copy            |
| ``_copyInTerminal``                     | Varies by OS                            |
| ``_copyPaste "foo"``                    | Copy text to clipboard and invoke paste |
| ``_copyPasteInTerminal "foo"``          | Copy text to clipboard and invoke paste |
| ``_cutAll``                             | Select all, than cut                    |
| ``_hitPaste``                           |                                         |
| ``_hitPasteInTerminal``                 | Varies by OS                            |


**Manipulate strings from clipboard**  

All manipulation commands on strings from the clipboard output the resulting string.  
To over/write the result back to files, you can use the shell redirection operator ``>``. 

| Command                                                    | Description                                                                   |
| ---------------------------------------------------------- | ----------------------------------------------------------------------------- |
| ``_extractBetweenFromClipboard before after``              | Extract text excluding but between "before" and "after"                       |
| ``_pregMatchAllFromClipboard regex``                       | Output all matches of given regex in clipboard content                        |
| ``_replaceAfterFromClipboard search replace``              | Replace everything after and including the first occurrences of given string  |                                                       |
| ``_replaceBeforeFromClipboard search replace``             | Replace everything before and including the first occurrences of given string |
| ``_replaceAllFromClipboard search replace``                | Replace all occurrences of given string                                       |
| ``_replaceBetweenFromClipboard before after replacement `` | Replace text including and between "before" and "after"                       |
| ``_replaceFirstFromClipboard search replace``              | Replace first occurrence of given string                                      |
| ``_replaceLastFromClipboard search replace``               | Replace last occurrence of given string                                       |


#### Paste dynamically rendered content

The ``_pasteRenderedFromFile`` command enables doShell to render dynamic content
from template files, useful for example for inserting parametric JavaScript into
the browser console.

**Example**


````
#!/usr/bin/env bash

_activateBrowser
_openBrowserDevConsole
_pasteRenderedFromFile ::DIR::/alert.js {"<alert_text>":"hello"}
_hitEnter
````

alert.js containing: ``alert('<alert_text>');``

will:
* activate the browser
* open and focus the dev console
* load alert.js, replace the string "<alert_text>" by "hello", copy it to the clipboard
* paste the clipboard (the rendered alert-script) into the dev console
* run the inserted script from within the console
* **=>** raise the dynamically scripted alert popup


### Dialogs

| Command                                                         | Description                                                     |
| --------------------------------------------------------------- | --------------------------------------------------------------- |
| ``_notify "MESSAGE"``                                           | Display notification                                            |
| ``_alert "MESSAGE"``                                            | Show alert popup                                                |
| ``var=_confirm "MESSAGE"``                                      | Open Ok/Cancel Dialog, ``$var`` contains "Ok" or "Cancel" after |
| ``var=_prompt "MESSAGE"``                                       | Popup with input field                                          |
| ``var=_select "Take your pick:" {"Apple", "Banana", "Orange"}`` | Popup with options to select from                               |


### Send keystrokes

**Hit single key:**  

| Command           | Description                            |
| ----------------- | -------------------------------------- |  
| ``_hitBackspace`` | Hit backspace key                      |
| ``_hitDown``      | Hit cursor down key                    |
| ``_hitEnter``     | Hit enter key                          |
| ``_hitEnd``       | Hit end key                            |
| ``_hitEsc``       | Hit escape key                         |
| ``_hitF1``        | Hit F-Key                              |
| ``_hitHome``      | Hit home key                           |
| ``_hitLeft``      | Hit cursor left key                    |
| ``_hitPageDown``  | Hit pageDown key                       |
| ``_hitPageUp``    | Hit pageUp key                         |
| ``_hitRight``     | Hit cursor right key                   |
| ``_hitSpace``     | Hit space bar                          |
| ``_hitTab``       | Hit tabulator key                      |
| ``_hitUp``        | Hit cursor up key                      |


**Stroke key combination:**

**Cursor combos:**

| Command                   | Linux             | Mac                |
| ------------------------- | ----------------- | ------------------ |
| ``_hitModDown``           |                   |                    |
| ``_hitModLeft``           |                   |                    |
| ``_hitModRight``          |                   |                    |
| ``_hitModUp``             | CTRL + cursor up  | ALT + cursor up    |
| ``_hitShiftModDown``      |                   |                    |
| ``_hitShiftModLeft``      |                   |                    |
| ``_hitShiftModRight``     |                   |                    |
| ``_hitShiftModUp``        |                   |                    |
| ``_hitShiftSuperDown``    |                   |                    |
| ``_hitShiftSuperLeft``    |                   |                    |
| ``_hitShiftSuperRight``   |                   |                    |
| ``_hitShiftSuperUp``      |                   |                    |
| ``_hitSuperDown``         |                   |                    |
| ``_hitSuperLeft``         |                   |                    |
| ``_hitSuperRight``        |                   |                    |
| ``_hitSuperUp``           | WIN + cursor up   | CMD + cursor up    |
| ``_moveCaretToLineStart`` | Home              | CMD + cursor left  |
| ``_moveCaretToLineEnd``   | End               | CMD + cursor right |

**Common functional shortcuts:**

| Command                 | Description                    |
| ----------------------- | ------------------------------ |   
| ``_hitCopy``            | Hit CTRL+C or CMD+c            |
| ``_hitFindInTerminal``  | Hit CTRL+SHIFT+F or CMD+F      | 
| ``_hitFind``            | Hit CTRL+F or CMD+F            | 
| ``_copyInTerminal``     | Varies by OS                   |
| ``_cut``                | Hit CTRL+X or CMD+x            |
| ``_hitPaste``              | Hit CTRL+V or CMD+V            |
| ``_hitPasteInTerminal``    | Varies by OS                   |
| ``_hitSelectAll``          | Hit CTRL+A or CMD+A            |


**Type text:**

| Command               | Description                                    |
| --------------------- | ---------------------------------------------- |  
| ``_copyPaste "foo"``  | Copy text to clipboard and invoke paste. ``*`` |
| ``_type "TEXT"``      | Simulate typing given text on keyboard         |

``* Oftentimes a faster alternative over typing``  


### Browser automation  

**Note:** At the time being doShell was tested using Firefox, but should be 
easily adaptable to other web browsers. 


#### Toggle browser panels

| Command                      | Description                                                                                 |
| ---------------------------- | ------------------------------------------------------------------------------------------- |
| ``_activateBrowser``         | Launch or bring browser window to front                                                     | 
| ``_closeBrowserTab``         | Hits CTRL+W or CMD+W                                                                        |
| ``_focusBrowserUrl``         | Hits CTRL+L or CMD+L                                                                        |
| ``_focusNextBrowserTab``     | Hits CTRL+TAB or CMD+TAB                                                                    |
| ``_focusPreviousBrowserTab`` | Hits CTRL+SHIFT+TAB or CMD+OPT+TAB                                                          |
| ``_openBrowserDevConsole``   | Hits CTRL+SHIFT+J or CMD+SHIFT+J (firefox) or CTRL+SHIFT+P / CMD+SHIFT+P in Chrome/Chromium |
| ``_openBrowserDevTools``     | Hits CTRL+SHIFT+I or CMD+OPT+I                                                              |
| ``_openBrowserSettings``     | Hits CTRL+Comma or CMD+Comma                                                                |
| ``_openNewBrowserTab``       | Hits CTRL+T or CMD+T                                                                        |
| ``#reopenBrowserTab``        | Hits CTRL+SHIFT+W or CMD+SHIFT+W                                                            |
| ``_openBrowserSource``       | Hits CTRL+U or CMD+U                                                                        |


#### Load and manipulate URLs

| Command                                               | Description                               |
| ----------------------------------------------------- | ----------------------------------------- |
| ``_copyBrowserUrl``                                   | Focus URL, than fire copy key-combination |
| ``myVar=_getBrowserUrl``                              | Get current URL                           |
| ``_openUrlInNewBrowserTab "https://duckduckgo.com/"`` | Load given URL in new browser tab         |


#### Use devTools and devConsole

| Command                              | Description                                                                                           |
| ------------------------------------ | ----------------------------------------------------------------------------------------------------- |
| ``_openBrowserDevConsole``           | Hits CTRL+SHIFT+J or CMD+SHIFT+J (firefox) or CTRL+SHIFT+P / CMD+SHIFT+P in Chrome/Chromium           |
| ``_openBrowserDevTools``             | Hits CTRL+SHIFT+I or CMD+OPT+I                                                                        |
| ``_runJs alert('hello') #end_runJs`` | Open and focus devConsole, paste and execute given script                                             |
| ``_execDevConsole``                  | Hits CTRL+ENTER or CMD+ENTER                                                                          |
| ``_clearDevConsole``                 | Clears current commands from devConsole                                                               |
| ``_copyRenderedBrowserHtml``         | Open devConsole and run JavaScript to retrieve and copy current HTML to clipboard                     |
| ``_pasteRenderedFromFile``           | Helpful for rendering JavaScript dynamically, see rel. [example](#paste-dynamically-rendered-content) |


#### Communication from browser to runtime system

For communication from web browser back to the runtime system, the system 
clipboard and file IO can be used. doShell provides built-in commands for 
manipulation and import / export of text from/to the clipboard.


### Terminal automation

| Command                           | Description                             |
| --------------------------------- | --------------------------------------- |
| ``_activateTerminal``             | Open or bring terminal to front         |
| ``_openNewTerminal``              |                                         |
| ``_openNewTerminalTab``           | Hit CTRL+SHIT+T or CMD+T                | 
| ``_hitFindInTerminal``            | Hit CTRL+SHIFT+F or CMD+F               |
| ``_copyPasteInTerminal "foo"``    | Copy text to clipboard and invoke paste | 
| ``_copyPasteInTerminal $VAR``     | Copy text to clipboard and invoke paste |
| ``_runInNewTerminal "ls"``        | Run given shell script in new terminal  | 


## Functions, iterations, conditions, extensions

doShell is a superset of shell script:  
All language constructs of regular shell script can be used within doShell 
script. 

DoShell can invoke all scripts that regular shell scripts can.
Therefor there is no limit to extend doShell with arbitrary tools, native or of
any language.


## Script Examples

The following example scripts can be found under [/examples](/examples):

| File                                                                                   | Description                                                                                  |
| -------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------- |
| [01_import.do.sh](/examples/01_import.do.sh)                                           | Import scripts from other file                                                               |
| [02_macros.do.sh](/examples/02_macros.do.sh)                                           | Use transpiler- and runtime macros                                                           |
| [03_platform_conditions.do.sh](/examples/03_platform_conditions.do.sh)                 | Vary code per platform                                                                       |
| [04_random.do.sh](/examples/04_random.do.sh)                                           | Random value generation                                                                      |
| [05_strings.do.sh](/examples/05_strings.do.sh)                                         | String manipulation                                                                          |
| [06_strings_from_files.do.sh](/examples/06_strings_from_files.do.sh)                   | Manipulation of strings from files                                                           |
| [07_clipboard_strings.do.sh](/examples/07_clipboard_strings.do.sh)                     | Clipboard manipulation commands                                                              |
| [08_parse_url.do.sh](/examples/08_parse_url.do.sh)                                     | Parse and encode/decode URL parts                                                            |
| [09_parse_php.do.sh](/examples/09_parse_php.do.sh)                                     | Use PHP within doShell script                                                                |
| [10_runtime_variables.do.sh](/examples/10_runtime_variables.do.sh)                     | Use of dynamic runtime variables                                                             |
| [11_dialogs_alert.do.sh](/examples/11_dialogs_alert.do.sh)                             | Display an alert popup on the desktop                                                        |
| [12_dialogs_notify.do.sh](/examples/12_dialogs_notify.do.sh)                           | Display a notification on the desktop                                                        |
| [13_dialogs_confirm.do.sh](/examples/13_dialogs_confirm.do.sh)                         | Display and evaluate the choice of an ok- or cancel- confirmation popup on the desktop       |
| [14_dialogs_prompt.do.sh](/examples/14_dialogs_prompt.do.sh)                           | Display and evaluate the input of a prompt popup on the desktop                              |
| [15_dialogs_select.do.sh](/examples/15_dialogs_select.do.sh)                           | Display and evaluate the choice of a selection popup on the desktop                          |
| [16_perform_google_search.do.sh](/examples/16_perform_google_search.do.sh)             | Open google in a new browser tab enter a search term and invoke search                       |
| [17_export_website_to_markdown.do.sh](/examples/17_export_website_to_markdown.do.sh)   | Get source HTML of website, convert (using Node.js) and output as markdown                   |
| [18_run_js_in_dev_console.do.sh](/examples/18_run_js_in_dev_console.do.sh)             | Open the browser's dev console, insert and run script in it                                  |
| [19_extract_urls_from_web_page.do.sh](/examples/19_extract_urls_from_web_page.do.sh)   | Extract all URLs from HTML source of a web page                                              |
| [20_swop_domain_to_localhost.do.sh](/examples/20_swop_domain_to_localhost.do.sh)       | Replace any domain loaded in browser by "localhost", maintaining rest of URL                 |
| [21_swop_to_selected_domain.do.sh](/examples/[21_swop_to_selected_domain.do.sh)        | Replace any domain loaded in browser by  domain selected from popup, maintaining rest of URL |


Third Party References
----------------------

## Runtime tools 

doShell invokes existing third party tools (and some doShell built-in commands)
to perform automation, display dialogs, etc. 
These vary by platform, not all tools are mandatory (depending on options used 
within doShell scripts).  


### Runtime tools on Linux 

| Tool                                                                       | Description                                                                             | License                                                                                              |
| -------------------------------------------------------------------------- | --------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------- |
| [PHP](https://www.php.net/)                                                | Open source general-purpose scripting language                                          | [PHP License](https://www.php.net/license/)                                                          |
| [wmctrl](http://tripie.sweb.cz/utils/wmctrl/)                              | UNIX/Linux command line tool to interact with an EWMH/NetWM compatible X Window Manager | [GNU General Public License](https://opensource.org/licenses/gpl-license)                            |
| [xclip](https://linux.die.net/man/1/xclip)                                 |                                                                                         |                                                                                                      |
| [xddotool](http://manpages.ubuntu.com/manpages/trusty/man1/xdotool.1.html) | Simulate keyboard input and mouse activity, move and resize windows, etc.               | [New BSD license](https://opensource.org/licenses/BSD-3-Clause)                                      |
| [xsel](https://linux.die.net/man/1/xsel)                                   |                                                                                         |                                                                                                      |
| [zenity](https://wiki.gnome.org/Projects/Zenity)                           | Execution of GTK dialog boxes from command-line and shell scripts                       | [Gnu Lesser General Public License](https://en.wikipedia.org/wiki/GNU_Lesser_General_Public_License) |

                                                        
### Runtime tools on Mac 

| Tool                                         | Description                                    | License                                                                              |
| -------------------------------------------- | ---------------------------------------------- | ------------------------------------------------------------------------------------ |
| AppleScript (osascript)                      | **Note:** Assistive access must be enabled     | Proprietary (parts available under [APSL](https://opensource.org/licenses/APSL-2.0)) |               
| [PHP](https://www.php.net/)                  | Open source general-purpose scripting language | [PHP License](https://www.php.net/license/)                                          |

As these third party runtime tools are not bundled in any form into doShell, 
their license liabilities are not affecting doShell.


### Third party tools used in examples

| Tool                                                                  | Description                                  | License                                            |
| --------------------------------------------------------------------- | -------------------------------------------- | -------------------------------------------------- |
| [Turndown](https://github.com/domchristie/turndown) (Node.js package) | Convert HTML into Markdown with JavaScript.  | [MIT License](https://opensource.org/licenses/MIT) |               


## Build tools and libraries

doShell was built using the following third party libraries and tools:

| Library                                           | Description                                                        | License                                                          |
| ------------------------------------------------- | ------------------------------------------------------------------ | ---------------------------------------------------------------- |
| [Clip Library](https://github.com/dacap/clip)     | Library to copy/retrieve content to/from the clipboard/pasteboard. | [MIT License](https://opensource.org/licenses/MIT)               |


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
