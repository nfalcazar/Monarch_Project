/*
    Monarch_Lib.cpp - library for controlling the animatronic monarch butterfly
    Created by the Cal Poly SLO Monarch capstone project team on Jan 12, 2023
    Just wing it!
*/

#include "Arduino.h"
#include "SoftwareSerial.h"
// #include "DFRobotDFPlayerMini.h"
#include "Monarch_Lib.h"

Monarch::Monarch(int antennae_pin, int wing_pin_1, int wing_pin_2,
                 int leg_l_pin, int leg_r_pin,
                 int player_rx, int player_tx)
{
    // Initialize serial
    Serial.begin(9600);  // connection to laptop for debugging
    Serial1.begin(9600); // connection to nano 33 ble sense

    // Initialize pins
    _antennae_pin = antennae_pin;
    _wing_pin_1 = wing_pin_1;
    _wing_pin_2 = wing_pin_2;
    pinMode(_antennae_pin, OUTPUT);
    pinMode(_wing_pin_1, OUTPUT);
    pinMode(_wing_pin_2, OUTPUT);

    // Initialize servos
    // ** NOTE: remember to change the constants if the servos are changed
    _leg_l_servo.attach(leg_l_pin, 900, 2100);
    // _leg_r_servo.attach(leg_r_pin, 900, 2100);  // TODO: ADD THE RIGHT LEG

    // Initialize audio player
    _volume = 30;
    SoftwareSerial playerSerial(player_rx, player_tx);
    playerSerial.begin(9600);
    _player.begin(playerSerial);
    _player.volume(_volume);
}

void Monarch::move_antennae()
{
    // Move antennae
    digitalWrite(_antennae_pin, HIGH);
    delay(1000);
    digitalWrite(_antennae_pin, LOW);
    delay(1000);
}

void Monarch::move_wings()
{
    // Move wings (TODO: CHANGE FOR STEPPER MOTOR)
    digitalWrite(_wing_pin_1, HIGH);
    digitalWrite(_wing_pin_2, LOW);
    delay(1000);
    digitalWrite(_wing_pin_1, HIGH);
    digitalWrite(_wing_pin_2, LOW);
    delay(1000);
}

void Monarch::move_legs()
{
    // Move legs; TODO: add right leg
    _leg_l_servo.write(90);
    delay(1000);
    _leg_l_servo.write(0);
    delay(1000);
}

void Monarch::vol_up()
{
    // Increase volume of player
    if(_volume < 30)
        _volume += 5;
}

void Monarch::vol_down()
{
    // Decrease volume of player
    if(_volume >= 0)
        _volume -= 5;
}

void Monarch::speak(int voice_line)
{
    // Send command for player to speak voice line
    _player.play(voice_line);
}

bool Monarch::get_player_status()
{
    // Returns whether player is available or not
    return _player.available();
}