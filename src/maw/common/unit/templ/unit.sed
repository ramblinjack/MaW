s/\([a-z][a-z0-9_]*\) *= *\(.*\)/define(`\1', `\2')dnl/g
s/against  *\([a-z][a-z0-9_]*\)  *\([1-9][0-9]*\)%/  case translit(`\1', `[a-z]', `[A-Z]'): return (\2f\/100f);/g
s/on  *\([a-z][a-z0-9_]*\)  *\([1-9][0-9]*\)%/  case translit(`\1', `[a-z]', `[A-Z]'): return (\2f\/100f);/g
s/from  *any  *to  *\(.*\)  *\([1-9][0-9]*\)%/if (maw_get_terr(to) == translit(`\1', `[a-z]', `[A-Z]')) return (\2f\/100f);/g
s/from  *\(.*\)  *to  *\(.*\)  *\([1-9][0-9]*\)/if (maw_get_terr(from) == translit(`\1', `[a-z]', `[A-Z]') && maw_get_terr(to) == translit(`\2', `[a-z]', `[A-Z]') return (\3f\/100f);/g
s/from  *any  *to  *\(.*\)  *\([1-9][0-9]*\)%/if (maw_get_terr(to) == translit(`\1', `[a-z]', `[A-Z]')) return (\2f\/100f);/g
s/from  *\(.*\)  *to  *any  *\([1-9][0-9]*\)/if (maw_get_terr(from) == translit(`\1', `[a-z]', `[A-Z]')) return (\2f\/100f);/g
s/\([a-z][a-z_]*\) *{/define(`\1',`/g
s/}/')dnl/g
