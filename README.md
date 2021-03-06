# esp8266+阿里云iot

> 前期准备：
>
> ​	python3.6
>
> ​	arduino
>
> ​	pycharm
>
> ​	阿里云（淘宝）账户 
>
> ​	esp8266WiFi模块一个（淘宝购买）
>
> ​	hdt11温控模块（淘宝购买）
>
> ​	红路灯模块（淘宝购买）
>
> ​	杜邦线（淘宝购买）
>
> ​	面包板（淘宝购买）
>
> 

## 环境搭建

### 1、python3.6

- 在清华镜像站（https://mirror.tuna.tsinghua.edu.cn/help/anaconda/）中下载最新的anaconda

- 参照https://jingyan.baidu.com/article/d8072ac48e5433ec95cefdb4.html安装并正确配置环境

  - ![{E5BA4921-171F-4417-BB9D-65AFD120B663}.png](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205240.jpg)

- 并测试conda环境是否配置

  - 下载numpy测试（首次下载会比较慢，conda会自动检测numpy的所有依赖包一起下载）

    ![{C5AD21D3-DFA7-495E-9988-5D43FB0B7B00}.png](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205249.jpg)

- 测试python

  - ![{BF48E704-2B42-4109-BE9A-3AE8AB714BD5}.png](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205259.jpg)

### 2、arduino

- 在https://www.arduino.cn/thread-1066-1-1.html中下载ide

![{210C59BE-9B3B-4517-AFF0-FB85C31822E2}.png](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205305.jpg)

- 下载并安装

  ![{EF788A7B-417E-4C2F-81B8-D778B50F3B4B}.png](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205310.jpg)

- 添加esp8266的开发板管理

  - 参考：https://www.arduino.cn/thread-17884-1-1.html （不推荐）

    - ![{1EDBF9AF-29DA-4A75-82DF-E1AE55103F2B}.png](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205314.jpg)

  - 或者使用 .\材料.\软件\8266_package_2.7.1（双击打开）

    ![{2A1629EF-DA1A-417C-B173-1DA3D9EF0919}.png](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205324.jpg)

    等待插件安装完成后，再次打开arduino软件，点击 工具-开发板 就可以看到ESP8266 Boards 的开发板选项

    ![{BF04A52A-EEF0-477B-B131-469862CE4D2B}.png](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205328.jpg)

    

### 3、组件展示

- esp8266

  ​	![image-20201017150012972](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205417.png)

- hdt11温控模块

  ​	![image-20201017150242599](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205412.png)

- 红路灯模块 & 面包板

  ​	![image-20201017150159731](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205408.png)

- 杜邦线

  ​	![image-20201017150340165](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205405.png)

  

## 一：配置阿里云iot

### 1、进入https://iot.aliyun.com/ 首页

![sadsad12vc](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205402.jpg)

### 2、进入控制台

![image-20201017142436786](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205359.png)

### 3、点击立即开通（如果此处出现未实名制验证，则需要先去验证）

![image-20201017142638429](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205356.png)

### 4、勾选已经阅读，并点击立即开通

![img](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205352.png)

### 5、点击管理控制台

![img](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205541.png)

### 6、 点击设备管理 – 产品

![img](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205546.png)

### 7、创建产品并且为其添加物模型

![img](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205550.png)

### 8、可以在物模型功能定义中看到我们刚刚创建的产品的信息和上传、设定的一些接口（不知道是不是免费版本的原因，这个产品的物模型代码不支持完全自定义修改，可以改一部分内容）

![image-20201017142827462](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205559.png)

![image-20201017142849684](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205603.png)

9、自定义添加了湿度的属性

![img](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205653.png)

![img](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205655.png)

### 10、然后我们在这个产品中添加设备，并获取到设备的三元组信息

![img](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205700)

![img](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205704)

--------------

## 二：初步体验

### 1、 阿里云设备创建完成图：

- 产品：

![img](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205710)

- 设备功能：

![img](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205715)

- 功能定义（需要先 编辑草稿 才可以操作）：根据自己的需求和上传的数据类型来设定这里的功能。

![img](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205718)

 

### 2、 阿里云iot平台开发的接口;

![img](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205758)

 

 

1. SDK

   wifi连接部分：

   ​		a） 引入依赖库：

![img](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205806)

​				b） 填入wifi账号密码：

![img](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205810)

2. DHT11感应器部分：

   a)   根据esp8266开发板的开发文档得知dht11的扩展接口是5号针脚:

![img](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205815)

​	b)    在SDK中设定好dht11模块返回数据的脚位：

![img](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205820)

 

3. Mqtt传输部分：

   a)   阿里云mqtt开发文档地址：https://www.yuque.com/cloud-dev/iot-tech/mebm5g

   b)   mqtt报文简介：

![img](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205825)

​		c)   链接所需准备的信息（使用阿里云物联网iot配置软件生成信息）：

<img src="https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205829.jpg" alt="img" style="zoom:150%;" />

​		d)   生成mqtt的链接密码：

<img src="https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205836.jpg" alt="img" style="zoom:150%;" />

<img src="https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205840.jpg" alt="img" style="zoom:150%;" />

​	e)   Mqtt反馈错误代码：

 

```
 The value of rc indicates success or not:

​    0: Connection successful 

​    1: Connection refused - incorrect protocol version 

​    2: Connection refused - invalid client identifier 

​    3: Connection refused - server unavailable 

​    4: Connection refused - bad username or password 

​    5: Connection refused - not authorised 

​    6-255: Currently unused.
```

 

![img](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205846.png)

-----

## 三：运行esp8266

### 1、在arduino 文件-打开 选择打开.\材料\esp8266程序\AliyunSDK_item3\AliyunSDK_item3

- 打开显示界面

​		![{A44470E7-006A-4E89-B84C-C138807AAA40}.png](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205850.jpg)

- 点击编译

  ![sp20201017_123558](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205854.png)

### 2、配置讲解

![sp20201017_141626](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205857.png)

### 3、配置完成后，插入esp8266烧录后到阿里云iot查看传输数据情况

![image-20201017144331748](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205901.png)

![image-20201017145041188](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205906.png)

--------

## 四、阿里云 iot Studio配置

### 1、进入

![image-20201017150612147](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205909.png)

### 2、	进入iot studio页面后点击WEB可视化开发

![image-20201017165109050](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205914.png)

### 3、创建web应用

![image-20201017165343708](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205920.png)

### 4、	输入信息

![image-20201017165511310](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205923.png)

### 5、web页面可视化编辑

![image-20201017171640625](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205927.png)

1. 创建模板页面

   ![image-20201017171820248](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205931.png)

2. 设计组件

   ![image-20201017172055889](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205934.png)

3. 为组件配置数据

   1. 获取数据

      ![image-20201017172339309](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205938.png)

   2. 发送数据

      ![image-20201017172445754](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205942.png)

## 五、数据流转

### 1、阿里iot设定流转规则（创建流转订阅）

​	![image-20201017172717715](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205945.png)

### 2、消费组设定

![image-20201017172901119](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205950.png)

### 3、流转信息接受Demo

> 阿里云iot的开发手册提供了现在流行计算机语言的接收Demo
>
> Demo参考地址：https://help.aliyun.com/document_detail/175270.html
>
> AMQP客户端接入说明：https://help.aliyun.com/document_detail/142489.html?spm=a2c4g.11186623.6.623.4ade354eMNlXlz
>
> （以下以python为例）

### 1、python需要stomp.py的第三方库支持

1. 下载stomp.py

   ​	![image-20201017174136754](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205956.png)

### 2、配置说明

1. 对阿里云账号的三组信息配置说明（以①、②、③为编号）

   ![image-20201017175038504](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022205959.png)

   > - ① = AccessKey : 登录阿里云控制台，将光标移至账号头像上，然后单击**accesskeys**，跳转至用户信息管理页，即可获取。
   > - ② = accessSecret : 您的阿里云账号的AccessKey Secret。登录阿里云控制台，将光标移至账号头像上，然后单击**accesskeys**，跳转至用户信息管理页，即可获取。
   > - ③ = consumerGroupId : 消费组ID。请在控制台上查看您的服务端订阅消费组ID。

2. 个人信息配置（以①、②为编号）

   ![image-20201017175411469](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022210004.png)

   > - ① = iotInstanceId ：实例ID。仅您购买的实例需要传入。（我们测试都没有购买，所以只需要默认的空号即可）
   >
   > - ② = clientId ：表示客户端ID，建议使用您的AMQP客户端所在服务器UUID、MAC地址、IP等唯一标识。长度不可超过64个字符。
   >
   >   控制台服务端订阅中消费组状态页将显示该参数，方便您识别区分不同的客户端。

3. 接入域名配置

   1. 需要配置一个变量

      ![image-20201017175716978](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022210008.png)

   2. 打开 .\材料\软件\阿里云物联平台配置_32

      1. 软件使用

         ​		![image-20201017180058727](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022210012.png)

      2. 生成

         ![image-20201017180308434](\材料\图片\image-20201017180308434.png)

   3. ① = Host ：域名地址

      1. 把从配置软件中获取到的字符除去端口，只保留地址

      2. 例如：

         ![image-20201017180903308](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022210019.png)

### 3、获取信息

![image-20201017181728831](https://gitee.com/andyxiaopeng/picbed/raw/master/pic/20201022210016.png)
