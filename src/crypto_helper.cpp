#include "crypto_helper.h"

// Helper: Generate Random Integer
// 生成一个范围为[min,max]的整数
long long CryptoHelper::randomInt(long long min, long long max) {
    //static保证 rd 和 gen 在整个程序的生命周期内只被初始化一次
    static std::random_device rd;
    static std::mt19937_64 gen(rd());
    std::uniform_int_distribution<long long> distrib(min, max);
    return distrib(gen);
}

// Helper: Check if a number is prime
// 根号n 复杂度的判断是否是素数
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
// 扩展欧几里得算法
long long CryptoHelper::exgcd(long long a, long long b, long long& x, long long& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a; // 返回 gcd(a, b)
    }
    long long d = exgcd(b, a % b, y, x); // 递归计算 gcd
    y -= (a / b) * x; // 更新 y
    return d;
}


// Helper: Compute Modular Inverse
// 求模逆元
long long CryptoHelper::modInverse(long long a, long long m) {
    long long x, y;
    long long gcd = exgcd(a, m, x, y); // 调用扩展欧几里得算法
    if (gcd != 1) {
        throw std::runtime_error("No modular inverse exists"); // 模逆元不存在
    }
    // 确保结果为正数
    return (x % m + m) % m;
}

// RSA: Generate Key Pair
CryptoHelper::RSAKeyPair CryptoHelper::generateRSAKeyPair(int bitLength) {
    long long p, q;
    //生成两个大质数 p , q
    do { p = randomInt(1 << (bitLength / 2 - 1), (1 << (bitLength / 2)) - 1); } while (!isPrime(p));
    do { q = randomInt(1 << (bitLength / 2 - 1), (1 << (bitLength / 2)) - 1); } while (!isPrime(q));

    //n 和 欧拉函数
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    //选择公钥指数 e
    long long e;
    do { e = randomInt(2, phi - 1); } while (gcd(e, phi) != 1);

    long long d = modInverse(e, phi);
    return { e, d, n };//用聚合初始化返回结构体
}

// RSA: Encrypt
// RSA加密
long long CryptoHelper::rsaEncrypt(long long message, long long e, long long n) {
    long long result = 1;
    long long base = message % n;
    //快速幂
    while (e > 0) {
        if (e % 2 == 1) { // 如果当前位为 1
            result = (result * base) % n;
        }
        base = (base * base) % n; // 基数平方
        e /= 2; // 右移指数
    }

    return result;
}


// RSA: Decrypt
// RSA解密
long long CryptoHelper::rsaDecrypt(long long ciphertext, long long d, long long n) {
    long long result = 1;
    long long base = ciphertext % n;
    //快速幂
    while (d > 0) {
        if (d % 2 == 1) { // 如果当前位为 1
            result = (result * base) % n;
        }
        base = (base * base) % n; // 基数平方
        d /= 2; // 右移指数
    }

    return result;
}


// AES: Generate Key
// 生成AES密钥，size传字节数 size = 32时为256位密钥
std::vector<unsigned char> CryptoHelper::generateAESKey(size_t size) {
    std::vector<unsigned char> key(size);
    for (size_t i = 0; i < size; ++i) {
        key[i] = randomInt(0, 255);
    }
    return key;
}

// AES: Generate IV
// 初始化向量
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
