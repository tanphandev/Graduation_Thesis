#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

string readBlockHeaderFromFile(string filePath) {
	ifstream inFile;
	string blockHeader;

	inFile.open(filePath);
	if (!inFile) {
		cout << "Can not read file!" << endl;
		exit(1);
	}

	// read BlockHeader.txt file and save value into blockHeader variable
	getline(inFile, blockHeader);
	return blockHeader;
	inFile.close();
}
void writeFile(string pathFile, string blockHeaderHex, string targetThreshold) {
	ofstream outFile(pathFile);
	if (!outFile) {
		cout << "Can not create file!" << endl;
		return;
	}
	outFile << "blockHeader=" << blockHeaderHex << endl;
	outFile << "target=" << targetThreshold << endl;
	outFile.close();
}

uint32_t getBits(string blockHeader) {
	// Tách chuỗi hex của thành phần bits trong blockheader ( dạng little endian )
	string bitsHex = blockHeader.substr(144, 8);
	// Chuyển đổi chuỗi hex sang giá trị uint32_t
	uint32_t bits = stoul(bitsHex, nullptr, 16);

	// Đảo thứ tự byte của giá trị uint32_t ( chuyển từ little endian sang big endian )
	bits = ((bits & 0xFF000000) >> 24) | ((bits & 0x00FF0000) >> 8) | ((bits & 0x0000FF00) << 8) | ((bits & 0x000000FF) << 24);

	return bits;
}

string calculateTargetHex(uint32_t bits)
{
	uint32_t exponent = bits >> 24;
	uint32_t mantissa = bits & 0x00ffffff;
	uint16_t byteShiftNum = exponent - 3;

	//convert mantissa value to hex string
	stringstream ss;
	ss << hex << setfill('0') << setw(64) << mantissa;
	string mantissahex = ss.str();

	//Shift left byteShiftNum (byte)
	string diffHex = mantissahex.substr(byteShiftNum * 2) + mantissahex.substr(0, byteShiftNum * 2);
	return diffHex;
}
int main() {
	string blockHeader = readBlockHeaderFromFile("D:/My_Data/KLTN/visual studio/BlockHeader.txt");
	cout << "Block Header: " << blockHeader << endl;

	//get Bits from block header
	uint32_t bits = getBits(blockHeader);

	// calculate Target Threshold
	string targetHex = calculateTargetHex(bits);
	cout << "Target: " << targetHex;

	// write block header hex and target hex into DataSendFPGA.txt file
	writeFile("D:/My_Data/KLTN/visual studio/DataSendFPGA.txt", blockHeader, targetHex);
	return 0;
}
