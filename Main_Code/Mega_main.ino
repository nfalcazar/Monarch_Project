// Read serial from nano
//#include <SoftwareSerial.h>
#include "Monarch_Lib.h"

//TODO: determine form of commands
//      - currently getting strings from Picovoice and Nums from BLE

//TODO: consistent antennae spelling (I suck at spelling too apparently)

#define BLE_BAUDRATE    9600
#define USE_SERIAL_MON  1

//Butterfly pins
//TODO: Confirm pins w/ Sean
const int antenna_pin = 31; //33?
const int wing_pin_1  = 4;
const int wing_pin_2  = 5;
const int leg_l_pin   = 6;
const int leg_r_pin   = 7;
const int player_rx   = 2;
const int player_tx   = 3;

Monarch myButterfly(
    antenna_pin, wing_pin_1, wing_pin_2,
    leg_l_pin, leg_r_pin,
    player_rx, player_tx
);

//BLE UART init (Either add funt to Monarch lib or remove Serial1 in Monarch lib) 
//const int rx_to_BLE = 0;
//const int tx_to_BLE = 1;
//SoftwareSerial serialrecv(rx_to_BLE, tx_to_BLE);

char incomingByte = 0;
char rx_buff[BUFF_SIZE];

void setup() {
    //Serial1.begin(BLE_BAUDRATE);
    //Serial.begin(9600);
}

void loop() {
    int i = 0;
    int voice_line = 0;
    String recv = "";
    String cmd[2];
    
    while (Serial1.available() > 0) {
        incomingByte = Serial1.read();
        recv += incomingByte;
        delay(10);  // Trying to match Baudrate led to some errors
                    // Waiting way longer than min Baudrate as a solution
    }

    if (recv != "") {
        if(USE_SERIAL_MON) {
            Serial.print("UART Grabbed: ");
            Serial.print(recv);
        }

        //Split string if more than one word
        i = recv.indexOf(' ');
        if (i != -1) {
            cmd[0] = recv.substring(0, i);
            cmd[1] = recv.substring(i + 1);
        }
        else {
            cmd[0] = recv;
            cmd[1] = "";
        }
    }
    else
        return;


    if (cmd[0] == "error") {
        if(USE_SERIAL_MON)
            Serial.println("Picovoice did not recognize voice CMD.");
            Serial.println("");
    }
    else if (cmd[0] == "moveItem") {
        if (USE_SERIAL_MON) {
            Serial.print("Recieved Move CMD: ");
            Serial.println(cmd[1]);
            Serial.println("");
        }

        if (cmd[1] == "wing" || cmd[1] == "wings") {
            myButterfly.move_wings();
        }
        else if (cmd[1] == "legs" || cmd[1] == "leg") {
            myButterfly.move_legs();
        }
        else if (cmd[1] == "antenna") {
            myButterfly.move_antennae();
        }
        else {
            // Rely unable to move body part
            Serail.print("Unable to move: ");
            Serial.println(cmd[1]);
        }
    }
    //TODO: Confirm Voice line numbers
    else if (cmd[0] == "infoReq") {
        if (USE_SERIAL_MON) {
            Serial.print("Recieved Info Request: ");
            Serial.println(cmd[1]);
            Serial.println("");
        }

        if (cmd[1] == "diet") {
            voice_line = VL_INFO_DIET; //TODO
        }
        else if (cmd[1] == "status" || cmd[1] == "endangered") {
            voice_line = VL_INFO_STATUS;
        }
        else if (cmd[1] == "migration") {
            voice_line = VL_INFO_MIGRAT;
        }
        //TODO: finish voice line selections
        else {
            if (USE_SERIAL_MON) {
                Serial.print("Unknown Info Request topic: ")
                Serial.println(cmd[1]);
                Serial.println("");
            }

            return;
        }

        //Output to Speaker
        myButterfly.speak(voice_line);
    }
    else {
        if(USE_SERIAL_MON) {
            Serial.print("Unknown Command: ");
            Serial.println(recv);
            Serial.println("");
        }

        return;
    }
}