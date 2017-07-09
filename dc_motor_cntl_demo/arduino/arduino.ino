/**
 * @file arduino.ino
 *
 * @brief Arduino DC motor control demo
 *
 * This program demonstrates how to configure the C8051F410 to write to & read
 * from the UART interface. The program reads a word using the UART interrupts
 * and outputs that word to the screen, with all characters in uppercase
 *
 * Target:         Arduino Duo
 * Tool chain:     Arduino IDE 1.8.2
 * Command Line:   None
 *
 * @author         Mike Qin (laigui)
 * @version        1.0
 * @date           2017-07-09
 * @bug No known bugs.
 *
 * Revision history:
 * $Log:$
 *
 */
int buttonPin = 2;                          ///< button连接到数字2
int relayPin = 3;                           ///< 继电器连接到数字3
int relayState = HIGH;                      ///< 继电器初始状态为HIGH 
int buttonState;                            ///< 记录button当前状态值
int lastButtonState = LOW;                  ///< 记录button前一个状态值
long lastDebounceTime = 0;                  
long debounceDelay = 50;                    ///< 去除抖动时间

/**
 * @brief setup
 *
 * put your setup code here, to run once.
 *
 * @return void
 */
void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(relayPin, OUTPUT);

  digitalWrite(relayPin, relayState);       // 设置继电器的初始状态
}

/**
 * @brief loop
 * 
 * put your main code here, to run repeatedly
 *
 * @return void
 */
void loop() {
  int reading = digitalRead(buttonPin);   // reading用来存储buttonPin的数据

  // 一旦检测到数据发生变化，记录当前时间
  if (reading != lastButtonState) {   
    lastDebounceTime = millis();
  } 

  // 等待50ms，再进行一次判断，是否和当前button状态相同
  // 如果和当前状态不相同，改变button状态
  // 同时，如果button状态为高（也就是被按下），那么就改变继电器的状态
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        relayState = !relayState;
      }
    }
  }
  digitalWrite(relayPin, relayState);

  // 改变button前一个状态值
  lastButtonState = reading;
}

