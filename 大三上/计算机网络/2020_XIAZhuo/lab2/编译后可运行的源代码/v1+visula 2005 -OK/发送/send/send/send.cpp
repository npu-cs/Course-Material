#include<stdio.h>
#include<stdlib.h>

#define HAVE_REMOTE
#include<pcap.h>
#pragma warning(disable:4996)
#define ETHERNET_TYPE 0x0080
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


void load_ethernet_header(u_int8_t *buffer)
{
	struct ethernet_header *hdr = (struct ethernet_header*)buffer;

	// add destination mac address
	hdr->dest_mac[0] = 0x44;
	hdr->dest_mac[1] = 0x87;
	hdr->dest_mac[2] = 0xFC;
	hdr->dest_mac[3] = 0xD6;
	hdr->dest_mac[4] = 0xBD;
	hdr->dest_mac[5] = 0x8C;

	//add source mac address
	hdr->src_mac[6] =  0x44;
	hdr->src_mac[7] =  0x87;
	hdr->src_mac[8] =  0xFC;
	hdr->src_mac[9] =  0xD6;
	hdr->src_mac[10] = 0xBF;
	hdr->src_mac[11] = 0x91;

	// add source typy
	hdr->ethernet_type = ETHERNET_TYPE;

	// caculate the size of packet now
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

	//problem: < 46, ADD 0s+1byte;  >1500 LOST


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

	// NETWORK LAYER IP, ARP ICMP protocol 

	if (load_ethernet_data(buffer + sizeof(ethernet_header), fp) == -1)
	{
		return -1;
	}
	load_ethernet_header(buffer);

	//send the packet
	pcap_t *adhandle;
	pcap_if_t *alldevs;
	pcap_if_t *d;
	int i=0;
	int inum;
	char error_buffer[PCAP_ERRBUF_SIZE];

	// get the all network adapter handle 

	if (pcap_findalldevs(&alldevs, error_buffer) == -1)
	{
		printf("%s\n", error_buffer);
		return -1;
	}


	/* Print the list of all network adapter information */
	for(d = alldevs; d; d=d->next)
	{
		printf("%d. %s", ++i, d->name);
		if (d->description)
			printf(" (%s)\n", d->description);
		else
			printf(" (No description available)\n");
	}

	if(i==0)
	{
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
		return -1;
	}

	printf("Enter the interface number (1-%d):",i);
	scanf("%d", &inum);
	if(inum < 1 || inum > i)
	{
		printf("\nInterface number out of range.\n");
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return -1;
	}

	/* Jump to the selected adapter */
	for(d=alldevs, i=0; i< inum-1 ;d=d->next, i++);



	/* Open the adapter */
	if ((adhandle= pcap_open_live(d->name, // name of the device
		65536, // portion of the packet to capture.65536 grants that the whole packet will be captured on/// all the MACs.
		1, // promiscuous mode
		1000, // read timeout
		error_buffer // error buffer
		) ) == NULL)
	{
		printf("\nUnable to open the adapter. %s is not supported by WinPcap\n");
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return -1;
	}


	/* Check the link layer. We support only Ethernet for simplicity. */
	if(pcap_datalink(adhandle) != DLT_EN10MB)
	{
		printf("\nThis program works only on Ethernet networks.\n");
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return -1;
	}

	// start to send ethernet frame
	while(1)
	{
	pcap_sendpacket(adhandle, (const u_char*)buffer, size_of_packet);;
	//printf("%d", *(int*)(buffer + size_of_packet - 4));
	}
	pcap_close(adhandle);
	return 0;

}

