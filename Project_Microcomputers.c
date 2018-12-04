#include <LiquidCrystal.h>

int RUN = 1;
int DB7 = 2;
int DB6 = 3;
int DB5 = 4;
int DB4 = 5;
int START = 6;
int STOP = 7;
int MIN10 = 8;
int MIN = 9;
int SEC = 10;
int E = 11;
int RS = 12;
int MIN10_VALUE = 0;
int MIN_VALUE = 0;
int SEC_VALUE = 0;
bool RUN_STATE = 0;
bool START_STATE = 0;
bool STOP_STATE = 0;
bool MIN10_STATE = 0;
bool MIN_STATE = 0;
bool SEC_STATE = 0;

LiquidCrystal lcd(RS, E, DB4, DB5, DB6, DB7);

void setup()
{
    pinMode(START, INPUT);
    pinMode(STOP, INPUT);
    pinMode(MIN10, INPUT);
    pinMode(MIN, INPUT);
    pinMode(SEC, INPUT);
    pinMode(RUN, OUTPUT);
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("00:00");
}

void loop()
{
    RUN_STATE = digitalRead(RUN);
    START_STATE = digitalRead(START);
    STOP_STATE = digitalRead(STOP);
    MIN10_STATE = digitalRead(MIN10);
    MIN_STATE = digitalRead(MIN);
    SEC_STATE = digitalRead(SEC);

    if(START_STATE == HIGH)
    {
        digitalWrite(RUN, HIGH);
    }
    else if(STOP_STATE == HIGH)
    {
        digitalWrite(RUN, LOW);
        MIN10_VALUE = 0;
        MIN_VALUE = 0;
        SEC_VALUE = 0;
        lcd.setCursor(0, 0);
        lcd.print("00:00");
    }
    else
    {
        /*Do nothing*/
    }

    if(RUN_STATE == LOW)
    {
        if(MIN10_STATE == HIGH)
        {
            MIN10_VALUE++;
            if(MIN10_VALUE < 10)
            {
                lcd.setCursor(0, 0);
                lcd.print(MIN10_VALUE);
                delay(100);
            }
            else
            {
                MIN10_VALUE = 0;
                lcd.setCursor(0, 0);
                lcd.print(MIN10_VALUE);
                delay(100);
            }
        }
        else
        {
            /*Do nothing*/
        }

        if(MIN_STATE == HIGH)
        {
            MIN_VALUE++;
            if(MIN_VALUE < 10)
            {
                lcd.setCursor(1, 0);
                lcd.print(MIN_VALUE);
                delay(100);
            }
            else
            {
                MIN_VALUE = 0;
                lcd.setCursor(1, 0);
                lcd.print(MIN_VALUE);
                delay(100);
            }
        }
        else
        {
        /*Do nothing*/
        }

        if(SEC_STATE == HIGH)
        {
            SEC_VALUE += 10;
            if(SEC_VALUE < 60)
            {
                lcd.setCursor(3, 0);
                lcd.print(SEC_VALUE);
                delay(100);
            }
            else
            {
                SEC_VALUE = 0;
                lcd.setCursor(3, 0);
                lcd.print(SEC_VALUE);
                delay(100);
            }
        }
        else
        {
            /*Do nothing*/
        }
    }
    else
    {
        if(MIN10_VALUE == 0 && MIN_VALUE == 0 && SEC_VALUE == 0)
        {
            digitalWrite(RUN, LOW);
            lcd.setCursor(0, 0);
            lcd.print("00:00");
            MIN10_VALUE = 0;
            MIN_VALUE = 0;
            SEC_VALUE = 0;
        }
        else
        {
            if(SEC_VALUE != 0)
            {
                SEC_VALUE--;
                if(SEC_VALUE > 9)
                {
                    lcd.setCursor(3, 0);
                    lcd.print(SEC_VALUE);
                    delay(1000);
                }
                else if(SEC_VALUE < 10)
                {
                    lcd.setCursor(3,0);
                    lcd.print(0);
                    lcd.setCursor(4,0);
                    lcd.print(SEC_VALUE);
                    delay(1000);
                }
                else
                {
                    /*Do nothing*/
                }
            }
            else
            {
                SEC_VALUE = 60;
                if(MIN_VALUE !=0)
                {
                    MIN_VALUE--;
                    lcd.setCursor(1, 0);
                    lcd.print(MIN_VALUE);
                }
                else
                {
                    MIN_VALUE = 9;
                    lcd.setCursor(1, 0);
                    lcd.print(MIN_VALUE);
                    MIN10_VALUE--;
                    lcd.setCursor(0, 0);
                    lcd.print(MIN10_VALUE);
                }
            }
        }
    }
}
