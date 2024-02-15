#include <NewPing.h>          //memanggil library ultrasonic
#include <Servo.h>            //memanggil library servo

//sensor pendeteksi orang 
#define TRIGGER_PIN   8       //pin trigger dihubungkan ke pin 8 arduino
#define ECHO_PIN      7       //pin echo dihubungkan ke pin 7 arduino
#define MAX_DISTANCE 100
//sensor kapasitas
#define TRIGGER_PIN2  10      //pin trigger dihubungkan ke pin 10 arduino
#define ECHO_PIN2     9       //pin echo dihubungkan ke pin 9 arduino
#define MAX_DISTANCE1 37     //batas jarak dari sensor

#include <LiquidCrystal_I2C.h>         //memanggil library LCD
//inisialisasi nomor pin LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);   //kalau masih tidak tampil, ganti menjadi 0x3f(alamat i2c)
//LiquidCrystal_I2C lcd(0x27,20,4);

#include <SoftwareSerial.h>

Servo servoAne;
NewPing orang(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);      //membuat variabel sampah
NewPing kapasitas(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE1); //membuat variabel kapasitas

const int buzzer = 4;            //inisialisasi pin buzzer
const int ledHijau = 11;         //inisialisasi pin led biru
const int ledMerah = 12;         //inisialisasi pin led merah

void setup() {
  Serial.begin(9600);
  lcd.begin();
  servoAne.attach(6);            //inisialisasi pin servo
  servoAne.write(0);

  pinMode (buzzer, OUTPUT);       //menetapkan pin 4 sebagai Output
  pinMode (ledHijau, OUTPUT);     //menetapkan pin 11 sebagai Output
  pinMode (ledMerah, OUTPUT);     //menetapkan pin 12 sebagai Output  
}
void loop() {
  //Rumus
  delay(50);
  int US1 = orang.ping_cm();
  int US2 = kapasitas.ping_cm()+61;   //nilai +71 di sesuaikan dengan tinggi tong sampah

  //tampil ke serial monitor 
  Serial.print("sampah : ");
  Serial.print(US1);
  Serial.println("cm ");
  //tampilkan ke lcd
  lcd.setCursor(0, 0); //set kolom dan baris
  lcd.print(" Sisa Kapasitas ");
  lcd.setCursor(0, 1); //set kolom dan baris
  lcd.print("Tong sampah:");
  lcd.print(US2);
  lcd.print("%");
  delay (50);
  
  //Jika sensor Ultrasonic 1 mendeteksi orang mendekati tong sampah , maka tetapkan servo di posisi 180 derajat
  //dan nyalakan led hijau serta matikan led merah.
  if(US1 <= 10 && US2 >= 10){
    servoAne.write(180);            //posisikan servo di 180 derajat
    digitalWrite (ledMerah, LOW);   //LED  merah padam
    digitalWrite (ledHijau, HIGH);  //LED hijau nyala
    digitalWrite (buzzer, LOW); //Buzzer mati
    delay (4000);
  }
  else if(US1 >=10 && US2 <= 10){
    servoAne.write(0);            //posisikan servo di 180 derajat
    digitalWrite (ledMerah, LOW);   //LED  merah padam
    digitalWrite (ledHijau, LOW);  //LED hijau nyala
    digitalWrite (buzzer, HIGH); //Buzzer hidup
  }else{
    servoAne.write(0);  //posisikan servo di 0 derajat
    delay(5);
    digitalWrite (ledMerah, HIGH);    //LED merah nyala
    digitalWrite (ledHijau, LOW);     //LED hijau padam
    digitalWrite (buzzer, LOW);       //Buzzer Mati
   }
  Serial.print("sampah");
   Serial.println (US2);
   delay(1000);
}
