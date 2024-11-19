#include "crypto_helper.h"
#include "EzClient.h"
#include "EzServer.h"
void test();
int main() {
    test();
    //return 0;


    // Create Server and Client
    Server server;
    Client client(server.getPublicKey(), server.getModulus());

    // Original Message
    std::string message = "Hello, secure world!1234567890123456789012345678901";
    std::cout << "[Main] Original Message: " << message << "\n";

    // Communication variables
    std::vector<long long> encryptedAESKeyBlocks;
    std::vector<unsigned char> encryptedMessage;
    std::vector<unsigned char> iv;

    // Client sends message
    client.sendMessage(message, encryptedAESKeyBlocks, encryptedMessage, iv);

    // Server receives and decrypts message
    server.receiveMessage(encryptedAESKeyBlocks, encryptedMessage, iv);
    return 0;
}
void test() {

    std::cout << "=======================================" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "Random number " << i + 1 << ": " << CryptoHelper::randomInt(1, 100) << "\n";
    }

    std::cout << "=======================================" << std::endl;
    std::cout << "Testing GCD Method:\n";
    std::cout << "GCD of 56 and 98: " << CryptoHelper::gcd(56, 98) << " (Expected: 14)\n";
    std::cout << "GCD of 101 and 103: " << CryptoHelper::gcd(101, 103) << " (Expected: 1)\n";
    std::cout << "GCD of 48 and 18: " << CryptoHelper::gcd(48, 18) << " (Expected: 6)\n";
    std::cout << "GCD of 0 and 7: " << CryptoHelper::gcd(0, 7) << " (Expected: 7)\n";
    std::cout << "GCD of 7 and 0: " << CryptoHelper::gcd(7, 0) << " (Expected: 7)\n\n";


    std::cout << "=======================================" << std::endl;
    std::cout << "Testing Modular Inverse:\n";

    try {
        std::cout << "Inverse of 3 mod 7: " << CryptoHelper::modInverse(3, 7) << " (Expected: 5)\n";
        std::cout << "Inverse of 10 mod 17: " << CryptoHelper::modInverse(10, 17) << " (Expected: 12)\n";
        std::cout << "Inverse of 2 mod 5: " << CryptoHelper::modInverse(2, 5) << " (Expected: 3)\n";
        std::cout << "Inverse of 6 mod 9: " << CryptoHelper::modInverse(6, 9) << " (Expected: No inverse)\n";
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }


    std::cout << "=======================================" << std::endl;

    //AES²âÊÔ
    std::vector<unsigned char> data = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', '!', '!', '!', '!' };
    std::vector<unsigned char> key = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
                                       0xab, 0xf7, 0xcf, 0xf5, 0x88, 0x09, 0xcf, 0x4f };
    std::vector<unsigned char> iv = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                      0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

    try {

        std::cout << "initial data  : " ;
        for (unsigned char byte : data) {
            std::cout << byte;
        }
        std::cout << std::endl;
        // AES-CBC Encryption
        std::vector<unsigned char> encrypted = CryptoHelper::aesCbcEncrypt(data, key, iv);
        std::cout << "Encrypted Data: ";
        for (unsigned char byte : encrypted) {
            printf("%02x ", byte);
        }
        std::cout << std::endl;
        /*std::cout << "Encrypted Data: ";
        for (unsigned char byte : encrypted) {
            std::cout << byte;
        }*/
        
        std::cout << std::endl;

        // AES-CBC Decryption
        std::vector<unsigned char> decrypted = CryptoHelper::aesCbcDecrypt(encrypted, key, iv);
        std::cout << "Decrypted Data: ";
        for (unsigned char byte : decrypted) {
            std::cout << byte;
        }
        std::cout << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "=======================================" << std::endl;

    try {
        // 1. Generate RSA Key Pair
        std::cout << "Generating RSA Key Pair..." << std::endl;
        CryptoHelper::RSAKeyPair keyPair = CryptoHelper::generateRSAKeyPair(16);
        std::cout << "Public Key (e, n): (" << keyPair.publicKey << ", " << keyPair.n << ")" << std::endl;
        std::cout << "Private Key (d, n): (" << keyPair.privateKey << ", " << keyPair.n << ")" << std::endl;

        // 2. Message to Encrypt
        long long message = -10086; // Example message
        std::cout << "Original Message: " << message << std::endl;

        // 3. Encrypt the message
        long long encryptedMessage = CryptoHelper::rsaEncrypt(message, keyPair.publicKey, keyPair.n);
        std::cout << "Encrypted Message: " << encryptedMessage << std::endl;

        // 4. Decrypt the message
        long long decryptedMessage = CryptoHelper::rsaDecrypt(encryptedMessage, keyPair.privateKey, keyPair.n);
        std::cout << "Decrypted Message: " << decryptedMessage << std::endl;

        // 5. Verify correctness
        if (message == decryptedMessage) {
            std::cout << "Test Passed: Decrypted message matches the original message." << std::endl;
        }
        else {
            std::cout << "Test Failed: Decrypted message does not match the original message." << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    std::cout << "=======================================" << std::endl;


}