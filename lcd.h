
#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

void init_lcd(void);
void moveto(unsigned char, unsigned char);
void stringout(char *);
void writecommand(unsigned char);
void writedata(unsigned char);
void writenibble(unsigned char);

#endif // LCD_H_INCLUDED
