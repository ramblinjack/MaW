#ifndef BITMASK_MACROS_H
#define BITMASK_MACROS_H

#define MAW_DECL_DUMMY_OFFS(pkg) \
  static const unsigned pkg##_offs = 0;  

#define MAW_BITMASK(to, from) ((2ULL << (to)) - (1ULL<<(from)))

#define MAW_GET_FIELD_OFFS(field) MAW_CAT(field, _offs)

#define MAW_CAT(x, y) x ## y

#define MAW_TOT_BITS MAW_GET_FIELD_OFFS(LAST_FIELD)

#define MAW_DECL_BITS(pkg_t, field, nrbits, type)			\
  typedef type field;							\
  static const unsigned field##_offs = MAW_TOT_BITS + nrbits;		\
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
