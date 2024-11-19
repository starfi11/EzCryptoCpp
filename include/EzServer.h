#pragma once
#include "crypto_helper.h"
#include <vector>

class Server {
public:
    Server();

    void receiveMessage(const std::vector<long long>& encryptedAESKeyBlocks,
        const std::vector<unsigned char>& encryptedMessage,
        const std::vector<unsigned char>& iv);

    long long getPublicKey() const;
    long long getModulus() const;

private:
    CryptoHelper::RSAKeyPair rsaKeyPair; // Ë½Ô¿¶Ô
};
