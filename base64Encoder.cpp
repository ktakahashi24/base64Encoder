#include <iostream>
#include <cstring>
#include "base64EncodeList.hpp"
#include "base64Encoder.hpp"

Base64Encoder::Base64Encoder(char *originInput) {
  strcpy(original, originInput);
}

void Base64Encoder::run(char *result) {
  split_six_bits();
  convert_bit_to_base64();

  // printf("%s\n", encodeBase64);
  strcpy(result, encodeBase64);
}

void Base64Encoder::split_six_bits() {
  int idx = 0;
  int idxEnc = 0;
  for(;;) {
    switch (idx % 3)
    {
    case 0:
      encodeBin[idxEnc++] = (original[idx]>>2 & 0x3F);
      break;
    case 1:
      encodeBin[idxEnc++] = (original[idx - 1]<<4 & 0x30) + (original[idx]>>4 & 0x3F);
      break;
    case 2:
      encodeBin[idxEnc++] = (original[idx - 1]<<2 & 0x3C) + (original[idx]>>6 & 3);
      encodeBin[idxEnc++] = (original[idx] & 0x3F);
      break;
    default:
      break;
    }

    idx++;

    if (original[idx] == '\0') {
      switch ((idx - 1) % 3)
      {
      case 0:
        encodeBin[idxEnc++] = (original[idx - 1]<<4 & 0x30);
        break;
      case 1:
        encodeBin[idxEnc++] = (original[idx - 1]<<2 & 0x3C);
        break;
      default:
        break;
      }

      break;
    }
  }

  encodeBin[idxEnc] = '\0';

  // int idxTest = 0;
  // while(encodeBin[idxTest] != '\0') {
  //   printf("encodeBin[%d]: ", idxTest);
  //   for(int s=7;s>=0;s--) {
  //     std::cout << (encodeBin[idxTest]>>s & 1);
  //   }
  //   printf("\n");
  //   idxTest++;
  // }
  iEncLength = idxEnc + 1;
}


void Base64Encoder::convert_bit_to_base64() {
  int index = 0;

  for(;;) {
    auto it = umBase64EncodeList.find(encodeBin[index]);
    if (it != umBase64EncodeList.end()) {
      encodeBase64[index] = it->second;
    }
    
    index++;
    if (encodeBin[index] == '\0') break;
  }

  for (int i = 0;i < (4 - (iEncLength % 4)); i++) {
    encodeBase64[index] = '=';
    index++;
  }
  encodeBase64[index] = '\0';
}
