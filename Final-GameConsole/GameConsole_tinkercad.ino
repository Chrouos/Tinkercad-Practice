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

#include <LiquidCrystal.h>
#include <Servo.h>

#define left_btn 13
#define right_btn 12
#define check_btn 11
#define submit_btn 10
#define led_1 9
#define direction_servo 8
#define buzzer A0
#define sensor A1

int gameMode = 0;  // 遊戲模式 0:1A2B, 1:反應小遊戲 (now: 0~1), 2:開車小遊戲
bool gameNow = false;  // 是否進行遊戲中

/* --- 防止彈跳BTN --- */
int buttonState_left = 0, buttonState_right = 0,
    buttonState_check = 0;  // 代表按鈕沒被按下
boolean buttonUp_left = true, buttonUp_right = true,
        buttonUp_check = true;  // 代表按鈕放開
int buttonState_submit = 0;
boolean buttonUp_submit = true;

unsigned long minTime = 500000;       // reaction game 變數
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);  // LCD
Servo servo_9;                        // 伺服馬達區

/* --- 音樂區 ---*/
int miichannelTempo = 114;
int miichannelMelody[] = {

    NOTE_FS4, 8, REST, 8, NOTE_A4, 8, NOTE_CS5, 8, REST, 8, NOTE_A4, 8, REST, 8,
    NOTE_FS4, 8,  // 1
    NOTE_D4, 8, NOTE_D4, 8, NOTE_D4, 8, REST, 8, REST, 4, REST, 8, NOTE_CS4, 8,
    NOTE_D4, 8, NOTE_FS4, 8, NOTE_A4, 8, NOTE_CS5, 8, REST, 8, NOTE_A4, 8, REST,
    8, NOTE_F4, 8, NOTE_E5, -4, NOTE_DS5, 8, NOTE_D5, 8, REST, 8, REST, 4,

    NOTE_GS4, 8, REST, 8, NOTE_CS5, 8, NOTE_FS4, 8, REST, 8, NOTE_CS5, 8, REST,
    8, NOTE_GS4, 8,  // 5
    REST, 8, NOTE_CS5, 8, NOTE_G4, 8, NOTE_FS4, 8, REST, 8, NOTE_E4, 8, REST, 8,
    NOTE_E4, 8, NOTE_E4, 8, NOTE_E4, 8, REST, 8, REST, 4, NOTE_E4, 8, NOTE_E4,
    8, NOTE_E4, 8, REST, 8, REST, 4, NOTE_DS4, 8, NOTE_D4, 8,

    NOTE_CS4, 8, REST, 8, NOTE_A4, 8, NOTE_CS5, 8, REST, 8, NOTE_A4, 8, REST, 8,
    NOTE_FS4, 8,  // 9
    NOTE_D4, 8, NOTE_D4, 8, NOTE_D4, 8, REST, 8, NOTE_E5, 8, NOTE_E5, 8,
    NOTE_E5, 8, REST, 8, REST, 8, NOTE_FS4, 8, NOTE_A4, 8, NOTE_CS5, 8, REST, 8,
    NOTE_A4, 8, REST, 8, NOTE_F4, 8, NOTE_E5, 2, NOTE_D5, 8, REST, 8, REST, 4,

    NOTE_B4, 8, NOTE_G4, 8, NOTE_D4, 8, NOTE_CS4, 4, NOTE_B4, 8, NOTE_G4, 8,
    NOTE_CS4, 8,  // 13
    NOTE_A4, 8, NOTE_FS4, 8, NOTE_C4, 8, NOTE_B3, 4, NOTE_F4, 8, NOTE_D4, 8,
    NOTE_B3, 8, NOTE_E4, 8, NOTE_E4, 8, NOTE_E4, 8, REST, 4, REST, 4, NOTE_AS4,
    4, NOTE_CS5, 8, NOTE_D5, 8, NOTE_FS5, 8, NOTE_A5, 8, REST, 8, REST, 4,

    REST, 2, NOTE_A3, 4, NOTE_AS3, 4,  // 17
    NOTE_A3, -4, NOTE_A3, 8, NOTE_A3, 2, REST, 4, NOTE_A3, 8, NOTE_AS3, 8,
    NOTE_A3, 8, NOTE_F4, 4, NOTE_C4, 8, NOTE_A3, -4, NOTE_A3, 8, NOTE_A3, 2,

    REST, 2, NOTE_B3, 4, NOTE_C4, 4,  // 21
    NOTE_CS4, -4, NOTE_C4, 8, NOTE_CS4, 2, REST, 4, NOTE_CS4, 8, NOTE_C4, 8,
    NOTE_CS4, 8, NOTE_GS4, 4, NOTE_DS4, 8, NOTE_CS4, -4, NOTE_DS4, 8, NOTE_B3,
    1,

    NOTE_E4, 4, NOTE_E4, 4, NOTE_E4, 4, REST, 8,  // 25

   
};
int miichanellNotes =
    sizeof(miichannelMelody) / sizeof(miichannelMelody[0]) / 2;
int miichanellWholenote = (60000 * 4) / miichannelTempo;
int divider = 0, noteDuration = 0;

int minuetgMelody[] = {

  // Minuet in G - Petzold
  // Score available at https://musescore.com/user/3402766/scores/1456391
  NOTE_D5,4, NOTE_G4,8, NOTE_A4,8, NOTE_B4,8, NOTE_C5,8, //1
  NOTE_D5,4, NOTE_G4,4, NOTE_G4,4,
  NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8, NOTE_FS5,8,
  NOTE_G5,4, NOTE_G4,4, NOTE_G4,4,
  NOTE_C5,4, NOTE_D5,8, NOTE_C5,8, NOTE_B4,8, NOTE_A4,8,
  
  NOTE_B4,4, NOTE_C5,8, NOTE_B4,8, NOTE_A4,8, NOTE_G4,8,//6
  NOTE_FS4,4, NOTE_G4,8, NOTE_A4,8, NOTE_B4,8, NOTE_G4,8,
  NOTE_A4,-2,
  
};
int minuetgNotes = sizeof(minuetgMelody) / sizeof(minuetgMelody[0]) / 2;
int minuetgWholenote = (60000 * 4) / 140;

int zeldathemeMelody[] = {

  //Based on the arrangement at https://www.flutetunes.com/tunes.php?id=169
  
  NOTE_AS4,-2,  NOTE_F4,8,  NOTE_F4,8,  NOTE_AS4,8,//1
  NOTE_GS4,16,  NOTE_FS4,16,  NOTE_GS4,-2,
  NOTE_AS4,-2,  NOTE_FS4,8,  NOTE_FS4,8,  NOTE_AS4,8,
  NOTE_A4,16,  NOTE_G4,16,  NOTE_A4,-2,
  REST,1
 
};
int zeldathemeNotes = sizeof(zeldathemeMelody) / sizeof(zeldathemeMelody[0]) / 2;
int zeldathemeWholenote = (60000 * 4) / 88;


void setup() {
    Serial.begin(9600);                          // 序列串輸出 Port:9600
    randomSeed(analogRead(0));                   // 亂數選擇器
    servo_9.attach(direction_servo, 500, 2500);  // 伺服馬達

    lcd.begin(16, 2);

    /* --- 輸入腳位位置 ---*/
    pinMode(left_btn, INPUT);
    pinMode(right_btn, INPUT);
    pinMode(check_btn, INPUT);
    pinMode(submit_btn, INPUT);
    pinMode(led_1, OUTPUT);
    pinMode(buzzer, OUTPUT);

    /* --- 模式相關 ---*/
    gameNow = false;
    lobby_lcdController(gameMode);

    buttonState_submit = false;
}

int nowNote = 0;
void loop() {
  	backgroundPlay();
    buttonState_left = digitalRead(left_btn);
    buttonState_right = digitalRead(right_btn);
    buttonState_check = digitalRead(check_btn);

      
    // 選擇遊戲畫面階段
    if (!gameNow) {
        // 讀取按鈕的狀態 (左)
        if (buttonState_left == HIGH &&
            buttonUp_left == true) {  // 左邊按鈕被按下，且剛剛沒有被按
            buttonState_left = !buttonState_left;  // 切換

            gameMode = rtGameMode(gameMode, -1);
            lobby_lcdController(gameMode);
            tone(buzzer, NOTE_A2);
            delay(100);
            noTone(buzzer);

            // delay(500);noTone(buzzer);

            buttonUp_left = false;  // 紀錄被按下
        } else if (buttonState_left == LOW && buttonUp_left == false) {
            buttonUp_left = true;
        }

        // 讀取按鈕的狀態 (右)
        if (buttonState_right == HIGH &&
            buttonUp_right == true) {  // 右邊按鈕被按下，且剛剛沒有被按
            buttonState_right = !buttonState_right;  // 切換

            gameMode = rtGameMode(gameMode, 1);
            lobby_lcdController(gameMode);
            tone(buzzer, NOTE_A5);
            delay(100);
            noTone(buzzer);

            buttonUp_right = false;  // 紀錄被按下
        } else if (buttonState_right == LOW && buttonUp_right == false) {
            buttonUp_right = true;
        }

        // 讀取按鈕的狀態 (確認)
        if (buttonState_check == HIGH &&
            buttonUp_check == true) {  // 確認按鈕被按下，且剛剛沒有被按
            buttonState_check = !buttonState_check;  // 切換
            gameNow = true;                          // 進入遊戲模式
            buttonUp_check = false;                  // 紀錄被按下
        } else if (buttonState_check == LOW && buttonUp_check == false) {
            buttonUp_check = true;
        }
        Serial.println("NOW GMAE MODE:" + String(gameMode) + ", GAME" +
                       String(gameNow));
    }
    // 進入遊戲模式
    else {
        // 1A2B
        if (gameMode == 0) {
            guessNumber_1A2B();
            gameNow = false;
            lobby_lcdController(gameMode);
        }
        // 反應小遊戲
        else if (gameMode == 1) {
            reactionGame();
            gameNow = false;
            lobby_lcdController(gameMode);
        }
        // 開車小遊戲
        else if (gameMode == 2) {
            driveGame();
            gameNow = false;
            lobby_lcdController(gameMode);
        }
      	// 收音機
        else if (gameMode == 3) {
            radio();
            gameNow = false;
            lobby_lcdController(gameMode);
        }
    }
}

// TODO 選擇畫面的LCD顯示畫面
void lobby_lcdController(int value) {
    lcd.clear();
    lcd.print("Game Console");
    lcd.setCursor(0, 1);
    switch (value) {
        case 0:
            lcd.print("1A2B");
            break;
        case 1:
            lcd.print("reaction game");
            break;
        case 2:
            lcd.print("drive game");
            break;
        case 3:
            lcd.print("Music Radio");
            break;
    }
}

int rtGameMode(int value, int index) {
    int tempValue = value + index;

    // now 0~1
    if (tempValue < 0)
        return 3;  //最後的模式
    else if (tempValue > 3)
        return 0;  // 第一個模式
    else
        return tempValue;
}

// TODO 1A2B
void guessNumber_1A2B() {
    int times = 0;

    // 獲得謎題: 4位數字不可重複
    int numList[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int ansNumber[4] = {0, 0, 0, 0};  // 要猜測的數字
    for (int i = 0; i < 4; i++) {
        int randNumber = random(10);  // 0~9
        if (numList[randNumber] != -1) {
            ansNumber[i] = numList[randNumber];
            Serial.println("rand:" + String(numList[randNumber]));
            numList[randNumber] = -1;
        } else
            i--;
    }

    int userAns[4] = {0, 0, 0, 0};
    String showPostion[4] = {"-", "-", "-", "-"};
    int nowPosition = 0, prePosition = nowPosition;  // 0 1 2 3
    guessNumber_lcdController(userAns, showPostion, nowPosition, prePosition);

    // 選擇階段
    while (!buttonState_submit && times <= 10) {
        Serial.println("1A2B:" + String(ansNumber[0]) + String(ansNumber[1]) +
                       String(ansNumber[2]) + String(ansNumber[3]));

        buttonState_submit = digitalRead(submit_btn);
        buttonState_left = digitalRead(left_btn);
        buttonState_right = digitalRead(right_btn);
        buttonState_check = digitalRead(check_btn);

        // check = 上升按鈕
        if (buttonState_check == HIGH &&
            buttonUp_check == true) {  // 確認按鈕被按下，且剛剛沒有被按
            buttonState_check = !buttonState_check;  // 切換

            userAns[nowPosition] = (userAns[nowPosition] < 9)
                                       ? userAns[nowPosition] + 1
                                       : 0;  // 數值 + 1
            guessNumber_lcdController(userAns, showPostion, nowPosition,
                                      prePosition);

            buttonUp_check = false;  // 紀錄被按下
        } else if (buttonState_check == LOW && buttonUp_check == false) {
            buttonUp_check = true;
        }

        // 左右為選擇 nowPosition

        // 讀取按鈕的狀態 (左)
        if (buttonState_left == HIGH &&
            buttonUp_left == true) {  // 左邊按鈕被按下，且剛剛沒有被按
            buttonState_left = !buttonState_left;  // 切換

            prePosition = nowPosition;
            nowPosition = (nowPosition > 0) ? nowPosition - 1 : 3;
            guessNumber_lcdController(userAns, showPostion, nowPosition,
                                      prePosition);

            buttonUp_left = false;  // 紀錄被按下
        } else if (buttonState_left == LOW && buttonUp_left == false) {
            buttonUp_left = true;
        }

        // 讀取按鈕的狀態 (右)
        if (buttonState_right == HIGH &&
            buttonUp_right == true) {  // 右邊按鈕被按下，且剛剛沒有被按
            buttonState_right = !buttonState_right;  // 切換

            prePosition = nowPosition;
            nowPosition = (nowPosition < 3) ? nowPosition + 1 : 0;
            guessNumber_lcdController(userAns, showPostion, nowPosition,
                                      prePosition);

            buttonUp_right = false;  // 紀錄被按下
        } else if (buttonState_right == LOW && buttonUp_right == false) {
            buttonUp_right = true;
        }

        // submit = 送出
        // 讀取按鈕的狀態 (submit)
        if (buttonState_submit == HIGH &&
            buttonUp_submit == true) {  // 左邊按鈕被按下，且剛剛沒有被按
            buttonState_submit = !buttonState_submit;  // 切換

            reply_guessNumber_lcdController(userAns,
                                            reply_str(ansNumber, userAns));
            guessNumber_lcdController(userAns, showPostion, nowPosition,
                                      prePosition);
            if (reply_str(ansNumber, userAns) == "4A0B")
                break;
            times++;

            buttonUp_submit = false;  // 紀錄被按下
        } else if (buttonState_submit == LOW && buttonUp_submit == false) {
            buttonUp_submit = true;
        }
    }

    if (times == 10) {
        lcd.clear();
        lcd.print("You are lose");
      	play(zeldathemeNotes, zeldathemeMelody, zeldathemeWholenote);
    } else {
        lcd.clear();
        lcd.print("clear~");
      	play(minuetgNotes, minuetgMelody, minuetgWholenote);
      	
    }

     
}

void guessNumber_lcdController(int value[4],
                               String show[4],
                               int nowPosition,
                               int prePosition) {
    lcd.clear();
    lcd.print("Your Choice");
    lcd.setCursor(0, 1);

    lcd.print(String(value[0]) + String(value[1]) + String(value[2]) +
              String(value[3]));
    lcd.setCursor(6, 1);

    show[prePosition] = "-";
    show[nowPosition] = "+";

    lcd.print(show[0] + show[1] + show[2] + show[3]);
}

void reply_guessNumber_lcdController(int ans[4], String reply) {
    int time = 5;
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(String(ans[0]) + String(ans[1]) + String(ans[2]) +
              String(ans[3]));
    lcd.setCursor(6, 1);
    lcd.print(reply);
    while (time != -1) {
        lcd.setCursor(0, 0);
        lcd.print("last time:" + String(time));
        delay(1000);
        time--;
    }
}

String reply_str(int ans[4], int user[4]) {
    int A = 0, B = 0;
    for (int i = 0; i < 4; i++) {
        if (ans[i] == user[i])
            A++;
        else {
            for (int j = 0; j < 4; j++) {
                if (ans[i] == user[j])
                    B++;
            }
        }
    }
    Serial.println("reply_str" + String(ans[0]) + String(ans[1]) +
                   String(ans[2]) + String(ans[3]) + " | " + String(user[0]) +
                   String(user[1]) + String(user[2]) + String(user[3]));
    return String(A) + "A" + String(B) + "B";
}

// TODO 反應速度
void reactionGame() {
    unsigned long startTime, endTime;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("START!! LOOK LED!");

    int randNumber = random(2, 7);  // 2~6

    boolean reactionGameState = false;
    digitalWrite(led_1, LOW);
    delay(randNumber * 1000);
    startTime = micros();
    while (!reactionGameState) {
        tone(buzzer, NOTE_D8, 1 * 0.9);

        digitalWrite(led_1, HIGH);
        endTime = micros();
        Serial.println(String(endTime - startTime) + " = " + String(endTime) +
                       "-" + String(startTime));
        buttonState_check = digitalRead(check_btn);

        // check = 看到綠燈就按
        if (buttonState_check == HIGH &&
            buttonUp_check == true) {  // 確認按鈕被按下，且剛剛沒有被按
            buttonState_check = !buttonState_check;  // 切換

            reactionGameState = true;
            noTone(buzzer);

            buttonUp_check = false;  // 紀錄被按下
        } else if (buttonState_check == LOW && buttonUp_check == false) {
            buttonUp_check = true;
        }
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    String yourTime_s;
    yourTime_s.concat((endTime - startTime) / 1000);
    Serial.println("yourTime_s:" + yourTime_s);
    lcd.print("Ur Time:" + yourTime_s + "ms");

    if (minTime > endTime - startTime)
        minTime = endTime - startTime;

    lcd.setCursor(0, 1);
    String minTime_s;
    minTime_s.concat(minTime / 1000);
    Serial.println("minTime_s:" + minTime_s);
    lcd.print("Min Time:" + minTime_s + "ms");
    digitalWrite(led_1, LOW);
    delay(3000);
}

// TODO 開車小遊戲
int maxDriveRoad = 0;
void driveGame() {
    boolean driveNow = true;
    int angle = 90;
    int randNumber = random(1, 4);  // 1~3
    unsigned long startTime = 0, endTime = 0;

    startTime = millis();
    driveGame_lcdController(randNumber);
    int durTime = 500;
  	int tempDriveRoad = 0;
    while (driveNow) {
        buttonState_left = digitalRead(left_btn);
        buttonState_right = digitalRead(right_btn);

        // 讀取按鈕的狀態 (左)
        if (buttonState_left == HIGH &&
            buttonUp_left == true) {  // 左邊按鈕被按下，且剛剛沒有被按
            buttonState_left = !buttonState_left;  // 切換

            angle = (angle >= 165) ? 180 : angle + 15;

            buttonUp_left = false;  // 紀錄被按下
        } else if (buttonState_left == LOW && buttonUp_left == false) {
            buttonUp_left = true;
        }

        // 讀取按鈕的狀態 (右)
        if (buttonState_right == HIGH &&
            buttonUp_right == true) {  // 右邊按鈕被按下，且剛剛沒有被按
            buttonState_right = !buttonState_right;  // 切換

            angle = (angle <= 15) ? 0 : angle - 15;

            buttonUp_right = false;  // 紀錄被按下
        } else if (buttonState_right == LOW && buttonUp_right == false) {
            buttonUp_right = true;
        }

        servo_9.write(angle);

        // 隨機道路(1~3)
        endTime = millis();
        int tempNumber = random(1, 4);
        if (endTime - startTime >= durTime && tempNumber != randNumber) {
            //  (121~180) (60~120) (0~59)

            if (randNumber == 1 && (angle < 121)) {  // 判斷左邊
                driveNow = false;
                driveGame_lcdController(4);
                break;
            } else if (randNumber == 2 &&
                       (angle < 60 && angle > 120)) {  // 判斷中間
                driveNow = false;
                driveGame_lcdController(4);
                break;
            } else if (randNumber == 3 && (angle > 60)) {  // 判斷中間
                driveNow = false;
                driveGame_lcdController(4);
                break;
            }
			
            randNumber = tempNumber;
            driveGame_lcdController(randNumber);

            startTime = millis();
            durTime -= 10;
          	tempDriveRoad++;
        }
      	
      	
    }
  
  	if( tempDriveRoad > maxDriveRoad ) maxDriveRoad = tempDriveRoad;
  	lcd.setCursor(0, 1);
  	lcd.print("max:" + String(maxDriveRoad) + " U:" + String(tempDriveRoad));

    delay(3000);
}

void driveGame_lcdController(int mode) {
    lcd.clear();
    switch (mode) {
        /*---------------
         *    ***********
         **    **********
         ---------------*/
        case 1:                   // 左
            lcd.setCursor(0, 0);  // 弄上排
            lcd.print("*");
            lcd.setCursor(5, 0);
            lcd.print("***********");

            lcd.setCursor(0, 1);  // 弄下排
            lcd.print("**");
            lcd.setCursor(6, 1);
            lcd.print("**********");

            break;

        /*---------------
         ******    ******
         ******    ******
         ---------------*/
        case 2:                   // 中
            lcd.setCursor(0, 0);  // 弄上排
            lcd.print("******");
            lcd.setCursor(10, 0);
            lcd.print("******");

            lcd.setCursor(0, 1);  // 弄下排
            lcd.print("******");
            lcd.setCursor(10, 1);
            lcd.print("******");

            break;

        /*---------------
         ***********    *
         **********    **
         ---------------*/
        case 3:                   // 右
            lcd.setCursor(0, 0);  // 弄上排
            lcd.print("***********");
            lcd.setCursor(15, 0);
            lcd.print("*");

            lcd.setCursor(0, 1);  // 弄上排
            lcd.print("**********");
            lcd.setCursor(14, 1);
            lcd.print("**");

            break;

        case 4:                   // 右
            lcd.setCursor(0, 0);  // 弄上排
            lcd.print("GAME OVER");

            break;

    }  // switch mode end
}

void play(int notes, int melody[], int wholenote){
  
  // 每次都跳兩層
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    
    divider = melody[thisNote + 1]; // 每次停隔點

    if (divider > 0) { // 若停止超過 0
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // 把時間拉長 1.5 倍
    }

    tone(buzzer, melody[thisNote], noteDuration * 0.9);
    delay(noteDuration);
    noTone(buzzer);
  }

}

void backgroundPlay(){
  
  // 每次都跳兩層    
  divider = miichannelMelody[ nowNote + 1]; // 每次停隔點

  if (divider > 0) { // 若停止超過 0
    noteDuration = (miichanellWholenote) / divider;
  } else if (divider < 0) {
    noteDuration = (miichanellWholenote) / abs(divider);
    noteDuration *= 1.5; // 把時間拉長 1.5 倍
  }

  tone(buzzer, miichannelMelody[nowNote], noteDuration * 0.9);
  delay(noteDuration);
  noTone(buzzer);

  nowNote = (nowNote < miichanellNotes * 2) ? nowNote + 2 : 0;
  
}

// 收音機
void radio() {
    boolean doRadio = true;
    int sensorValue = 0;
    byte minuetgNote = 0, zeldathemeNote = 0, miichannelNote = 0;

    while (doRadio) {
        sensorValue = analogRead(sensor);  // 0 ~ 1024
        // submit = 送出
        // 讀取按鈕的狀態 (submit) 結束radio
        if (buttonState_submit == HIGH &&
            buttonUp_submit == true) {  // 左邊按鈕被按下，且剛剛沒有被按
            buttonState_submit = !buttonState_submit;  // 切換

            doRadio = false;

            buttonUp_submit = false;  // 紀錄被按下
        } else if (buttonState_submit == LOW && buttonUp_submit == false) {
            buttonUp_submit = true;
        }
        Serial.println("sensorvalue:" + String(sensorValue));
        if (sensorValue <= 300) {
             radioPlay(minuetgNotes, minuetgMelody,
             minuetgWholenote,minuetgNote);
            minuetgNote =
                (minuetgNote < minuetgNotes * 2) ? minuetgNote + 2 : 0;
        } else if (sensorValue <= 600) {
            radioPlay(zeldathemeNotes, zeldathemeMelody, zeldathemeWholenote,
                      zeldathemeNote);
            zeldathemeNote =
                (zeldathemeNote < zeldathemeNotes * 2) ? zeldathemeNote + 2 : 0;
        } else {
            radioPlay(miichanellNotes, miichannelMelody, miichanellWholenote,
            miichannelNote);
            miichannelNote =
                (miichannelNote < miichanellNotes * 2) ? miichannelNote + 2 : 0;
        }
    }
}


void radioPlay(int notes, int melody[], int wholenote, int tNote) {
    // 每次都跳兩層
    int tempDivider = melody[nowNote + 1];  // 每次停隔點

    if (tempDivider > 0) {  // 若停止超過 0
        noteDuration = (wholenote) / tempDivider;
    } else if (tempDivider < 0) {
        noteDuration = (wholenote) / abs(tempDivider);
        noteDuration *= 1.5;  // 把時間拉長 1.5 倍
    }

    tone(buzzer, melody[tNote], noteDuration * 0.9);
    delay(noteDuration);
    noTone(buzzer);
}