s/^ *\([A-Z][A-Z0-9_]*\) *$/define(`\1')dnl/g
s/NAME *= *\([A-Z0-9][A-Z0-9_]*\)/define(NAME, `translit(`\1', `A-Z', `a-z')')dnl/g
s/PRETTY_NAME *= *\(.*\)/define(PRETTY_NAME, `translit(`\1', `A-Z', `a-z')')dnl/g
s/PLURAL *= *\(.*\)/define(PLURAL, `translit(`\1', `A-Z', `a-z')')dnl/g
s/\([A-Z][A-Z0-9_]*\) *= *\(.*\)/define(`\1', `\2')dnl/g
s/AGAINST  *\([A-Z][A-Z0-9_]*\)  *\([1-9][0-9]*\)%/  case \1: return (\2f\/100f);/g
s/ON  *\([A-Z][A-Z0-9_]*\)  *\([1-9][0-9]*\)%/  case \1: return (\2f\/100f);/g
s/FROM  *ANY  *TO  *\(.*\)  *\([1-9][0-9]*\)%/if (get_terr(to) == \1) return (\2f\/100f);/g
s/FROM  *\(.*\)  *TO  *\(.*\)  *\([1-9][0-9]*\)/if (get_terr(from) == \1 && get_terr(to) == \2) return (\3f\/100f);/g
s/FROM  *ANY  *TO  *\(.*\)  *\([1-9][0-9]*\)%/if (get_terr(to) == \1) return (\2f\/100f);/g
s/FROM  *\(.*\)  *TO  *ANY  *\([1-9][0-9]*\)/if (get_terr(from) == \1) return (\2f\/100f);/g
s/\([A-Z][A-Z_]*\) *{/define(`\1',`/g
s/}/')dnl/g
