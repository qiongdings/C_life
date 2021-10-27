
#include <string.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

/*
 * api:(88端口)
 * get  / 管理页面
 * post / 管理页面
 * post /openComputer   开机接口
 * post /closeComputer  关机接口
 * post /openLED  打开LED
 * post /closeLED 关闭LED
 * get  /stateLED       LED状态
 * get  /stateComputer  computer状态
 * 
 * 
 * 
 * 
 * web_server库
 * http://www.taichi-maker.com/homepage/iot-development/iot-dev-reference/esp8266-c-plus-plus-reference/esp8266webserver/argname/
 */

ESP8266WiFiMulti wifimut;
ESP8266WebServer server_main(88);

int pin=4; //开机键IO口
int computerState=0; //电脑状态 0:未开机 -1:开机中 1:正常开机 2:异常开机

String username="1581716687";
String password="ganyujia.";

void setup() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);//设置4号引脚D2输出高电平防止通电开机
  
  pinMode(LED_BUILTIN, OUTPUT);//设置LED输出
  digitalWrite(LED_BUILTIN,LOW);//点亮LED,开始初始化
  Serial.begin(9600);//开启串口通讯
  Serial.println("connection......");

  connectWifi();
  server_main_init();
  
  digitalWrite(LED_BUILTIN,HIGH);//关闭LED,初始化完成
}

void loop() {

}
void server_main_init(){
  server_main.begin();
  server_main.on("/",HTTP_GET,Main);// 设置服务器根目录即’/‘的函数’Main’
  server_main.on("/",HTTP_POST,Main);// 设置服务器根目录即’/‘的函数’Main’
  server_main.on("/openLED",HTTP_POST,openLED);
  server_main.on("/closeLED",HTTP_POST,closeLED);
  server_main.on("/openComputer",HTTP_POST,openComputer);
  server_main.on("/closeComputer",HTTP_POST,closeComputer);
  server_main.on("/stateLED",HTTP_GET,stateLED);// LED状态
  server_main.on("/stateComputer",HTTP_GET,stateComputer);// 服务器状态
  
//  server_main.on("/start",HTTP_GET,Start);
//  server_main.on("/changeState",HTTP_GET,changeState);//修改服务器状态
//  server_main.on("/admin",HTTP_GET,admin);//服务器后台
//  server_main.on("/admin",HTTP_POST,admin);//服务器后台
  
  server_main.onNotFound(notFound); // 设置处理404情况的函数’handleNotFound’
  Serial.println("HTTP esp8266_server started");
}

void connectWifi(){
  wifimut.addAP("TP-LINK_2312","ganyujia.");//设置wifi名和密码
  
  int i = 0;
  while(wifimut.run() != WL_CONNECTED){
    delay(500);
    Serial.print("try:");
    Serial.println(++i);
    if(i>9999){
      i=0;
    }
  }
  Serial.print("connected to:");
  Serial.print(WiFi.SSID());
  Serial.print("\r\nIP address:");
  Serial.print(WiFi.localIP());
  Serial.print("\r\n");
}
void Main(){


}
void notFound(){
  server_main.send(404,"texxt/plain","404:Not Found");
}


