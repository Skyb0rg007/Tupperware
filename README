Tupperware - Tufts CLI Companion

# The problem:

TuftsCS: "Compile early and often! Test your program as much as possible!"

Reality:
    - Compiling on the server is extremely slow:
        ```time clang++ hello.cpp```
            real	0m9.330s
            user	0m2.911s
            sys	0m0.137s
        
      (This is real!!)
    - Compiling locally is not reliable
        - Problems setting up an environment
        - System-specific problems, functions, etc.
    - There is a memory leak in libstd++, so ALL PROGRAMS fail valgrind tests

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
