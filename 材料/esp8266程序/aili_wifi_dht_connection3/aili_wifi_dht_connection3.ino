#include <ESP8266WiFi.h>
/* 依赖 PubSubClient 2.4.0 */
#include <PubSubClient.h>
/* 依赖 ArduinoJson 5.13.4 */
#include <ArduinoJson.h>
#include <SparkFun_SHTC3.h>

/* 连接您的WIFI SSID和密码 */
#define WIFI_SSID         "LYW"
#define WIFI_PASSWD       "29303270"


/* 设备的三元组信息*/
#define PRODUCT_KEY       "a10R0jb1HhA"
#define DEVICE_NAME       "WZd5lOvQpTRKxuL1YhPM"
#define DEVICE_SECRET     "8a30a05929b214e7e051b0ad5c1703f2"
#define REGION_ID         "cn-shanghai"

/* 线上环境域名和端口号，不需要改 */
#define MQTT_SERVER       PRODUCT_KEY ".iot-as-mqtt." REGION_ID ".aliyuncs.com"
#define MQTT_PORT         1883
#define MQTT_USRNAME      DEVICE_NAME "&" PRODUCT_KEY

#define CLIENT_ID         "SN180774203272030327|securemode=3,signmethod=hmacsha1,timestamp=1539421321846|"
// 算法工具: http://iot-face.oss-cn-shanghai.aliyuncs.com/tools.htm 进行加密生成password
// password教程 https://www.yuque.com/cloud-dev/iot-tech/mebm5g
#define MQTT_PASSWD       "8CC1CF2682CF893152185B77A87EE101C9B41BF4"

/*
设备三元组
#define PRODUCT_KEY       "a10R0jb1HhA"
#define DEVICE_NAME       "WZd5lOvQpTRKxuL1YhPM"
#define DEVICE_SECRET     "8a30a05929b214e7e051b0ad5c1703f2"


建立MQTT连接时参数
clientId = SN180774203272030327
timestamp = 1539421321846
signmethod = hmacsha1

clientId${id}deviceName${deviceName}productKey${productKey}timestamp${timestamp}

clientIdSN2930327deviceNameWZd5lOvQpTRKxuL1YhPMproductKeya10R0jb1HhAtimestamp1539421321846
#define MQTT_PASSWD       "4603a8a5d0545e20c87ee86954f387c57dfb7421"
*/

#define ALINK_BODY_FORMAT         "{\"id\":\"SN180774203272030327\",\"version\":\"1.0\",\"method\":\"thing.event.property.post\",\"params\":%s}"
#define ALINK_TOPIC_PROP_POST     "/sys/" PRODUCT_KEY "/" DEVICE_NAME "/thing/event/property/post"

#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT11
// 初始化 DHT 传感器
DHT dht(DHTPIN, DHTTYPE, 15);

unsigned long lastMs = 0;
float RH,T,RH_sum,T_sum;
unsigned char count=0;
WiFiClient espClient;
PubSubClient  client(espClient);
SHTC3 mySHTC3;

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    payload[length] = '\0';
    Serial.println((char *)payload);

}

void wifiInit()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWD);   //连接WiFi
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("WiFi not Connect");
    }
    Serial.println("Connected to AP");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());    
    Serial.print("espClient [");
    client.setServer(MQTT_SERVER, MQTT_PORT);   /* 连接WiFi之后，连接MQTT服务器 */
    client.setCallback(callback);
}


void mqttCheckConnect()
{
    while (!client.connected())
    {
        Serial.println("Connecting to MQTT Server ...");
        if (client.connect(CLIENT_ID, MQTT_USRNAME, MQTT_PASSWD))

        {

            Serial.println("MQTT Connected!");

        }
        else
        {
            Serial.print("MQTT Connect err:");
            Serial.println(client.state());
            delay(5000);
        }
    }
}


void mqttIntervalPost()
{
    char param[32];
    char jsonBuf[128];

    //CurrentTemperature
    sprintf(param, "{\"Temperature\":%f}",T_sum/count);
    sprintf(jsonBuf, ALINK_BODY_FORMAT, param);
    Serial.println(jsonBuf);
    boolean d = client.publish(ALINK_TOPIC_PROP_POST, jsonBuf);
    if(d){
      Serial.println("publish Temperature success"); 
    }else{
      Serial.println("publish Temperature fail"); 
    }


    //TargetHumidity
    sprintf(param, "{\"Humidity\":%f}",RH_sum/count);
    sprintf(jsonBuf, ALINK_BODY_FORMAT, param);
    Serial.println(jsonBuf);
    d = client.publish(ALINK_TOPIC_PROP_POST, jsonBuf);
    if(d){
      Serial.println("publish Humidity success"); 
    }else{
      Serial.println("publish Humidity fail"); 
    }
}

void errorDecoder(SHTC3_Status_TypeDef message) // The errorDecoder function prints "SHTC3_Status_TypeDef" resultsin a human-friendly way
{
  switch(message)
  {
    case SHTC3_Status_Nominal : Serial.print("Nominal"); break;
    case SHTC3_Status_Error : Serial.print("Error"); break;
    case SHTC3_Status_CRC_Fail : Serial.print("CRC Fail"); break;
    default : Serial.print("Unknown return code"); break;
  }
}
//https://blog.zeruns.tech
void setup() 
{
    /* initialize serial for debugging */
    Serial.begin(115200);
    Serial.println("Demo Start");
    wifiInit();
    Wire.begin(D5,D6);           //初始化Wire（IIC）库

    // Init DHT 
    dht.begin();
    
    unsigned char i=0;
    errorDecoder(mySHTC3.begin());
}


// the loop function runs over and over again forever
void loop()
{
  delay(4000);                  //延时4000毫秒

  RH = dht.readHumidity();
  T  = dht.readTemperature();
  RH_sum+=RH;
  T_sum+=T;
  count+=1;

  Serial.print("Humidity:");  //向串口打印 Humidity:
  Serial.print(RH);           //向串口打印湿度数据
  Serial.print("%");
  Serial.print("  Temperature:");
  Serial.print(T);            //向串口打印温度数据
  Serial.println("C"); 
  if (millis() - lastMs >= 30000)
  {
    lastMs = millis();
    mqttCheckConnect(); // MQTT连接

    /* 上报 */
    mqttIntervalPost();
    count=0;
    RH_sum=0;
    T_sum=0;
  }
  client.loop();
}
