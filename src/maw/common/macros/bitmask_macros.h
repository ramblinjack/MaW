#ifndef BITMASK_MACROS_H
#define BITMASK_MACROS_H

#define MAW_DECL_DUMMY_OFFS(pkg) \
  static constexpr unsigned pkg##_offs = 0;  

#define MAW_BITMASK(to, from) ((2ULL << (to)) - (1ULL<<(from)))

#define MAW_GET_FIELD_OFFS(field) MAW_CAT(field, _offs)

#define MAW_CAT(x, y) x ## y

#define MAW_TOT_BITS MAW_GET_FIELD_OFFS(LAST_FIELD)

/* 
   This macro is used to create getter and setters for bitfields
   The argument pkg_t is the type of the "container" of the bitfields.
   The argument field is the name of the field defined, it can't
   contain spaces or other weirdness of course.
   nrbits is the number of bits to be used for field.
   type is the type used for field, it should be the smallest type
   able to hold enough bits, and it should be unsigned to avoid
   trouble with the shifts.
   
   After this macro is used one must undef the symbol LAST_FIELD
   and redefine it to be the field that was just declared. Thus
   we push the problem of keeping state in the preprocessor
   (to know what bit in pkg_t we're currently on) to compile time.
   This means that we must define symbols to hold the offset, and
   this brings with it the unfortunate effect that we have to take
   up a name in the namespace. Thus if you want to fields in different
   containers to have the same name, it might cause a problem. This
   should be resolved by daclaring them in different namespaces though.
   
   We also have to define a starting point (0) for the bitmasks, this
   is done with the macro MAW_DECL_DUMMY_OFFS(pkg) combined with
   define LAST_FIELD pkg. This is not pretty, but it's the best I came
   up with...
*/
#define MAW_DECL_BITS(pkg_t, field, nrbits, type)			\
  typedef type field;							\
  static constexpr unsigned field##_offs = MAW_TOT_BITS + nrbits;		\
  constexpr field get_##field(const pkg_t in) {				\
    return (field) ((in & MAW_BITMASK(MAW_TOT_BITS + nrbits -1 , MAW_TOT_BITS)) \
                    >> MAW_TOT_BITS);                                   \
  }									\
  constexpr pkg_t set_##field(const pkg_t target, const field mask) {	\
    return (target & (~(MAW_BITMASK(MAW_TOT_BITS + nrbits -1 , MAW_TOT_BITS)))) | \
      ((unsigned long long) mask << MAW_TOT_BITS);			\
  }									\
  inline void set_##field(pkg_t *target, const field mask) {		\
    *target = (*target &                                                \
               ~(MAW_BITMASK(MAW_TOT_BITS + nrbits - 1, MAW_TOT_BITS))) |   \
      ((unsigned long long) mask << MAW_TOT_BITS);			\
  }									\

#endif
