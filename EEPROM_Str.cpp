#include "EEPROM_Str.hpp"
#include <iostream>
#include <EEPROM.h>

EEPROM_Str::EEPROM_Str(int s) {
    Serial.print("Creating memory of size: ");
    Serial.println(size);
    size = s;
    lastRead = 0;
    memory = new char [size]();
    EEPROM.begin(size);
    import();
}

EEPROM_Str::~EEPROM_Str() {
}

void EEPROM_Str::import() {
    Serial.println("Importing memory...");
    for (int i = 0; i < size; i++) {
        memory[i] = EEPROM.read(i);
    }
    Serial.println("Memory imported");

    for (int i = 0; i < size;) {
        int len = strlen(memory+i);
        int len2 = strlen(memory+i+len+1);
        
        if (len == 0 || len2 == 0) break;
        
        lookup[memory+i] = memory+i+len+1;
        i+=len+len2+2;
        lastRead = i;
    }
    Serial.print("Last read: ");
    Serial.println(lastRead);
}

bool EEPROM_Str::hasKey(char* key) {
    Serial.print("Checking if key is in EEPROM: ");
    Serial.println(key);
    for (auto elem: lookup) {
        if (strcmp(elem.first, key) == 0) {
            return 1;
        }
    }
    return 0;
}

char *EEPROM_Str::getString(char* key) {
    Serial.print("Getting key from EEPROM: ");
    Serial.println(key);
    for (auto elem: lookup) {
        if (strcmp(elem.first, key) == 0) {
            return elem.second;
        }
    }
    return key;
}

void EEPROM_Str::add(char* key, char* value) {
    Serial.println("Adding value to EEPROM");
    for (int i = 0; i <= strlen(key); i++) {
        EEPROM.write(lastRead++, key[i]);
    }
    for (int i = 0; i <= strlen(value); i++) {
        EEPROM.write(lastRead++, value[i]);
    }
    EEPROM.commit();
    import();
}

void EEPROM_Str::clear() {
    Serial.println("Clearing EEPROM");
    lastRead = 0;
    for (int i = 0; i < size; i++) {
        EEPROM.write(i, 0);
    }
    EEPROM.commit();
    import();
}

void EEPROM_Str::print() {
    Serial.println();
    Serial.println("PRINTING EEPROM");
    for (int i = 0; i < size; i++) {
        if (strcmp(&memory[i], "\0")) {
            Serial.print(" ");
        } else {
            Serial.print(memory[i]);
        }
    }
    Serial.println("formatted:");
    for (auto elem :lookup) {
        Serial.print(elem.first);
        Serial.print(" ");
        Serial.print(elem.second);
        Serial.println();
    }
    Serial.println("END OF EEPROM");
    Serial.println();
}
