#include <Arduino.h>
#include <SoftwareSerial.h>

void sendATCommand(String command);
void sendSMS(String number, String message);
void sim7600_on();
void sim7600_off();

#define FULLWATER_PIN 15
#define LOWWATER_PIN 2
#define PUMP_PIN 22
#define MIN_THRESHOLD 500
#define MAX_THRESHOLD 2000
#define MODEM_PWRKEY 4
#define MODEM_FLIGHT 25
#define BUILTIN_LED 12

bool simActive = 0;
bool pumpActive = 0;
bool minThresholdAlertSent = 0;
bool maxThresholdAlertSent = 0;
String mobileNumber = "8308305181";
unsigned long simONCounter;
unsigned long simOFFCounter;

SoftwareSerial sim7600(26, 27);

void setup()
{
  Serial.begin(115200);
  sim7600.begin(9600);
  delay(100);

  pinMode(FULLWATER_PIN, INPUT);
  pinMode(LOWWATER_PIN, INPUT);
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);
  pinMode(MODEM_PWRKEY, OUTPUT);
  pinMode(MODEM_FLIGHT, OUTPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, LOW);

  Serial.print("Checking if SIM7600 Module is Connected and Working Properly");
  sim7600_on();
  while (millis() - simONCounter < 20000)
  {
    Serial.print(".");
    delay(1000);
  }
  simActive = 1;
  sim7600.println("AT");
  delay(1000);
  while (sim7600.available())
  {
    if (sim7600.find("OK"))
    {
      Serial.println(" SIM7600 Module is Connected and Working Properly");
      break;
    }
    else
    {
      Serial.println(" SIM7600 Module is not Connected or Working Properly");
    }
  }

  if (simActive)
  {
    Serial.print("Turning off SIM7600 Module");
    sim7600_off();
    while (millis() - simOFFCounter < 28000)
    {
      Serial.print(".");
      delay(1000);
    }
    Serial.println(" SIM7600 Module is Turned Off");
    simActive = 0;
  }
  else
  {
    Serial.println("Please check the SIM7600 Module, Unplug Power Supply and try again");
    while (1)
    {
      digitalWrite(BUILTIN_LED, HIGH);
      delay(1000);
      digitalWrite(BUILTIN_LED, LOW);
      delay(1000);
    }
  }

  Serial.println("System Setup Completed and Ready to Operate");
  digitalWrite(BUILTIN_LED, HIGH);
}

void loop()
{
  /*
  There are two levels for water detection: the "Full Water" pin and the "Low Water" pin. For both pins, if water has reached the specified level, the analog reading will give a value less than MIN_THRESHOLD. Otherwise, it will give a value greater than MAX_THRESHOLD.
  If the water rises to the low water level, we should send an SMS message. Similarly, if the water rises to the full water level, we should send an SMS message and turn on the pump until the water level settles back to the low water level. Once the water level drops back to the low water level, we will turn off the pump (if it is on) and send an SMS message indicating the change.
  The SIM7600 module will turn on if the water level is above the low water level and will remain on until the water level falls below the low water level again. Once the water level drops below the low water level, the SIM7600 module will be turned off to save power.
  */

  int fullWaterLevel = analogRead(FULLWATER_PIN);
  int lowWaterLevel = analogRead(LOWWATER_PIN);

  if (lowWaterLevel < MIN_THRESHOLD)
  {
    if (fullWaterLevel < MIN_THRESHOLD && !maxThresholdAlertSent)
    {
      digitalWrite(PUMP_PIN, HIGH);
      pumpActive = 1;
      Serial.println("The Water Level has Reached 2nd Threshold, Turned on the Pump...  Sending SMS Alert");
      if (!simActive)
      {
        Serial.print("Turning on SIM7600 Module");
        sim7600_on();
        while (millis() - simONCounter < 20000)
        {
          Serial.print(".");
          delay(1000);
        }
        Serial.println(" SIM7600 Module is Turned On");
        simActive = 1;
      }
      sendSMS(mobileNumber, "The Water Level has Reached 2nd Threshold, Turned on the Pump");
      Serial.println("SMS Alert Sent Successfully");
      maxThresholdAlertSent = 1;
    }
    else if (fullWaterLevel < MIN_THRESHOLD && maxThresholdAlertSent)
    {
      Serial.println("The Water Level is Above 2nd Threshold, Pump is ON");
    }
    else if (fullWaterLevel > MAX_THRESHOLD && !maxThresholdAlertSent)
    {
      if (!minThresholdAlertSent)
      {
        Serial.println("The Water Level has Reached 1st Threshold, Water Starting to Fill...  Sending SMS Alert");
        if (!simActive)
        {
          Serial.print("Turning on SIM7600 Module");
          sim7600_on();
          while (millis() - simONCounter < 20000)
          {
            Serial.print(".");
            delay(1000);
          }
          Serial.println(" SIM7600 Module is Turned On");
          simActive = 1;
        }
        sendSMS(mobileNumber, "The Water Level has Reached 1st Threshold, Water Starting to Fill");
        Serial.println("SMS Alert Sent Successfully");
        minThresholdAlertSent = 1;
      }
      else
      {
        Serial.println("The Water Level is Between 1st and 2nd Threshold, Pump is OFF");
      }
    }
    else if (fullWaterLevel > MAX_THRESHOLD && maxThresholdAlertSent)
    {
      Serial.println("The Water Level is Between 1st and 2nd Threshold, Pump is ON");
    }
  }

  else if (lowWaterLevel > MAX_THRESHOLD)
  {
    if (minThresholdAlertSent && !maxThresholdAlertSent)
    {
      Serial.println("The Water Level has itself reached below 1st Threshold, Pump was not Turned on...  Sending SMS Alert");
      sendSMS(mobileNumber, "The Water Level has itself reached below 1st Threshold, Pump was not Turned on");
      Serial.println("SMS Alert Sent Successfully");
      minThresholdAlertSent = 0;

      if (simActive)
      {
        Serial.print("Turning off SIM7600 Module");
        sim7600_off();
        while (millis() - simOFFCounter < 28000)
        {
          Serial.print(".");
          delay(1000);
        }
        Serial.println(" SIM7600 Module is Turned Off");
        simActive = 0;
      }
    }
    if (maxThresholdAlertSent)
    {
      digitalWrite(PUMP_PIN, LOW);
      pumpActive = 0;
      Serial.println("The Water Level has reached below 1st Threshold, Turned off the Pump...  Sending SMS Alert");
      sendSMS(mobileNumber, "The Water Level has reached below 1st Threshold, Turned off the Pump");
      Serial.println("SMS Alert Sent Successfully");
      maxThresholdAlertSent = 0;
      minThresholdAlertSent = 0;

      if (simActive)
      {
        Serial.print("Turning off SIM7600 Module");
        sim7600_off();
        while (millis() - simOFFCounter < 28000)
        {
          Serial.print(".");
          delay(1000);
        }
        Serial.println(" SIM7600 Module is Turned Off");
        simActive = 0;
      }
    }
    Serial.println("The Water Level is Below 1st Threshold, Pump is OFF");
  }

  delay(1000);
}

void sendATCommand(String command)
{
  sim7600.println(command);
  delay(1000);
  while (sim7600.available())
  {
    Serial.write(sim7600.read());
  }
}

void sendSMS(String number, String message)
{
  delay(1000);
  sendATCommand("AT+CMGF=1");
  sendATCommand("AT+CMGS=\"+91" + number + "\"");
  sendATCommand(message + (char)26);
}

void sim7600_on()
{
  digitalWrite(MODEM_PWRKEY, HIGH);
  delay(300);
  digitalWrite(MODEM_PWRKEY, LOW);
  digitalWrite(MODEM_FLIGHT, HIGH);
  simONCounter = millis();
  delay(5);
}

void sim7600_off()
{
  digitalWrite(MODEM_PWRKEY, HIGH);
  delay(3000);
  digitalWrite(MODEM_PWRKEY, LOW);
  simOFFCounter = millis();
  delay(5);
}