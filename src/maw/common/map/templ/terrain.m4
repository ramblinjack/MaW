
class NAME : public terrain
#ifdef CLIENT
, public gphx_obj
#endif
{
  public:
    NAME`()': terrain(FOOD, PRODUCTION, TRADE)
#ifdef CLIENT
    , gphx_obj(DATADIR/resc/ "ICON",
    DATADIR/resc/ "ifdef(`BACKGROUND_ICON', `BACKGROUND_ICON', `nullptr')",
    ifdef(`PRETTY_NAME', `PRETTY_NAME', `NAME'),
    ifdef(`PLURAL', `PLURAL', `NAME'))
#endif
     {}
};
