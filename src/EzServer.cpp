#include "EzServer.h"
#include <iostream>

// Constructor: Initialize RSA key pair
Server::Server() {
    rsaKeyPair = CryptoHelper::generateRSAKeyPair();
    std::cout << "[Server] Public Key: " << rsaKeyPair.publicKey << ", N: " << rsaKeyPair.n << "\n";
}
// Receive and decrypt the message
void Server::receiveMessage(const std::vector<long long>& encryptedAESKeyBlocks,
    const std::vector<unsigned char>& encryptedMessage,
    const std::vector<unsigned char>& iv) {

    std::cout << "[Server] Encrypted AES Key Blocks: ";
    for (auto block : encryptedAESKeyBlocks) {
        std::cout << block << " ";
    }
    std::cout << std::endl;

    // Step 1: Decrypt each byte of the AES Key using RSA
    // 使用RSA私钥解密AES密钥
    std::vector<unsigned char> aesKey;

    for (auto encryptedByte : encryptedAESKeyBlocks) {
        long long decryptedByte = CryptoHelper::rsaDecrypt(encryptedByte, rsaKeyPair.privateKey, rsaKeyPair.n);
        aesKey.push_back(static_cast<unsigned char>(decryptedByte));
    }

    std::cout << "[Server] AES Key (Decrypted): ";
    CryptoHelper::printHex(aesKey);
    std::cout << std::endl;

    std::cout << "[Server] Encrypted Message: ";
    CryptoHelper::printHex(encryptedMessage);
    std::cout << std::endl;

    // Step 2: Decrypt the message using AES-CBC with received IV
    // 使用AES密钥解密信息
    std::vector<unsigned char> decryptedMessage =
        CryptoHelper::aesCbcDecrypt(encryptedMessage, aesKey, iv);

    // Display decrypted message
    std::cout << "[Server] Decrypted Message: ";
    for (unsigned char c : decryptedMessage) {
        std::cout << c;
    }
    std::cout << "\n";
}


// 返回服务器的 RSA 公钥
long long Server::getPublicKey() const {
    return rsaKeyPair.publicKey; // 返回密钥对中的 publicKey
}

// 返回服务器的模数
long long Server::getModulus() const {
    return rsaKeyPair.n; // 返回密钥对中的 n
}