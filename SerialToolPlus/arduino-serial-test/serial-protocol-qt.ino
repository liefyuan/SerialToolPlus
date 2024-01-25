void setup() {
    // put your setup code here, to run once:

    Serial.begin(115200);
    int noise = analogRead(A3);
    // 使用噪声值作为随机数生成器的种子
    randomSeed(noise);
}
void send_1byte_data(uint8_t data)
{
    uint8_t cnt=0, i=0, sum = 0;
    uint8_t send_buff[100] = {0};
    
    //char 类型为两个字节
    send_buff[cnt++] = 0xAA;  //帧头
    send_buff[cnt++] = 0xAA;
    send_buff[cnt++] = 0x02;  //功能字
    send_buff[cnt++] = 0;     //需要发送数据的字节数，暂时给0，后面再赋值。

    send_buff[cnt++] = data;
    
    send_buff[3] = cnt-4;   //赋值数据包长度
    for(i = 0; i < cnt; i++)
      sum = sum + send_buff[i];  //校验位计算
    
    send_buff[cnt++] = sum; //赋值校验位

    Serial.write(send_buff,cnt);
}

void send_2byte_data(uint16_t data)
{
    uint8_t cnt=0, i=0, sum = 0;
    uint8_t send_buff[100] = {0};
    
    //char 类型为两个字节
    send_buff[cnt++] = 0xAA;  //帧头
    send_buff[cnt++] = 0xAA;
    send_buff[cnt++] = 0x02;  //功能字
    send_buff[cnt++] = 0;     //需要发送数据的字节数，暂时给0，后面再赋值。
    send_buff[cnt++] = data>>8;       //数据的高8位
    send_buff[cnt++] = data&0x00ff;  //数据的低8位
    
    send_buff[3] = cnt-4;   //赋值数据包长度
    for(i = 0; i < cnt; i++)
      sum = sum + send_buff[i];  //校验位计算
    
    send_buff[cnt++] = sum; //赋值校验位

    Serial.write(send_buff,cnt);
}

void send_4byte_data(uint16_t data1, uint16_t data2)
{
    uint8_t cnt=0, i=0, sum = 0;
    uint8_t send_buff[100] = {0};
    
    //char 类型为两个字节
    send_buff[cnt++] = 0xAA;  //帧头
    send_buff[cnt++] = 0xAA;
    send_buff[cnt++] = 0x02;  //功能字
    send_buff[cnt++] = 0;     //需要发送数据的字节数，暂时给0，后面再赋值。
    send_buff[cnt++] = data1>>8;       //数据的高8位
    send_buff[cnt++] = data1&0x00ff;  //数据的低8位
    send_buff[cnt++] = data2>>8;       //数据的高8位
    send_buff[cnt++] = data2&0x00ff;  //数据的低8位
    
    send_buff[3] = cnt-4;   //赋值数据包长度
    for(i = 0; i < cnt; i++)
      sum = sum + send_buff[i];  //校验位计算
    
    send_buff[cnt++] = sum; //赋值校验位

    Serial.write(send_buff,cnt);
}


void send_6byte_data(uint16_t data1, uint16_t data2, uint16_t data3)
{
    uint8_t cnt=0, i=0, sum = 0;
    uint8_t send_buff[100] = {0};
    
    //char 类型为两个字节
    send_buff[cnt++] = 0xAA;  //帧头
    send_buff[cnt++] = 0xAA;
    send_buff[cnt++] = 0x02;  //功能字
    send_buff[cnt++] = 0;     //需要发送数据的字节数，暂时给0，后面再赋值。
    send_buff[cnt++] = data1>>8;       //数据的高8位
    send_buff[cnt++] = data1&0x00ff;  //数据的低8位
    send_buff[cnt++] = data2>>8;       //数据的高8位
    send_buff[cnt++] = data2&0x00ff;  //数据的低8位
    send_buff[cnt++] = data3>>8;       //数据的高8位
    send_buff[cnt++] = data3&0x00ff;  //数据的低8位
    
    send_buff[3] = cnt-4;   //赋值数据包长度
    for(i = 0; i < cnt; i++)
      sum = sum + send_buff[i];  //校验位计算
    
    send_buff[cnt++] = sum; //赋值校验位

    Serial.write(send_buff,cnt);
}

void loop() {
  // put your main code here, to run repeatedly:
    // Serial.println("helloworld!");

    send_1byte_data(random(0, 256));
    delay(10);

    // send_1byte_data(0x44);
    // delay(10);
    // send_2byte_data(0x5678);
    // delay(5);
    // send_4byte_data(0x2233, 0x6655);
    // delay(5);
    // send_6byte_data(0x1234, 0x5678, 0x6699);
    // delay(5);
}
