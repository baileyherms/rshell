# rshell
The simple shell created for CS100 at UCR.

##Dependences
This shell requires a unix terminal to be run.

##To Build
```
$ git clone  https://github.com/baileyherms/rshell.git
$ cd <branch>
$ git checkout hw<#>
$ make
$ bin/<branch>
```
##Bugs/Limitations
###rshell
- Will not exit the shell if exit is called between two functions
- cd does not work
- No colors
- Does not detect more than double connectors (ex: '|||')
- No input or output redirection
- The arrow keys are unreliable
- Pipes ('|') do not work with input/output redirection ('<,>,>>')

###ls
- Does not run correct colors on ls, ls -a, ls -R, ls -Ra due to an error in the ls and ls -a functions (planning to fix in the future)
- Spacing for all but ls -l is based on the largest file in the set instead of the largest file in the column
- Connectors do not work
- There is an extra new line at the end of any -R argument
- Will not fit output to terminal, fixed alloted horizontal length
- No personalization of colors
