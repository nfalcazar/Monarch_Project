// Read serial from nano
//#include <SoftwareSerial.h>
#include "Monarch_Lib.h"

//TODO: determine form of commands
//      - currently getting strings from Picovoice and Nums from BLE

//TODO: consistent antennae spelling (I suck at spelling too apparently)

#define BLE_BAUDRATE    9600

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
    String recv = "";
    String cmd[2];
    
    while (Serial1.available() > 0) {
        incomingByte = Serial1.read();
        recv += incomingByte;
        delay(10);  // Trying to match Baudrate led to some errors
                    // Waiting way longer than min Baudrate as a solution
    }

    if (recv != "") {
        Serial.print("UART Grabbed: ");
        Serial.print(recv);

        //Split string if more than one word
        //Mainly used to grab body part slot from move command
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
        Serial.println("Picovoice did not recognize voice CMD.");
        Serial.println("");
    }
    else if (cmd[0] == "moveItem") {
        Serial.print("Recieved Move CMD: ");
        Serial.println(cmd[1]);
        Serial.println("");

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
    else if (cmd[0] == "infoAllParts") {
        myButterfly.speak(VL_BODY_PARTS);
    }
    else if (cmd[0] == "infoMigrateWhy") {
        myButterfly.speak(VL_MIG_WHY);
    }
    else if (cmd[0] == "infoMigrateHow") {
        myButterfly.speak(VL_MIG_HOW);
    }
    else if (cmd[0] == "infoCycle") {
        myButterfly.speak(VL_CYCLE);
    }
    else if (cmd[0] == "infoHelp") {
        myButterfly.speak(VL_HELP);
    }
    else {
        Serial.print("Unknown Command: ");
        Serial.println(recv);
        Serial.println("");

        return;
    }
}