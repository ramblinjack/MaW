s/NAME *= *\([A-Z0-9][A-Z0-9_]*\)/define(NAME, `translit(`\1', `A-Z', `a-z')')dnl/g
s/DEFAULT MOVE COST *= *\([1-9][0-9]*\)/define(`DLUMC', `\1')dnl/
s/\([A-Z][A-Z0-9_]*\) *= *\([A-Z0-9][A-Z0-9_]*\)/define(`\1', `\2')dnl/g
