#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//pΪ���ģ�nΪp�ĳ��ȣ�des_ivΪ����DES�㷨��CFBģʽ����ʱ��Ҫ��8�ֽڳ�ʼ����

typedef struct rc4_key
{
     unsigned char state[256];
     unsigned char x;
     unsigned char y;
} rc4_key;

static void swap_byte(unsigned char *a, unsigned char *b)
{
   unsigned char swapByte;
   swapByte = *a;
   *a = *b;
   *b = swapByte;
}
 
void prepare_key(unsigned char *key_data_ptr, int key_data_len, rc4_key *key)
{
   unsigned char swapByte;
   unsigned char index1;
   unsigned char index2;
   unsigned char *state;
   short counter;

   state = &key->state[0];
   for(counter = 0; counter < 256; counter++)
      state[counter] = counter; /* ��ʼ��256����Կ */
   key->x = 0;
   key->y = 0;
   index1 = 0;
   index2 = 0;
   for(counter = 0; counter < 256; counter++)
   {   /*[%] key_data_ptrΪ������Կ, ������԰���[1,256]���ֽ�, ����256�ֽڵĲ������� */
       /*[%] ����ѭ������key_data_ptr����state, ע��256��stateֻ����, ����ֵ */
       index2 = (key_data_ptr[index1] + state[counter] + index2) % 256;
       swap_byte(&state[counter], &state[index2]);
       index1 = (index1 + 1) % key_data_len;
   }
}

void rc4(unsigned char *buffer_ptr, int buffer_len, rc4_key *key)
{
   unsigned char x;
   unsigned char y;
   unsigned char *state;
   unsigned char xorIndex;
   short counter;

   x = key->x;
   y = key->y;

   state = &key->state[0];
   for(counter = 0; counter < buffer_len; counter ++)
   {
      x = (x + 1) % 256;
      y = (state[x] + y) % 256;
      swap_byte(&state[x], &state[y]); /*[%] ����/����ǰ, ����һ��state */

      /* xorIndex = state[x] + (state[y]) % 256; */
      /*[%] ����������ԭ����д�����, �����ܲ������ı���, �ʸĳ��������: */
      xorIndex = (state[x] + state[y]) % 256; /*[%] ������Կ��index */
      buffer_ptr[counter] ^= state[xorIndex]; /*[%] state[xorIndex]Ϊ��ǰ��Կ */
   }
   key->x = x; /* ����x��y������state���±�, ʹ���´�rc4()�����뱾�ε��ÿ����ν� */
   key->y = y;
}



void des_encrypt(unsigned char *block, unsigned char *des_key)
{
	;
}

void des_cfb_encrypt(unsigned char p[], int n, unsigned char des_seed_iv[],
/*=================*/ unsigned char des_iv[], unsigned char des_seed_key[])
{
	int i,j, bytes = 1;
	
	unsigned char state[8];  
	
	for(i = 0; i<8; i++)
	{
		state[i] = des_seed_iv[i] ^ des_iv[i];
	}
	
	unsigned char des_key[8];
    
	for(i = 0; i<8; i++)
	{
		des_key[i] = des_seed_key[i] ^ state[i];
	}
	for (i = 0; i<8; i++)
        if (des_key[i] >= 'a' && des_key[i] <= 'z')
            des_key[i] -= 32;
	
	unsigned char sv[8], t[16];
	unsigned char c[0x200] = {0}; //���� 
	int s = 0;
	
	memcpy(sv, des_iv, 8);
	while(n >= bytes)
	{
		n -= bytes;
		memcpy(t, sv, 8);
		des_encrypt(t, des_key); //t[0]...t[7]������ 
		memset(t+8, 0, 8);
		memcpy(t+8, p, bytes);//t[8] = p[0]
		p += bytes;
		
		for(j=0; j<8; j++)
			t[j+8] ^= t[j];
		 
		c[s++] = t[8];
		
		memcpy(t, sv, 8);//t[0] - t[7]����Ϊԭ����sv 
		memcpy(t, t+1, 8);//t[1] -> t[0]...t[8] -> t[7]�ƶ� 
		memcpy(sv, t, 8);//����sv 
		memcpy(des_iv, t, 8);
	}
	for(i=0; i<s; i++) //[%] �������п��ܰ���������ʾ���ַ�, ����ʮ��������� 
    	printf("%X", c[i]);
}

main()
{
   /*
   input:
   ABCD1234 DEARSEED DEADBEEF Hello123
   output:
   A69AFFEA65AB11E3
   */
   unsigned char rc4_seed_key[0x40], des_seed_iv[0x40], des_seed_key[0x40];
   unsigned char des_iv[0x40],  des_key[0x40];
   rc4_key k;
   unsigned char p[0x100];

   scanf("%s %s %s %s", rc4_seed_key, des_seed_iv, des_seed_key, p);
   prepare_key(rc4_seed_key, strlen(rc4_seed_key), &k);
   strcpy(des_iv, des_seed_iv);
   rc4(des_iv, strlen(des_iv), &k);
   
   printf("%d\n", strlen(p));

   /* ע������3�仰��ע�͵���:
   prepare_key(rc4_seed_key, strlen(rc4_seed_key), &k);
   strcpy(des_key, des_seed_key);
   rc4(des_key, strlen(des_key), &k);
   */
   des_cfb_encrypt(p, strlen(p), des_seed_iv, des_iv, des_seed_key);
}
