#include <cstdio>
#include <cstdint>
#include "bitmask_macros.h"

// Need to define these before calling MAW_DECL_BITS
#define LAST_FIELD test
MAW_DECL_DUMMY_OFFS(test)

// typedef our container
typedef uint16_t test_t;

// declare some fields, field1 of test_t uses
// 8 bits and is typedefed as uint8_t
MAW_DECL_BITS(test_t, field1, 8, uint8_t)
#undef LAST_FIELD
#define LAST_FIELD field1

MAW_DECL_BITS(test_t, field2, 3, uint8_t)
#undef LAST_FIELD
#define LAST_FIELD field2

MAW_DECL_BITS(test_t, field3, 2, uint8_t)
#undef LAST_FIELD
#define LAST_FIELD field3

MAW_DECL_BITS(test_t, field4, 1, bool)
#undef LAST_FIELD
#define LAST_FIELD field4

// field{1,2} were typedefed by MAW_DECL_BITS
enum FIELD1: field1_t {F1BE = 0xbe, F1CD = 0xcd};
enum FIELD2: field2_t {F27 = 0x7, F25 = 0x5};

// test the getter and setters declared by MAW_DECL_BITS.
// We return 77 in case of a failure because that's what
// automake wants I think.
int main(int argc, char** argv) {
  
  test_t t1 = 0;
  set_field1(&t1, F1BE);
  field1_t be = get_field1(t1);
  if (be != 0xbe) return 77;
  set_field2(&t1, F25);
  if (get_field2(t1) != F25) return 77;
  get_field1(t1);
  get_field2(t1);
  get_field3(t1);
  get_field4(t1);
  
  test_t t2 = 0;
  set_field1(&t2, 0xFF);
  set_field2(&t2, 0x7);
  set_field3(&t2, 0x3);
  set_field4(&t2, true);
  if (!get_field4(t2)) return 77;
  if (t2 != 0x3FFF) return 77;
  if (set_field4(t2, false) != 0x1FFF) return 77;
  
  return 0;
}

