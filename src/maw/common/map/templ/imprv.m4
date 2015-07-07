class name : public imprv {
  public:
    name`()': imprv(cost) {}

  virtual unsigned get_food_bonus(maw_tile tile) const {
    switch(maw_get_terr(tile)) {ifdef(`food_bonus', `food_bonus')
    default: return 0;
    }
  }
  virtual unsigned get_trade_bonus(maw_tile tile) const {
    switch(maw_get_terr(tile)) {ifdef(`trade_bonus', `trade_bonus')
    default: return 0;
    }
  }
  virtual unsigned get_prod_bonus(maw_tile tile) const {
    switch(maw_get_terr(tile)) {ifdef(`production_bonus', `production_bonus')
    default: return 0;
    }
  }
};

