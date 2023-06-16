#include "SHA256.h"

int main() {

	SHA256 sha;
	std::cout << sha.getDigest("helloworldhelloworldhelloworldhelloworldhelloworldhelloworldhelloworldhelloworldhelloworldhelloworldhelloworldhelloworld");

	return 0;
	
}