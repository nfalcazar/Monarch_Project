/*
    Monarch_Lib.cpp - library for controlling the animatronic monarch butterfly
    Created by the Cal Poly SLO Monarch capstone project team on Jan 12, 2023
    Just wing it!
*/

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <Monarch_Lib.h>

Monarch::Monarch(int antennae_pin_l, int antennae_pin_r,
		 int wing_pin_1, int wing_pin_2,
                 int leg_pin_l, int leg_pin_r,
                 int player_rx, int player_tx)
{
    // Initialize pins
    _antennae_pin_l = antennae_pin_l;
    _antennae_pin_r = antennae_pin_r;
    _wing_pin_1 = wing_pin_1;
    _wing_pin_2 = wing_pin_2;
    _player_rx = player_rx;
    _player_tx = player_tx;
    _leg_pin_l = leg_pin_l;
    _leg_pin_r = leg_pin_r;
    pinMode(_antennae_pin_l, OUTPUT);
    pinMode(_antennae_pin_r, OUTPUT);
    pinMode(_wing_pin_1, OUTPUT);
    pinMode(_wing_pin_2, OUTPUT);
}

void Monarch::begin()
{
    // Setup components with specialized hardware (serial and servos)
    Serial.begin(9600);  // connection to laptop for debugging
    // Serial1.begin(9600); // connection to nano 33 ble sense
    
    SoftwareSerial playerSerial(_player_rx, _player_tx);
    playerSerial.begin(9600);
    Serial.println("Initializing dfplayer...");
    if (!_player.begin(playerSerial)) {
    	Serial.println("Error: dfplayer not properly configured");
    }
    Serial.println("Dfplayer initialized");
    set_vol(30);
    
    _leg_servo_l.attach(_leg_pin_l);
    _leg_servo_r.attach(_leg_pin_r);
    _leg_servo_l.write(90);
    _leg_servo_r.write(90);
    
    Serial.println("Setup complete");
}

void Monarch::move_antennae()
{
    // Move antennae
    Serial.println("Moving antennae");
    digitalWrite(_antennae_pin_l, HIGH);
    digitalWrite(_antennae_pin_r, HIGH);
    delay(1000);
    digitalWrite(_antennae_pin_l, LOW);
    digitalWrite(_antennae_pin_r, LOW);
    delay(1000);
}

void Monarch::move_wings()
{
    // Move wings
    Serial.println("Moving wings");
    digitalWrite(_wing_pin_1, HIGH);
    digitalWrite(_wing_pin_2, LOW);
    delay(1000);
    digitalWrite(_wing_pin_1, LOW);
    digitalWrite(_wing_pin_2, LOW);
    delay(1000);
}

void Monarch::move_legs()
{
    // Move legs
    Serial.println("Moving legs");
    _leg_servo_l.write(180);
    _leg_servo_r.write(180);
    delay(500);
    _leg_servo_l.write(90);
    _leg_servo_r.write(90);
    delay(500);
    _leg_servo_l.write(0);
    _leg_servo_r.write(0);
    delay(500);
    _leg_servo_l.write(90);
    _leg_servo_r.write(90);
    delay(500);
}

void Monarch::vol_up()
{
    // Increase volume of player
    _player.volumeUp();
}

void Monarch::vol_down()
{
    // Decrease volume of player
    _player.volumeDown();
}

void Monarch::set_vol(int vol)
{
    // Set volume of player to an integer value
    _player.volume(vol);
}

void Monarch::speak(int voice_line)
{
    // Send command for player to speak voice line
    Serial.println("Speaking");
    _player.play(voice_line);
}

int Monarch::get_player_state()
{
    // Returns player's state (stuff for status)
    return _player.readType();
}

bool Monarch::is_player_available()
{
    // Returns whether player is available for commands or not
    return _player.available();
}

bool Monarch::is_player_speaking()
{
    // DOESN'T WORK
    // Returns whether player is speaking or not
    return true;
}
