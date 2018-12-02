#ifndef EEPROM_Str_hpp
#define EEPROM_Str_hpp

#include <map>
#include <Arduino.h>

class EEPROM_Str {
  public:
    EEPROM_Str(int size);
    ~EEPROM_Str();
    void import();
    void clear();
    void print();
    void add(char *key, char *value);
    bool hasKey(char *key);
    char *getString(char *key);

  private:
    int lastRead;
    int size;
    char *memory;
    std::map<char*, char*> lookup;
};

#endif
