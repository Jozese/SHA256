#include "SHA256.h"

int main() {

	SHA256 sha;

	std::string toHash = "Hello, world!";
	std::cout << "Orig string: " << toHash << std::endl;
	std::cout << "Hashed string: " << sha.getDigest(toHash);

	return 0;
	
}