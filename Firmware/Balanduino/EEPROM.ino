#include "EEPROMAnything.h"

cfg_t cfg; //  Struct for all the configuration values

bool checkInitializationFlags() {
  uint8_t initFlag;
  EEPROM_readAnything(initFlagsAddr, initFlag);
  if (initFlag != eepromVersion) { // Check if the EEPROM version matches the current one
    restoreEEPROMValues();
    EEPROM_updateAnything(initFlagsAddr, eepromVersion); // After the default values have been restored, set the flag
    return true; // Indicate that the values have been restored
  }
  return false;
}

void readEEPROMValues() {
  EEPROM_readAnything(configAddr, cfg);

  kalman.setQangle(cfg.Qangle);
  kalman.setQbias(cfg.Qbias);
  kalman.setRmeasure(cfg.Rmeasure);
}

void updateConfig() {
  EEPROM_updateAnything(configAddr, cfg);

  kalman.setQangle(cfg.Qangle);
  kalman.setQbias(cfg.Qbias);
  kalman.setRmeasure(cfg.Rmeasure);
}

void restoreEEPROMValues() {
  cfg.P = 10.0;
  cfg.I = 2.0;
  cfg.D = 3.0;

  cfg.targetAngle = 180.0;
  cfg.backToSpot = 1;
  cfg.controlAngleLimit = 7;
  cfg.turningLimit = 25;

  cfg.Qangle = 0.001;
  cfg.Qbias = 0.003;
  cfg.Rmeasure = 0.03;

  cfg.accYzero = cfg.accZzero = 0;
  cfg.leftMotorScaler = cfg.rightMotorScaler = 1;

  updateConfig();
}
