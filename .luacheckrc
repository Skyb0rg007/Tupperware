ignore = {
    '611','612','613','614','631', -- whitespace warnings
    '521', -- unused label
    '541','542', -- empty `if` and `do` blocks
    '211','212','213', -- unused warnings (variable, arg, loop)
    '111', -- setting undefined global
}

std = "luajit+lua52"

files.spec.std = "+busted"
