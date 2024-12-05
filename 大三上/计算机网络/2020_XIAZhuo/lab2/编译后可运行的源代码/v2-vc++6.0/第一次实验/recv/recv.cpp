#include<stdio.h>
#include<stdlib.h>


#define HAVE_REMOTE
#include<pcap.h>
#include<WinSock2.h>

#pragma warning(disable:4996)
#pragma comment(lib,"packet.lib")
#pragma comment(lib,"wpcap.lib")
#pragma comment(lib,"ws2_32.lib")

void ethernet_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *packet_header, const u_char *packet_content);

//ethernet protocol header format
struct ethernet_header
{
	u_int8_t ether_dhost[6];//destination mac
	u_int8_t ether_shost[6];//src mac
	u_int16_t ether_type;
};

u_int8_t accept_dest_mac[2][6] = { { 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 }, { 0x33, 0x33, 0x33, 0x33, 0x33, 0x33 } };
u_int32_t crc32_table[256];
//generate table
void generate_crc32_table()
{
	int i, j;
	u_int32_t crc;
	for (i = 0; i < 256; i++)
	{
		crc = i;
		for (j = 0; j < 8; j++)
		{
			if (crc & 1)
				crc = (crc >> 1) ^ 0xEDB88320;
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


//ethernet protocol analysis
void ethernet_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *packet_header, const u_char *packet_content)
{
	u_short ethernet_type;
	struct ethernet_header *ethernet_protocol;
	u_char *mac_string;
	static int packet_number = 1;
	ethernet_protocol = (struct ethernet_header*)packet_content;
	int len = packet_header->len;
	int i, j;

	////check the mac address
	////if the packet is sended to my pc or broadcast
	int flag = 2;
	for (i = 0; i < 2; i++)
	{
		flag = 2;
		for (j = 0; j < 6; j++)
		{
			if (ethernet_protocol->ether_dhost[j] == accept_dest_mac[i][j])
				continue;
			else
			{
				flag = i;
				break;
			}
		}
		if (flag != 2)continue;
		else
			break;
	}
	if (flag != 2)
	{
		return;
	}
	if (i == 0)
	{
		printf("It's broadcasted.\n");
	}
	

	//see if the data is changed or not
	u_int32_t crc = calculate_crc((u_int8_t*)(packet_content + sizeof(ethernet_header)), len - 4 - sizeof(ethernet_header));
	if (crc != *((u_int32_t*)(packet_content + len - 4)))
	{
		printf("The data has been changed.\n");
		return;
	}
	
	printf("----------------------------\n");
	printf("capture %d packet\n", packet_number);
	printf("capture time: %d\n", packet_header->ts.tv_sec);
	printf("packet length: %d\n", packet_header->len);
	printf("-----Ethernet protocol-------\n");
	
	ethernet_type = ethernet_protocol->ether_type;
	printf("Ethernet type: %04x\n", ethernet_type);
	switch (ethernet_type)
	{
	case 0x0800:printf("Upper layer protocol: IPV4\n"); break;
	case 0x0806:printf("Upper layer protocol: ARP\n"); break;
	case 0x8035:printf("Upper layer protocol: RARP\n"); break;
	case 0x814c:printf("Upper layer protocol: SNMP\n"); break;
	case 0x8137:printf("Upper layer protocol: IPX\n"); break;
	case 0x86dd:printf("Upper layer protocol: IPV6\n"); break;
	case 0x880b:printf("Upper layer protocol: PPP\n"); break;
	default:
		break;
	}

	mac_string = ethernet_protocol->ether_shost;
	printf("MAC source address: %02x:%02x:%02x:%02x:%02x:%02x\n", *mac_string, *(mac_string + 1), *(mac_string + 2), *(mac_string + 3),
		*(mac_string + 4), *(mac_string + 5));
	mac_string = ethernet_protocol->ether_dhost;
	printf("MAC destination address: %02x:%02x:%02x:%02x:%02x:%02x\n", *mac_string, *(mac_string + 1), *(mac_string + 2),
		*(mac_string + 3), *(mac_string + 4), *(mac_string + 5));

	/*if (ethernet_type == 0x0800)
	{
		ip_protocol_packet_callback(argument, packet_header, packet_content + sizeof(ethernet_header));
	}
*/
	//show the data;
	for (u_int8_t *p = (u_int8_t*)(packet_content + sizeof(ethernet_header)); p != (u_int8_t*)(packet_content + packet_header->len - 4); p++)
	{
		printf("%c", *p);
	}
	printf("\n");

	printf("----------------------\n");
	packet_number++;
}

int main()
{
	generate_crc32_table();

	pcap_if_t *all_adapters;
	pcap_if_t *adapter;
	pcap_t *adapter_handle;
	char error_buffer[PCAP_ERRBUF_SIZE];

	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &all_adapters, error_buffer) == -1)
	{
		fprintf(stderr, "Error in findalldevs_ex function: %s\n", error_buffer);
		return -1;
	}
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
	adapter_handle = pcap_open(adapter->name, 65535, PCAP_OPENFLAG_PROMISCUOUS, 5, NULL, error_buffer);
	if (adapter_handle == NULL)
	{
		fprintf(stderr, "\n Unable to open adapter: %s\n", adapter->name);
		pcap_freealldevs(all_adapters);
		return -1;
	}

	pcap_loop(adapter_handle, NULL, ethernet_protocol_packet_callback, NULL);
	pcap_close(adapter_handle);
	pcap_freealldevs(all_adapters);
	return 0;
}
