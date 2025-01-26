#include<stdio.h>
#include<stdlib.h>

#define HAVE_REMOTE
#include<pcap.h>

#pragma warning(disable:4996)
#define ETHERNET_IP 0x0800
#define MAX_SIZE 2048

int size_of_packet = 0;
u_int32_t crc32_table[256];

//ethernet header
struct ethernet_header
{
	u_int8_t dest_mac[6];
	u_int8_t src_mac[6];
	u_int16_t ethernet_type;
};

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
	int i, j;
	u_int32_t crc;
	crc = 0xffffffff;
	for (i = 0; i < len; i++)
	{
		crc = (crc >> 8) ^ crc32_table[(crc & 0xFF) ^ buffer[i]];
	}
	crc ^= 0xffffffff;
	return crc;
}


void load_ethernet_header(u_int8_t *buffer)
{
	struct ethernet_header *hdr = (struct ethernet_header*)buffer;
	/*int i = 0;
	for (i = 0; i < 6; i++)
	{
		hdr->dest_mac[i] = 0x11;//this is where you can define the mac address
	}
	for (i = 0; i < 6; i++)
	{
		hdr->src_mac[i] = 0x22;//source mac address
	}*/
	hdr->dest_mac[0] = 0x00;
	hdr->dest_mac[1] = 0x09;
	hdr->dest_mac[2] = 0x73;
	hdr->dest_mac[3] = 0x07;
	hdr->dest_mac[4] = 0x74;
	hdr->dest_mac[5] = 0x73;

	hdr->src_mac[0] = 0x00;
	hdr->src_mac[1] = 0x09;
	hdr->src_mac[2] = 0x73;
	hdr->src_mac[3] = 0x07;
	hdr->src_mac[4] = 0x73;
	hdr->src_mac[5] = 0xf9;
	hdr->ethernet_type = ETHERNET_IP;

	size_of_packet += sizeof(ethernet_header);
}


int load_ethernet_data(u_int8_t *buffer, FILE *fp)
{
	int size_of_data = 0;
	char tmp[MAX_SIZE], ch;
	while ((ch = fgetc(fp)) != EOF)
	{
		tmp[size_of_data] = ch;
		size_of_data++;
	}
	if (size_of_data < 46 || size_of_data>1500)
	{
		printf("Size of data is not satisfied with condition!!!\n");
		return -1;
	}

	u_int32_t crc = calculate_crc((u_int8_t*)tmp, size_of_data);
	//printf("%d\n", crc);
	int i;
	for (i = 0; i < size_of_data; i++)
	{
		*(buffer + i) = tmp[i];
	}
	*(u_int32_t*)(buffer + i) = crc;
	size_of_packet += size_of_data + 4;
	return 1;
}



int main()
{
	u_int8_t buffer[MAX_SIZE];//as a carrier of packet
	generate_crc32_table();

	//generate a packet
	size_of_packet = 0;
	FILE *fp = fopen("data.txt", "r");
	if (load_ethernet_data(buffer + sizeof(ethernet_header), fp) == -1)
	{
		return -1;
	}
	load_ethernet_header(buffer);

	//send the packet
	pcap_t *handle;
	char *device;
	char error_buffer[PCAP_ERRBUF_SIZE];
	device = pcap_lookupdev(error_buffer);
	if (device == NULL)
	{
		printf("%s\n", error_buffer);
		return -1;
	}
	handle = pcap_open_live(device, size_of_packet, PCAP_OPENFLAG_PROMISCUOUS, 1, error_buffer);
	if (handle == NULL)
	{
		printf("Open adapter is failed..\n");
		return -1;
	}
	int i = 20;
	while(i--)
	{
		pcap_sendpacket(handle, (const u_char*)buffer, size_of_packet);;
		//printf("%d", *(int*)(buffer + size_of_packet - 4));
	}
	
	pcap_close(handle);
	return 0;
	
}
