#include "SHA256.h"

void SHA256::messagePadding() {

	for (char c : this->message) {
		std::bitset<8> binaryChar(c);
		for (int i = 7; i >= 0; i--) {
			bitsMessage.push_back(binaryChar[i]);
		}
	}
	//Appending single 1 to the end
	bitsMessage.push_back(0b1);

	//Adding zeros until bitsMessage length is a multiple of 512 - 64 bits
	while (this->bitsMessage.size() % 512 != 0)
	{
		bitsMessage.push_back(0b0);
	}
	for (int i = 0; i < 64; i++) {
		bitsMessage.pop_back();
	}

	//Big-endian integer representing the length of the original input in binary
	std::bitset<64> binaryNumber(this->message.size() * 8);
	for (int i = 63; i >= 0; i--) {
		bitsMessage.push_back(binaryNumber[i]);
	}
	
}


std::vector<uint32_t> SHA256::messageSchedule(std::vector<bool>& padded) {
	std::vector<uint32_t> wordsMessage; //message in 32 bit words
	//bool vector to 32bit representation of the output we got
	/* */
	uint32_t a = 0b0;
	int counter2 = 0;
	for (int k = 0; k < padded.size() / 32; k++) {
		for (int i = 0; i < 32; i++) {
			a <<= 1;
			if (padded[counter2]) a |= 1;
			counter2++;
		}
		wordsMessage.push_back(a);
		a = 0b0;
	}

	//filling until W[63]
	for (int i = wordsMessage.size(); i < 64; i++) {
		wordsMessage.push_back(0b0);
	}


	/*
	*   For i from w[16…63]
		s0 = (w[i-15] rightrotate 7) xor (w[i-15] rightrotate 18) xor (w[i-15] rightshift 3)
		s1 = (w[i- 2] rightrotate 17) xor (w[i- 2] rightrotate 19) xor (w[i- 2] rightshift 10)
		w[i] = w[i-16] + s0 + w[i-7] + s1
	*/
	uint32_t s0 = 0, s1 = 0;
	for (int i = 16; i < 64; i++) {
		s0 = (rightRotate(wordsMessage[i - 15], 7)) ^ (rightRotate(wordsMessage[i - 15], 18)) ^ (wordsMessage[i - 15] >> 3);
		s1 = (rightRotate(wordsMessage[i - 2], 17)) ^ (rightRotate(wordsMessage[i - 2], 19)) ^ (wordsMessage[i - 2] >> 10);
		wordsMessage[i] = wordsMessage[i - 16] + s0 + wordsMessage[i - 7] + s1;
	}


	//checking values
	/*int counter = 0;
	for (uint32_t word : wordsMessage) {
		std::cout << std::bitset<32>(word) << " ";
		counter++;
		if (counter == 2) {
			std::cout << "\n";
			counter = 0;
		}
	}
	
	std::cout << "-----------------------------------------" << std::endl;
	*/

	return wordsMessage; 
}

void SHA256::compression(std::vector<uint32_t>& wordsMessage) {



	//compresion loop
	/*
		for i from 0 to 63
		S1 = (e rightrotate 6) xor (e rightrotate 11) xor (e rightrotate 25)
		ch = (e and f) xor ((not e) and g)
		temp1 = h + S1 + ch + k[i] + w[i]
		S0 = (a rightrotate 2) xor (a rightrotate 13) xor (a rightrotate 22)
		maj = (a and b) xor (a and c) xor (b and c)
		temp2 = S0 + maj
		h = g
		g = f
		f = e
		e = d + temp1
		d = c
		c = b
		b = a
		a = temp1 + temp2
	*/
	for (int i = 0; i < 64; i++) {
		S1 = (rightRotate(e, 6)) ^ (rightRotate(e, 11)) ^ (rightRotate(e, 25));
		ch = (e & f) ^ ((~e) & g);
		temp1 = h + S1 + ch + K[i] + wordsMessage[i];
		S0 = (rightRotate(a, 2)) ^ (rightRotate(a, 13)) ^ (rightRotate(a, 22));
		maj = (a & b) ^ (a & c) ^ (b & c);
		temp2 = S0 + maj;
		h = g;
		g = f;
		f = e;
		e = d + temp1;
		d = c;
		c = b;
		b = a;
		a = temp1 + temp2;
	}
	
	/*
	std::cout << std::bitset<32>(a) << std::endl;
	std::cout << std::bitset<32>(b) << std::endl;
	std::cout << std::bitset<32>(c) << std::endl;
	std::cout << std::bitset<32>(d) << std::endl;
	std::cout << std::bitset<32>(e) << std::endl;
	std::cout << std::bitset<32>(f) << std::endl;
	std::cout << std::bitset<32>(g) << std::endl;
	std::cout << std::bitset<32>(h) << std::endl;
	*/

	H[0] = H[0] + a;
	H[1] = H[1] + b;
	H[2] = H[2] + c;
	H[3] = H[3] + d;
	H[4] = H[4] + e;
	H[5] = H[5] + f;
	H[6] = H[6] + g;
	H[7] = H[7] + h;

}

std::string SHA256::getDigest(const std::string& toHash) {
	this->message = toHash;

	std::vector<bool> padded;

	int c = 0;
	messagePadding();
	//Chunk loop

	

	for (int i = 0; i < bitsMessage.size() / 512; i++) {
		for (int k = c; k < 512*(i+1); k++)
		{
			padded.push_back(bitsMessage[k]);
			c = k + 1;
		}
		

		std::vector<uint32_t> words = messageSchedule(padded);

		

		compression(words);
		

		padded.clear();

	}
	
	std::string digest = "";
	for (int i = 0; i < 8; i++) {
		digest += uint32ToHexString(H[i]);
	}
	return digest;
}