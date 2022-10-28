#if !defined(INC_H___23CD6496_8888_4885_B41E_5DB45E38EF67__HEAD__)
#define INC_H___23CD6496_8888_4885_B41E_5DB45E38EF67__HEAD__

namespace local {

 class Encryption final : public IEncryption {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  Encryption();
  virtual ~Encryption();
 private:
  void Init();
  void UnInit();
 public:
  bool MD5(const std::string input, std::string& output, const std::vector<std::uint8_t> seed = {}, const bool& hex_output = true, const bool& base64_output = false) const override final;
  bool HMAC_SHA1(const std::string& input, std::string& output, const std::string& seed, const bool& hex_output = true, const bool& base64_output = false) const override final;
  bool HMAC_SHA256(const std::string& input, std::string& output, const std::string& seed, const bool& hex_output = true, const bool& base64_output = false) const override final;
  bool SHA256(const std::string& inData, const bool& isHex, std::string& outData) const override final;
  bool Base64Encode(const std::string& input, std::string& output, const bool& multiline = false) const override final;
  bool Base64Decode(const std::string& input, std::string& output, const bool& multiline = false) const override final;
  bool RsaGenerate(const EnEncryptionRSAType&, const std::string& pwd, std::string& outKeyPublic, std::string& outKeyPrivate) const override final;
  bool RsaPrivateToPublic(const EnEncryptionRSAType&, const std::string& pwd, const std::string& inKeyPrivate, std::string& outKeyPublic) const override final;
  bool RsaDERPublic(const EnEncryptionRSAType&, const std::string& keyPublic, const std::string& pwd, std::string& outDER) const override final;
  bool RsaEncode(const EnEncryptionRSAType&, const std::string& pwd, const std::string& keyPublic, const std::string& keyPrivate, const std::string& inData, std::string& outData) const override final;
  bool RsaDecode(const EnEncryptionRSAType&, const std::string& pwd, const std::string& keyPublic, const std::string& keyPrivate, const std::string& inData, std::string& outData) const override final;
 };

}///namespace local 

/// /*新生®（上海）**/
/// /*2022_10_21T14:00:12.6639695Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___23CD6496_8888_4885_B41E_5DB45E38EF67__HEAD__


