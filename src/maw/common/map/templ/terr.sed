s/default_move_cost *= *\([1-9][0-9]*\)/define(`DLUMC', `\1')dnl/
s/\([a-z][a-z0-9_]*\) *= *\([a-z0-9][a-z0-9_]*\)/define(`\1', `\2')dnl/g
