#include <iostream>
#include <string>

const unsigned char SBox[64][64] = { 
    {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
    {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
    {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
    {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
    {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
    {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
    {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
    {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
    {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
    {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
    {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
    {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
    {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
    {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
    {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
    {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}
};

const unsigned char InvSBox[64][64] = {
    {0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb},
    {0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb},
    {0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e},
    {0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25},
    {0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92},
    {0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84},
    {0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06},
    {0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b},
    {0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73},
    {0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e},
    {0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b},
    {0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4},
    {0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f},
    {0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef},
    {0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61},
    {0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d}
};

const unsigned char Rcon[10][4] = {
    {0x01, 0x00, 0x00, 0x00},
    {0x02, 0x00, 0x00, 0x00},
    {0x04, 0x00, 0x00, 0x00},
    {0x08, 0x00, 0x00, 0x00},
    {0x10, 0x00, 0x00, 0x00},
    {0x20, 0x00, 0x00, 0x00},
    {0x40, 0x00, 0x00, 0x00},
    {0x80, 0x00, 0x00, 0x00},
    {0x1b, 0x00, 0x00, 0x00},
    {0x36, 0x00, 0x00, 0x00},
};

// Convert uint32 to string with hex form of this number
template <class T>
std::string IntToHexForm(T a)
{
    std::string res;
    
    for (int i = 0; i < sizeof(T); i++)
    {
        int lowByte = a % 16;
        a /= 16;
        
        int highByte = a % 16;
        a /= 16;

        if (highByte > 9)
        {
            if (highByte == 10) res += "a";
            if (highByte == 11) res += "b";
            if (highByte == 12) res += "c";
            if (highByte == 13) res += "d";
            if (highByte == 14) res += "e";
            if (highByte == 15) res += "f";
        }
        else
            res += std::to_string(highByte);

        if (lowByte > 9)
        {
            if (lowByte == 10) res += "a";
            if (lowByte == 11) res += "b";
            if (lowByte == 12) res += "c";
            if (lowByte == 13) res += "d";
            if (lowByte == 14) res += "e";
            if (lowByte == 15) res += "f";
        }
        else
            res += std::to_string(lowByte);
    }

    return res;
}

// Galois Field (256) Multiplication of two Bytes
unsigned char GaloisMul(unsigned char a, unsigned char b)
{
    unsigned char p = 0;

    for (int counter = 0; counter < 8; counter++) 
    {
        if ((b & 1) != 0) 
            p ^= a;

        bool hi_bit_set = (a & 0x80) != 0;

        a <<= 1;

        if (hi_bit_set) 
            a ^= 0x1B; /* x^8 + x^4 + x^3 + x + 1 */

        b >>= 1;
    }

    return p;
}

// Process 16 unsigned chars. Change unsigned chars to chars in const SBox matrix
inline void SubBytes(unsigned char *mat)
{
    for (int i = 0; i < 16; i++)
        mat[i] = SBox[mat[i] / 16][mat[i] % 16];
}

// Process 16 unsigned chars. Change unsigned chars to chars in const SBox matrix
inline void InvSubBytes(unsigned char *mat)
{
    for (int i = 0; i < 16; i++)
        mat[i] = InvSBox[mat[i] / 16][mat[i] % 16];
}

// Process 16 unsigned chars. Circular shift 3 last lines to 1, 2, 3.
inline void ShiftRows(unsigned char *mat)
{
    // Second line shifts on 1 to left
    unsigned char tmp1 = mat[4];
    mat[4] = mat[5]; mat[5] = mat[6]; mat[6] = mat[7]; mat[7] = tmp1;

    // Third line shifts on 2 left
    unsigned char tmp2 = mat[9]; tmp1 = mat[8]; 
    mat[8] = mat[10]; mat[9] = mat[11]; mat[10] = tmp1; mat[11] = tmp2;

    // Fourth line shifts on 3 left or thar equls shift on 1 right
    tmp1 = mat[15]; 
    mat[15] = mat[14]; mat[14] = mat[13]; mat[13] = mat[12]; mat[12] = tmp1;
}

// Process 16 unsigned chars. Circular shift 3 last lines to 1, 2, 3.
inline void InvShiftRows(unsigned char *mat)
{
    // Second line shifts on 1 to right
    unsigned char tmp1 = mat[7];
    mat[7] = mat[6]; mat[6] = mat[5]; mat[5] = mat[4]; mat[4] = tmp1;

    // Third line shifts on 2 right
    unsigned char tmp2 = mat[9]; tmp1 = mat[8]; 
    mat[8] = mat[10]; mat[9] = mat[11]; mat[10] = tmp1; mat[11] = tmp2;

    // Fourth line shifts on 3 right or thar equls shift on 1 left
    tmp1 = mat[12]; 
    mat[12] = mat[13]; mat[13] = mat[14]; mat[14] = mat[15]; mat[15] = tmp1;
}

// Process 16 unsigned chars matrix state. Make GF(2^8) operations
void MixColumns(unsigned char *mat) 
{
    unsigned char a, b, c, d;
    for (int i = 0; i < 4; i++)
    {
        a = GaloisMul(2, mat[i]) ^ GaloisMul(3, mat[4 + i]) ^ mat[8 + i] ^ mat[12 + i];
        b = mat[i] ^ GaloisMul(2, mat[4 + i]) ^ GaloisMul(3, mat[8 + i]) ^ mat[12 + i];
        c = mat[i] ^ mat[4 + i] ^ GaloisMul(2, mat[8 + i]) ^ GaloisMul(3, mat[12 + i]);
        d = GaloisMul(3, mat[i]) ^ mat[4 + i] ^ mat[8 + i] ^ GaloisMul(2, mat[12 + i]);

        mat[i] = a;
        mat[4 + i] = b;
        mat[8 + i] = c;
        mat[12 + i] = d;
    }
}

// Process 16 unsigned chars matrix state. Make GF(2^8) operations
void InvMixColumns(unsigned char *mat) 
{
    unsigned char a, b, c, d;
    for (int i = 0; i < 4; i++)
    {
        a = GaloisMul(14, mat[i]) ^ GaloisMul(11, mat[4 + i]) ^ GaloisMul(13, mat[8 + i]) ^ GaloisMul(9, mat[12 + i]);
        b = GaloisMul(9, mat[i]) ^ GaloisMul(14, mat[4 + i]) ^ GaloisMul(11, mat[8 + i]) ^ GaloisMul(13, mat[12 + i]);
        c  = GaloisMul(13, mat[i]) ^ GaloisMul(9, mat[4 + i]) ^ GaloisMul(14, mat[8 + i]) ^ GaloisMul(11, mat[12 + i]);
        d = GaloisMul(11, mat[i]) ^ GaloisMul(13, mat[4 + i]) ^ GaloisMul(9, mat[8 + i]) ^ GaloisMul(14, mat[12 + i]);
        
        mat[i] = a;
        mat[4 + i] = b;
        mat[8 + i] = c;
        mat[12 + i] = d;    
    }
}

// Process 16 chars string. Make key shedule
std::string KeyExpansion(std::string key)
{
    std::string KeyShedule = key;

    for (int i = 4; i < 44; i++)
    {
        // Get previous column element
        unsigned char w[4] = {(unsigned char)KeyShedule[i*4 - 4], (unsigned char)KeyShedule[i*4 - 3], (unsigned char)KeyShedule[i*4 - 2], (unsigned char)KeyShedule[i*4 - 1]};

        // Check if column multiply for 4
        if (i % 4 == 0)
        {
            // Circular shift in column
            unsigned char tmp = w[0];
            w[0] = w[1]; w[1] = w[2]; w[2] = w[3]; w[3] = tmp;

            // Change unsigned chars to chars in const SBox matrix
            w[0] = SBox[w[0] / 16][w[0] % 16];
            w[1] = SBox[w[1] / 16][w[1] % 16];
            w[2] = SBox[w[2] / 16][w[2] % 16];
            w[3] = SBox[w[3] / 16][w[3] % 16];

            // Xoring
            w[0] = w[0] ^ Rcon[i/4 - 1][0] ^ KeyShedule[i*4 - 16];
            w[1] = w[1] ^ Rcon[i/4 - 1][1] ^ KeyShedule[i*4 - 15];
            w[2] = w[2] ^ Rcon[i/4 - 1][2] ^ KeyShedule[i*4 - 14];
            w[3] = w[3] ^ Rcon[i/4 - 1][3] ^ KeyShedule[i*4 - 13];
        }
        else
        {
            // Xoring
            w[0] = w[0] ^ KeyShedule[i*4 - 16];
            w[1] = w[1] ^ KeyShedule[i*4 - 15];
            w[2] = w[2] ^ KeyShedule[i*4 - 14];
            w[3] = w[3] ^ KeyShedule[i*4 - 13];
        }
        KeyShedule += w[0];
        KeyShedule += w[1];
        KeyShedule += w[2];
        KeyShedule += w[3];
    }

    return KeyShedule;
}

std::string AddRoundKey(std::string mat1, std::string mat2) 
{
    std::string xoredString;

    for (int i = 0; i < 16; i++)
        xoredString += (unsigned char)(mat1[i] ^ mat2[i]);
    
    return xoredString;
}

// Process 16 chars string
std::string AES_EncryptStep(const std::string& data, bool isMixColumns = true)
{
    unsigned char state[4][4];

    // Save data from string to state matrix
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            state[j][i] = data[i * 4 + j];

    // Change unsigned chars from matrix to const SBox table
    SubBytes(&state[0][0]);
    // Change unsigned chars from matrix to const SBox table
    ShiftRows(&state[0][0]);

    if(isMixColumns)
        MixColumns(&state[0][0]);

    std::string res;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            res += state[j][i];


    return res;
}

// Now length must be multiple of the number 16
std::string AES_Encrypt(const std::string& data, const std::string& key)
{
    if (data.length() % 16 != 0 || key.length() != 16)
        return "";

    std::string keyShedule = KeyExpansion(key);

    std::string res;
    for(int i = 0; i < data.length() / 16; i++)
    {
        std::string encryptedData = AddRoundKey(data, key);

        std::string tmp;
        for (int j = 1; j < 10; j++)
        {
            tmp = AES_EncryptStep(encryptedData);
            encryptedData = AddRoundKey(tmp, keyShedule.substr(j*16, 16));
        }

        tmp = AES_EncryptStep(encryptedData, false);
        encryptedData = AddRoundKey(tmp, keyShedule.substr(10*16, 16));
        res += encryptedData;
    }

    return res;
}

// Process 16 chars string
std::string AES_DecryptStep(const std::string& data, bool isMixColumns = false)
{
    unsigned char state[4][4];

    // Save data from string to state matrix
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            state[j][i] = data[i * 4 + j];

    if(isMixColumns)
        InvMixColumns(&state[0][0]);
    else
    {
        // Change unsigned chars from matrix to const SBox table
        InvShiftRows(&state[0][0]);
        // Change unsigned chars from matrix to const SBox table
        InvSubBytes(&state[0][0]);
    }

    std::string res;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            res += state[j][i];

    return res;
}

// Now length must be multiple of the number 16
std::string AES_Decrypt(const std::string& data, const std::string& key)
{
    if (data.length() % 16 != 0 || key.length() != 16)
        return "";

    std::string res;
    std::string keyShedule = KeyExpansion(key);

    for(int i = 0; i < data.length() / 16; i++)
    {
        std::string decryptedData = AddRoundKey(data, keyShedule.substr(keyShedule.length() - 16));

        std::string tmp1, tmp2;
        for (int j = 1; j < 10; j++)
        {
            tmp1 = AES_DecryptStep(decryptedData);
            tmp2 = AddRoundKey(tmp1, keyShedule.substr((10 - j) * 16, 16));
            decryptedData = AES_DecryptStep(tmp2, true);
        }

        tmp2 = AES_DecryptStep(decryptedData);
        decryptedData = AddRoundKey(tmp2, keyShedule.substr(0, 16));
        res += decryptedData;
    }

    return res;
}

std::string StringWithHexToNormalString(const std::string& str)
{
    if (str.length() % 2 != 0)  return "";

    std::string res;
    unsigned char hi, low;
    for (int i = 0; i < str.length(); i += 2)
    {
        if (str[i] == '0') hi = 0;
        if (str[i] == '1') hi = 1;
        if (str[i] == '2') hi = 2;
        if (str[i] == '3') hi = 3;
        if (str[i] == '4') hi = 4;
        if (str[i] == '5') hi = 5;
        if (str[i] == '6') hi = 6;
        if (str[i] == '7') hi = 7;
        if (str[i] == '8') hi = 8;
        if (str[i] == '9') hi = 9;

        if (str[i] == 'a' || str[i] == 'A') hi = 10;
        if (str[i] == 'b' || str[i] == 'B') hi = 11;
        if (str[i] == 'c' || str[i] == 'C') hi = 12;
        if (str[i] == 'd' || str[i] == 'D') hi = 13;
        if (str[i] == 'e' || str[i] == 'E') hi = 14;
        if (str[i] == 'f' || str[i] == 'F') hi = 15;

        if (str[i + 1] == '0') low = 0;
        if (str[i + 1] == '1') low = 1;
        if (str[i + 1] == '2') low = 2;
        if (str[i + 1] == '3') low = 3;
        if (str[i + 1] == '4') low = 4;
        if (str[i + 1] == '5') low = 5;
        if (str[i + 1] == '6') low = 6;
        if (str[i + 1] == '7') low = 7;
        if (str[i + 1] == '8') low = 8;
        if (str[i + 1] == '9') low = 9;

        if (str[i + 1] == 'a' || str[i + 1] == 'A') low = 10;
        if (str[i + 1] == 'b' || str[i + 1] == 'B') low = 11;
        if (str[i + 1] == 'c' || str[i + 1] == 'C') low = 12;
        if (str[i + 1] == 'd' || str[i + 1] == 'D') low = 13;
        if (str[i + 1] == 'e' || str[i + 1] == 'E') low = 14;
        if (str[i + 1] == 'f' || str[i + 1] == 'F') low = 15;

        res += hi*16 + low;
    }
    return res;
}

int main()
{
    std::string data = "lollollollollolH";
    std::string key = "abcdabcdabcdabcd";
    std::string encryptedData = AES_Encrypt(data, key);

    for (auto it : encryptedData) 
        std::cout << IntToHexForm((unsigned char)it);
    
    std::cout << std::endl;

    std::string decryptedData = AES_Decrypt(StringWithHexToNormalString("93ed6702d47b821b5f3139d7818f3db2"), key);
    std::cout << decryptedData << std::endl;
}