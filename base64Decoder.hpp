class Base64Decoder {
  public:
    Base64Decoder(char*);
    void run(char*);
  private:
    void convert_base64_to_bit();
    void convert_bit_to_original();
};