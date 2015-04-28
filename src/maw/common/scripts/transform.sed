# transform maw definition files to m4 macros.
s/\([A-Z][A-Z0-9_]*\) *= *\([A-Z0-9][A-Z0-9_]*\)/define(`\1', `\2')dnl/g
s/AGAINST  *\([A-Z][A-Z0-9_]*\) \([0-9][0-9]*\)%/case \1: mod+=(\2f\/100f); break;/g
s/ON  *\([A-Z][A-Z0-9_]*\) \([0-9][0-9]*\)%/case \1: mod+=(\2f\/100f); break;/g
s/\([A-Z][A-Z_]*\) *{/define(`\1',/g
s/}/)/g











