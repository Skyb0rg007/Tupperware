Tupperware - Tufts CLI Companion

# The problem:

TuftsCS: "Compile early and often! Test your program as much as possible!"

Reality:
   - Compiling on the server is extremely slow, take this REAL example (program just prints "Hello world"):
    
         time clang++ hello.cpp
            real    0m9.330s
            user    0m2.911s
            sys     0m0.137s
            
     Taking 10 seconds per file to compile is unacceptable, especially in COMP11 (You haven't learned about Makefiles yet)
     For comparison, on my laptop:
          
          time clang++ hello.cpp
             real    0m0.371s
             user    0m0.312s
             sys     0m0.041s 
      
   - Compiling locally is not reliable
        - Problems setting up an environment
        - System-specific problems, functions, etc.
   - There is a memory leak in Halligan's libstd++, so ALL PROGRAMS fail valgrind tests
        - It's a pain to test for memory leaks with ```valgrind``` on the server

There must be a better way!

## Introducing Tupperware!

_Bring a bit of Halligan home with you_


# Goal spec:

Commands:

    tupp setup 
     - Runs the setup procedure, downloading docker, the docker image, 
       and configuring ssh and directory structure within the Halligan servers
       Writes all the data to the ~/.tupperwarerc file (different on Windows)

    tupp fetch [<project>]
     - Grab the specified project from the Halligan servers
       and place it in the current directory

    tupp sync
     - Synchronize your working directory with the one in Halligan servers
       Requires ssh and directory setup

    tupp make [<target>]
     - Runs `make [<target>]` from the Docker image

    tupp bash|tcsh|fish|zsh|sh
     - Run a shell from the Docker image.
       NOTE: No lasting effects are possible
    
    tupp [-z|--freeze] run <executable> [<args>]
     - Runs the executable from the Docker image
       `make`s the target, unless -z or --freeze is specified

    tupp push [-f|--force]
     - Sends your current changes to the Halligan server
       Requires ssh and directory setup
       Does not overwrite if there are files already there unless forced

    tupp <command> [help|-h|--help]
     - Show help dialog for the command
     

# Helping out

I would love help of any kind in creating this project!

Please submit any issues or ideas in the Github issue tracker

If you want to help with the program itself, let me know! I would be more than welcome to help you improve/develop Tupperware.


# FAQ
### Why am I making this I haven't even made a prototype

## Why Docker?

Docker lets people run a GNU/Linux "computer" with access to local files

Docker itself is not something that new CS students should be using however. Docker is meant for development teams on Linux machines.

Basically Docker is useful but hard

## Why CentOS?

Tufts uses a _proprietary_ GNU/Linux OS known as RHEL7 (Red Hat Enterprise Linux)

This means you can't emulate it without paying money

CentOS is the "free version of RHEL". (Community ENTerprise Operating System)

CentOS and RHEL are (for our purposes) 100% compatible. I run Fedora 28 (similar to RHEL, not as close as CentOS) and my executables run on the Halligan servers, so I guarentee that the CentOS ones will too
 
## Why Lua(jit)?

Docker is a huge download. The Halligan Docker image is a large download.

Tupperware should be as small as physically possible.

Because I want to run on all desktops, I want a fully bundled executable with minimal dependencies.

C++ is nice, but developing C++ on Windows is impossibly complex.

Java, C#, and Python are nice, but they all need runtimes/interpreters

Lua also needs an interpreter, but because it's size is so small, it can be inbedded into one executable easily
