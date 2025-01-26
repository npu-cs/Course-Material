**常见协议首部格式**：

- 以太网MAC

  ![image-20241213171206112](https://ob-and-pic.oss-cn-beijing.aliyuncs.com/img/202412131712268.png)

- PPP

  ![image-20241213171723641](https://ob-and-pic.oss-cn-beijing.aliyuncs.com/img/202412131717690.png)

- IP数据报 IPv4

  ![image-20241213171830771](https://ob-and-pic.oss-cn-beijing.aliyuncs.com/img/202412131718839.png)

- IPv6

  ![image-20241213172016361](https://ob-and-pic.oss-cn-beijing.aliyuncs.com/img/202412131720449.png)

- UDP

  ![image-20241213172137640](https://ob-and-pic.oss-cn-beijing.aliyuncs.com/img/202412131721676.png)

- TCP

  ![image-20241213172204120](https://ob-and-pic.oss-cn-beijing.aliyuncs.com/img/202412131722167.png)

- HTTP

  ![image-20241213172312126](https://ob-and-pic.oss-cn-beijing.aliyuncs.com/img/202412131723200.png)

- 常见应用层协议

  ![image-20241213172452624](https://ob-and-pic.oss-cn-beijing.aliyuncs.com/img/202412131724665.png)

  

## 概述

延迟时间：发送时间 + 传播时间

时延带宽积 = 传播时延 * 带宽

TCP/IP OSI参考模型 不直接考



## 物理层

1. 信号编码 归零 不归零 差分不归零 曼彻斯特 差分曼彻斯特
2. PCM 模拟信号转为数字信号
3. 奈式准则，香农定理



## 数据链路层

1. 差错控制：校验码（CRC）不考计算CRC，机理性；序号 + ACK应答确认 + 超时重发

2. 流量控制：停止等待协议，后退N帧协议GBN，选择重发协议SR



## 局域网 LAN

1. CSMA/CD CSMA/CA

2. 向后学习机制（交换机）



## 网络层

1. IP协议：分片，组装，首部字段

2. ARP; ICMP



## 传输层

1. TCP：
   1. **三次握手**，四次挥手；
   2. 流量控制；差错控制；
   3. **拥塞控制（曲线）：慢开始, 拥塞避免，快速重传/恢复**（考了好几年）
2. UDP

首部各个字段含义，端口号，可能考给一个抓包，分析是发客户端/服务器



## 应用层

1. DNS：传输层调用UDP  端口：53
2. HTTP 默认端口80/FTP 控制端口21 数据端口20：传输层调用TCP

