#include "crypto_helper.h"

// Helper: Generate Random Integer
// ����һ����ΧΪ[min,max]������
long long CryptoHelper::randomInt(long long min, long long max) {
    //static��֤ rd �� gen ���������������������ֻ����ʼ��һ��
    static std::random_device rd;
    static std::mt19937_64 gen(rd());
    std::uniform_int_distribution<long long> distrib(min, max);
    return distrib(gen);
}

// Helper: Check if a number is prime
// ����n ���Ӷȵ��ж��Ƿ�������
bool CryptoHelper::isPrime(long long num) {
    if (num < 2) return false;
    for (long long i = 2; i <= std::sqrt(num); ++i) {
        if (num % i == 0) return false;
    }
    return true;
}

// Helper: Compute GCD
long long CryptoHelper::gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Helper: Exgcd
// ��չŷ������㷨
long long CryptoHelper::exgcd(long long a, long long b, long long& x, long long& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a; // ���� gcd(a, b)
    }
    long long d = exgcd(b, a % b, y, x); // �ݹ���� gcd
    y -= (a / b) * x; // ���� y
    return d;
}


// Helper: Compute Modular Inverse
// ��ģ��Ԫ
long long CryptoHelper::modInverse(long long a, long long m) {
    long long x, y;
    long long gcd = exgcd(a, m, x, y); // ������չŷ������㷨
    if (gcd != 1) {
        throw std::runtime_error("No modular inverse exists"); // ģ��Ԫ������
    }
    // ȷ�����Ϊ����
    return (x % m + m) % m;
}

// RSA: Generate Key Pair
CryptoHelper::RSAKeyPair CryptoHelper::generateRSAKeyPair(int bitLength) {
    long long p, q;
    //�������������� p , q
    do { p = randomInt(1 << (bitLength / 2 - 1), (1 << (bitLength / 2)) - 1); } while (!isPrime(p));
    do { q = randomInt(1 << (bitLength / 2 - 1), (1 << (bitLength / 2)) - 1); } while (!isPrime(q));

    //n �� ŷ������
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    //ѡ��Կָ�� e
    long long e;
    do { e = randomInt(2, phi - 1); } while (gcd(e, phi) != 1);

    long long d = modInverse(e, phi);
    return { e, d, n };//�þۺϳ�ʼ�����ؽṹ��
}

// RSA: Encrypt
// RSA����
long long CryptoHelper::rsaEncrypt(long long message, long long e, long long n) {
    long long result = 1;
    long long base = message % n;
    //������
    while (e > 0) {
        if (e % 2 == 1) { // �����ǰλΪ 1
            result = (result * base) % n;
        }
        base = (base * base) % n; // ����ƽ��
        e /= 2; // ����ָ��
    }

    return result;
}


// RSA: Decrypt
// RSA����
long long CryptoHelper::rsaDecrypt(long long ciphertext, long long d, long long n) {
    long long result = 1;
    long long base = ciphertext % n;
    //������
    while (d > 0) {
        if (d % 2 == 1) { // �����ǰλΪ 1
            result = (result * base) % n;
        }
        base = (base * base) % n; // ����ƽ��
        d /= 2; // ����ָ��
    }

    return result;
}


// AES: Generate Key
// ����AES��Կ��size���ֽ��� size = 32ʱΪ256λ��Կ
std::vector<unsigned char> CryptoHelper::generateAESKey(size_t size) {
    std::vector<unsigned char> key(size);
    for (size_t i = 0; i < size; ++i) {
        key[i] = randomInt(0, 255);
    }
    return key;
}

// AES: Generate IV
// ��ʼ������
std::vector<unsigned char> CryptoHelper::generateIV(size_t size) {
    return generateAESKey(size);
}

// Encrypt a single block using AES (simplified example)
std::vector<unsigned char> CryptoHelper::aesEncryptBlock(const std::vector<unsigned char>& block,
    const std::vector<unsigned char>& key) {
    if (key.size() != AES_BLOCK_SIZE || block.size() != AES_BLOCK_SIZE) {
        throw std::invalid_argument("Block and key size must be 16 bytes for AES-128.");
    }
    std::vector<unsigned char> encryptedBlock = block;
    for (size_t i = 0; i < AES_BLOCK_SIZE; ++i) {
        encryptedBlock[i] ^= key[i]; // Simplified XOR for demonstration
    }
    return encryptedBlock;
}

// Decrypt a single block using AES (simplified example)
std::vector<unsigned char> CryptoHelper::aesDecryptBlock(const std::vector<unsigned char>& block,
    const std::vector<unsigned char>& key) {
    if (key.size() != AES_BLOCK_SIZE || block.size() != AES_BLOCK_SIZE) {
        throw std::invalid_argument("Block and key size must be 16 bytes for AES-128.");
    }
    std::vector<unsigned char> decryptedBlock = block;
    for (size_t i = 0; i < AES_BLOCK_SIZE; ++i) {
        decryptedBlock[i] ^= key[i]; // Simplified XOR for demonstration
    }
    return decryptedBlock;
}

// AES-CBC Encryption
std::vector<unsigned char> CryptoHelper::aesCbcEncrypt(const std::vector<unsigned char>& data,
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& iv) {
    if (key.size() != AES_BLOCK_SIZE) {
        throw std::invalid_argument("Key size must be 16 bytes for AES-128.");
    }
    if (iv.size() != AES_BLOCK_SIZE) {
        throw std::invalid_argument("IV size must be 16 bytes.");
    }

    std::vector<unsigned char> encryptedData;
    std::vector<unsigned char> prevBlock = iv;

    for (size_t i = 0; i < data.size(); i += AES_BLOCK_SIZE) {
        // Take current block (padding if necessary)
        std::vector<unsigned char> block(AES_BLOCK_SIZE, 0);
        for (size_t j = 0; j < AES_BLOCK_SIZE && i + j < data.size(); ++j) {
            block[j] = data[i + j];
        }

        // XOR with previous block (or IV for the first block)
        for (size_t j = 0; j < AES_BLOCK_SIZE; ++j) {
            block[j] ^= prevBlock[j];
        }

        // Encrypt the block
        std::vector<unsigned char> encryptedBlock = aesEncryptBlock(block, key);

        // Append encrypted block to the result
        encryptedData.insert(encryptedData.end(), encryptedBlock.begin(), encryptedBlock.end());

        // Update previous block
        prevBlock = encryptedBlock;
    }

    return encryptedData;
}

// AES-CBC Decryption
std::vector<unsigned char> CryptoHelper::aesCbcDecrypt(const std::vector<unsigned char>& encryptedData,
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& iv) {
    if (key.size() != AES_BLOCK_SIZE) {
        throw std::invalid_argument("Key size must be 16 bytes for AES-128.");
    }
    if (iv.size() != AES_BLOCK_SIZE) {
        throw std::invalid_argument("IV size must be 16 bytes.");
    }

    std::vector<unsigned char> decryptedData;
    std::vector<unsigned char> prevBlock = iv;

    for (size_t i = 0; i < encryptedData.size(); i += AES_BLOCK_SIZE) {
        // Take current encrypted block
        std::vector<unsigned char> encryptedBlock(encryptedData.begin() + i,
            encryptedData.begin() + i + AES_BLOCK_SIZE);

        // Decrypt the block
        std::vector<unsigned char> decryptedBlock = aesDecryptBlock(encryptedBlock, key);

        // XOR with previous block (or IV for the first block)
        for (size_t j = 0; j < AES_BLOCK_SIZE; ++j) {
            decryptedBlock[j] ^= prevBlock[j];
        }

        // Append decrypted block to the result
        decryptedData.insert(decryptedData.end(), decryptedBlock.begin(), decryptedBlock.end());

        // Update previous block
        prevBlock = encryptedBlock;
    }

    return decryptedData;
}

// Helper: Print Hex
void CryptoHelper::printHex(const std::vector<unsigned char>& data) {
    for (unsigned char c : data) {
        printf("%02x ", c);
    }
    std::cout << std::endl;
}
