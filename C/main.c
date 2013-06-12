#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static char* find_and_replace(char *orig, char *finder, char *replacer)
{
	char buffer[5000];
	char temp1[1000] = "";
	char temp2[1000] = "";
	char *reply;
	int  l_index;

	memset(buffer,0,sizeof(buffer));
	reply   = NULL;
	l_index = 0;

	while(*orig)
	{
		// Move html keywords
		if('<' == *orig)
		{
			while(('>' != *orig) && ('\0' != *orig))
			{
				buffer[l_index++] = *orig;
				orig++;
			}
			buffer[l_index++] = '>';
			orig++;
		}
		else // Get 'real' data & replace
		{
			int j;
			char *p;
			char *p1 = temp1;// original
			char *p2 = temp2;// modified

			// Get 'real' data
			while(('<' != *orig) && ('\0' != *orig))
			{
				temp1[j++] = *orig;
				orig++;
			}
			temp1[j]='\0';

			// Search & Replace
			strncpy(temp2,p1,strlen(p1));

			while ( (p = strstr (p1,finder)) )
			{
				sprintf(p2 + (p-p1), "%s%s", replacer, p + strlen(finder));
				p2 = p2 + ((p - p1) + strlen(replacer));
				p1 = p1 + (p - p1 + strlen(finder));
			}

			// Append into buffer
			strcat(buffer,temp2);
			l_index = l_index + strlen(temp2);
		}
	}

	reply = buffer;

	return reply;
}

int main(void)
{
	FILE *file1;
	FILE *file2;
	char data[5000];
	int index1 = 0;
	int index2 = 0;

	file1 = fopen("/home/ceslab/Desktop/dantri.txt","r");
	if(NULL == file1)
	{
		fprintf(stderr,"Can't open file1!");
		exit(EXIT_FAILURE);
	}

	file2 = fopen("/home/ceslab/Desktop/dantri_modified.txt","w");
	if(NULL == file2)
	{
			fprintf(stderr,"Can't open file2!");
			exit(EXIT_FAILURE);
	}

	while(!feof(file1))
	{
		// Maybe html file greater than data size
		while(index1 < sizeof(data))
		{
			data[index1++] = fgetc(file1);
		}

		find_and_replace(data," ","_");

		// Write data modified
		while('\0' != data[index2])
		{
			fputc(data[index2++],file2);
		}

		index1 = 0;
	}

	fprintf(stdout,"Successfully!");
	fclose(file1);
	fclose(file2);

	exit(EXIT_SUCCESS);
}

