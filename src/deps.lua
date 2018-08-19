-- Tupperware
-- Skye Soss 2018

local ffi = require 'ffi'
local lfs = require 'lfs'
local U   = require 'utils'

local M = {}

local sys = ffi.os

-- Ensure there is a shell available
if not os.execute() then
    U.fatal"Tupperware needs an available shell!"
end

function M.docker_is_installed()
    if sys == "Windows" then
        local exeloc = "C:\\Program Files\\Docker\\Docker\\Docker for Windows.exe"
        return (lfs.attributes(exeloc)) 
    end
end



return M
