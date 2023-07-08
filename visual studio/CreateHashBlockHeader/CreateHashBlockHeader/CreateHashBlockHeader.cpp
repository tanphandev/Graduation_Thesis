#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <ctime>
#include <openssl/sha.h>

using namespace std;

unsigned char* calculateTargetByte(string target_hex)
{
	unsigned char* targetByte = new unsigned char[32];

	// convert target_hex to byte array
	for (int i = 0; i < 32; i++) {
		stringstream bytestr;
		bytestr << hex << target_hex.substr(i * 2, 2);
		uint32_t bytevalue;
		bytestr >> bytevalue;
		targetByte[i] = (unsigned char)bytevalue;
	}

	return targetByte;
}

void showBytesValue(unsigned char* byteArrray)
{
	for (int i = 0; i < 32; i++) {
		cout << hex << (int)byteArrray[i] << " ";
	}
	cout << endl;
}

void ReverseByte(unsigned char ByteValue[32])
{
	for (int i = 0; i < 16; i++) {
		unsigned char temp = ByteValue[i];
		ByteValue[i] = ByteValue[31 - i];
		ByteValue[31 - i] = temp;
	}
}

string ConvertByteToHex(unsigned char byteArray[32])
{
	//Reverse the hash bytes and print the hash as a hexadecimal string
	stringstream hex_stream;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		hex_stream << hex << setfill('0') << setw(2) << (int)byteArray[i];
	}
	return hex_stream.str();
}

unsigned char * blockHeaderHashByte(unsigned char block_header_bytes[80])
{
	// Create a SHA256_CTX object to hold the context for the hash computation
	SHA256_CTX sha256_1, sha256_2;
	SHA256_Init(&sha256_1);

	// Update the hash computation with the block header bytes
	SHA256_Update(&sha256_1, block_header_bytes, 80);

	// Create an array to hold the first hash bytes
	unsigned char hash_1[SHA256_DIGEST_LENGTH];

	// Finalize the first hash computation and store the result in the hash_1 array
	SHA256_Final(hash_1, &sha256_1);

	// Initialize a second hash computation with the first hash bytes
	SHA256_Init(&sha256_2);
	SHA256_Update(&sha256_2, hash_1, SHA256_DIGEST_LENGTH);

	// Create an array to hold the final hash bytes
	unsigned char hash_final[SHA256_DIGEST_LENGTH];

	// Finalize the final hash computation and store the result in the hash_final array
	SHA256_Final(hash_final, &sha256_2);

	//Reverse byte ofhash_final ( big-endian )
	ReverseByte(hash_final);

	//show hash byte of block header
	//cout << endl << "HASH_B:";
	//showBytesValue(hash_final);
	return hash_final;
}

void readDataFromFile(string filePath, string &blockHeader, string &target) {
	ifstream inFile;
	inFile.open(filePath);
	if (!inFile) {
		cout << "Can not read file!" << endl;
		exit(1);
	}
	string dataFile;
	while (getline(inFile, dataFile)) {
		if (dataFile.find("blockHeader=") == 0) {
			blockHeader = dataFile.substr(12); // bỏ đi "blockHeader="
		}
		else if (dataFile.find("target=") == 0) {
			target = dataFile.substr(7); // bỏ đi "target="
		}
	}
	inFile.close();
}

int main() {
	//read file to get block_header_hex and target_hex
	string block_header_hex; 	// Block header in hex format (little-endian)
	string target_hex;			// target threshold in hex format ( big-endian )
	uint32_t nounce = 0x0; // first time to check first block header  ( nounce true = 0xb38c4c30) 
	readDataFromFile("D:/My_Data/KLTN/visual studio/DataSendFPGA.txt", block_header_hex, target_hex);

	//show block header hex

	cout << "Block header: " << block_header_hex << endl;

	//show target hex

	cout << "Target: " << target_hex << endl;

	//calculate Target bytes
	unsigned char* targetByte = nullptr;
	targetByte = calculateTargetByte(target_hex);
	//cout << "TARGET_BYTES:";
	//showBytesValue(targetByte);

	// Convert block header hex to bytes
	unsigned char block_header_bytes[80];
	for (int i = 0; i < 80; i++) {
		stringstream ss;
		ss << hex << block_header_hex.substr(i * 2, 2);
		int byte_value;
		ss >> byte_value;
		block_header_bytes[i] = (unsigned char)byte_value;
	}

	//show block header byte
	//cout << "Block Header (80 bytes) : ";
	//for (int i = 0; i < 80; i++) {
	//	cout << (int)block_header_bytes[i] << " ";
	//}

	time_t startTime = time(nullptr);
	while (nounce < 0xffffffff)
	{
		//hash block header
		unsigned char* hash_final = new unsigned char[SHA256_DIGEST_LENGTH];
		hash_final = blockHeaderHashByte(block_header_bytes);

		time_t currTime = time(nullptr);
		
		uint32_t diffTime = currTime - startTime;
		float hashRate = (float)nounce / diffTime;


		// Compare two arrays of bytes
		if (memcmp(hash_final, targetByte, 32) < 0)
		{
			cout << endl << "SUCCESS!" << endl;
			cout << "Nounce = " << nounce << " is valid! Hashrate = " << dec << hashRate << endl;
			string hash_final_hex = ConvertByteToHex(hash_final);

			//show hash_final_hex
			cout << "Block Header below Target: " << hash_final_hex;
			break;
		}
		else
		{	
			cout << endl << "Nounce = " << hex << nounce << " is invalid! Hashrate = " << dec << hashRate;
			nounce++;

			// convert uint32_t to byte array;
			union {
				uint32_t n;
				unsigned char nounceByte[4];
			} data;
			data.n = nounce;

			//ghep nounce mới vào block header
			for (int i = 76, j = 0; i < 80, j < 4; i++, j++)
			{
				block_header_bytes[i] = data.nounceByte[j];
			}
			//show new block header byte
			//cout << endl << "New Block header byte: ";
			//for (int i = 0; i < 80; i++) {
			//	cout << (int)block_header_bytes[i] << " ";
			//}
		}
	}
	delete[] targetByte;
	return 0;
}
