#include  <stdio.h>
#include  <stdlib.h>

#define HAVE_REMOTE
#include<pcap.h>
#include<WinSock2.h>

#pragma warning(disable:4996)
FILE *recvfile = fopen("recv.txt", "w");
void ethernet_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *packet_header, const u_char *packet_content);

//以太帧帧头格式
struct ethernet_header
{
	u_int8_t ether_dhost[6];//目的mac地址
	u_int8_t ether_shost[6];//源mac地址
	u_int16_t ether_type;//协议类型
};

u_int8_t accept_dest_mac[2][6] = { { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }, { 0x44, 0x87, 0xFC, 0xD6, 0xBD, 0x8C } };
u_int32_t crc32_table[256];

void generate_crc32_table()//动态生成CRC32的码表 
{
	int i, j;
	u_int32_t crc;//产生32位的冗余校验码
	for (i = 0; i < 256; i++)
	{
		crc = i;
		for (j = 0; j < 8; j++)
		{
			if (crc & 1)//与操作
				crc = (crc >> 1) ^ 0xEDB88320; //完成两个数据的按位异或操作
			else
				crc >>= 1;
		}
		crc32_table[i] = crc;
	}
}

u_int32_t calculate_crc(u_int8_t *buffer, int len)
{
	int i;
	u_int32_t crc;
	crc = 0xffffffff;
	for (i = 0; i < len; i++)
	{
		crc = (crc >> 8) ^ crc32_table[(crc & 0xFF) ^ buffer[i]];
	}
	crc ^= 0xffffffff;
	return crc;
}


void ethernet_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *packet_header, const u_char *packet_content)//数据接收回调函数
{
	//packet_content的类型是char,说明数据是按照字节进行计算的
	u_short ethernet_type;//协议类型
	struct ethernet_header *ethernet_protocol;//帧头部
	u_char *mac_string;//保存MAC地址，利用指针
	static int packet_number = 1;
	ethernet_protocol = (struct ethernet_header*)packet_content;//强制类型转换，取了14个字节
	int len = packet_header->len;//数据包的实际长度
	int i, j;

	int flag = 2;
	for (i = 0; i < 2; i++)
	{
		flag = 2;
		for (j = 0; j < 6; j++)
		{
			if (ethernet_protocol->ether_dhost[j] == accept_dest_mac[i][j])//数据包帧的目的地址是否相同
				continue;
			else
			{
				flag = i;
				break;
			}
		}
		if (flag != 2)
			continue;
		else
		{

			break;
		}
	}
	if (flag != 2)
	{
		printf("目的地址不匹配\n");
		return;

	}

	if (i==0)
	{
		printf("广播地址\n");
	}



	
	//进行长度校验，有两种方法：
	//方法一：
	int datalen = len - 4 - sizeof(ethernet_header);
	if (datalen<46 || datalen>1500)
	{
		printf("数据长度为： %d，不符合要求\n\n", datalen);
		return;
	}


	//CRC检验????


	printf("----------------------------\n");
	printf("capture %d packet\n", packet_number);//数据帧序号
	printf("capture time: %d\n", packet_header->ts.tv_sec);//数据帧接受时间
	printf("packet length: %d\n", packet_header->len);//数据帧总长度
	printf("packet header length: %d\n", sizeof(ethernet_header));//数据帧爆头长度
	printf("packet data length: %d\n", len - 4 - sizeof(ethernet_header));//数据帧数据部分长度
	printf("-----Ethernet protocol-------\n");
	ethernet_type = ethernet_protocol->ether_type;
	printf("Ethernet type: %04x\n", ethernet_type);//%04x 表示按16进制输出数据，最小输出宽度为4个字符，右对齐，如果输出的数据小于4个字符，前补0

	mac_string = ethernet_protocol->ether_shost;
	printf("MAC source address: %02x:%02x:%02x:%02x:%02x:%02x\n", *mac_string, *(mac_string + 1), *(mac_string + 2), *(mac_string + 3),
		*(mac_string + 4), *(mac_string + 5));
	mac_string = ethernet_protocol->ether_dhost;
	printf("MAC destination address: %02x:%02x:%02x:%02x:%02x:%02x\n", *mac_string, *(mac_string + 1), *(mac_string + 2),
		*(mac_string + 3), *(mac_string + 4), *(mac_string + 5));
	printf("数据内容：   \n");
	//输出数据
	u_int8_t *p;
	if (recvfile != NULL)
	{
		fprintf(recvfile, "%d:     ", packet_number);
		for (p = (u_int8_t*)(packet_content + sizeof(ethernet_header)); p != (u_int8_t*)(packet_content + packet_header->len - 4); p++)
		{
			printf("%c", char(*p));//每次读入一个字节
			fprintf(recvfile,"%c", *p);
		}

	}
	printf("\n");
	printf("补零的个数：%c", (*(char*)(packet_content + packet_header->len - 5)));//最后一个字节一定是补0的个数

	fprintf(recvfile, "\n");
	printf("\n");
	printf("----------------------\n");
	packet_number++;
	//system("pause");
}


int main()
{
	generate_crc32_table();

	pcap_if_t *all_adapters;//网卡设备列表
	pcap_if_t *adapter;
	pcap_t *adapter_handle;//捕捉实例的句柄
	char error_buffer[PCAP_ERRBUF_SIZE];
	printf("本机中mac地址列表如下：\n");
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &all_adapters, error_buffer) == -1)
	{
		fprintf(stderr, "Error in findalldevs_ex function: %s\n", error_buffer);
		return -1;
	}
	/*pcap_findalldevs() 组建一个网络设备表，该表可被pcap_open_live()打开。
	（注意可能有些网络设备不能被pcap_open_live()通过调用pcap_findalldevs()打开，
	因为，例如进程不具有打开它们的特权；出现这种情况，这些设备将不会在列表中出现）
	alldevsp指向列表的第一项，列表的每一项都是一个pcap_if_t结构。*/
	if (all_adapters == NULL)
	{
		printf("\nNo adapters found! Make sure WinPcap is installed!!!\n");
		return 0;
	}

	int id = 1;
	for (adapter = all_adapters; adapter != NULL; adapter = adapter->next)
	{
		printf("\n%d.%s\n", id++, adapter->name);
		printf("--- %s\n", adapter->description);
	}
	printf("\n");

	int adapter_id;
	printf("Enter the adapter id between 1 and %d: ", id - 1);
	scanf("%d", &adapter_id);
	if (adapter_id<1 || adapter_id>id - 1)
	{
		printf("\n Adapter id out of range.\n");
		pcap_freealldevs(all_adapters);
		return -1;
	}

	adapter = all_adapters;
	for (id = 1; id < adapter_id; id++)
	{
		adapter = adapter->next;
	}
	adapter_handle = pcap_open(adapter->name, 65535, PCAP_OPENFLAG_PROMISCUOUS, 5, NULL, error_buffer);//打开网卡的句柄
	/*
	pcap_t *pcap_open(const char *               source,
	int                              snaplen,
	int                              flags,
	int                              read_timeout,
	struct pcap_rmtauth *       auth,
	char *                        errbuf
	)
	为捕获/发送数据打开一个普通的源。pcap_open()能够替代所有的pcap_open_xxx()函数，它隐藏了不同的pcap_open_xxx()之间的差异，所以程序员不必使用不同的open函数。
	source：的是包含要打开的源名称的以’\0’结尾的字符串。源名称得包含新的源规范语法(Source Specification Syntax)，并且它不能为NULL。为了方便的使用源语法，请记住：（1）pcap_findalldevs_ex()返回的适配器（网卡）可以直接被pcap_open()使用；（2）万一用户想传递他自己的源字符串给pcap_open()，pcap_createsrcstr()可以创建正确的源标识。
	snaplen：需要保留的数据包的长度。对每一个过滤器接收到的数据包，第一个‘snaplen’字节的内容将被保存到缓冲区，并且传递给用户程序。例如，snaplen等于100，那么仅仅每一个数据包的第一个100字节的内容被保存。简言之就是从每一个包的开头到snaplen的那段内容将被保存。
	flags：保存一些由于抓包需要的标志。Winpcap定义了三种标志：
	l         PCAP_OPENFLAG_PROMISCUOUS：1，它定义了适配器（网卡）是否进入混杂模式（promiscuous mode）。
	l         PCAP_OPENFLAG_DATATX_UDP：2，它定义了数据传输（假如是远程抓包）是否用UDP协议来处理。
	l         PCAP_OPENFLAG_NOCAPTURE_RPCAP：4，它定义了远程探测器是否捕获它自己产生的数据包。
	read_timeout：以毫秒为单位。read timeout被用来设置在遇到一个数据包的时候读操作不必立即返回，而是等待一段时间，让更多的数据包到来后从OS内核一次读多个数据包。并非所有的平台都支持read timeout；在不支持read timeout的平台上它将被忽略。
	auth：一个指向’struct pcap_rmtauth’的指针，保存当一个用户登录到某个远程机器上时的必要信息。假如不是远程抓包，该指针被设置为NULL。
	errbuf：一个指向用户申请的缓冲区的指针，存放当该函数出错时的错误信息。
	返回值是一个’pcap_t’指针，它可以作为下一步调用（例如pcap_compile()等）的参数，并且指定了一个已经打开的Winpcap会话。在遇到问题的情况下，它返回NULL并且’errbuf’变量保存了错误信息。
	*/

	if (adapter_handle == NULL)
	{
		fprintf(stderr, "\n Unable to open adapter: %s\n", adapter->name);
		pcap_freealldevs(all_adapters);
		return -1;
	}

	pcap_loop(adapter_handle, NULL, ethernet_protocol_packet_callback, NULL);


	/*其中第一个参数是pcap的句柄, 第二个是指定捕获的数据包个数,pcap
	如果为 - 1则无限循环捕获。第四个参数user是留给用户使用的。
	第三个是回调函数其原型如下 :
	pcap_callback(u_char* argument, const struct pcap_pkthdr* packet_header, const u_char* packet_content)
	其中参数pcap_content表示的捕获到的数据包的内容
	参数argument是从函数pcap_loop()传递过来的。注意：这里的参数就是指 pcap_loop中的 *user 参数
	参数pcap_pkthdr 表示捕获到的数据包基本信息, 包括时间, 长度等信息.
	另外:回调函数必须是全局函数或静态函数, 其参数默认, 比如pcap_loop()可以写成
	pcap_loop(pcap_handle, 10, pcap_callback, NULL)不能往里面传递实参.
	*/

	pcap_close(adapter_handle);
	pcap_freealldevs(all_adapters);
	return 0;
}
