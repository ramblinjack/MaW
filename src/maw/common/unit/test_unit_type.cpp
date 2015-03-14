
#include "unit_type.h"

namespace maw {
namespace common {
namespace unit {

using namespace map;

// moce supertypes
enum class supertype {TYPE1, TYPE2};

class fake1 : public unit_type {

public:
  fake1(const supertype stype,
            const movp_num_t movs,
            const atk_t atk,
            const dfns_t dfns,
            const hlth_t hlth):
    unit_type(stype, movs, atk, dfns, hlth) {}
private:
  virtual const movp mov_cst(const tile_t to) const
  {return std::make_pair(1, 1);}
  virtual const dfns_t def_bonus(const tile_t on) const {return 0;}
  virtual const atk_t atk_bonus(const unit_t target, const tile_t from,
                                const tile_t to) const {return 0;}
};

  
} // end namespace unit
} // end namespace common
} // end namespace maw

using namespace maw::common::unit;

int main(int argc, char *argv[]) {

  unit_type* type = new fake1(supertype::TYPE1, 4, 2, 1, 4);
  unit_t u = 0;
  set_hlth(&u, 4);
  set_movp_den(&u, 1);
  set_movp_num(&u, 4);

  if (type->get_rem_movs(u).first != 4) return 77;
  set_hlth(&u, 2);
  if (type->get_rem_movs(u).first != 2) return 77;
  return 0;
}



