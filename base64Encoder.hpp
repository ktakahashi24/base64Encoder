class Base64Encoder {
  public:
    Base64Encoder(char *originInput);
    void run(char *result);
  private:
    void split_six_bits();
    void convert_bit_to_base64();
    char original[256];
    char encodeBin[256];
    char encodeBase64[256];
    int iEncLength;
    const int target = 4;
};