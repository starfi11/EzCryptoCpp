#include "EzClient.h"
#include <iostream>

// Constructor: Initialize keys and IV
Client::Client(long long serverPublicKey, long long serverN)
    : serverPublicKey(serverPublicKey), serverN(serverN) {
    aesKey = CryptoHelper::generateAESKey();
    iv = CryptoHelper::generateIV();
}

// Send Encrypted Message
void Client::sendMessage(const std::string& message,
    std::vector<long long>& encryptedAESKeyBlocks,
    std::vector<unsigned char>& encryptedMessage,
    std::vector<unsigned char>& ivOut) {

    // Step 1: Encrypt each byte of the AES Key using RSA
    // 使用服务器RSA公钥加密AES密钥

    std::cout << "[Client] AES Key (Original): ";
    CryptoHelper::printHex(this->aesKey);
    std::cout << std::endl;

    // 每个字节单独加密
    for (unsigned char byte : aesKey) {
        long long encryptedByte = CryptoHelper::rsaEncrypt(byte, serverPublicKey, serverN);
        encryptedAESKeyBlocks.push_back(encryptedByte);
    }

    // Debug: 输出加密的 AES 密钥块
    std::cout << "[Client] Encrypted AES Key Blocks: ";
    for (auto block : encryptedAESKeyBlocks) {
        std::cout << block << " ";
    }
    std::cout << "\n";

    // Step 2: Encrypt the message using AES-CBC
    // 使用AES密钥加密信息
    std::vector<unsigned char> plaintext(message.begin(), message.end());
    encryptedMessage = CryptoHelper::aesCbcEncrypt(plaintext, aesKey, iv);

    // Step 3: Pass IV to server
    // 传递iv
    ivOut = iv;

    // Debug information
    std::cout << "[Client] Encrypted Message: ";
    CryptoHelper::printHex(encryptedMessage);
    std::cout << "\n[Client] IV: ";
    CryptoHelper::printHex(iv);
}


