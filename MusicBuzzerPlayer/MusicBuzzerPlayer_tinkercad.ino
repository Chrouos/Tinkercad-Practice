#include <LiquidCrystal.h>

#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
#define REST 0

int Overworld[] = {

    NOTE_E5,  8,  NOTE_E5,  8,  REST,     8,  NOTE_E5, 8,
    REST,     8,  NOTE_C5,  8,  NOTE_E5,  8,  NOTE_G5, 4,
    REST,     4,  NOTE_G4,  8,  REST,     4,  // 第一階段

    NOTE_C5,  -4, NOTE_G4,  8,  REST,     4,  NOTE_E4, -4,  // 3
    NOTE_A4,  4,  NOTE_B4,  4,  NOTE_AS4, 8,  NOTE_A4, 4,
    NOTE_G4,  -8, NOTE_E5,  -8, NOTE_G5,  -8, NOTE_A5, 4,
    NOTE_F5,  8,  NOTE_G5,  8,  REST,     8,  NOTE_E5, 4,
    NOTE_C5,  8,  NOTE_D5,  8,  NOTE_B4,  -4,  // 第二階段 Part 1

    NOTE_C5,  -4, NOTE_G4,  8,  REST,     4,  NOTE_E4, -4,
    NOTE_A4,  4,  NOTE_B4,  4,  NOTE_AS4, 8,  NOTE_A4, 4,
    NOTE_G4,  -8, NOTE_E5,  -8, NOTE_G5,  -8, NOTE_A5, 4,
    NOTE_F5,  8,  NOTE_G5,  8,  REST,     8,  NOTE_E5, 4,
    NOTE_C5,  8,  NOTE_D5,  8,  NOTE_B4,  -4,  // 第二階段 Part 2 ( 結束 )

    REST,     4,  NOTE_G5,  8,  NOTE_FS5, 8,  NOTE_F5, 8,
    NOTE_DS5, 4,  NOTE_E5,  8,  // 7
    REST,     8,  NOTE_GS4, 8,  NOTE_A4,  8,  NOTE_C4, 8,
    REST,     8,  NOTE_A4,  8,  NOTE_C5,  8,  NOTE_D5, 8,
    REST,     4,  NOTE_DS5, 4,  REST,     8,  NOTE_D5, -4,
    NOTE_C5,  2,  REST,     2,  // 第三階段

    NOTE_C5,  8,  NOTE_C5,  4,  NOTE_C5,  8,  REST,    8,
    NOTE_C5,  8,  NOTE_D5,  4,  NOTE_E5,  8,  NOTE_C5, 4,
    NOTE_A4,  8,  NOTE_G4,  2,  NOTE_C5,  8,  NOTE_C5, 4,
    NOTE_C5,  8,  REST,     8,  NOTE_C5,  8,  NOTE_D5, 8,
    NOTE_E5,  8,  // 第四階段

    REST,     1,  NOTE_C5,  8,  NOTE_C5,  4,  NOTE_C5, 8,
    REST,     8,  NOTE_C5,  8,  NOTE_D5,  4,  NOTE_E5, 8,
    NOTE_C5,  4,  NOTE_A4,  8,  NOTE_G4,  2,  NOTE_E5, 8,
    NOTE_E5,  8,  REST,     8,  NOTE_E5,  8,  REST,    8,
    NOTE_C5,  8,  NOTE_E5,  4,  NOTE_G5,  4,  REST,    4,
    NOTE_G4,  4,  REST,     4,  // 結束回到開頭

};

int Underground[] = {

    NOTE_C4,
    12,
    NOTE_C5,
    12,
    NOTE_A3,
    12,
    NOTE_A4,
    12,
    NOTE_AS3,
    12,
    NOTE_AS4,
    12,
    REST,
    6,
    REST,
    3,

    NOTE_C4,
    12,
    NOTE_C5,
    12,
    NOTE_A3,
    12,
    NOTE_A4,
    12,
    NOTE_AS3,
    12,
    NOTE_AS4,
    12,
    REST,
    6,
    REST,
    3,

    NOTE_F3,
    12,
    NOTE_F4,
    12,
    NOTE_D3,
    12,
    NOTE_D4,
    12,
    NOTE_DS3,
    12,
    NOTE_DS4,
    12,
    REST,
    6,
    REST,
    3,

    NOTE_F3,
    12,
    NOTE_F4,
    12,
    NOTE_D3,
    12,
    NOTE_D4,
    12,
    NOTE_DS3,
    12,
    NOTE_DS4,
    12,
    REST,
    6,

    REST,
    6,
    NOTE_DS4,
    18,
    NOTE_CS4,
    18,
    NOTE_D4,
    18,
    NOTE_CS4,
    6,
    NOTE_DS4,
    6,
    NOTE_DS4,
    6,
    NOTE_GS3,
    6,
    NOTE_G3,
    6,
    NOTE_CS4,
    6,
    NOTE_C4,
    18,
    NOTE_FS4,
    18,
    NOTE_F4,
    18,
    NOTE_E3,
    18,
    NOTE_AS4,
    18,
    NOTE_A4,
    18,
    NOTE_GS4,
    10,
    NOTE_DS4,
    10,
    NOTE_B3,
    10,
    NOTE_AS3,
    10,
    NOTE_A3,
    10,
    NOTE_GS3,
    10,
    REST,
    3,
    REST,
    3,
    REST,
    3,

    // 以下重複

    NOTE_C4,
    12,
    NOTE_C5,
    12,
    NOTE_A3,
    12,
    NOTE_A4,
    12,
    NOTE_AS3,
    12,
    NOTE_AS4,
    12,
    REST,
    6,
    REST,
    3,

    NOTE_C4,
    12,
    NOTE_C5,
    12,
    NOTE_A3,
    12,
    NOTE_A4,
    12,
    NOTE_AS3,
    12,
    NOTE_AS4,
    12,
    REST,
    6,
    REST,
    3,

    NOTE_F3,
    12,
    NOTE_F4,
    12,
    NOTE_D3,
    12,
    NOTE_D4,
    12,
    NOTE_DS3,
    12,
    NOTE_DS4,
    12,
    REST,
    6,
    REST,
    3,

    NOTE_F3,
    12,
    NOTE_F4,
    12,
    NOTE_D3,
    12,
    NOTE_D4,
    12,
    NOTE_DS3,
    12,
    NOTE_DS4,
    12,
    REST,
    6,

    REST,
    6,
    NOTE_DS4,
    18,
    NOTE_CS4,
    18,
    NOTE_D4,
    18,
    NOTE_CS4,
    6,
    NOTE_DS4,
    6,
    NOTE_DS4,
    6,
    NOTE_GS3,
    6,
    NOTE_G3,
    6,
    NOTE_CS4,
    6,
    NOTE_C4,
    18,
    NOTE_FS4,
    18,
    NOTE_F4,
    18,
    NOTE_E3,
    18,
    NOTE_AS4,
    18,
    NOTE_A4,
    18,
    NOTE_GS4,
    10,
    NOTE_DS4,
    10,
    NOTE_B3,
    10,
    NOTE_AS3,
    10,
    NOTE_A3,
    10,
    NOTE_GS3,
    10,
    REST,
    3,
    REST,
    3,
    REST,
    3,

};

// 變數設定區
int tempo = 100;
int buzzer = 8;  // 第八腳位輸出

int notes_overworld = sizeof(Overworld) / sizeof(Overworld[0]) /
                      2;  // 每次都跳兩個，所以真正只有一半
int notes_underground = sizeof(Underground) / sizeof(Underground[0]) / 2;
int wholenote_overworld = (60000 * 4) / 200;
int wholenote_underground = (60000 * 4) / 150;

int divider = 0, noteDuration = 0;

/* 74595 NewPart Start*/
const byte dataPin = A3;
const byte latchPin = A4;
const byte clockPin = A5;
/* 74595 NewPart End*/

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

/* 74595 NewPart Start*/
const byte LEDs[10] = {
    B01111110, B00110000, B01101101, B01111001, B00110011,
    B01011011, B01011111, B01110000, B01111111, B01111011,
};
/* 74595 NewPart End*/

void setup() {
    /* 74595 NewPart Start*/
    pinMode(dataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    /* 74595 NewPart End*/

    pinMode(buzzer, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);

    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);

    lcd.begin(16, 2);
    lcd.print("Super Mario Bros");
    lcd.setCursor(0, 1);

    /* 74595 NewPart Start*/
    SevenSegmentDisplay(0);
    /* 74595 NewPart End*/
}

void loop() {
    // if button press on A0 is detected
    if (digitalRead(A0) == HIGH) {
        /* 74595 NewPart Start*/
        SevenSegmentDisplay(1);
        /* 74595 NewPart End*/
        LcdController("no.0 overworld");
        play(notes_overworld, Overworld, wholenote_overworld);
    }
    // if button press on A1 is detected
    if (digitalRead(A1) == HIGH) {
        /* 74595 NewPart Start*/
        SevenSegmentDisplay(2);
        /* 74595 NewPart End*/

        LcdController("no.8 underground");
        play(notes_underground, Underground, wholenote_underground);
    }

    delay(10);  // Delay a little bit to improve simulation performance
}

void play(int notes, int melody[], int wholenote) {
    // 每次都跳兩層
    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
        if (digitalRead(A2) == HIGH) {
            break;
        }

        divider = melody[thisNote + 1];  // 每次停隔點

        if (divider > 0) {  // 若停止超過 0
            noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5;  // 把時間拉長 1.5 倍
        }

        tone(buzzer, melody[thisNote], noteDuration * 0.9);
        delay(noteDuration);
        noTone(buzzer);
    }

    /* 74595 NewPart Start*/
    SevenSegmentDisplay(0);
    /* 74595 NewPart End*/
    LcdController("END");
}

void LcdController(String action) {
    lcd.clear();
    lcd.print("Super Mario Bros");
    lcd.setCursor(0, 1);
    lcd.print(action);
}

/* 74595 NewPart Start*/
void SevenSegmentDisplay(int number) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, LEDs[number]);
    digitalWrite(latchPin, HIGH);
}
/* 74595 NewPart End*/