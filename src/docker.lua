#!/usr/bin/env luajit

-- Tupperware
-- Skye Soss 2018

local deps = require 'deps'
local lfs  = require 'lfs'
local U    = require 'utils'

local M = {}

local image_name = "skyb0rg/tupperware:initial"
local cache_dir  = "~/.tupperware"

function M.docker_setup()
    assert(os.execute('docker pull "'..image_name..'"'))
end

function M.docker_make(target)
    local curr_dir = assert(lfs.currentdir())
    if curr_dir:find":" then
        U.fatal "Cannot have a directory with a colon in it!"
    end
    assert(os.execute(
        'docker run -it --rm -v "'..curr_dir..
        ':/opt/app-root/src:rw,z" '..image_name..
        ' scl enable devtoolset-7 llvm-toolset-7 make '..
        (target or "")))
end

return M
