s/NAME *= *\([A-Z0-9][A-Z0-9_]*\)/define(NAME, `translit(`\1', `A-Z', `a-z')')dnl/g
s/\([A-Z][A-Z0-9_]*\) *= *\([A-Z0-9][A-Z0-9_]*\)/define(`\1', `\2')dnl/g
s/ON  *\([A-Z][A-Z0-9_]*\) \([0-9][0-9]*\)/  case \1: return \2;/g
s/\([A-Z][A-Z_]*\) *{/define(`\1',`/g
s/}/')dnl/g
