#include <string.h>

#define ADDRESS_SIZE 2
#define DATA_SIZE 8
#define WAIT_PERIOD 100
#define MAX_INPUT

//SIGNALS
const unsigned short clk = 23;
const unsigned short we = 25;
const unsigned short write_addr[ADDRESS_SIZE] = { 27, 29 };
const unsigned short read_addr1[ADDRESS_SIZE] = { 31, 33 };
const unsigned short read_addr2[ADDRESS_SIZE] = { 35, 37 };
const unsigned short write_data[DATA_SIZE] = { 22, 24, 26, 28, 30, 32, 34, 36 };
const unsigned short read_data1[DATA_SIZE] = { 39, 41, 43, 45, 47, 49, 51, 53 };
const unsigned short read_data2[DATA_SIZE] = { 38, 40, 42, 44, 46, 48, 50, 52 };

unsigned char arg1, arg2;

void setBits(const unsigned short port[], const size_t data_size, const unsigned char data);
void writeData(const unsigned short address, const unsigned char data);
const unsigned char readData(const unsigned short port[]);
void clearPorts();

void setup() {
  Serial.begin(9600);

  //Clock signal
  pinMode(clk, OUTPUT);
  digitalWrite(clk, LOW);

  //Write enabled signal
  pinMode(we, OUTPUT);
  digitalWrite(we, LOW);

  //Address signals
  for(int i = 0; i < ADDRESS_SIZE; i++) {
    pinMode(write_addr[i], OUTPUT);
    digitalWrite(write_addr[i], LOW);
    
    pinMode(read_addr1[i], OUTPUT);
    digitalWrite(read_addr1[i], LOW);

    pinMode(read_addr2[i], OUTPUT);
    digitalWrite(read_addr2[i], LOW);
  }

  //Data signals
  for(int i = 0; i < DATA_SIZE; i++) {
    pinMode(write_data[i], OUTPUT);
    digitalWrite(write_data[i], LOW);
    
    pinMode(read_data1[i], INPUT);
    digitalWrite(read_data1[i], LOW);

    pinMode(read_data2[i], INPUT);
    digitalWrite(read_data2[i], LOW);
  }
}
void loop() {
  if(Serial.available()) {

    String str = Serial.readString();
    char* token = strtok((char*)(str.c_str()), " ");
    arg1 = atoi(strtok(NULL, " "));
    arg2 = atoi(strtok(NULL, " "));

    if(!strcmp(token, "r"))
    {
      Serial.println("Sent Address 1: " + String(arg1));
      Serial.println("Sent Address 2: " + String(arg2) + "\n");
      setBits(read_addr1, ADDRESS_SIZE, arg1);
      setBits(read_addr2, ADDRESS_SIZE, arg2);
      Serial.println("Read Data 1: " + String((unsigned short)readData(read_data1)));
      Serial.println("Read Data 2: " + String((unsigned short) readData(read_data2)) + "\n");
    }
    else if (!strcmp(token, "w"))
    {
      Serial.println("Target Address: " + String(arg1));
      Serial.println("Sent Data: " + String(arg2) + "\n");
      setBits(write_addr, ADDRESS_SIZE, arg1);
      setBits(write_data, DATA_SIZE, arg2);
      writeData((unsigned short)arg1, arg2);
    }
    else
    {
      Serial.println("Not a valid operation");
    }
    
  }
}

void setBits(const unsigned short port[], const size_t data_size, const unsigned char data) {
  for(int i = 0; i < data_size; i++) {
    if(data & (1 << i))
      digitalWrite(port[i], HIGH);
    else
      digitalWrite(port[i], LOW);
  }
}

void writeData(const unsigned short address, const unsigned char data) {
  setBits(write_addr, ADDRESS_SIZE, address);
  setBits(write_data, DATA_SIZE, data);
  digitalWrite(we, HIGH);
  digitalWrite(clk, HIGH);
  delay(WAIT_PERIOD);
  digitalWrite(clk, LOW);
  digitalWrite(we, LOW);
}

const unsigned char readData(const unsigned short port[]) {
  unsigned char data = 0;
  
  for(int i = 0; i < DATA_SIZE; i++)
    data |= (digitalRead(port[i]) << i);
    
  return data;
}

