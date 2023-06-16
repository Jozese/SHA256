#include<string>
#include<bitset>
#include<iostream>
#include<vector>
#include<sstream>
#include <iomanip>

#pragma once

class SHA256
{
public:
	//Hash values
	std::vector<uint32_t> H = {
		0x6A09E667 ,
		0xBB67AE85 ,
		0x3C6EF372 ,
		0xA54FF53A ,
		0x510E527F ,
		0x9B05688C ,
		0x1F83D9AB ,
		0x5BE0CD19
	};

	//Round constants
	std::vector<uint32_t> K = {
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
		0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
		0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
		0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
	};
public:

	inline uint32_t rightRotate(uint32_t value, unsigned int rotation) {
		return (value >> rotation) | (value << (32 - rotation));
	}

	inline std::string uint32ToHexString(uint32_t value) {
		std::stringstream stream;
		stream << std::hex << std::setw(8) << std::setfill('0') << value;
		return stream.str();
	}

public:
	void messagePadding();
	std::vector<uint32_t> messageSchedule(std::vector<bool>& padded); //W
	void compression(std::vector<uint32_t>& wordsMessage);
	std::string getDigest(const std::string& toHash);
private:
	/*
		h0 := 0x6a09e667
		h1 := 0xbb67ae85
		h2 := 0x3c6ef372
		h3 := 0xa54ff53a
		h4 := 0x510e527f
		h5 := 0x9b05688c
		h6 := 0x1f83d9ab
		h7 := 0x5be0cd19
	*/
	uint32_t a = H[0], b = H[1], c = H[2], d = H[3], e = H[4], f = H[5], g = H[6], h = H[7];
	uint32_t S1 = 0, ch = 0, temp1 = 0, S0 = 0, maj = 0, temp2 = 0;

	std::string message = "";
	std::vector<bool> bitsMessage; //message in bits

};

