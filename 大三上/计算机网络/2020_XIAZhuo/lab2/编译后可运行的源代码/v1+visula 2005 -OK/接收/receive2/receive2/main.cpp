#include  <stdio.h>
#include  <stdlib.h>

#define HAVE_REMOTE
#include<pcap.h>
#include<WinSock2.h>

#pragma warning(disable:4996)
FILE *recvfile = fopen("recv.txt", "w");
void ethernet_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *packet_header, const u_char *packet_content);

//��̫֡֡ͷ��ʽ
struct ethernet_header
{
	u_int8_t ether_dhost[6];//Ŀ��mac��ַ
	u_int8_t ether_shost[6];//Դmac��ַ
	u_int16_t ether_type;//Э������
};

u_int8_t accept_dest_mac[2][6] = { { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }, { 0x44, 0x87, 0xFC, 0xD6, 0xBD, 0x8C } };
u_int32_t crc32_table[256];

void generate_crc32_table()//��̬����CRC32����� 
{
	int i, j;
	u_int32_t crc;//����32λ������У����
	for (i = 0; i < 256; i++)
	{
		crc = i;
		for (j = 0; j < 8; j++)
		{
			if (crc & 1)//�����
				crc = (crc >> 1) ^ 0xEDB88320; //����������ݵİ�λ������
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


void ethernet_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *packet_header, const u_char *packet_content)//���ݽ��ջص�����
{
	//packet_content��������char,˵�������ǰ����ֽڽ��м����
	u_short ethernet_type;//Э������
	struct ethernet_header *ethernet_protocol;//֡ͷ��
	u_char *mac_string;//����MAC��ַ������ָ��
	static int packet_number = 1;
	ethernet_protocol = (struct ethernet_header*)packet_content;//ǿ������ת����ȡ��14���ֽ�
	int len = packet_header->len;//���ݰ���ʵ�ʳ���
	int i, j;

	int flag = 2;
	for (i = 0; i < 2; i++)
	{
		flag = 2;
		for (j = 0; j < 6; j++)
		{
			if (ethernet_protocol->ether_dhost[j] == accept_dest_mac[i][j])//���ݰ�֡��Ŀ�ĵ�ַ�Ƿ���ͬ
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
		printf("Ŀ�ĵ�ַ��ƥ��\n");
		return;

	}

	if (i==0)
	{
		printf("�㲥��ַ\n");
	}



	
	//���г���У�飬�����ַ�����
	//����һ��
	int datalen = len - 4 - sizeof(ethernet_header);
	if (datalen<46 || datalen>1500)
	{
		printf("���ݳ���Ϊ�� %d��������Ҫ��\n\n", datalen);
		return;
	}


	//CRC����????


	printf("----------------------------\n");
	printf("capture %d packet\n", packet_number);//����֡���
	printf("capture time: %d\n", packet_header->ts.tv_sec);//����֡����ʱ��
	printf("packet length: %d\n", packet_header->len);//����֡�ܳ���
	printf("packet header length: %d\n", sizeof(ethernet_header));//����֡��ͷ����
	printf("packet data length: %d\n", len - 4 - sizeof(ethernet_header));//����֡���ݲ��ֳ���
	printf("-----Ethernet protocol-------\n");
	ethernet_type = ethernet_protocol->ether_type;
	printf("Ethernet type: %04x\n", ethernet_type);//%04x ��ʾ��16����������ݣ���С������Ϊ4���ַ����Ҷ��룬������������С��4���ַ���ǰ��0

	mac_string = ethernet_protocol->ether_shost;
	printf("MAC source address: %02x:%02x:%02x:%02x:%02x:%02x\n", *mac_string, *(mac_string + 1), *(mac_string + 2), *(mac_string + 3),
		*(mac_string + 4), *(mac_string + 5));
	mac_string = ethernet_protocol->ether_dhost;
	printf("MAC destination address: %02x:%02x:%02x:%02x:%02x:%02x\n", *mac_string, *(mac_string + 1), *(mac_string + 2),
		*(mac_string + 3), *(mac_string + 4), *(mac_string + 5));
	printf("�������ݣ�   \n");
	//�������
	u_int8_t *p;
	if (recvfile != NULL)
	{
		fprintf(recvfile, "%d:     ", packet_number);
		for (p = (u_int8_t*)(packet_content + sizeof(ethernet_header)); p != (u_int8_t*)(packet_content + packet_header->len - 4); p++)
		{
			printf("%c", char(*p));//ÿ�ζ���һ���ֽ�
			fprintf(recvfile,"%c", *p);
		}

	}
	printf("\n");
	printf("����ĸ�����%c", (*(char*)(packet_content + packet_header->len - 5)));//���һ���ֽ�һ���ǲ�0�ĸ���

	fprintf(recvfile, "\n");
	printf("\n");
	printf("----------------------\n");
	packet_number++;
	//system("pause");
}


int main()
{
	generate_crc32_table();

	pcap_if_t *all_adapters;//�����豸�б�
	pcap_if_t *adapter;
	pcap_t *adapter_handle;//��׽ʵ���ľ��
	char error_buffer[PCAP_ERRBUF_SIZE];
	printf("������mac��ַ�б����£�\n");
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &all_adapters, error_buffer) == -1)
	{
		fprintf(stderr, "Error in findalldevs_ex function: %s\n", error_buffer);
		return -1;
	}
	/*pcap_findalldevs() �齨һ�������豸���ñ�ɱ�pcap_open_live()�򿪡�
	��ע�������Щ�����豸���ܱ�pcap_open_live()ͨ������pcap_findalldevs()�򿪣�
	��Ϊ��������̲����д����ǵ���Ȩ�����������������Щ�豸���������б��г��֣�
	alldevspָ���б�ĵ�һ��б��ÿһ���һ��pcap_if_t�ṹ��*/
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
	adapter_handle = pcap_open(adapter->name, 65535, PCAP_OPENFLAG_PROMISCUOUS, 5, NULL, error_buffer);//�������ľ��
	/*
	pcap_t *pcap_open(const char *               source,
	int                              snaplen,
	int                              flags,
	int                              read_timeout,
	struct pcap_rmtauth *       auth,
	char *                        errbuf
	)
	Ϊ����/�������ݴ�һ����ͨ��Դ��pcap_open()�ܹ�������е�pcap_open_xxx()�������������˲�ͬ��pcap_open_xxx()֮��Ĳ��죬���Գ���Ա����ʹ�ò�ͬ��open������
	source�����ǰ���Ҫ�򿪵�Դ���Ƶ��ԡ�\0����β���ַ�����Դ���Ƶð����µ�Դ�淶�﷨(Source Specification Syntax)������������ΪNULL��Ϊ�˷����ʹ��Դ�﷨�����ס����1��pcap_findalldevs_ex()���ص�������������������ֱ�ӱ�pcap_open()ʹ�ã���2����һ�û��봫�����Լ���Դ�ַ�����pcap_open()��pcap_createsrcstr()���Դ�����ȷ��Դ��ʶ��
	snaplen����Ҫ���������ݰ��ĳ��ȡ���ÿһ�����������յ������ݰ�����һ����snaplen���ֽڵ����ݽ������浽�����������Ҵ��ݸ��û��������磬snaplen����100����ô����ÿһ�����ݰ��ĵ�һ��100�ֽڵ����ݱ����档����֮���Ǵ�ÿһ�����Ŀ�ͷ��snaplen���Ƕ����ݽ������档
	flags������һЩ����ץ����Ҫ�ı�־��Winpcap���������ֱ�־��
	l         PCAP_OPENFLAG_PROMISCUOUS��1�������������������������Ƿ�������ģʽ��promiscuous mode����
	l         PCAP_OPENFLAG_DATATX_UDP��2�������������ݴ��䣨������Զ��ץ�����Ƿ���UDPЭ��������
	l         PCAP_OPENFLAG_NOCAPTURE_RPCAP��4����������Զ��̽�����Ƿ񲶻����Լ����������ݰ���
	read_timeout���Ժ���Ϊ��λ��read timeout����������������һ�����ݰ���ʱ������������������أ����ǵȴ�һ��ʱ�䣬�ø�������ݰ��������OS�ں�һ�ζ�������ݰ����������е�ƽ̨��֧��read timeout���ڲ�֧��read timeout��ƽ̨�����������ԡ�
	auth��һ��ָ��struct pcap_rmtauth����ָ�룬���浱һ���û���¼��ĳ��Զ�̻�����ʱ�ı�Ҫ��Ϣ�����粻��Զ��ץ������ָ�뱻����ΪNULL��
	errbuf��һ��ָ���û�����Ļ�������ָ�룬��ŵ��ú�������ʱ�Ĵ�����Ϣ��
	����ֵ��һ����pcap_t��ָ�룬��������Ϊ��һ�����ã�����pcap_compile()�ȣ��Ĳ���������ָ����һ���Ѿ��򿪵�Winpcap�Ự�����������������£�������NULL���ҡ�errbuf�����������˴�����Ϣ��
	*/

	if (adapter_handle == NULL)
	{
		fprintf(stderr, "\n Unable to open adapter: %s\n", adapter->name);
		pcap_freealldevs(all_adapters);
		return -1;
	}

	pcap_loop(adapter_handle, NULL, ethernet_protocol_packet_callback, NULL);


	/*���е�һ��������pcap�ľ��, �ڶ�����ָ����������ݰ�����,pcap
	���Ϊ - 1������ѭ�����񡣵��ĸ�����user�������û�ʹ�õġ�
	�������ǻص�������ԭ������ :
	pcap_callback(u_char* argument, const struct pcap_pkthdr* packet_header, const u_char* packet_content)
	���в���pcap_content��ʾ�Ĳ��񵽵����ݰ�������
	����argument�ǴӺ���pcap_loop()���ݹ����ġ�ע�⣺����Ĳ�������ָ pcap_loop�е� *user ����
	����pcap_pkthdr ��ʾ���񵽵����ݰ�������Ϣ, ����ʱ��, ���ȵ���Ϣ.
	����:�ص�����������ȫ�ֺ�����̬����, �����Ĭ��, ����pcap_loop()����д��
	pcap_loop(pcap_handle, 10, pcap_callback, NULL)���������洫��ʵ��.
	*/

	pcap_close(adapter_handle);
	pcap_freealldevs(all_adapters);
	return 0;
}
