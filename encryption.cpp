#include "stdafx.h"

namespace local {

 Encryption::Encryption() {
  Init();
 }

 Encryption::~Encryption() {
  UnInit();
 }
 void Encryption::Init() {

 }
 void Encryption::UnInit() {

 }
 bool Encryption::MD5(const std::string input, std::string& output, const std::vector<std::uint8_t> seed /*= {}*/, const bool& hex_output /*= true*/, const bool& base64_output /*= false*/) const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return shared::Openssl::MD5(input, output, seed, hex_output, base64_output);
 }
 bool Encryption::HMAC_SHA1(const std::string& input, std::string& output, const std::string& seed, const bool& hex_output /*= true*/, const bool& base64_output /*= false*/) const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return shared::Openssl::HMAC_SHA1(input, output, seed, hex_output, base64_output);
 }
 bool Encryption::HMAC_SHA256(const std::string& input, std::string& output, const std::string& seed, const bool& hex_output /*= true*/, const bool& base64_output /*= false*/) const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return shared::Openssl::HMAC_SHA256(input, output, seed, hex_output, base64_output);
 }
 bool Encryption::SHA256(const std::string& inData, const bool& isHex, std::string& outData) const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return shared::Openssl::SHA256(inData, isHex, outData);
 }
 bool Encryption::Base64Encode(const std::string& input, std::string& output, const bool& multiline /*= false*/) const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return shared::Openssl::Base64Encode(input, output, multiline);
 }
 bool Encryption::Base64Decode(const std::string& input, std::string& output, const bool& multiline /*= false*/) const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return shared::Openssl::Base64Decode(input, output, multiline);
 }
 bool Encryption::RsaGenerate(const EnEncryptionRSAType& type, const std::string& pwd, std::string& outKeyPublic, std::string& outKeyPrivate) const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return shared::Openssl::Rsa::Generate(shared::Openssl::Rsa::EnType(type), pwd, outKeyPublic, outKeyPrivate);
 }
 bool Encryption::RsaPrivateToPublic(const EnEncryptionRSAType& type, const std::string& pwd, const std::string& inKeyPrivate, std::string& outKeyPublic) const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return shared::Openssl::Rsa::PrivateToPublic(shared::Openssl::Rsa::EnType(type), pwd, inKeyPrivate, outKeyPublic);
 }
 bool Encryption::RsaDERPublic(const EnEncryptionRSAType& type, const std::string& keyPublic, const std::string& pwd, std::string& outDER) const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return shared::Openssl::Rsa::DERPublic(shared::Openssl::Rsa::EnType(type), keyPublic, pwd, outDER);
 }
 bool Encryption::RsaEncode(const EnEncryptionRSAType& type, const std::string& pwd, const std::string& keyPublic, const std::string& keyPrivate, const std::string& inData, std::string& outData) const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return shared::Openssl::Rsa::Encode(shared::Openssl::Rsa::EnType(type), pwd, keyPublic, keyPrivate, inData, outData);
 }
 bool Encryption::RsaDecode(const EnEncryptionRSAType& type, const std::string& pwd, const std::string& keyPublic, const std::string& keyPrivate, const std::string& inData, std::string& outData) const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return shared::Openssl::Rsa::Decode(shared::Openssl::Rsa::EnType(type), pwd, keyPublic, keyPrivate, inData, outData);
 }
}///namespace lcoal
