#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define RUN 1
#define START 2
#define STOP 3
#define MIN10 4
#define MIN 5
#define SEC 6
#define DEFAULT_ZERO 0
#define DEFAULT_ONE 1
#define DEFAULT_NINE 9
#define DEFAULT_TEN 10
#define DEFAULT_FIFTY_NINE 59
#define DEFAULT_SIXTY 60
#define BUTTON_PRESS_CYCLE 200
#define ONE_SECOND_CYCLE 1000
#define LCD_INIT "00:00"
#define LCD_I2C_ADDRESS 0x3F
#define LCD_SIXTEEN_COLUMNS 16
#define LCD_TWO_ROWS 2
#define LCD_FIRST_COLUMN 0
#define LCD_SECOND_COLUMN 1
#define LCD_FOURTH_COLUMN 3
#define LCD_FIFTH_COLUMN 4
#define LCD_FIRST_ROW 0
#define ZERO_SECONDS 0
#define BUTTON_NOT_PRESSED 0
#define BUTTON_PRESSED 1
#define COUNTDOWN_NOT_STARTED 0
#define COUNTDOWN_STARTED 1

unsigned int Previous_Time_uint = ZERO_SECONDS;
unsigned int Current_Time_uint = ZERO_SECONDS;
unsigned int Min10_Value_uint = DEFAULT_ZERO;
unsigned int Min_Value_uint = DEFAULT_ZERO;
unsigned int Sec_Value_uint = DEFAULT_ZERO;
bool Run_Led_Status_b = COUNTDOWN_NOT_STARTED;
bool Start_Button_Status_b = BUTTON_NOT_PRESSED;
bool Stop_Button_Status_b = BUTTON_NOT_PRESSED;
bool Min10_Button_Old_Status_b = BUTTON_NOT_PRESSED;
bool Min10_Button_Status_b = BUTTON_NOT_PRESSED;
bool Min_Button_Old_Status_b = BUTTON_NOT_PRESSED;
bool Min_Button_Status_b = BUTTON_NOT_PRESSED;
bool Sec_Button_Old_Status_b = BUTTON_NOT_PRESSED;
bool Sec_Button_Status_b = BUTTON_NOT_PRESSED; 

LiquidCrystal_I2C Lcd(LCD_I2C_ADDRESS, LCD_SIXTEEN_COLUMNS, LCD_TWO_ROWS);

void setup()
{
    pinMode(RUN, OUTPUT);
    pinMode(START, INPUT);
    pinMode(STOP, INPUT);
    pinMode(MIN10, INPUT);
    pinMode(MIN, INPUT);
    pinMode(SEC, INPUT);
	
    Lcd.init();                      
    Lcd.backlight();
    Lcd.setCursor(LCD_FIRST_COLUMN, LCD_FIRST_ROW);
    Lcd.print(LCD_INIT);
}

void loop()
{
    Run_Led_Status_b = digitalRead(RUN);
    Start_Button_Status_b = digitalRead(START);
    Stop_Button_Status_b = digitalRead(STOP);
    Min10_Button_Status_b = digitalRead(MIN10);
    Min_Button_Status_b = digitalRead(MIN);
    Sec_Button_Status_b = digitalRead(SEC);

    if(BUTTON_PRESSED == Start_Button_Status_b)
    {
	if(DEFAULT_ZERO == Min10_Value_uint && DEFAULT_ZERO == Min_Value_uint && DEFAULT_ZERO == Sec_Value_uint)
        {
            digitalWrite(RUN, COUNTDOWN_NOT_STARTED);
        }
        else
        {
          digitalWrite(RUN, COUNTDOWN_STARTED);
        }
    }
    else if(BUTTON_PRESSED == Stop_Button_Status_b)
    {
        digitalWrite(RUN, COUNTDOWN_NOT_STARTED);
        Min10_Value_uint = DEFAULT_ZERO;
        Min_Value_uint = DEFAULT_ZERO;
        Sec_Value_uint = DEFAULT_ZERO;
        Lcd.setCursor(LCD_FIRST_COLUMN, LCD_FIRST_ROW);
        Lcd.print(LCD_INIT);
    }
    else
    {
        /*Do nothing*/
    }

    if(COUNTDOWN_NOT_STARTED == Run_Led_Status_b)
    {     
		if(Min10_Button_Old_Status_b != Min10_Button_Status_b)
		{
			if(BUTTON_PRESSED == Min10_Button_Status_b)
			{
				Current_Time_uint = millis();
				if(BUTTON_PRESS_CYCLE <= Current_Time_uint - Previous_Time_uint)
				{
					Min10_Value_uint += DEFAULT_ONE;
					if(DEFAULT_TEN > Min10_Value_uint)
					{
						Lcd.setCursor(LCD_FIRST_COLUMN, LCD_FIRST_ROW);
						Lcd.print(Min10_Value_uint);
					}
					else
					{
						Min10_Value_uint = DEFAULT_ZERO;
						Lcd.setCursor(LCD_FIRST_COLUMN, LCD_FIRST_ROW);
						Lcd.print(Min10_Value_uint);
					}
        
					Previous_Time_uint = Current_Time_uint;
				}
				else
				{
					/*Do nothing*/
				}
			}
			else
			{
				/*Do nothing*/
			}
      
			Min10_Button_Old_Status_b = Min10_Button_Status_b;
		}
		else
		{
		/*Do nothing*/
		} 

		if(Min_Button_Old_Status_b != Min_Button_Status_b)
		{
			if(BUTTON_PRESSED == Min_Button_Status_b)
			{
				Current_Time_uint = millis();
				if(BUTTON_PRESS_CYCLE <= Current_Time_uint - Previous_Time_uint)
				{
					Min_Value_uint += DEFAULT_ONE;
					if(DEFAULT_TEN > Min_Value_uint)
					{
						Lcd.setCursor(LCD_SECOND_COLUMN, LCD_FIRST_ROW);
						Lcd.print(Min_Value_uint);
					}	
					else
					{
						Min_Value_uint = DEFAULT_ZERO;
						Lcd.setCursor(LCD_SECOND_COLUMN, LCD_FIRST_ROW);
						Lcd.print(Min_Value_uint);
					}
        
					Previous_Time_uint = Current_Time_uint;
				}
				else
				{
					/*Do nothing*/
				}
			}
			else
			{
				/*Do nothing*/
			}
      
			Min_Button_Old_Status_b = Min_Button_Status_b;
		}
		else
		{
			/*Do nothing*/
		}
    
		if(Sec_Button_Old_Status_b != Sec_Button_Status_b)
		{
			if(BUTTON_PRESSED == Sec_Button_Status_b)
			{
				Current_Time_uint = millis();
				if(BUTTON_PRESS_CYCLE <= Current_Time_uint - Previous_Time_uint)
				{
					Sec_Value_uint += DEFAULT_TEN;
					if(DEFAULT_SIXTY > Sec_Value_uint)
					{
						Lcd.setCursor(LCD_FOURTH_COLUMN, LCD_FIRST_ROW);
						Lcd.print(Sec_Value_uint);
					}
					else
					{
						Sec_Value_uint = DEFAULT_ZERO;
						Lcd.setCursor(LCD_FOURTH_COLUMN, LCD_FIRST_ROW);
						Lcd.print(Sec_Value_uint);
					}
        
					Previous_Time_uint = Current_Time_uint;
				}
				else
				{
					/*Do nothing*/
				}
			}
			else
			{
				/*Do nothing*/
			}
      
			Sec_Button_Old_Status_b = Sec_Button_Status_b;
		}
		else
		{
			/*Do nothing*/
		}
    }
    else
    {
        if(DEFAULT_ZERO == Min10_Value_uint && DEFAULT_ZERO == Min_Value_uint && DEFAULT_ZERO == Sec_Value_uint)
        {
            digitalWrite(RUN, COUNTDOWN_NOT_STARTED);
            Lcd.setCursor(LCD_FIRST_COLUMN, LCD_FIRST_ROW);
            Lcd.print(LCD_INIT);
            Min10_Value_uint = DEFAULT_ZERO;
            Min_Value_uint = DEFAULT_ZERO;
            Sec_Value_uint = DEFAULT_ZERO;
        }
        else
        {
			Current_Time_uint = millis();
			if(ONE_SECOND_CYCLE <= Current_Time_uint - Previous_Time_uint)
			{
				if(DEFAULT_ZERO != Sec_Value_uint)
				{
					Sec_Value_uint -= DEFAULT_ONE;
					if(DEFAULT_NINE < Sec_Value_uint)
					{
						Lcd.setCursor(LCD_FOURTH_COLUMN, LCD_FIRST_ROW);
						Lcd.print(Sec_Value_uint);
					}
					else if(DEFAULT_TEN > Sec_Value_uint)
					{
						Lcd.setCursor(LCD_FOURTH_COLUMN, LCD_FIRST_ROW);
						Lcd.print(DEFAULT_ZERO);
						Lcd.setCursor(LCD_FIFTH_COLUMN, LCD_FIRST_ROW);
						Lcd.print(Sec_Value_uint);
					}
					else
					{
						/*Do nothing*/
					}
				}
				else
				{
					Sec_Value_uint = DEFAULT_FIFTY_NINE;
					if(DEFAULT_ZERO != Min_Value_uint)
					{
						Min_Value_uint -= DEFAULT_ONE;
						Lcd.setCursor(LCD_SECOND_COLUMN, LCD_FIRST_ROW);
						Lcd.print(Min_Value_uint);
						Lcd.setCursor(LCD_FOURTH_COLUMN, LCD_FIRST_ROW);
						Lcd.print(Sec_Value_uint);
					}
					else
					{
						Min_Value_uint = DEFAULT_NINE;
						Lcd.setCursor(LCD_SECOND_COLUMN, LCD_FIRST_ROW);
						Lcd.print(Min_Value_uint);
						Lcd.setCursor(LCD_FOURTH_COLUMN, LCD_FIRST_ROW);
						Lcd.print(Sec_Value_uint);
                  
						Min10_Value_uint -= DEFAULT_ONE;
						Lcd.setCursor(LCD_FIRST_COLUMN, LCD_FIRST_ROW);
						Lcd.print(Min10_Value_uint);
					}
				}
            
				Previous_Time_uint = Current_Time_uint;
			}       
        }
    }
}
