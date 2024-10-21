#include <iostream>
#include <string>
#include <vector>

// Function to encrypt the text using the modified transposition cipher
std::string encrypt(const std::string& text, int n) {
    std::vector<std::string> rows;
    std::string encryptedText = "";

    // Divide the text into rows of length n
    for (size_t i = 0; i < text.size(); i += n) {
        rows.push_back(text.substr(i, n));
    }

    // Read the text column by column to create the encrypted text
    for (int col = 0; col < n; ++col) {
        for (const auto& row : rows) {
            if (col < row.size()) {
                encryptedText += row[col];
            }
        }
    }

    return encryptedText;
}

// Function to decrypt the text using the modified transposition cipher
std::string decrypt(const std::string& text, int n) {
    int numRows = (text.size() + n - 1) / n;  // Calculate the number of rows
    std::vector<std::string> columns(n);
    int currentPos = 0;

    // Fill the columns with characters from the encrypted text
    for (int col = 0; col < n; ++col) {
        for (int row = 0; row < numRows && currentPos < text.size(); ++row) {
            columns[col] += text[currentPos++];
        }
    }

    // Reconstruct the original text by reading row by row
    std::string decryptedText = "";
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < n; ++col) {
            if (row < columns[col].size()) {
                decryptedText += columns[col][row];
            }
        }
    }

    return decryptedText;
}

int main() {
    std::string text;
    int n;

    std::cin >> text;
    std::cin >> n;

    std::string encryptedText = encrypt(text, n);
    std::cout << encryptedText << " ";

    std::cout << decrypt(encryptedText, n);

    return 0;
}
