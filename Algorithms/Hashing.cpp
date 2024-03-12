#include <iostream>
#include <string>
#include <functional>

//In C++, you can use various hash algorithms depending on your specific requirements.
// C++ provides a few standard libraries for hashing, including the <functional> header and the std::hash class.
// Additionally, you can implement custom hash functions when necessary.

//Here's a basic example using the std::hash class from the <functional> header:
//In this example, we use std::hash<std::string> to create a hash object specialized for strings.
// You can use this object to compute the hash value for a given string.
// Note that the hash value may vary between different runs of the program.

int main() {
    std::string input = "Hello, World!";

    // Create a hash object for strings
    std::hash<std::string> stringHash;

    // Compute the hash value for the input string
    size_t hashValue = stringHash(input);

    // Print the hash value
    std::cout << "Hash value: " << hashValue << std::endl;

    return 0;
}

//Keep in mind that the standard library provides hash functions for fundamental data types (like int, float, double, etc.),
// and you can use std::hash with custom data types as well.
// However, if you need a specific hashing algorithm or want more control over the hash function, you can implement a custom hash function.
// This is often necessary when working with custom data structures or complex objects.
//
//Here's a simple example of a custom hash function for a custom data type:
//In this example, we define a custom Person struct and a custom PersonHash struct that provides the hash function for Person objects.
// We combine the hash values of the name and age fields to create a unique hash for each Person object.

struct Person {
    std::string name;
    int age;
};

// Custom hash function for the Person struct
struct PersonHash {
    std::size_t operator()(const Person& p) const {
        // Combine the hash values of name and age
        return std::hash<std::string>{}(p.name) ^ std::hash<int>{}(p.age);
    }
};

int main() {
    Person person{"Alice", 30};

    // Create a hash object using the custom hash function
    std::hash<Person> personHash;

    // Compute the hash value for the person
    size_t hashValue = personHash(person);

    // Print the hash value
    std::cout << "Hash value: " << hashValue << std::endl;

    return 0;
}
