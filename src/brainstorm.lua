#!/usr/bin/env luajit

local yaml = require 'lyaml'
local null = yaml.null

local M = {}

local function fatal(str, ...)
    io.stderr:write(string.format(str.."\n", ...))
    os.exit(1)
end

local config_filename = "~/.tupperwarerc"
local config_file = io.open(config_filename)
if config_file then
    local err, config = pcall(yaml.load, config_file:read"*a")
    if err then
        fatal("Error loading %s: %s", config_filename, config)
    end
    config_file:close()
end

--[[
     Config Format:
     image: "<image name>"
--]]

local image_name = "cpp_dev_image"

function M.docker_setup()
    os.execute("docker build -t "..image_name.." .")
end

function M.docker_make(target)
    M.docker("make "..(target or ""))
end

function M.docker_run(target)
    M.docker(target)
end

function M.docker(cmd)
    cmd = cmd or "bash"
    os.execute("docker run -it --rm -v $PWD:/opt/app-root/src:rw,z "
        ..image_name.." scl enable devtoolset-7 llvm-toolset-7 "
        ..cmd)
end

return M
