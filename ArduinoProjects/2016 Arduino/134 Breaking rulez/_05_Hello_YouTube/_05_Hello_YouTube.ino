// Drawing letters on scope by Hari Wiguna, 2016
// Playing with R-2R Ladder to convert Digital to Analog
// We'll use PORTD because it gives us contiguous 8 bits
// Font courtesy of: http://jared.geek.nz/2014/jan/custom-fonts-for-microcontrollers

const uint8_t fontWidth = 8;
const unsigned char font[96][8]  = {
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, //  
  {0x00,0x5f,0x00,0x00,0x00,0x00,0x00,0x00}, // !
  {0x00,0x03,0x00,0x03,0x00,0x00,0x00,0x00}, // "
  {0x0a,0x1f,0x0a,0x1f,0x0a,0x00,0x00,0x00}, // #
  {0x24,0x2a,0x2a,0x7f,0x2a,0x2a,0x12,0x00}, // $
  {0x00,0x47,0x25,0x17,0x08,0x74,0x52,0x71}, // %
  {0x00,0x36,0x49,0x49,0x49,0x41,0x41,0x38}, // &
  {0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00}, // '
  {0x00,0x3e,0x41,0x00,0x00,0x00,0x00,0x00}, // (
  {0x41,0x3e,0x00,0x00,0x00,0x00,0x00,0x00}, // )
  {0x04,0x15,0x0e,0x15,0x04,0x00,0x00,0x00}, // *
  {0x08,0x08,0x3e,0x08,0x08,0x00,0x00,0x00}, // +
  {0x00,0xc0,0x00,0x00,0x00,0x00,0x00,0x00}, // ,
  {0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x00}, // -
  {0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // .
  {0x40,0x20,0x10,0x08,0x04,0x02,0x01,0x00}, // /
  {0x00,0x3e,0x61,0x51,0x49,0x45,0x43,0x3e}, // 0
  {0x01,0x01,0x7e,0x00,0x00,0x00,0x00,0x00}, // 1
  {0x00,0x71,0x49,0x49,0x49,0x49,0x49,0x46}, // 2
  {0x41,0x49,0x49,0x49,0x49,0x49,0x36,0x00}, // 3
  {0x00,0x0f,0x10,0x10,0x10,0x10,0x10,0x7f}, // 4
  {0x00,0x4f,0x49,0x49,0x49,0x49,0x49,0x31}, // 5
  {0x00,0x3e,0x49,0x49,0x49,0x49,0x49,0x30}, // 6
  {0x01,0x01,0x01,0x01,0x01,0x01,0x7e,0x00}, // 7
  {0x00,0x36,0x49,0x49,0x49,0x49,0x49,0x36}, // 8
  {0x00,0x06,0x49,0x49,0x49,0x49,0x49,0x3e}, // 9
  {0x14,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // :
  {0x40,0x34,0x00,0x00,0x00,0x00,0x00,0x00}, // ;
  {0x08,0x14,0x22,0x00,0x00,0x00,0x00,0x00}, // <
  {0x14,0x14,0x14,0x14,0x14,0x00,0x00,0x00}, // =
  {0x22,0x14,0x08,0x00,0x00,0x00,0x00,0x00}, // >
  {0x00,0x06,0x01,0x01,0x59,0x09,0x09,0x06}, // ?
  {0x00,0x3e,0x41,0x5d,0x55,0x5d,0x51,0x5e}, // @
  {0x00,0x7e,0x01,0x09,0x09,0x09,0x09,0x7e}, // A
  {0x00,0x7f,0x41,0x49,0x49,0x49,0x49,0x36}, // B
  {0x00,0x3e,0x41,0x41,0x41,0x41,0x41,0x22}, // C
  {0x00,0x7f,0x41,0x41,0x41,0x41,0x41,0x3e}, // D
  {0x00,0x3e,0x49,0x49,0x49,0x49,0x49,0x41}, // E
  {0x00,0x7e,0x09,0x09,0x09,0x09,0x09,0x01}, // F
  {0x00,0x3e,0x41,0x49,0x49,0x49,0x49,0x79}, // G
  {0x00,0x7f,0x08,0x08,0x08,0x08,0x08,0x7f}, // H
  {0x00,0x7f,0x00,0x00,0x00,0x00,0x00,0x00}, // I
  {0x00,0x38,0x40,0x40,0x41,0x41,0x41,0x3f}, // J
  {0x00,0x7f,0x08,0x08,0x08,0x0c,0x0a,0x71}, // K
  {0x00,0x3f,0x40,0x40,0x40,0x40,0x40,0x40}, // L
  {0x00,0x7e,0x01,0x01,0x7e,0x01,0x01,0x7e}, // M
  {0x00,0x7e,0x01,0x01,0x3e,0x40,0x40,0x3f}, // N
  {0x00,0x3e,0x41,0x41,0x41,0x41,0x41,0x3e}, // O
  {0x00,0x7e,0x09,0x09,0x09,0x09,0x09,0x06}, // P
  {0x00,0x3e,0x41,0x41,0x71,0x51,0x51,0x7e}, // Q
  {0x00,0x7e,0x01,0x31,0x49,0x49,0x49,0x46}, // R
  {0x00,0x46,0x49,0x49,0x49,0x49,0x49,0x31}, // S
  {0x01,0x01,0x01,0x7f,0x01,0x01,0x01,0x00}, // T
  {0x00,0x3f,0x40,0x40,0x40,0x40,0x40,0x3f}, // U
  {0x00,0x0f,0x10,0x20,0x40,0x20,0x10,0x0f}, // V
  {0x00,0x3f,0x40,0x40,0x3f,0x40,0x40,0x3f}, // W
  {0x00,0x63,0x14,0x08,0x08,0x08,0x14,0x63}, // X
  {0x00,0x07,0x08,0x08,0x78,0x08,0x08,0x07}, // Y
  {0x00,0x71,0x49,0x49,0x49,0x49,0x49,0x47}, // Z
  {0x00,0x7f,0x41,0x00,0x00,0x00,0x00,0x00}, // [
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // "\"
  {0x41,0x7f,0x00,0x00,0x00,0x00,0x00,0x00}, // ]
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // ^
  {0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00}, // _
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // `
  {0x00,0x7e,0x01,0x09,0x09,0x09,0x09,0x7e}, // A
  {0x00,0x7f,0x41,0x49,0x49,0x49,0x49,0x36}, // B
  {0x00,0x3e,0x41,0x41,0x41,0x41,0x41,0x22}, // C
  {0x00,0x7f,0x41,0x41,0x41,0x41,0x41,0x3e}, // D
  {0x00,0x3e,0x49,0x49,0x49,0x49,0x49,0x41}, // E
  {0x00,0x7e,0x09,0x09,0x09,0x09,0x09,0x01}, // F
  {0x00,0x3e,0x41,0x49,0x49,0x49,0x49,0x79}, // G
  {0x00,0x7f,0x08,0x08,0x08,0x08,0x08,0x7f}, // H
  {0x00,0x7f,0x00,0x00,0x00,0x00,0x00,0x00}, // I
  {0x00,0x38,0x40,0x40,0x41,0x41,0x41,0x3f}, // J
  {0x00,0x7f,0x08,0x08,0x08,0x0c,0x0a,0x71}, // K
  {0x00,0x3f,0x40,0x40,0x40,0x40,0x40,0x40}, // L
  {0x00,0x7e,0x01,0x01,0x7e,0x01,0x01,0x7e}, // M
  {0x00,0x7e,0x01,0x01,0x3e,0x40,0x40,0x3f}, // N
  {0x00,0x3e,0x41,0x41,0x41,0x41,0x41,0x3e}, // O
  {0x00,0x7e,0x09,0x09,0x09,0x09,0x09,0x06}, // P
  {0x00,0x3e,0x41,0x41,0x71,0x51,0x51,0x7e}, // Q
  {0x00,0x7e,0x01,0x31,0x49,0x49,0x49,0x46}, // R
  {0x00,0x46,0x49,0x49,0x49,0x49,0x49,0x31}, // S
  {0x01,0x01,0x01,0x7f,0x01,0x01,0x01,0x00}, // T
  {0x00,0x3f,0x40,0x40,0x40,0x40,0x40,0x3f}, // U
  {0x00,0x0f,0x10,0x20,0x40,0x20,0x10,0x0f}, // V
  {0x00,0x3f,0x40,0x40,0x3f,0x40,0x40,0x3f}, // W
  {0x00,0x63,0x14,0x08,0x08,0x08,0x14,0x63}, // X
  {0x00,0x07,0x08,0x08,0x78,0x08,0x08,0x07}, // Y
  {0x00,0x71,0x49,0x49,0x49,0x49,0x49,0x47}, // Z
  {0x08,0x36,0x41,0x00,0x00,0x00,0x00,0x00}, // {
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // |
  {0x41,0x36,0x08,0x00,0x00,0x00,0x00,0x00}, // }
  {0x02,0x01,0x01,0x02,0x02,0x01,0x00,0x00}, // ~
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
};

char topWord[] =    " HELLO ";
char bottomWord[] = "YouTube";


void setup() {
  DDRD = B11111111; // Set all bits of PORTD as output
}

void loop() {
  MultiChar();
}

void MultiChar()
{
  int horizUnit = 90;

  PORTD = 250;
  
  for (uint8_t i = 0; i < sizeof(topWord) - 1; i++)
  {

    for (uint8_t x = 0; x < fontWidth; x++)
    {
      for (uint8_t r = 0; r < 2; r++)
      {
        int ch = ((r == 0) ? bottomWord[i] : topWord[i]) - ' ';
        uint8_t rowOffset = 80 * r;
        uint8_t bitAnalogValue = 40 + rowOffset;
        unsigned char vertByte = font[ch][x];
        for (uint8_t y = 0; y <= 7; y++)
        {
          bitAnalogValue += 7;
          if (bitRead(vertByte, 7 - y)) PORTD = bitAnalogValue;// else PORTD = 0;
          delayMicroseconds(horizUnit);
        }
      }

    }
  PORTD = 0;  delayMicroseconds(500);
  }
  
    delay(20);
}
