#pragma once
#include "crypto_helper.h"
#include <string>
#include <vector>

class Client {
public:
    Client(long long serverPublicKey, long long serverN);

    void sendMessage(const std::string& message,
        std::vector<long long>& encryptedAESKeyBlocks,
        std::vector<unsigned char>& encryptedMessage,
        std::vector<unsigned char>& iv);

private:
    long long serverPublicKey;  // Server's public key (e)  服务器的RSA公钥，用于客户端加密AES密钥
    long long serverN;          // Server's modulus (n)     服务器的RSA模数
    std::vector<unsigned char> aesKey; // AES key AES key   客户端的AES密钥
    std::vector<unsigned char> iv;     // Initialization Vector AES-CBC模式下的初始化向量
};