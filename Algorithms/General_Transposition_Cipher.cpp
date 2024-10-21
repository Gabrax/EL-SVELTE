#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Function to encrypt the text using the transposition cipher
std::string encrypt(const std::string& text, const std::string& key) {
    int numRows = (text.size() + key.size() - 1) / key.size();
    std::vector<std::string> grid(numRows, std::string(key.size(), ' '));

    // Fill the grid row by row with the text
    int textIndex = 0;
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < key.size(); ++col) {
            if (textIndex < text.size()) {
                grid[row][col] = text[textIndex++];
            }
        }
    }

    // Read the characters column by column based on the sorted key
    std::string encryptedText = "";
    std::string sortedKey = key;
    std::sort(sortedKey.begin(), sortedKey.end());

    for (char ch : sortedKey) {
        int col = key.find(ch);
        for (int row = 0; row < numRows; ++row) {
            if (grid[row][col] != ' ') {
                encryptedText += grid[row][col];
            }
        }
    }

    return encryptedText;
}

// Function to decrypt the text using the transposition cipher
std::string decrypt(const std::string& text, const std::string& key) {
    int numRows = (text.size() + key.size() - 1) / key.size();
    std::vector<std::string> grid(numRows, std::string(key.size(), ' '));
    std::string sortedKey = key;
    std::sort(sortedKey.begin(), sortedKey.end());

    // Fill the grid column by column based on the sorted key
    int textIndex = 0;
    for (char ch : sortedKey) {
        int col = key.find(ch);
        for (int row = 0; row < numRows; ++row) {
            if (textIndex < text.size()) {
                grid[row][col] = text[textIndex++];
            }
        }
    }

    // Read the characters row by row to reconstruct the original text
    std::string decryptedText = "";
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < key.size(); ++col) {
            if (grid[row][col] != ' ') {
                decryptedText += grid[row][col];
            }
        }
    }

    return decryptedText;
}

int main() {
    std::string text = "attackatdawn";
    std::string key = "4312";

    std::string encryptedText = encrypt(text, key);
    std::cout << "Encrypted Text: " << encryptedText << std::endl;

    std::string decryptedText = decrypt(encryptedText, key);
    std::cout << "Decrypted Text: " << decryptedText << std::endl;
}
