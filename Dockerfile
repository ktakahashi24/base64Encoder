FROM gcc:latest
COPY . /usr/src/base64App
WORKDIR /usr/src/base64App
RUN g++ -std=c++17 main.cpp base64Encoder.cpp base64Decoder.cpp -o base64App
CMD ["./base64App"]