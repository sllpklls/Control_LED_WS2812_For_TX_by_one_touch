#include <NeoPixelBus.h>
#include <Preferences.h>

Preferences preferences;
const int touchPin = 1; 
const int TimeCount = 200;
const uint16_t numPixels = 27; // Số lượng LED
const uint8_t pin = 2;
int status = 0;
int dem=0;
int demSelect=0;
int storedValue;
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(numPixels, pin);
void rainbow(){
   static uint16_t hue = 0; // Giá trị màu sắc ban đầu

  for (int i = 0; i < numPixels; i++) {
    uint16_t pixelHue = hue + (i * 65536L / numPixels); // Tính giá trị màu sắc cho từng LED
    strip.SetPixelColor(i, HsbColor(pixelHue / 65536.0f, 1.0, 0.5)); // Đặt màu sắc cho từng LED
  }

  strip.Show();
  hue += 256; // Tăng giá trị màu sắc để tạo hiệu ứng chuyển màu
  delay(20); // Độ trễ để điều chỉnh tốc độ hiệu ứng
}
void tripShow() {
  // Tạo hiệu ứng ánh sáng đơn giản (đổi màu mỗi giây)
  for (int i = 0; i < numPixels; i++) {
    strip.SetPixelColor(i, RgbColor(255, 0, 0)); // Đỏ
    strip.Show();
    delay(1000);
    strip.SetPixelColor(i, RgbColor(0, 255, 0)); // Xanh lá
    strip.Show();
    delay(1000);
    strip.SetPixelColor(i, RgbColor(0, 0, 255)); // Xanh dương
    strip.Show();
    delay(1000);
  }
}
void waveEffect() {
  static uint8_t offset = 0;
  const uint8_t waveLength = 20;
  const uint8_t waveAmplitude = 100;

  for (int i = 0; i < numPixels; i++) {
    uint8_t brightness = waveAmplitude * sin(2 * PI * (i + offset) / waveLength);
    strip.SetPixelColor(i, RgbColor(brightness, brightness, brightness));
  }

  strip.Show();
  offset++;
  delay(30);
}
void waveEffectBlue() {
  static uint8_t offset = 0;
  const uint8_t waveLength = 20;
  const uint8_t waveAmplitude = 100;

  for (int i = 0; i < numPixels; i++) {
    uint8_t brightness = waveAmplitude * sin(2 * PI * (i + offset) / waveLength);
    strip.SetPixelColor(i, RgbColor(0, 0, brightness));
  }

  strip.Show();
  offset++;
  delay(30);
}
void waveEffectGreen() {
  static uint8_t offset = 0;
  const uint8_t waveLength = 20;
  const uint8_t waveAmplitude = 100;

  for (int i = 0; i < numPixels; i++) {
    uint8_t brightness = waveAmplitude * sin(2 * PI * (i + offset) / waveLength);
    strip.SetPixelColor(i, RgbColor(0,brightness, 0));
  }

  strip.Show();
  offset++;
  delay(30);
}
void waveEffectNo1() {
  static uint8_t offset = 0;
  const uint8_t waveLength = 20;
  const uint8_t waveAmplitude = 100;

  for (int i = 0; i < numPixels; i++) {
    uint8_t brightness = waveAmplitude * sin(2 * PI * (i + offset) / waveLength);
    strip.SetPixelColor(i, RgbColor(0, brightness, brightness));
  }

  strip.Show();
  offset++;
  delay(30);
}
void waveEffectRed() {
  static uint8_t offset = 0;
  const uint8_t waveLength = 20;
  const uint8_t waveAmplitude = 100;

  for (int i = 0; i < numPixels; i++) {
    uint8_t brightness = waveAmplitude * sin(2 * PI * (i + offset) / waveLength);
    strip.SetPixelColor(i, RgbColor(brightness, 0, 0));
  }

  strip.Show();
  offset++;
  delay(30);
}
void waveEffectNo2() {
  static uint8_t offset = 0;
  const uint8_t waveLength = 20;
  const uint8_t waveAmplitude = 100;

  for (int i = 0; i < numPixels; i++) {
    uint8_t brightness = waveAmplitude * sin(2 * PI * (i + offset) / waveLength);
    strip.SetPixelColor(i, RgbColor(brightness, 0, brightness));
  }

  strip.Show();
  offset++;
  delay(30);
}
void waveEffectNo3() {
  static uint8_t offset = 0;
  const uint8_t waveLength = 20;
  const uint8_t waveAmplitude = 100;

  for (int i = 0; i < numPixels; i++) {
    uint8_t brightness = waveAmplitude * sin(2 * PI * (i + offset) / waveLength);
    strip.SetPixelColor(i, RgbColor(brightness, brightness, 0));
  }

  strip.Show();
  offset++;
  delay(30);
}
void saveValue(int value){
  preferences.begin("my-app", false);
  preferences.putInt("my-var", value);
  preferences.end();
}
void selectMode() {
  dem=0;
  strip.ClearTo(RgbColor(0, 0, 0));  // Đặt tất cả các đèn LED về màu đen (tắt)
  strip.Show();      
  delay(1000);
  int touchState = digitalRead(touchPin);
  
    for (int i = 0; i < numPixels; i++){
      strip.SetPixelColor(i, RgbColor(255, 0, 0));
      strip.Show();
      delay(2000);
      if(digitalRead(touchPin) == HIGH){
        storedValue=i;
        dem=0;
        Serial.println("storedValue");
        Serial.println(storedValue);
        saveValue(i);
        break;
        executeLoopLogic();
      }
    }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(touchPin, INPUT);


  preferences.begin("my-app", false);
  storedValue = preferences.getInt("my-var", 0);
  Serial.println(storedValue);
  preferences.end();

  strip.Begin();
  delay(500);
  strip.Show();
}
void executeLoopLogic(){
  
  int touchState = digitalRead(touchPin);
  if(touchState == HIGH){
    dem++;
    Serial.println(dem);
    if(dem>TimeCount){
      selectMode();
    }
  }
  else{
    dem=0;
  }
  delay(5);
  if(storedValue==1){
    rainbow();
  }
  if(storedValue==2){
    waveEffectGreen();
  }
  if(storedValue==3){
    waveEffectBlue();
  }
  if(storedValue==4){
    waveEffectRed();
  }
  if(storedValue==5){
    waveEffectNo1();
  }
  //rainbow();
}
void loop() {
  executeLoopLogic();
}
