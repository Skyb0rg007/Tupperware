#!/usr/bin/env luajit

local U       = require 'utils'
local docker  = require 'docker'
local deps    = require 'deps'
local cli     = require 'cliargs'
local inspect = require 'inspect'

-- cli.lua
-- Descriptions and implementations of the cli arguments
-- Words followed with a '*' indicate default behavior that
--  can be changed as a cli-argument
-- Words followed with a '+' indicate default behavior that
--  can be changed in the config file as well as a cli-argument

cli:set_name "tupp"
cli:set_description "TuftsCS compilation companion"

local defaults = {
    shellname = "bash",
    ssh_keys = true,
    run_make = true,
    make_autogen = true,
}

-- tutorial: run a sample tutorial on how to use this program
cli
    :command("tutorial", "- runs a simple tutorial on how to use tupp")
    :action(function()
        print "running tutorial..."
        os.exit(0)
    end)

-- setup: create the environment for tupp to run in
--  Exits* if this has already been done before
--  Creates .tuperwarerc template from user questionaire
--  Directs user on how to download docker
--  Helps set up ssh keys with the Halligan server
cli
    :command("setup", "- set-up Docker and ssh")
    :flag('-f, --force', ':: run even if already set-up')
    :action(function(options)
        return pcall(docker.docker_setup, options.force)
    end)

-- fetch: grabs the project from Halligan servers
--  Confirms* current location
--  If no .tuppconfig, generate one after asking for remote complement dir
--  Uses ssh keys+ to connect to Halligan
--  If not downloaded from server, searches from student's class,
--   copying locally and to the remote complement dir
cli
    :command("fetch", "- fetch the project from the Halligan servers")
    :argument("project", ":: project to fetch")
    :flag("--no-confirm", ":: do not confirm the current directory")
    :flag("--ssh-keys", ":: use ssh-keys to connect to Halligan")
    :flag("--no-ssh-keys", ":: prompt for password rather than using ssh-keys")
    :action(function(options)
        print("fetching project "..options.project.." is not yet implemented")
    end)

-- sync: uploads changes from current directory to Halligan servers
--  Uses ssh keys+ to connect to Halligan
--  Checks whether any changes were made since last sync
--  Exits* if remote changes were made since last sync
cli
    :command("sync", "- synchronize working dir with Halligan server dir")
    :flag("--ssh-keys", ":: use ssh-keys to connect to Halligan")
    :flag("--no-ssh-keys", ":: prompt for password rather than using ssh-keys")
    :flag("-f, --force", ":: overwrite Halligan files without remorse")
    :action(function()
        print "sync is not yet implemented"
    end)

-- make: compiles the project in the current directory
--  Checks for a Makefile, prompts+ for auto-generation
--  Runs 'make' from a temporary Docker container on the given target
cli
    :command("make", "- compile project in the current directory")
    :splat("target", ":: Makefile target to build", nil, 1)
    :flag("-a, --auto-gen", ":: generates a Makefile if none exist", defaults.make_autogen)
    :action(function(options)
        return docker.docker_make(options.target)
    end)

-- shell: run a shell from a temporary Docker container
--  Runs bash+ by default
cli
    :command("shell", "- run a shell from within the Docker image")
    :splat("shellname", ":: bash, tcsh, fish, zsh, csh, sh", defaults.shellname, 1, 
        function(_,sh)
            if not ({bash=true,tcsh=true,fish=true,zsh=true,
                    csh=true,sh=true})[sh] then
                U.fatal("error: "..sh.." is not a valid shell\n")
            end
        end)
    :action(function(options)
        print("Going to run "..options.shellname..
            " once this gets implemented")
    end)

-- tinker: make permanent modifications to the local docker image
--  Runs bash+ shell in a permanent docker container
--  Prompts whether to commit the change to the local docker image
--  Removes the previous docker image
cli
    :command("tinker", "- make permanent modifications to the Docker image.")
    :splat("shellname", ":: bash, tcsh, fish, zsh, csh, sh", defaults.shellname, 1, 
        function(_,sh)
            if not ({bash=true,tcsh=true,fish=true,zsh=true,
                    csh=true,sh=true})[sh] then
                U.fatal("error: "..sh.." is not a valid shell\n")
            end
        end)
    :action(function(options)
        print("Going to tinker with the image while running "..options.shellname)
    end)

-- run: execute the executable
--  Runs the given executable from the Docker container
--  If the executable is a make target, runs make+ prior to executing
cli
    :command("run", "- run an executable from within the Docker image")
    :argument("executable", ":: executable to run")
    :splat("arguments", ":: arguments to pass to the executable", "", 999)
    :flag("-z, --freeze", ":: do not `make` the target before running", defaults.run_make)
    :action(function(options)
        print(options.freeze and "Frozen" or "Making "..options.executable)
        print("[Docker]$ ./"..options.executable.." "..table.concat(options.arguments))
    end)

local args, err = cli:parse()
if not args then
    print(err)
    os.exit(1)
elseif next(args) == nil then
    cli:print_help()
    os.exit(1)
end
print(inspect(args))
