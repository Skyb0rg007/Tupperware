#!/usr/bin/env luajit

-- Tupperware
-- Skye Soss 2018

local ffi = require 'ffi'
local M   = {}

M.endl = ffi.os == "Windows" and "\r\n" or "\n"

function M.printf(fmt, ...)
    io.stdout:write(string.format(fmt, ...))
end

function M.fprintf(file, fmt, ...)
    file:write(string.format(fmt, ...))
end

function M.fatal(fmt, ...)
    M.fprintf(io.stderr, fmt, ...)
    os.exit(1)
end

return M
