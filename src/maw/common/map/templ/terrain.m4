
class NAME : public terrain
#ifdef CLIENT
, public gphx_obj
#endif
{
  public:
    NAME`()': terrain(FOOD, PRODUCTION, TRADE)
#ifdef CLIENT
     , gphx_obj(ICON, BACKGROUND_ICON, PRETTY_NAME, PLURAL)
#endif
     {}
};
