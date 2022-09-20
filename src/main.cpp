#include <Arduino.h>
#include <config.h>
#include <ImageData.h>
#include <IotWebConf.h>
#include <IotWebConfTParameter.h>
#include <PCF8574.h>

#define STRING_LEN 128
#define NUMBER_LEN 32

// -- Method declarations.
void handleRoot();
void handleCSS();
// -- Callback methods.
void configSaved();

DNSServer dnsServer;
WebServer server(80);

struct ModeData
{
  unsigned int minDelayTime;
  unsigned int maxDelayTime;
  byte minSticksNumber;
  byte maxSticksNumber;
};

ModeData Modes[5];

IotWebConf iotWebConf(WIFI_AP_SSID, &dnsServer, &server, WIFI_AP_DEFAULT_PASSWORD, CONFIG_VERSION);

// -- HTML element will be added inside the body element.

iotwebconf::ParameterGroup mode0 = iotwebconf::ParameterGroup("mode0", "Mode 0");
iotwebconf::IntTParameter<uint16_t> minDelayTimer_0 =
    iotwebconf::Builder<iotwebconf::IntTParameter<uint16_t>>("minDelayTimer_0").label("Min Delay Timer [ms]").defaultValue(2000).min(10).max(30000).step(10).placeholder("10..30000").build();
iotwebconf::IntTParameter<uint16_t> maxDelayTimer_0 =
    iotwebconf::Builder<iotwebconf::IntTParameter<uint16_t>>("maxelayTimer_0").label("Max Delay Timer [ms]").defaultValue(5000).min(10).max(30000).step(10).placeholder("10..30000").build();
iotwebconf::IntTParameter<uint16_t> minStickNumber_0 =
    iotwebconf::Builder<iotwebconf::IntTParameter<uint16_t>>("minStickNumber_0").label("Min Stick Number [n]").defaultValue(1).min(1).max(12).step(1).placeholder("1..12").build();
iotwebconf::IntTParameter<uint16_t> maxStickNumber_0 =
    iotwebconf::Builder<iotwebconf::IntTParameter<uint16_t>>("maxStickNumber_0").label("Max Stick Number [n]").defaultValue(1).min(1).max(12).step(1).placeholder("1..12").build();

iotwebconf::ParameterGroup mode1 = iotwebconf::ParameterGroup("mode1", "Mode 1");
iotwebconf::IntTParameter<uint16_t> minDelayTimer_1 =
    iotwebconf::Builder<iotwebconf::IntTParameter<uint16_t>>("minDelayTimer_1").label("Min Delay Timer [ms]").defaultValue(2000).min(10).max(30000).step(10).placeholder("10..30000").build();
iotwebconf::IntTParameter<uint16_t> maxDelayTimer_1 =
    iotwebconf::Builder<iotwebconf::IntTParameter<uint16_t>>("maxelayTimer_1").label("Max Delay Timer [ms]").defaultValue(5000).min(10).max(30000).step(10).placeholder("10..30000").build();
iotwebconf::IntTParameter<uint16_t> minStickNumber_1 =
    iotwebconf::Builder<iotwebconf::IntTParameter<uint16_t>>("minStickNumber_1").label("Min Stick Number [n]").defaultValue(1).min(1).max(12).step(1).placeholder("1..12").build();
iotwebconf::IntTParameter<uint16_t> maxStickNumber_1 =
    iotwebconf::Builder<iotwebconf::IntTParameter<uint16_t>>("maxStickNumber_1").label("Max Stick Number [n]").defaultValue(1).min(1).max(12).step(1).placeholder("1..12").build();

iotwebconf::ParameterGroup mode2 = iotwebconf::ParameterGroup("mode2", "Mode 2");
iotwebconf::IntTParameter<uint16_t> minDelayTimer_2 =
    iotwebconf::Builder<iotwebconf::IntTParameter<uint16_t>>("minDelayTimer_2").label("Min Delay Timer [ms]").defaultValue(2000).min(10).max(30000).step(10).placeholder("10..30000").build();
iotwebconf::IntTParameter<uint16_t> maxDelayTimer_2 =
    iotwebconf::Builder<iotwebconf::IntTParameter<uint16_t>>("maxelayTimer_2").label("Max Delay Timer [ms]").defaultValue(5000).min(10).max(30000).step(10).placeholder("10..30000").build();
iotwebconf::IntTParameter<uint16_t> minStickNumber_2 =
    iotwebconf::Builder<iotwebconf::IntTParameter<uint16_t>>("minStickNumber_2").label("Min Stick Number [n]").defaultValue(1).min(1).max(12).step(1).placeholder("1..12").build();
iotwebconf::IntTParameter<uint16_t> maxStickNumber_2 =
    iotwebconf::Builder<iotwebconf::IntTParameter<uint16_t>>("maxStickNumber_2").label("Max Stick Number [n]").defaultValue(1).min(1).max(12).step(1).placeholder("1..12").build();

iotwebconf::ParameterGroup mode3 = iotwebconf::ParameterGroup("mode3", "Mode 3");
iotwebconf::IntTParameter<uint16_t> minDelayTimer_3 =
    iotwebconf::Builder<iotwebconf::IntTParameter<uint16_t>>("minDelayTimer_3").label("Min Delay Timer [ms]").defaultValue(2000).min(10).max(30000).step(10).placeholder("10..30000").build();
iotwebconf::IntTParameter<uint16_t> maxDelayTimer_3 =
    iotwebconf::Builder<iotwebconf::IntTParameter<uint16_t>>("maxelayTimer_3").label("Max Delay Timer [ms]").defaultValue(5000).min(10).max(30000).step(10).placeholder("10..30000").build();
iotwebconf::IntTParameter<uint16_t> minStickNumber_3 =
    iotwebconf::Builder<iotwebconf::IntTParameter<uint16_t>>("minStickNumber_3").label("Min Stick Number [n]").defaultValue(1).min(1).max(12).step(1).placeholder("1..12").build();
iotwebconf::IntTParameter<uint16_t> maxStickNumber_3 =
    iotwebconf::Builder<iotwebconf::IntTParameter<uint16_t>>("maxStickNumber_3").label("Max Stick Number [n]").defaultValue(1).min(1).max(12).step(1).placeholder("1..12").build();

iotwebconf::ParameterGroup mode4 = iotwebconf::ParameterGroup("mode4", "Mode 4");
iotwebconf::IntTParameter<uint16_t> minDelayTimer_4 =
    iotwebconf::Builder<iotwebconf::IntTParameter<uint16_t>>("minDelayTimer_4").label("Min Delay Timer [ms]").defaultValue(2000).min(10).max(30000).step(10).placeholder("10..30000").build();
iotwebconf::IntTParameter<uint16_t> maxDelayTimer_4 =
    iotwebconf::Builder<iotwebconf::IntTParameter<uint16_t>>("maxelayTimer_4").label("Max Delay Timer [ms]").defaultValue(5000).min(10).max(30000).step(10).placeholder("10..30000").build();
iotwebconf::IntTParameter<uint16_t> minStickNumber_4 =
    iotwebconf::Builder<iotwebconf::IntTParameter<uint16_t>>("minStickNumber_4").label("Min Stick Number [n]").defaultValue(1).min(1).max(12).step(1).placeholder("1..12").build();
iotwebconf::IntTParameter<uint16_t> maxStickNumber_4 =
    iotwebconf::Builder<iotwebconf::IntTParameter<uint16_t>>("maxStickNumber_4").label("Max Stick Number [n]").defaultValue(1).min(1).max(12).step(1).placeholder("1..12").build();

boolean needReset = false;

unsigned long starttime;
unsigned long APTIMEAVALIABLE = 300000;
bool APOfflineMode = false;

// Game Data
unsigned int Magnetstate[12];
unsigned long Delaysequence[12];
byte Sequencelength;
byte MachineState = 0;
unsigned long StartDelay;
byte GameSequence;
unsigned long Gametime;
unsigned long ButtonTimer;
unsigned long WakupTime;

// Light Timer
byte LightMachineStateOld;
byte LightState;
unsigned long LightDelayTimer;
byte LightBuffer;
unsigned int OutputRegister;
unsigned long StartLedDelayTimer;

void CalculateSequence();
int GetModeSelection();
bool GameRunningFunc();
void ActivateMagnets();
void DeactivateMagnets();
void SetMagnetOutputs(unsigned int OutputState);
void SetupBlinkLights();
void UpdateOutputs();
void SetupLights(byte Lights);

#define InputMode1 D5
#define InputMode2 D1
#define InputMode3 D6
#define InputMode4 D2

#define InputStartbutton D7

#define OutStartLed D0

#define SCANI2C 0
#ifdef SCANI2C
void ScanI2C();
#endif

#define I2C_SDA_PIN D3 // SDA;  // i2c SDA Pin
#define I2C_SCL_PIN D4 // SCL;  // i2c SCL Pin

#define IOEXPANDER_ADDRESS_1 0x24
#define IOEXPANDER_ADDRESS_2 0x20

PCF8574 IOExpander_1;
PCF8574 IOExpander_2;

void setup()
{
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting up...");

  Wire.begin((int)I2C_SDA_PIN, (int)I2C_SCL_PIN);

#ifdef SCANI2C
  ScanI2C();
#endif

  // I2C IOExpander,
  IOExpander_1.init((int)I2C_SDA_PIN, (int)I2C_SCL_PIN, IOEXPANDER_ADDRESS_1);
  IOExpander_2.init((int)I2C_SDA_PIN, (int)I2C_SCL_PIN, IOEXPANDER_ADDRESS_2);

  mode0.addItem(&minDelayTimer_0);
  mode0.addItem(&maxDelayTimer_0);
  mode0.addItem(&minStickNumber_0);
  mode0.addItem(&maxStickNumber_0);

  mode1.addItem(&minDelayTimer_1);
  mode1.addItem(&maxDelayTimer_1);
  mode1.addItem(&minStickNumber_1);
  mode1.addItem(&maxStickNumber_1);

  mode2.addItem(&minDelayTimer_2);
  mode2.addItem(&maxDelayTimer_2);
  mode2.addItem(&minStickNumber_2);
  mode2.addItem(&maxStickNumber_2);

  mode3.addItem(&minDelayTimer_3);
  mode3.addItem(&maxDelayTimer_3);
  mode3.addItem(&minStickNumber_3);
  mode3.addItem(&maxStickNumber_3);

  mode4.addItem(&minDelayTimer_4);
  mode4.addItem(&maxDelayTimer_4);
  mode4.addItem(&minStickNumber_4);
  mode4.addItem(&maxStickNumber_4);

  iotWebConf.addParameterGroup(&mode0);
  iotWebConf.addParameterGroup(&mode1);
  iotWebConf.addParameterGroup(&mode2);
  iotWebConf.addParameterGroup(&mode3);
  iotWebConf.addParameterGroup(&mode4);

  iotWebConf.setConfigSavedCallback(&configSaved);

  iotWebConf.getWifiParameterGroup()->visible = false;
  iotWebConf.getThingNameParameter()->visible = false;
  iotWebConf.getWifiPasswordParameter()->visible = false;
  iotWebConf.getWifiSsidParameter()->visible = false;
  iotWebConf.getApPasswordParameter()->visible = false;

  // -- Initializing the configuration.
  bool validConfig = iotWebConf.init();
  if (!validConfig)
  {
    /*
    iotWebConf.getThingNameParameter()->visible = true;
    iotWebConf.getWifiPasswordParameter()->visible = true;
    iotWebConf.getWifiSsidParameter()->visible = true;
    iotWebConf.getApPasswordParameter()->visible = true;
    */
  }

  randomSeed(millis());

  iotWebConf.forceApMode(true);

  // -- Set up required URL handlers on the web server.
  server.on("/", handleRoot);
  server.on("/main.css", handleCSS);
  server.on("/config", []
            { iotWebConf.handleConfig(); });
  server.onNotFound([]()
                    { iotWebConf.handleNotFound(); });

  Serial.println("Ready.");

  Modes[0].minDelayTime = minDelayTimer_0.value();
  Modes[0].maxDelayTime = maxDelayTimer_0.value();
  Modes[0].minSticksNumber = minStickNumber_0.value();
  Modes[0].maxSticksNumber = maxStickNumber_0.value();

  Modes[1].minDelayTime = minDelayTimer_1.value();
  Modes[1].maxDelayTime = maxDelayTimer_1.value();
  Modes[1].minSticksNumber = minStickNumber_1.value();
  Modes[1].maxSticksNumber = maxStickNumber_1.value();

  Modes[2].minDelayTime = minDelayTimer_2.value();
  Modes[2].maxDelayTime = maxDelayTimer_2.value();
  Modes[2].minSticksNumber = minStickNumber_2.value();
  Modes[2].maxSticksNumber = maxStickNumber_2.value();

  Modes[3].minDelayTime = minDelayTimer_3.value();
  Modes[3].maxDelayTime = maxDelayTimer_3.value();
  Modes[3].minSticksNumber = minStickNumber_3.value();
  Modes[3].maxSticksNumber = maxStickNumber_3.value();

  Modes[4].minDelayTime = minDelayTimer_4.value();
  Modes[4].maxDelayTime = maxDelayTimer_4.value();
  Modes[4].minSticksNumber = minStickNumber_4.value();
  Modes[4].maxSticksNumber = maxStickNumber_4.value();

  pinMode(InputMode1, INPUT_PULLUP);
  pinMode(InputMode2, INPUT_PULLUP);
  pinMode(InputMode3, INPUT_PULLUP);
  pinMode(InputMode4, INPUT_PULLUP);

  pinMode(InputStartbutton, INPUT_PULLUP);

  pinMode(OutStartLed, OUTPUT);

  starttime = millis();
  MachineState = 0;
}

void loop()
{
  // -- doLoop should be called as frequently as possible.
  if (needReset)
  {
    // Doing a chip reset caused by config changes
    printf("Rebooting after 1 second.");
    delay(1000);
    ESP.restart();
  }
  iotWebConf.doLoop();
  if (starttime + APTIMEAVALIABLE < millis() && !APOfflineMode)
  {
    APOfflineMode = true;
    iotWebConf.goOffLine();
  }

  // Game Statemachine
  switch (MachineState)
  {
  case 0:
    Serial.println("Sate 0 - Go to Sleep");
    // Startup / Start Sleep
    DeactivateMagnets();
    MachineState++;
    break;
  case 1:
    // Serial.println("State 1 - Sleep");
    //  Standby
    if (digitalRead(InputStartbutton) == LOW)
    {
      ButtonTimer = millis();
      MachineState++;
    }
    break;
  case 2:
    Serial.println("State 2 - Wakeup");
    // Ready for Play - Magnets active (5min)
    ActivateMagnets();
    WakupTime = millis();
    MachineState++;
    break;
  case 3:
    // Serial.println("State 3 - Wakeup delay");
    if (digitalRead(InputStartbutton) == HIGH && (millis() - ButtonTimer > 500))
    {
      MachineState++;
    }
    break;
  case 4:
    // Serial.println("State 4 - Ready for Game start");
    //  Wait for Game Start
    if (digitalRead(InputStartbutton) == LOW)
    {
      ButtonTimer = millis();
      MachineState++;
    }
    if (millis() - WakupTime > 300000)
    {
      MachineState = 0;
    }
    break;
  case 5:
    Serial.println("State 5 - Game Started ");
    // Prepare Game Calculate Sequence
    CalculateSequence();
    StartDelay = millis();
    GameSequence = 0;
    MachineState++;
    break;
  case 6:
    // Serial.println("State 6 - Game Start Delay");
    if (millis() - StartDelay > 5000)
    {
      Gametime = millis();
      MachineState++;
    }
    break;
  case 7:
    // Serial.println("state 7 - Game Running");
    //  Game Running
    if (digitalRead(InputStartbutton) == LOW && (millis() - ButtonTimer > 500))
    {
      MachineState = 2;
      ButtonTimer = millis();
    }
    if (!GameRunningFunc())
    {
      MachineState = 8;
      ButtonTimer = millis();
    }
    break;
  case 8:
    if (millis() - ButtonTimer > 1000)
    {
      MachineState = 0; // Sleep Mode after Game
    }
    break;
  default:
    MachineState = 0;
    break;
  }

  SetupBlinkLights();
}

/**
 * Handle web requests to "/" path.
 */
void handleRoot()
{
  // -- Let IotWebConf test and handle captive portal requests.
  if (iotWebConf.handleCaptivePortal())
  {
    // -- Captive portal request were already served.
    return;
  }
  String s = "<!DOCTYPE html><html lang=\"en\"><head><link rel=\"stylesheet\" type=\"text/css\" href=\"main.css\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>";
  s += "<title>Catch the Stick Werte</title></head><body>";
  s += "<div class=\"main\">";
  s += "<h1>Kiwwelschisser Catch The Stick</h1>";
  s += FPSTR(CUSTOMHTML_BODY_INNER_LOGO);

  s += "<h2>Aktueller Modus: " + String(GetModeSelection()) + "</h2>";
  for (byte i = 0; i < 5; i++)
  {
    s += "<h2>Werte Modus: " + String(i) + "</h2>";
    s += "<ul>";
    s += "<li>Min Delay [ms]: ";
    s += String(Modes[i].minDelayTime);
    s += "<li>Max Delay [ms]: ";
    s += String(Modes[i].maxDelayTime);
    s += "<li>Min Sticks [n]: ";
    s += String(Modes[i].minSticksNumber);
    s += "<li>Max Sticks [n]: ";
    s += String(Modes[i].maxSticksNumber);
    s += "</ul>";
  }
  s += "Wechsel zu <a href='config'>Einstellungen</a> um die Werte anzupassen.";
  s += "</div>";
  s += "</body></html>\n";

  server.send(200, "text/html", s);
}

void handleCSS()
{
  String s = ".main{text-align: center;}";
  s += "body {background-color: powderblue;}";
  server.send(200, "text/css", s);
}

void configSaved()
{
  Serial.println("Configuration was updated.");
  needReset = true;
}

void CalculateSequence()
{
  int Mode = GetModeSelection();
  Serial.print("Mode Selected: ");
  Serial.println(Mode);
  unsigned long tmpDelay;
  byte tmpsticks;
  byte actualcycle = 0;
  byte Magnetnumber;

  randomSeed(millis());

  for (byte i = 0; i < 12; i++)
  {
    Magnetstate[i] = 0;
    Delaysequence[i] = 0;
  }

  bool bitsetdone;
  while (Magnetstate[actualcycle] <= 4095)
  {
    tmpDelay = random(Modes[Mode].minDelayTime, Modes[Mode].maxDelayTime);
    tmpsticks = random(Modes[Mode].minSticksNumber, Modes[Mode].maxSticksNumber + 1);
    Delaysequence[actualcycle] = tmpDelay;

    if (actualcycle > 0)
    {
      Magnetstate[actualcycle] = Magnetstate[actualcycle - 1];
    }

    for (byte i = 0; i < tmpsticks; i++)
    {
      bitsetdone = false;
      while (!bitsetdone && Magnetstate[actualcycle] < 4095)
      {
        Magnetnumber = random(0, 12);
        if (bitRead(Magnetstate[actualcycle], Magnetnumber) == 0)
        {
          bitSet(Magnetstate[actualcycle], Magnetnumber);
          bitsetdone = true;
        }
      }
    }
    if (Magnetstate[actualcycle] >= 4095)
    {
      break;
    }
    actualcycle++;
  }
  Sequencelength = actualcycle;

  Serial.println("End Of Calculation");

  for (byte i = 0; i <= Sequencelength; i++)
  {
    Serial.print(i);
    Serial.print(" - ");
    for (byte x = 0; x < 12; x++)
    {
      if (bitRead(Magnetstate[i], x))
      {
        Serial.print("X ");
      }
      else
      {
        Serial.print("O ");
      }
    }
    Serial.print(" - ");
    Serial.print(Delaysequence[i]);
    Serial.println(" ms");
  }
}

int GetModeSelection()
{
  if (digitalRead(InputMode1) == LOW)
  {
    return 1;
  };
  if (digitalRead(InputMode2) == LOW)
  {
    return 2;
  };
  if (digitalRead(InputMode3) == LOW)
  {
    return 3;
  };
  if (digitalRead(InputMode4) == LOW)
  {
    return 4;
  };
  return 0;
}

bool GameRunningFunc()
{
  // Drop Delay according to Sequence
  if (millis() - Gametime < Delaysequence[GameSequence])
  {
    return true;
  }

  // Set Magnet Outputs
  SetMagnetOutputs(Magnetstate[GameSequence]);
  /*
  for (byte x = 0; x < 12; x++)
  {
    if (bitRead(Magnetstate[GameSequence], x))
    {
      Serial.print("X");
    }
    else
    {
      Serial.print("O");
    }
  }
  Serial.print(" - ");
  Serial.print(Delaysequence[GameSequence]);
  Serial.println(" ms");
  */
  Gametime = millis();

  GameSequence++;
  if (GameSequence > Sequencelength)
  {
    Serial.println("End of Game");
    WakupTime = millis();
    return false;
  }
  return true;
}

void ActivateMagnets()
{
  for (byte x = 0; x < 12; x++)
  {
    bitSet(OutputRegister, x);
  }
  UpdateOutputs();
}

void DeactivateMagnets()
{
  for (byte x = 0; x < 12; x++)
  {
    bitClear(OutputRegister, x);
  }
  UpdateOutputs();
}

void SetMagnetOutputs(unsigned int OutputState)
{
  // Serial.print("Mag");
  for (byte x = 0; x < 12; x++)
  {
    // Serial.print(bitRead(OutputState,x));
    if (bitRead(OutputState, x))
    {
      bitClear(OutputRegister, x);
    }
  }
  // Serial.println();
  UpdateOutputs();
}

void SetupBlinkLights()
{
  if (MachineState != LightMachineStateOld)
  {
    Serial.print("LightState changed to:");
    Serial.println(MachineState);
    LightMachineStateOld = MachineState;
    LightState = 0;
    LightBuffer = 0;
  }

  switch (MachineState)
  {
  case 1:
    // Game Sleep
    switch (LightState)
    {
    case 0:
      LightBuffer = 1;
      SetupLights(LightBuffer);
      break;
    case 1:
      if (millis() - LightDelayTimer > 2000)
      {
        LightState--;
        LightBuffer <<= 1;
        SetupLights(LightBuffer);
        if (LightBuffer >= 8)
        {
          LightState++;
        }
      }
      break;
    case 2:
      if (millis() - LightDelayTimer > 2000)
      {
        LightState--;
        LightBuffer >>= 1;
        SetupLights(LightBuffer);
        if (LightBuffer <= 0)
        {
          LightState++;
        }
      }
      break;
    case 3:
      if (millis() - LightDelayTimer > 2000)
      {
        LightState = 0;
      }
    default:
      break;
    }
    break;
  case 4:
    // Game Ready Standby
    switch (LightState)
    {
    case 0:
      LightBuffer = 1;
      SetupLights(LightBuffer);
      break;
    case 1:
      if (millis() - LightDelayTimer > 200)
      {
        LightState--;
        LightBuffer <<= 1;
        SetupLights(LightBuffer);
        if (LightBuffer >= 8)
        {
          LightState++;
        }
      }
      break;
    case 2:
      if (millis() - LightDelayTimer > 200)
      {
        LightState--;
        LightBuffer >>= 1;
        SetupLights(LightBuffer);
        if (LightBuffer <= 1)
        {
          LightState = 0;
        }
      }
      break;
    default:
      break;
    }
    break;
  case 6:
    // Game Start Delay
    switch (LightState)
    {
    case 0:
      LightBuffer = 0;
      SetupLights(LightBuffer);
      LightBuffer++;
      break;
    case 1:
      if (millis() - LightDelayTimer > 1000)
      {
        LightState--;

        SetupLights(LightBuffer);
        LightBuffer <<= 1;
        LightBuffer = LightBuffer + 1;

        if (LightBuffer >= 16)
        {
          LightState++;
        }
      }
      break;
    default:
      break;
    }

    break;
  case 7:
    // Game Running
    switch (LightState)
    {
    case 0:
      LightBuffer = 0;
      SetupLights(LightBuffer);
      LightBuffer++;
      break;
    case 1:
      unsigned int buffer;
      buffer = random(800, 1500);
      if (millis() - LightDelayTimer > buffer)
      {
        LightState--;
        LightBuffer = random(0, 15);
        SetupLights(LightBuffer);
      }
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }

  switch (MachineState)
  {
  case 1:
    // Game Sleep
    if (millis() - StartLedDelayTimer > 2000)
    {
      StartLedDelayTimer = millis();
      digitalWrite(OutStartLed, !digitalRead(OutStartLed));
    }
    break;
  case 4:
    // Game Ready Standby
    if (millis() - StartLedDelayTimer > 200)
    {
      StartLedDelayTimer = millis();
      digitalWrite(OutStartLed, !digitalRead(OutStartLed));
    }
    break;
  case 6:
    // Game Start Delay
    if (millis() - StartLedDelayTimer > 500)
    {
      StartLedDelayTimer = millis();
      digitalWrite(OutStartLed, !digitalRead(OutStartLed));
    }
    break;
  case 7:
    // Game Running
    if (millis() - StartLedDelayTimer > 500)
    {
      StartLedDelayTimer = millis();
      digitalWrite(OutStartLed, !digitalRead(OutStartLed));
    }
    break;
  default:
    break;
  }
}

void UpdateOutputs()
{
  IOExpander_1.write(byte(OutputRegister));
  IOExpander_2.write(byte(OutputRegister >> 8));
  /*
  for (byte i = 0; i < 16; i++)
  {
    Serial.print(bitRead(OutputRegister, i));
  }
  Serial.print(" ");
  Serial.println(OutputRegister);
  */
}

void SetupLights(byte Lights)
{
  // Serial.println(Lights);
  for (byte x = 0; x < 4; x++)
  {
    bitWrite(OutputRegister, x + 12, bitRead(Lights, x));
  }
  UpdateOutputs();
  LightDelayTimer = millis();
  LightState++;
}

#ifdef SCANI2C
void ScanI2C()
{
  Serial.println("\nI2C Scanner");

  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++)
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      nDevices++;

      Serial.print("Device found @ 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");
    }
    else if (error == 4)
    {
      Serial.print("Unknow error @ 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
  {
    Serial.println("No I2C devices found\n");
  }
  else
  {
    Serial.println("done\n");
  }
}
#endif