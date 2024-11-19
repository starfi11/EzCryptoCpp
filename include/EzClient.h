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
    long long serverPublicKey;  // Server's public key (e)  ��������RSA��Կ�����ڿͻ��˼���AES��Կ
    long long serverN;          // Server's modulus (n)     ��������RSAģ��
    std::vector<unsigned char> aesKey; // AES key AES key   �ͻ��˵�AES��Կ
    std::vector<unsigned char> iv;     // Initialization Vector AES-CBCģʽ�µĳ�ʼ������
};