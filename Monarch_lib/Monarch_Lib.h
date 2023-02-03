/*
    Monarch_Lib.h - library for controlling the animatronic monarch butterfly
    Created by the Cal Poly SLO Monarch capstone project team on Jan 12, 2023
    Just wing it!
*/

#ifndef MONARCH_LIB_H
#define MONARCH_LIB_H

#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include "Servo.h"

class Monarch
{
    public:
        Monarch(int antennae_pin, int wing_pin_1, int wing_pin_2,
                int leg_l_pin, int leg_r_pin,
                int player_rx, int player_tx);
        void move_antennae();
        void move_wings();
        void move_legs();
        void vol_up();
        void vol_down();
        void speak(int voice_line);
        bool get_player_status();
    private:
        int _antennae_pin;
        int _wing_pin_1, _wing_pin_2;
        Servo _leg_l_servo;
        Servo _leg_r_servo;
        int _volume;
        DFRobotDFPlayerMini _player;
};

#endif