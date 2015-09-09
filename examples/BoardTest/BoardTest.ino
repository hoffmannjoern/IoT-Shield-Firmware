#include <ParkingShield.h>
#include <Scheduler.h>

Scheduler scheduler;
ParkingShield shield(scheduler);
unsigned char counter = 0;

void setup(void)
{
    Serial.begin(9600);
    scheduler.addTask(output, 1000);
    shield.playMarch();
    shield.playMelody();
}

void loop(void)
{
  buttonS1Handler();
  buttonS2Handler();
  showNumber(counter);
  scheduler.scheduleTasks();
}

void output(void * nothing)
{
    Serial.print("Button S1: ");
    Serial.println(shield.buttonS1Pressed());
    Serial.print("Button S2: ");
    Serial.println(shield.buttonS2Pressed());
    Serial.print("Licht: ");
    Serial.println(shield.getBrightness());
    Serial.print("Temperatur: ");
    Serial.print(shield.getTemperature());
    Serial.println(" Grad Celsius");
}

void buttonS1Handler(void)
{
    if (shield.buttonS1Pressed())
      counter = ++counter % 10;
}

void buttonS2Handler(void)
{
  if (shield.buttonS2Pressed())
    counter = 0;
}

void showNumber(unsigned char counter)
{
  shield.sevenSeg.showNumber(counter);
  
  if (counter < 8)
  {
    if (0b001 & counter)
      shield.setLed(ParkingShield::GREEN_LED, true);
    else
      shield.setLed(ParkingShield::GREEN_LED, false);
  
    if (0b010 & counter)
      shield.setLed(ParkingShield::YELLOW_LED, true);
    else
      shield.setLed(ParkingShield::YELLOW_LED, false);
  
    if (0b100 & counter)
      shield.setLed(ParkingShield::RED_LED, true);
    else
      shield.setLed(ParkingShield::RED_LED, false);
  }
}

