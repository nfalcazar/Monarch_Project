/*
    Monarch_Lib.h - library for controlling the animatronic monarch butterfly
    Created by the Cal Poly SLO Monarch capstone project team on Jan 12, 2023
    Just wing it!
*/

#ifndef MONARCH_LIB_H
#define MONARCH_LIB_H



#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>
#include <Servo.h>

class Monarch
{
    public:
        Monarch(int antennae_pin_l, int antennae_pin_r,
        	int wing_pin_1, int wing_pin_2,
                int leg_pin_l, int leg_pin_r,
                int player_rx, int player_tx);
        void begin();
        void move_antennae();
        void move_wings();
        void move_legs();
        void vol_up();
        void vol_down();
        void set_vol(int vol);
        void speak(int voice_line);
        int get_player_status();
        bool is_player_available();
        // bool is_player_speaking();
    private:
        int _antennae_pin_l, _antennae_pin_r;
        int _wing_pin_1, _wing_pin_2;
        int _player_rx, _player_tx;
        int _leg_pin_l, _leg_pin_r;
        Servo _leg_servo_l, _leg_servo_r;
        DFRobotDFPlayerMini _player;
        // bool _player_speaking;
};

#endif
