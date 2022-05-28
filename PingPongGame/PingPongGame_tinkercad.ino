#include <SoftwareSerial.h>

#define p1_led_2_0 12
#define p1_led_2_1 13
#define p1_input_right A2
#define p1_input_left A3

#define p2_led_2_0 10
#define p2_led_2_1 11
#define p2_input_right A4
#define p2_input_left A5

#define out_0 2
#define out_1 3
#define out_2 4
#define out_3 5
#define out_4 6
#define out_5 7
#define out_6 8
#define out_7 9

void setup() {
    Serial.begin(9600);

    pinMode(p1_led_2_0, OUTPUT);
    pinMode(p1_led_2_1, OUTPUT);

    pinMode(p2_led_2_0, OUTPUT);
    pinMode(p2_led_2_1, OUTPUT);

    pinMode(out_0, OUTPUT);
    pinMode(out_1, OUTPUT);
    pinMode(out_2, OUTPUT);
    pinMode(out_3, OUTPUT);

    pinMode(out_4, OUTPUT);
    pinMode(out_5, OUTPUT);
    pinMode(out_6, OUTPUT);
    pinMode(out_7, OUTPUT);

    pinMode(p1_input_right, INPUT);
    pinMode(p1_input_left, INPUT);
    pinMode(p2_input_right, INPUT);
    pinMode(p2_input_left, INPUT);
    randomSeed(analogRead(A0));
}

/*
Player2 4 5 6 7
        4 5 6 7
Output  0 1 2 3
Player1 0 1 2 3
*/

// 準備值
int two_to_four[4][2] = {{LOW, LOW}, {LOW, HIGH}, {HIGH, LOW}, {HIGH, HIGH}};

// player 1 status
int p1_nowPosition = 0;
bool p1_buttonUp = true;  // p1按鈕為放開狀態

// player 2 status
int p2_nowPosition = 4;
bool p2_buttonUp = true;  // p2按鈕為放開狀態

// out status
int out_now = 0, up_down = 0, direct = 0;
int out_LED[8] = {out_0, out_1, out_2, out_3, out_4, out_5, out_6, out_7};

// 計算時間
unsigned long ti, outTime = millis();
unsigned p1_late = millis(), p2_late = millis();

bool Start = false;

void loop() {
    // 獲得目前左右狀態
    int p1_R = digitalRead(p1_input_right);
    int p1_L = digitalRead(p1_input_left);
    int p2_R = digitalRead(p2_input_right);
    int p2_L = digitalRead(p2_input_left);

    // P1 目前的左右狀態
    if (p1_R == HIGH && p1_buttonUp == true) {
        if (p1_nowPosition < 3)  // 若小於3，就是除了最右邊
            p1_nowPosition++;
        p1_buttonUp = false;

    } else if (p1_L == HIGH && p1_buttonUp == true) {
        if (p1_nowPosition > 0)  // 若在0，就是最左邊 無法在過去了
            p1_nowPosition--;
        p1_buttonUp = false;

    } else if (p1_L == LOW && p1_R == LOW && p1_buttonUp == false) {
        p1_buttonUp = true;
    }
    //# 之後補一個delay類似用法 #//

    // P2 目前的左右狀態
    if (p2_R == HIGH && p2_buttonUp == true) {
        if (p2_nowPosition < 7)  // 4 5 6 (7)
            p2_nowPosition++;
        p2_buttonUp = false;
    } else if (p2_L == HIGH && p2_buttonUp == true) {
        if (p2_nowPosition > 4)  // (4) 5 6 7
            p2_nowPosition--;
        p2_buttonUp = false;

    } else if (p2_L == LOW && p2_R == LOW && p2_buttonUp == false) {
        p2_buttonUp = true;
    }
    //# 之後補一個delay類似用法 #//

    // Player 1 目前顯示狀況
    digitalWrite(p1_led_2_1, two_to_four[p1_nowPosition][0]);
    digitalWrite(p1_led_2_0, two_to_four[p1_nowPosition][1]);

    // Player 2 目前顯示狀況
    digitalWrite(p2_led_2_1, two_to_four[p2_nowPosition - 4][0]);
    digitalWrite(p2_led_2_0, two_to_four[p2_nowPosition - 4][1]);

    // 顯示 out

    if (ti <= 1000)
        out_now = p1_nowPosition;  // 由 Player1 發球，會從Player 1的位置開始
    if (ti - 300 > outTime && ti >= 1000) {
        // 判斷遊戲結束
        if (out_now - direct >= 4 && out_now - 4 - direct != p1_nowPosition)
            gameOver("player 1");
        else if (out_now - direct <= 3 &&
                 out_now + 4 - direct != p2_nowPosition && Start != false) {
            Serial.println(out_now + 4 - direct);
            Serial.println(p2_nowPosition);
            gameOver("player 2");
        }

        // 顯示 out START
        for (int i = 0; i < 8; i++) {
            if (i == out_now)
                digitalWrite(out_LED[i], HIGH);
            else
                digitalWrite(out_LED[i], LOW);
        }
        // 顯示 out END

        // 上上下下區
        (out_now >= 4) ? up_down = -4 : up_down = 4;

        // 左右隨機區 START
        direct = random(3) - 1;  // 0 1 2 (改成 -1 0 1)
        if (out_now == 0 || out_now == 4)
            direct = random(2);  // 0 or 1 (不動或往右)
        else if (out_now == 3 || out_now == 7)
            direct = random(2) - 1;  // 0 1 -> -1 0 (不動或往左)
        // 左右隨機區 END

        // 下一個位置
        out_now += up_down;
        out_now += direct;

        outTime = ti;  // 計算最後出去的時間，過了一秒才會下一次
        Start = true;
    }
    // 計算時間區
    Serial.print("Time:");
    ti = millis();
    Serial.println(ti);
}

void gameOver(String user) {
    for (int i = 0; i < 4; i++) {
        digitalWrite(p1_led_2_1, two_to_four[i][0]);
        digitalWrite(p1_led_2_0, two_to_four[i][1]);
        digitalWrite(p2_led_2_1, two_to_four[i][0]);
        digitalWrite(p2_led_2_0, two_to_four[i][1]);

        digitalWrite(out_LED[i], HIGH);
        digitalWrite(out_LED[i + 4], HIGH);

        digitalWrite(out_LED[i], LOW);
        digitalWrite(out_LED[i + 4], LOW);
        delay(300);
    }
    Serial.print(user);
    Serial.println("'s losed");
    delay(500);
    exit(0);
}

/*
for (int i = 0; i < 8; i++) {
        if (i == out_now) {
            digitalWrite(out_LED[i], HIGH);
            digitalWrite(out_LED[i], LOW);
        }
    }

*/
