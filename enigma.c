#include<stdio.h>
#include<string.h>

char refleCor[]="YRUHQSLDPXNGOKMIEBFZCWVJAT"; 
char rotor_table[5][27] = 
{
 "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
 "AJDKSIRUXBLHWTMCQGZNPYFVOE",
 "BDFHJLCPRTXVZNYEIWGAKMUSQO",
 "ESOVPZJAYQUIRHXLNFTGKDCMWB",
 "VZBRGITYUPSDNHLXAWMJQOFECK"
};
char step_char[5]="RFWKA"; // Royal Flags Wave Kings Above 
char alphabet[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char RingSettinga, RingSettingb, RingSettingc;
char RingSetting[3];



int main()
{
	char result[30];
	char Word[30];
	char PlainText[510];
	char Plugboard[10][3];
	char CypherText[510];
	int rotorc, rotorb, rotora;//未知的三个轮子的顺序 
	
	int Messagea, Messageb, Messagec;
	int Bmessagea, Bmessageb, Bmessagec;
	int deltaa, deltab, deltac;
	
	int time;//总共多少次 进入密码机 
	int num;//反射板 
	int sun;//看看提供的单词在字符串什么位置 
	char C;
	
	int i;
	for(i = 0;i < 10; i++)
	{
		scanf("%s", Plugboard[i]);//输入Plugboard 
	}
	scanf("%s", RingSetting);
	RingSettinga = RingSetting[2];
	RingSettingb = RingSetting[1];
	RingSettingc = RingSetting[0];
	
	scanf("%s", CypherText);
	scanf("%s", Word);
	scanf("%d", &rotorc);
	
	int m = strlen(CypherText);
	int n = strlen(Word);
	
	for(rotora = 1; rotora<=5; rotora++)//求三个轮子的序号 
		if(rotora!=rotorc)
	for(rotorb = 1; rotorb<=5; rotorb++)
		if(rotorb!=rotorc && rotorb!=rotora)
	for (Bmessagea = 0; Bmessagea<26; Bmessagea++)
	for (Bmessageb = 0; Bmessageb<26; Bmessageb++)
	for (Bmessagec = 0; Bmessagec<26; Bmessagec++)
	{
		Messagea = Bmessagea+'A';
		Messageb = Bmessageb+'A';
		Messagec = Bmessagec+'A';
		for (time = 0; time < m; time++)
		{
			C = CypherText[time];
			for(i = 0; i<10; i++)//进接线板
			{
				if(C == Plugboard[i][0])
					C = Plugboard[i][1];
				else if(C == Plugboard[i][1])
					C = Plugboard[i][0];
			}
		
			if(Messagea != 'Z')
				Messagea = Messagea + 1;//转齿轮
			else
				Messagea = 'A';
			if ((Messagea) == (step_char[rotora-1]) || Messageb ==  (step_char[rotorb-1]-1) )
			{
				if ( Messageb == (step_char[rotorb-1]-1) )
				{
					if(Messagec != 'Z')
						Messagec = Messagec + 1;//转齿轮
					else
						Messagec = 'A';
				}
				if(Messageb != 'Z')
					Messageb = Messageb + 1;//转齿轮
				else
					Messageb = 'A'; 
			}
			
			deltaa = Messagea - RingSettinga;//经过齿轮A
			C = ((C - 'A') + deltaa + 26) % 26 + 'A';
			C = rotor_table[rotora-1][C - 'A'];
			C = ((C - 'A') - deltaa + 26) % 26 + 'A';
	
			deltab = Messageb - RingSettingb;//经过齿轮b
			C = ((C - 'A') + deltab + 26) % 26 + 'A';
			C = rotor_table[rotorb-1][C - 'A'];
			C = ((C - 'A') - deltab + 26) % 26 + 'A';
	
			deltac = Messagec - RingSettingc;//经过齿轮c
			C = ((C - 'A') + deltac + 26) % 26 + 'A';
			C = rotor_table[rotorc-1][C - 'A'];
			C = ((C - 'A') - deltac + 26) % 26 + 'A';
	
			for (num = 0; num < 26; num++)//反射板
			{
				if (refleCor[num] == C)
				{
					C = alphabet[num];
					break;
				}
			}
	
			deltac = Messagec - RingSettingc;//经过齿轮c
			C = ((C - 'A') + deltac + 26) % 26 + 'A';
			for (num = 0; num < 26; num++)
			{
				if (rotor_table[rotorc-1][num] == C)
				{
					C = alphabet[num];
					break;
				}
	
			}
			C = ((C - 'A') - deltac + 26) % 26 + 'A';
	
			deltab = Messageb - RingSettingb;//经过齿轮b
			C = ((C - 'A') + deltab + 26) % 26 + 'A';
			for (num = 0; num < 26; num++)
			{
				if (rotor_table[rotorb-1][num] == C)
				{
					C = alphabet[num];
					break;
				}
	
			}
			C = ((C - 'A') - deltab + 26) % 26 + 'A';
	
			deltaa = Messagea - RingSettinga;//经过齿轮a
			C = ((C - 'A') + deltaa + 26) % 26 + 'A';
			for (num = 0; num < 26; num++)
			{
				if (rotor_table[rotora-1][num] == C)
				{
					C = alphabet[num];
					break;
				}
	
			}
			C = ((C - 'A') - deltaa + 26) % 26 + 'A';
			
			for(i = 0; i<10; i++)//进接线板
			{
				if(C == Plugboard[i][0])
					C = Plugboard[i][1];
				else if(C == Plugboard[i][1])
					C = Plugboard[i][0];
			}
			PlainText[time] = C;
		}PlainText[m] = '\0';
		
		for (num = 0; num <510; num++)//寻找单词的位置 
		{
			for (sun = 0; sun < 30; sun++)
			{
				result[sun] = PlainText[num + sun];
			}result[n] = '\0';
			
			if ((0 == strcmp(result, Word)))
			{
				printf("MessageKey=%c%c%c\n", (char)(Bmessagec + 'A'), (char)(Bmessageb + 'A'), (char)(Bmessagea + 'A'));
				printf("PlainText=%s\n", PlainText);
				printf("RotorNum=%d%d%d\n", rotorc, rotorb, rotora);
				goto SUCCESS;
			}
		}
	}
	
	printf("%s\n", PlainText);
	
	return 0;
	SUCCESS: return 0;
}
