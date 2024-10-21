#include <iostream>
#include <string>

std::string caesarEncrypt(const std::string& input, int shift) {
    std::string result = "";

    for (char c : input) {
        if (isupper(c)) {
            result += static_cast<char>(static_cast<int>(c + shift - 'A') % 26 + 'A'); 
        }else if (islower(c)) {
            result += static_cast<char>(static_cast<int>(c + shift - 'a') % 26 + 'a'); 
        }else {
            result += c; 
        }
    }

    return result;
}

std::string caesarDecrypt(const std::string& text, int shift) {
    // shift in the opposite direction
    return caesarEncrypt(text, 26 - (shift % 26));
}

int main() {
    std::string text;
    int n;

    std::cin >> text;
    std::cin >> n;

    std::string encryptedText = caesarEncrypt(text, n);

    std::cout << encryptedText << " ";
    std::cout << caesarDecrypt(encryptedText, n);
}
