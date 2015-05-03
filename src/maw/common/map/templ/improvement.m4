class NAME : public improvement
#ifdef CLIENT
, public gphx_obj
#endif
{
  public:
    NAME`()': improvement(TURNS, VALUE, ifdef(`FOOD_BONUS', `true', `false'), ifdef(`TRADE_BONUS', `true', `false'), ifdef(`PRODUCTION_BONUS', `true', `false'))
#ifdef CLIENT
    , gphx_obj(ICON, BACKGROUND_ICON, PRETTY_NAME, PLURAL)
#endif
    {}

  virtual unsigned food_bonus(tile_t tile) const {
    switch(get_terr(tile)) { ifdef(`FOOD_BONUS', `FOOD_BONUS')
    default: return 0;
    }
  }

  virtual unsigned trade_bonus(tile_t tile) const {
    switch(get_terr(tile)) { ifdef(`TRADE_BONUS', `TRADE_BONUS')
    default: return 0;
    }
  }
  
  virtual unsigned prod_bonus(tile_t tile) const {
    switch(get_terr(tile)) { ifdef(`PRODUCTION_BONUS', `PRODUCTION_BONUS')
    default: return 0;
    }
  }
};

