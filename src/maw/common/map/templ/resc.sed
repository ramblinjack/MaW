s/\([a-z][a-z0-9_]*\) *= *\([a-z0-9][a-z0-9_]*\)/define(`\1', `\2')dnl/g
s/on  *\([a-z][a-z0-9_]*\) \([0-9][0-9]*\)/  case translit(`\1',`a-z',`A-Z'): return \2;/g
s/\([a-z][a-z_]*\) *{/define(`\1',`/g
s/}/')dnl/g
