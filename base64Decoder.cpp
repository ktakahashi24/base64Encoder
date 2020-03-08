#include <iostream>
#include <cstring>
#include "base64EncodeList.hpp"
#include "base64Decoder.hpp"
  char chrBasa64[256];
  char chrSixBits[256];
  char chrOriginal[256];

  Base64Decoder::Base64Decoder(char *input) {
    strcpy(chrBasa64, input);
  }

  void Base64Decoder::run(char *result) {
    convert_base64_to_bit();
    convert_bit_to_original();
    strcpy(result, chrOriginal);
    // printf("result: %s\n", result);
  }

  void Base64Decoder::convert_base64_to_bit() {
    int idx = 0;

    // printf("chrSixBits: ");
    while(chrBasa64[idx] != '=') {
      for(auto base64EncVal=umBase64EncodeList.begin();base64EncVal!=umBase64EncodeList.end();base64EncVal++) {
        if (base64EncVal->second == chrBasa64[idx]) {
          chrSixBits[idx] = base64EncVal->first;
          // printf("%02x ", chrSixBits[idx]);
        }
      }
      idx++; 
      if (idx >= (sizeof(chrBasa64)) - 1) break;

    }
    chrSixBits[idx] = '\0';
    // printf("\n");
  }

  void Base64Decoder::convert_bit_to_original() {
    int idx = 0;
    int idxOriginal = 0;
    while(chrSixBits[idx + 1] != '\0') {
      switch(idx % 4) {
        case 0:
          chrOriginal[idxOriginal++] = (chrSixBits[idx]<<2 & 0xFC) + (chrSixBits[idx + 1]>>4 &3);
          break;
        case 1:
          chrOriginal[idxOriginal++] = (chrSixBits[idx]<<4 & 0xF0) + (chrSixBits[idx + 1]>>2 & 0x0F);
          break;
        case 2:
          chrOriginal[idxOriginal++] = (chrSixBits[idx]<<6 & 0xC0) + (chrSixBits[idx + 1] & 0x3F);
          break;
        case 3:
          // 何もしない
          break;
        default:
          break;
      }

      // for (int i=7; i>=0; i--) {
      //   std::cout << (chrOriginal[idxOriginal - 1]>>i & 1);
      // }
      // printf("\n");
      idx++;

      if (idx >= (sizeof(chrBasa64)) - 1) break;
    }
    chrOriginal[idx] = '\0';
  }