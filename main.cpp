#include <iostream>
#include <cstdio>
#include "base64Encoder.hpp"
#include "base64Decoder.hpp"

int main() {

  char inputOriginal[256];
  
  std::cout << "変換する文字列を入力してください";
	std::cin >> inputOriginal;
	std::cout << "input " << inputOriginal << std::endl;

  Base64Encoder base64Encoder = Base64Encoder(inputOriginal);
  char encodeResult[256];
  base64Encoder.run(encodeResult);
  printf("encodeResult: %s\n", encodeResult);

  Base64Decoder base64Decoder = Base64Decoder(encodeResult);
  char decodeOriginal[256];
  base64Decoder.run(decodeOriginal);
  printf("decodeOriginal: %s\n", decodeOriginal);
  
}