# WebNative
`webnative` is a tool chain which allows you to make native application with the help of web technologies. It's made for those who want really hands on access of lower level stuff for javascript like File IO, System Calls , ASyncronisation at low level and don't wanna write a single like of C++. It exposes it's direct api of C++ to JavaScript allowing you to write applications really quick without loosing the power! It directly compiles your html , css and javascript into a format which is looseless in terms of UI , Means what you saw in your browser is exactly what you get in your application.

## Installation
`WebNative` is called `wn` in it's apis and it has 2 repositories , One containg just the libraries which you can find (https://github.com/darkyboys/webnative-libraries)[here] and the repository containing the wncc which can is this repository, You only have to install from this repo and wncc has builtin repo management then.

 > Before you install make sure that you have the cook build system which you can fine (https://github.com/darkyboys/cook)[here] and git and gcc compiler

Now then just these commands in your shell:
```bash
git clone https://github.com/darkyboys/webnative
cd webnative
cook
sudo cook install
wncc --version
```

 > After running these you must see the version of WNCC!


## How To Compile A Program With wncc
`wncc` is the webnative compiler for the html , css and javascript and it does it's compiling via dynamic flags which you gives like `wncc --flag or --flag=value`

The known flags are:
 - `--version` : This flag shows the version of your wncc installation
 - `--WindowName=[name]` : This flag sets the window name of your compiled application
 - `--WindowHeight=[xyz number]` : This flag sets the window height of your compiled application
 - `--WindowWidth=[xyz number]` : This flag sets the window width of your compiled application
 - `-css=[file path]` : This flag links the defined css file in the path to the compiled executable
 - `-html=[file path]` : This flag links the defined html file in the path to the compiled executable
 - `-js=[file path]` : This flag links the defined js file in the path to the compiled executable
 - `-o=[name]` : This sets the output project name

 > You can use these flags repeatedly as many times as you wish. And remember that wncc uses gtk3 and webkit2gtk packages for it's window management and rendering so please make sure that you have these packages installed, When you compile the wncc will generate the project/project.cc and project/recipe files where recipe is for the cook build system and project.cc is based on the project name and contains the compiled CASCI linked , html , css and javascript code ready to be turned into binary.


## How To Code In Wn API ?
`wnApi` is the javascript side api which the `wncc` provides to work with as when you are writting a `wncc` program you are not working on normal javascript level , But you are working on the C++ Level but you just don't realises that because of the `wnApi`. So you will need to learn this api as it's straightforward and really important.

 - In WnApi everything is mostly defined as a function and there are 2 types of functions , Read functions and Write Functions , Basically read functions are those who just takes the input and provides the output without returning anything to the javascript , But Write functions are those who does the job and also returns something in javascript via buffers. And since C++ does all the backend so it sends the signals to javascript wnApi is a task is being executed already.

 ### Known functions
 > These are for the wncc 1 compiler so please check the latest docs for your latest features.

 - `wn_main()` : This is the main function which runs only when the wncc runtime is fully loaded means if you wanna execute any wn_api without events then use this for direct runtime excess. and remember to initalise `function wn_main(){}` even if you do nothing to it.
 - `wn_cli_argumentList` : This is not a function but a really important thing as it's a list of those CLI Argument which are gives to your application via the CLI. (This stores the data as CASCI so please call `wn_normalize (bufferData)` to see the original string)
 - `wn_home_directory` : This is also not a function but a really important variable as it contains the path to your user's home directory like `/home/usr` but only works for UNIX Like systems like Liniux or MAC OS But now on Windows.
 - `wn_event_signal` : This is the lowest level of wncc calls you can get because this variable is directly written by the wncc C++ Runtime which sends the signals to the javascript runtime , If any task is executing then it will contain 1 othervise 0 so feel free to use it with setIntervals.
 - `wn_error(error)` : This is a function which simply is used to log errors.
 - `wn_init()` : This is the function which tells the wn javascript runtime if the C++ runtime is initalised (Loaded and ready to use)
 - `wn_run(func)` : This takes a function as an argument and only runs it if the wncc runtime is loaded , And it is needed to prevent loading your application in normal browsers. But you don't have to call it manually as wnApi handles it for you.
 - `wn_fs_newFile(file_Path)` : This function makes a new file on the given filePath e.g: `a.txt`
 - `wn_continue (func, checks = 100)` : This function takes a function as an argument and second optional argument for check intervals , And this only runs the function when ever the C++ runtime sends the `0` signal to javascript , And this becomes necessary for things like File IO where time varies.
 - `wn_fs_openFile(file_Path)` : THis function opens a file which except for the `wn_fs_newFile` and `wn_fs_isFileExists` every other wn fs functions uses as file name.
 - `wn_fs_writeFile(file_Data)`: This function writes the `file_Data` on the opened file and use this carefully as it never warns and overwrites the file.
 - `wn_fs_readFile()` : This function returns the entire file content of an opened file in a buffer (Variables who temporary stores data) which is the variable `wn_fs_readFileData` and is always string. And it will not return anything if the `File` couldn't be opened. (`wn_fs_readFileData` stores file data in CASCI so be sure to call `wn_normalize (bufferData)` to see the actual file content)
 - `wn_fs_isFileExists(file_Name)` : This function checks if a file as `file_Name` exists or not, This is important for any file IO including read operations. If the file exists then write to the buffer / variable `wn_fs_isFileExistsBuffer` as 1 othervise 0 if don't exists.
 - `wn_fs_closeFile()` : This function closes any open file by assigning `wnx0000` in C++ Runtime.
 - `wn_normalize (bufferData)` : This function normalizes any `CASCI` buffer data into the original form by using the `libcasci` which `wncc` already links with your compiled javascript.
 - `wn_exit (code = 3)` : This function terminates your program anywhere with an exit code and bydefault it is 3.
 - `wn_system (command)` : This function runs a system shell command by blocking your application and only run it when the system command is finished.
 - `wn_psystem (command)` : This function is same as `wn_system (command)` but this one runt the command parallely to your program meaning it don't blocks your programs but use this carefully as it don't writes the signal buffer meaning `wn_continue (func, checks=100)` can't detect it.

 > Always remember these functions are only what you would need for most of the things , And don't use window.open and anchor tags as wn can only load online sites with anchor tags not the local files who aren't linked!! and linking also means your html will be directly rendered means if you link 2 pages and you want them to be seperately renderd then no they will render in a single frame / window.

---

## Contributing ?
Fork it! Mod it! Pull it!

## Thanks for reading.
written by ghgltggamer on 7/28/25 , 9:53PM IST
