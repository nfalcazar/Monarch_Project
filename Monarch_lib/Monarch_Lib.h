/*
    Monarch_Lib.h - library for controlling the animatronic monarch butterfly
    Created by the Cal Poly SLO Monarch capstone project team on Jan 12, 2023
    Just wing it!
*/

#ifndef MONARCH_LIB_H
#define MONARCH_LIB_H



#define HELLO_AUDIO_INDEX 1
#define BODY_AUDIO_INDEX 2
#define ANTENNAE_AUDIO_INDEX 3
#define WINGS_AUDIO_INDEX 4
#define CYCLE_AUDIO_INDEX 5
#define MIGRATION_WHY_AUDIO_INDEX 6
#define MIGRATION_WHERE_AUDIO_INDEX 7
#define BODY_SURVIVE_AUDIO_INDEX 8
#define HELP_HOW_AUDIO_INDEX 9
#define DIET_AUDIO_INDEX 10
#define ENDANGERED_AUDIO_INDEX 11
#define HABITAT_LOCATIONS_AUDIO_INDEX 12
#define JOB_AUDIO_INDEX 13
#define LEGS_AUDIO_INDEX 14

// Not implemented yet!
#define WAKE_AUDIO_INDEX 101
#define MISUNDERSTOOD_AUDIO_INDEX_102

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
        int get_player_state();
        bool is_player_available();
        bool is_player_speaking();
    private:
        int _antennae_pin_l, _antennae_pin_r;
        int _wing_pin_1, _wing_pin_2;
        int _player_rx, _player_tx;
        int _leg_pin_l, _leg_pin_r;
        Servo _leg_servo_l, _leg_servo_r;
        DFRobotDFPlayerMini _player;
};



#endif
