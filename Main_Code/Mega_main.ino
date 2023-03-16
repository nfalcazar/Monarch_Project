// Read serial from nano
//#include <SoftwareSerial.h>
#include "Monarch_Lib.h"

//TODO: determine form of commands
//      - currently getting strings from Picovoice and Nums from BLE

//TODO: consistent antennae spelling (I suck at spelling too apparently)

#define BLE_BAUDRATE    9600

//Butterfly pins
//TODO: Confirm pins w/ Sean
const int antennae_pin_l = 4;
const int antennae_pin_r = 5;
const int wing_pin_1  = 12;
const int wing_pin_2  = 13;
const int leg_l_pin   = 2;
const int leg_r_pin   = 3;
const int player_rx   = 10;
const int player_tx   = 11;

Monarch myButterfly(
    antennae_pin_l, antennae_pin_r, 
    wing_pin_1, wing_pin_2,
    leg_l_pin, leg_r_pin,
    player_rx, player_tx
);

//BLE UART init (Either add funt to Monarch lib or remove Serial1 in Monarch lib) 
//const int rx_to_BLE = 0;
//const int tx_to_BLE = 1;
//SoftwareSerial serialrecv(rx_to_BLE, tx_to_BLE);

char incomingByte = 0;

void setup() {
    //Serial1.begin(BLE_BAUDRATE);
    //Serial.begin(9600);
}

void loop() {
    int i = 0;
    int voice_line = -1;
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
            Serial.print("Unable to move: ");
            Serial.println(cmd[1]);
        }
    }
    else if (cmd[0] == "infoPart") {
        Serial.print("Recieved Info for bodypart: ");
        Serial.println(cmd[1]);

        if (cmd[1] == "wing" || cmd[1] == "wings") {
            voice_line = WINGS_AUDIO_INDEX;
        }
        else if (cmd[1] == "leg" || cmd[1] == "legs") {
            voice_line = LEGS_AUDIO_INDEX;
        }
        else if (cmd[1] == "antenna") {
            voice_line = ANTENNAE_AUDIO_INDEX;
        }

        if (voice_line == -1) {
            Serial.println("Unhandled or invalid body part");
        }
        else {
            myButterfly.speak(voice_line);
        } 
    }
    else if (cmd[0] == "infoAllParts") { //have
       // myButterfly.speak(VL_BODY_PARTS);
       myButterfly.speak(BODY_AUDIO_INDEX);
       myButterfly.speak(ANTENNAE_AUDIO_INDEX);
       myButterfly.speak(WINGS_AUDIO_INDEX);
       myButterfly.speak(LEGS_AUDIO_INDEX);
    }
    else if (cmd[0] == "infoMigrateWhy") {
        myButterfly.speak(MIGRATION_WHY_AUDIO_INDEX);
    }
    else if (cmd[0] == "infoMigrateHow") {
        myButterfly.speak(MIGRATION_WHERE_AUDIO_INDEX);
    }
    else if (cmd[0] == "infoCycle") {
        myButterfly.speak(CYCLE_AUDIO_INDEX);
    }
    else if (cmd[0] == "infoHelp") {
        myButterfly.speak(HELP_HOW_AUDIO_INDEX);
    }
    else {
        Serial.print("Unknown Command: ");
        Serial.println(recv);
        Serial.println("");

        return;
    }
}