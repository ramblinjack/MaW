s|# *\(.*\)|/\* \1 \*/dnl|g
s/\([a-z][a-z0-9_]*\) *: *\([0-9][0-9]*\)/define(`FIELD_NAME',`\1')define(`SIZE',`\2')dnl/g