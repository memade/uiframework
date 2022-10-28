#if !defined(INC_H___54A6E252_470E_4954_BCD7_FCC0A55E25F0__HEAD__)
#define INC_H___54A6E252_470E_4954_BCD7_FCC0A55E25F0__HEAD__

namespace local {

 class Com final : public ICom {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  Com();
  virtual ~Com();
 private:
  void Init();
  void UnInit();

 };

}///namespace local 

/// /*新生®（上海）**/
/// /*2022_10_21T14:44:55.8904235Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___54A6E252_470E_4954_BCD7_FCC0A55E25F0__HEAD__



