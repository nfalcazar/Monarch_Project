#include <Arduino.h>
#include <ArduinoBLE.h>

#include <Picovoice_EN.h>
#include "pv_porcupine_params.h"
#include "Butterfly_en_cortexm_v2_1_0.h"


#define UART_BAUDRATE       115200
#define ENABLE_BLE_STRING   0

//TODO: Clean up Bluetooth command proc when format determined

//Bluetooth Init
static const char* ble_key = "19B10000-E8F2-537E-4F6C-D104768A1214";
BLEService monarchService(ble_key);  // Bluetooth® Low Energy LED Service
BLEByteCharacteristic switchCharacteristic(ble_key, BLERead | BLEWrite);

#define BLE_RCV_BUFF_LEN    100
char ble_rcv_buff[BLE_RCV_BUFF_LEN];
bool ble_is_conn = false;


//Picovoice Init
#define MEMORY_BUFFER_SIZE (70 * 1024)
static const char* ACCESS_KEY = "Xui3OgJwFmO9R6CPi9r4JLkdkTQsnBA1qpCKqKQITiEG+t4Z7mgHvw==";
static pv_picovoice_t *handle = NULL;
static int8_t memory_buffer[MEMORY_BUFFER_SIZE] __attribute__((aligned(16)));
static const float PORCUPINE_SENSITIVITY = 0.75f;
static const float RHINO_SENSITIVITY = 0.5f;

static void wake_word_callback(void) {
    //Send CMD to MEGA to output detection
    Serial1.write("wake");
    Serial.println("Wakeword Detected!");

    delay(500);
}

static void inference_callback(pv_inference_t *inference) {
    String cmd = "";

    if (!(inference->is_understood)) {
        Serial1.write("error");
    }
    else {
        cmd += String(inference->intent);

        //If there are slots in expression, add all slot values to cmd
        for (int i = 0; i < inference->num_slots; i++) {
            cmd += (String(" ") + String(inference->values[i])); 
        }

        //Send result to Mega thru UART
        Serial1.print(cmd);
    }

    Serial.print("Recieved voice cmd: ");
    Serial.println(cmd);
    pv_inference_delete(inference);
}


void setup() {
    Serial.begin(9600);
    
    //Picovoice Setup
    pv_status_t status = pv_audio_rec_init();
    if (status != PV_STATUS_SUCCESS) {
        Serial.print("Audio init failed with ");
        Serial.println(pv_status_to_string(status));
        while (1);  //Program fails if Picovoice fails to init
    } else {
        Serial.println("Picovoice Audio Init successful.");
    }

    status = pv_picovoice_init(
        ACCESS_KEY,
        MEMORY_BUFFER_SIZE,
        memory_buffer,
        sizeof(KEYWORD_ARRAY),
        KEYWORD_ARRAY,
        PORCUPINE_SENSITIVITY,
        wake_word_callback,
        sizeof(CONTEXT_ARRAY),
        CONTEXT_ARRAY,
        RHINO_SENSITIVITY,
        1.0,
        true,
        inference_callback,
        &handle);
    if (status != PV_STATUS_SUCCESS) {
        Serial.print("Picovoice init failed with ");
        Serial.println(pv_status_to_string(status));
        while (1);  //Program fails if Picovoice fails to init
    } else {
        Serial.println("Picovoice Object init successful.");
    }

    const char *rhino_context = NULL;
    status = pv_picovoice_context_info(handle, &rhino_context);
    if (status != PV_STATUS_SUCCESS) {
        Serial.print("retrieving context info failed with");
        Serial.println(pv_status_to_string(status));
        while (1);  //Program fails if Picovoice fails to init
    } else {
        Serial.println("Picovoice Context init successful.");
    }

    //Bluetooth setup
    if (!BLE.begin()) {
        Serial.println("starting Bluetooth® Low Energy module failed!");
        //while (1);    //Shouldn't just kill program if Bluetooth fails
    }
    else {
        BLE.setLocalName("Butterfly");
        BLE.setAdvertisedService(monarchService);
        monarchService.addCharacteristic(switchCharacteristic);
        BLE.addService(monarchService);
        switchCharacteristic.writeValue(0);
        BLE.advertise();

        Serial.println("Bluetooth init successful.");
    }

    //Output to Mega setup
    Serial1.begin(UART_BAUDRATE);
    while(!Serial1);
}

void loop() {
    BLEDevice ble_connection = BLE.central();
    if (ble_connection) {
        if(ble_is_conn == false)
            Serial.println("Found Bluetooth Connection.");

        ble_is_conn = true;
    }

    //If bluetooth connected, use bluetooth, otherwise use picovoice
    if (ble_is_conn) {
        if (!ble_connection.connected()) {
            ble_is_conn = false;

            Serial.println("Lost Bluetooth connection, defaulting back to Picovoice.");
            return;
        }
        
        if (switchCharacteristic.written()) {
            #if (ENABLE_BLE_STRING)
            //Grab string from BLE
            int cmd_len = switchCharacteristic.valueLength();
            if (cmd_len > BLE_RCV_BUFF_LEN - 1) {
                Serial.println("Received BT command is too large. cmd: ");
                char *res;
                sprintf(res,"len: %d   msg: %s", cmd_len, (char *)switchCharacteristic.value()); 
                Serial.println(res);
                
                return;
            }
            strncpy(ble_rcv_buff, (char *)switchCharacteristic.value(), cmd_len);

            ble_rcv_buff[cmd_len] = '\0';
            Serial1.print(ble_rcv_buff);   //Forward cmd to Mega

            Serial.print("Recived Bluetooth command: ");
            Serial.println(ble_rcv_buff);
            #else
            //Grab Int from BLE
            int value = switchCharacteristic.value();
            String res = String(value);

            Serial1.print(res);
            String term_out = String("Got Bluetooth cmd: ") + res;
            Serial.println(term_out);
            #endif
        }
    }
    else {
        //Use Picovoice
        const int16_t *buffer = pv_audio_rec_get_new_buffer();
        if (buffer) {
            const pv_status_t status = pv_picovoice_process(handle, buffer);
            if (status != PV_STATUS_SUCCESS) {
                Serial.print("Picovoice process failed with ");
                Serial.println(pv_status_to_string(status));
                //while(1); //prevent auto term when process fails
            }
        }
    }
}