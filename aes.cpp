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

// Process 16 unsigned chars. Change unsigned chars to chars in const SBox matrix
inline void SubBytes(unsigned char *mat)
{
    for (int i = 0; i < 16; i++)
        mat[i] = SBox[mat[i] / 16][mat[i] % 16];
}

// Process 16 unsigned chars. Change unsigned chars to chars in const SBox matrix
inline void InvSubBytes(unsigned char *mat)
{

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

// Process 16 unsigned chars matrix state. Make GF(2^8) operations
void MixColumns(unsigned char *mat) 
{
    for (int i = 0; i < 4; i++)
    {
        unsigned char a[4];
        unsigned char b[4];
        unsigned char c;
        unsigned char h;

        for (c = 0; c < 4; c++) 
        {
            a[c] = mat[4 * c + i];
            h = (mat[4 * c + i] >> 7) & 1;
            b[c] = mat[4 * c + i] << 1;
            b[c] ^= h * 0x1B;
        }

        mat[i] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1];
        mat[4 + i] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2];
        mat[8 + i] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3];
        mat[12 + i] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0];
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
    for (auto it : mat1)
        std::cout << IntToHexForm((unsigned char)it) << " ";
    std::cout << std::endl;

    for (auto it : mat2)
        std::cout << IntToHexForm((unsigned char)it) << " ";
    std::cout << std::endl;

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

    std::cout << "Print initial state matrix" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            std::cout << IntToHexForm(state[i][j]) << " ";
        std::cout << std::endl;
    }

    std::cout << std::endl;

    // Change unsigned chars from matrix to const SBox table
    SubBytes(&state[0][0]);
    
    std::cout << "Print after SubBytes state matrix" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            std::cout << IntToHexForm(state[i][j]) << " ";
        std::cout << std::endl;
    }

    std::cout << std::endl;

    // Change unsigned chars from matrix to const SBox table
    ShiftRows(&state[0][0]);
    
    std::cout << "Print after ShiftRows state matrix" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            std::cout << IntToHexForm(state[i][j]) << " ";
        std::cout << std::endl;
    }

    std::cout << std::endl;

    if(isMixColumns)
    {
        MixColumns(&state[0][0]);
        
        std::cout << "Print after MixColumns state matrix" << std::endl;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                std::cout << IntToHexForm(state[i][j]) << " ";
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }

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

    std::string res;
    for(int i = 0; i < data.length() / 16; i++)
    {
        std::string encryptedData = AddRoundKey(data, key);

        std::string keyShedule = KeyExpansion(key);

        std::string tmp;
        for (int i = 1; i < 10; i++)
        {
            tmp = AES_EncryptStep(encryptedData);
            encryptedData = AddRoundKey(tmp, keyShedule.substr(i*16, 16));
        }

        tmp = AES_EncryptStep(encryptedData, false);
        encryptedData = AddRoundKey(tmp, keyShedule.substr(10*16, 16));
        res += encryptedData;
    }

    return res;
}

int main()
{
    // std::string data = {
    //     (char)0x32, (char)0x43, (char)0xf6, (char)0xa8,
    //     (char)0x88, (char)0x5a, (char)0x30, (char)0x8d,
    //     (char)0x31, (char)0x31, (char)0x98, (char)0xa2,
    //     (char)0xe0, (char)0x37, (char)0x07, (char)0x34
    // };

    // std::string key = {
    //     (char)0x2b, (char)0x7e, (char)0x15, (char)0x16,
    //     (char)0x28, (char)0xae, (char)0xd2, (char)0xa6,
    //     (char)0xab, (char)0xf7, (char)0x15, (char)0x88,
    //     (char)0x09, (char)0xcf, (char)0x4f, (char)0x3c
    // };

    std::string data = "qwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwer";
    std::string key = "abcdabcdabcdabcd";
    std::string encryptedData = AES_Encrypt(data, key);

    for (auto it : encryptedData) 
        std::cout << IntToHexForm((unsigned char)it);
    
    std::cout << std::endl;

    // AES_Step("0123456789ABCDEF");

    // std::string t = {
    //     (char)0xd4, (char)0xe0, (char)0xb8, (char)0x1e,
    // };

    // MixColumns(t);

    // int count = 0;
    // for (auto it : t) 
    // {
    //     std::cout << ((int)(unsigned char)it) / 16 << " " << ((int)(unsigned char)it) % 16 << "\t";
    //     count++;
    //     if (count % 4 == 0)
    //         std::cout << std::endl;
    // };
}