#include "ESP8266.h"
#include<Wire.h>
#include <I2Cdev.h>
#include <Microduino_Motor.h>



Motor MotorLeft(MOTOR0_PINA, MOTOR0_PINB);
Motor MotorRight(MOTOR1_PINA, MOTOR1_PINB);
#ifdef ESP32
#error "This code is not recommended to run on the ESP32 platform! Please check your Tools->Board setting."
#endif
#include <SoftwareSerial.h>

#define EspSerial mySerial
#define UARTSPEED  9600
SoftwareSerial mySerial(3, 2); 

ESP8266 wifi(&EspSerial);
#define SSID        "firstblood" //改为你的Wi-Fi名称

#define PASSWORD    "pypypypy"//Wi-Fi密码

#define HOST_NAME   "api.heclouds.com"

#define DEVICEID    "505374882" //OneNet上的设备ID

#define PROJECTID   "193429" //OneNet上的产品ID

#define HOST_PORT   (80)

String apiKey="K8K5LOUaVpudnjNieA=FeSEOmAE=";
String jsonToSend;
String postString;
String  t="ssuo";
long start;
int servopin=10;
int angle;
static const byte  GETDATA[]  PROGMEM = {
  "GET https://api.heclouds.com/devices/505374882/datapoints?datastream_id=open HTTP/1.1\r\nHost:api.heclouds.com\r\napi-key:K8K5LOUaVpudnjNieA=FeSEOmAE=\r\nConnection: close\r\n\r\n"
};

int ws;
String control="";
int judge;



void setup() {
  pinMode(13,OUTPUT);
  Wire.begin();
  Serial.begin(9600);
  MotorLeft.begin();   //电机MotorLeft初始化
  MotorRight.begin();  //电机MotorLeft初始化
WifiInit(EspSerial, UARTSPEED);
Serial.println(wifi.getVersion().c_str());
  if (wifi.setOprToStationSoftAP()) {} else {}
if (wifi.joinAP(SSID, PASSWORD)) {ws=1;} else {ws=0;}
  if (wifi.disableMUX()) {} else {}
}

String online()
{

 //if(!tcp)
wifi.createTCP(HOST_NAME, HOST_PORT);


 wifi.sendFromFlash(GETDATA, sizeof(GETDATA));
//从Flash读取发送内容，节约内存
  uint8_t buffer[350] = {0};
  uint32_t len = wifi.recv(buffer, sizeof(buffer), 20000);
  if (len > 0)
  {
     short k=0,temp=0;
     
    for (uint32_t i = 0; i < len; i++) {
      if((char)buffer[i]=='v'&&(char)buffer[i+1]=='a'&&(char)buffer[i+2]=='l'&&(char)buffer[i+3]=='u'&&(char)buffer[i+4]=='e')
      {
        for(int j = i + 8; j < len;j++) {
       char c = (char) buffer[j];
        if(buffer[j+1] == '}')
          goto ABC;
          control += c;
          
        }
    } }
    ABC:
      Serial.println("分行");
      Serial.println(control);
 return control;
}
}

void loop() {
  t="";
  control="";
  Serial.println(1);
control=online();
Serial.println(control);
if(control!=t){
  Serial.println(control);
if(control=="123")
{
  t=control;
  Serial.println("debug one");
 digitalWrite(13,HIGH);
        judge=1;
}
else
{ 
  Serial.println("debug two");
  digitalWrite(13,LOW);
}

updateSensorData();
}
}
void updateSensorData() {

  if (wifi.createTCP(HOST_NAME, HOST_PORT)) { //建立TCP连接，如果失败，不能发送该数据

    Serial.print("create tcp ok\r\n");



jsonToSend="{\"judge\":\"";
jsonToSend+=23486;
jsonToSend+="\"";
    jsonToSend+="}";







    postString="POST /devices/";

    postString+=DEVICEID;

    postString+="/datapoints?type=3 HTTP/1.1";

    postString+="\r\n";

    postString+="api-key:";

    postString+=apiKey;

    postString+="\r\n";

    postString+="Host:api.heclouds.com\r\n";

    postString+="Connection:close\r\n";

    postString+="Content-Length:";

    postString+=jsonToSend.length();

    postString+="\r\n";

    postString+="\r\n";

    postString+=jsonToSend;

    postString+="\r\n";

    postString+="\r\n";

    postString+="\r\n";



  const char *postArray = postString.c_str();                 //将str转化为char数组

  Serial.println(postArray);

  wifi.send((const uint8_t*)postArray, strlen(postArray));    //send发送命令，参数必须是这两种格式，尤其是(const uint8_t*)

  Serial.println("send success");   

     if (wifi.releaseTCP()) {                                 //释放TCP连接

        Serial.print("release tcp ok\r\n");

        } 

     else {

        Serial.print("release tcp err\r\n");

        }

      postArray = NULL;                                       //清空数组，等待下次传输数据

  

  } else {

    Serial.print("create tcp err\r\n");

  }

}
