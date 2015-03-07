#include <cstdio>
#include <cstdint>
#include "bitmask_macros.h"

#define LAST_FIELD test
MAW_DECL_DUMMY_OFFS(test)

typedef uint16_t test_t;

MAW_DECL_BITS(test_t, field1, 8, uint8_t)
#undef LAST_FIELD
#define LAST_FIELD field1

MAW_DECL_BITS(test_t, field2, 3, uint8_t)
#undef LAST_FIELD
#define LAST_FIELD field2

MAW_DECL_BITS(test_t, field3, 2, uint8_t)
#undef LAST_FIELD
#define LAST_FIELD field3

MAW_DECL_BITS(test_t, field4, 3, uint8_t)
#undef LAST_FIELD

enum FIELD1: field1 {F1BE = 0xbe, F1CD = 0xcd};
enum FIELD2: field2 {F27 = 0x7, F25 = 0x5};

int main(int argc, char** argv) {
  
  test_t t1 = 0;
  set_field1(&t1, F1BE);
  field1 be = get_field1(t1);
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
  set_field4(&t2, 0x7);
  if (t2 != 0xFFFF) return 77;
  if (set_field4(t2, 0x5) != 0xBFFF) return 77;
  
  return 0;
}

