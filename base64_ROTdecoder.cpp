#include <iostream>
#include <string>
#include <vector>
#include <cctype>

std::string base64Decode(const std::string& input) {
    static const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    auto isBase64 = [](unsigned char c) {
        return (isalnum(c) || (c == '+') || (c == '/'));
    };

    int in_len = input.size();
    int i = 0, j = 0, in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string decoded;

    while (in_len-- && (input[in_] != '=') && isBase64(input[in_])) {
        char_array_4[i++] = input[in_];
        in_++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char_array_4[i] = static_cast<unsigned char>(base64_chars.find(char_array_4[i]));

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                decoded += char_array_3[i];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 4; j++)
            char_array_4[j] = 0;

        for (j = 0; j < 4; j++)
            char_array_4[j] = static_cast<unsigned char>(base64_chars.find(char_array_4[j]));

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_3[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++)
            decoded += char_array_3[j];
    }

    return decoded;
}

std::string rotN(const std::string& input, int shift) {
    std::string result = input;
    const int firstChar = 32;
    const int lastChar = 126;
    const int range = lastChar - firstChar + 1;

    shift = ((shift % range) + range) % range;

    for (char& c : result) {
        if (c >= firstChar && c <= lastChar) {
            c = static_cast<char>(firstChar + (c - firstChar + shift) % range);
        }
    }
    return result;
}

int main() {
    std::cout << "===========================================\n";
    std::cout << "  Base64 & ROT (1-47) Decoder Tool\n";
    std::cout << "===========================================\n\n";

    std::cout << "Select Input Type:\n";
    std::cout << "1. Base64 encoded string\n";
    std::cout << "2. Raw text (apply ROT directly)\n";
    std::cout << "Choice (1 or 2): ";

    int choice;
    std::cin >> choice;
    std::cin.ignore();

    std::string textToDecode;
    if (choice == 1) {
        std::string b64Input;
        std::cout << "\nEnter Base64 string: ";
        std::getline(std::cin, b64Input);
        textToDecode = base64Decode(b64Input);
        std::cout << "\n[Base64 Decoded Output]: " << textToDecode << "\n";
    } else {
        std::cout << "\nEnter text: ";
        std::getline(std::cin, textToDecode);
    }

    std::cout << "\n-------------------------------------------\n";
    std::cout << " HINT PREVIEW (Sample ROT shifts 1 - 47):\n";
    std::cout << "-------------------------------------------\n";

    std::vector<int> sampleRot = {1, 5, 13, 18, 25, 30, 47};
    for (int rot : sampleRot) {
        std::cout << "ROT-" << rot << " preview: " << rotN(textToDecode, rot) << "\n";
    }

    char keepGoing = 'y';
    while (keepGoing == 'y' || keepGoing == 'Y') {
        int customRot;
        std::cout << "\nEnter a specific ROT number (1-47): ";
        std::cin >> customRot;

        std::cout << "Result (ROT-" << customRot << "): " 
                  << rotN(textToDecode, customRot) << "\n";

        std::cout << "\nWould you like to try another ROT shift? (y/n): ";
        std::cin >> keepGoing;
    }

    std::cout << "\nExiting program.\n";
    return 0;
}
