#include <avr/io.h>
#include <stdio.h>

#define F_CPU 8000000UL

#include <util/delay.h>

#define RS PB0  // Define Register Select pin
#define RW PB1  // Define Read/Write pin
#define EN PB2  // Define Enable signal pin

char keypad[4][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};

char key;
int num1;
int num2;
int result;

void init_keypad(){
    DDRC &= ~((1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC3));
    PORTC |= (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3); 

    DDRC |= (1 << PC4) | (1 << PC5) | (1 << PC6);
    PORTC |= (1 << PC4) | (1 << PC5) | (1 << PC6);
}

char scan_keypad(){
  for(int col = 0; col < 3;col++){
    PORTC &= ~(1 << (PC4 + col));

    for(int row=0;row<4;row++){
      if(!(PINC & (1<<row))){
        _delay_ms(50);
        while(!(PINC & (1 << row)));
        return keypad[row][col];
      }
    }
    PORTC |= (1 << (PC4 + col));
  }
  return 0;
}

void lcd_command(unsigned char cmd) {
    PORTD = cmd;                // Send command to LCD
    PORTB &= (~(1<<RS));          // RS=0 for command
    PORTB &= (~(1<<RW));          // RW=0 for write
    PORTB |= (1<<EN);           // Enable pulse
    _delay_ms(10);
    PORTB &= (~(1<<EN));
}

void lcd_data(unsigned char data) {
    PORTD = data;               // Send data to LCD
    PORTB |= (1<<RS);           // RS=1 for data
    PORTB &= (~(1<<RW));          // RW=0 for write
    PORTB |= (1<<EN);           // Enable pulse
    _delay_ms(10);
    PORTB &= (~(1<<EN));
}

void LCD_Init(void) {
    _delay_ms(20);              // LCD power-on delay
    lcd_command(0x38);          // 8-bit mode, 2 lines, 5x7 font
    lcd_command(0x0C);          // Display on, cursor off
    lcd_command(0x06);          // Increment cursor
    lcd_command(0x01);          // Clear display
    _delay_ms(2);
}

void lcd_string(char *str) {
    int i;
    for(i = 0; str[i] != 0; i++) {
        lcd_data(str[i]);       // Send each character of the string
    }
}

int addition(int num1,int num2){
    return num1+num2;
}

int subtraction(int num1,int num2){
    return num1-num2;
}

int main(void) {
    DDRD = 0xFF;
    DDRB |= (1<<DDB0) | (1<<DDB1) | (1<<DDB2);
    LCD_Init();
    init_keypad();
  while(1){
    lcd_command(0x01);
    num1 = 0;
    num2 = 0;
    key = '\0';
    lcd_string("Enter 1st num:");
    while(1){
      key = scan_keypad();
      if(key!=0){
        lcd_command(0x01);
        char strKey[2] = {key, '\0'};
        lcd_string(strKey);
        num1 = key - '0';
        lcd_command(0xC0); 
        lcd_string("Press Any Key");
        break;
      }
  }
  while(1){
    key = scan_keypad();
    if(key!=0){
      break;
    }
  }
  lcd_command(0x01);
  lcd_string("Enter 2nd num:");
  while(1){
    key = scan_keypad();
    if(key!=0){
      lcd_command(0x01);
      char strKey[2] = {key,'\0'};
      lcd_string(strKey);
      num2 = key - '0';
      lcd_command(0xC0);
      lcd_string("Press Any Key");
      break;
    }
  }
   while(1){
    key = scan_keypad();
    if(key!=0){
      break;
    }
  }
   lcd_command(0x01);
   lcd_string("Operation?");
   while(1){
     key = scan_keypad();
     if(key!=0){
      if(key == '*' || key=='#'){
        if(key=='*'){
          result = addition(num1,num2);
          lcd_command(0x01);
          break;
        } else {
          result = subtraction(num1,num2);
          lcd_command(0x01);
          break;
      }
      } else {
        lcd_command(0x01);
        lcd_string("Invalid");
      }
    } 
  }
  char resultStr[20]; 
  sprintf(resultStr, "%d", result);
  lcd_string("The result is:");
  lcd_command(0xC0);
  lcd_string(resultStr);
  _delay_ms(6000);
  }
  return 0;
}





