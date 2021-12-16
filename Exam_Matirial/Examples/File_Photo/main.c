#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char*	ReadBinaryBufferFromFile(const char* pFileIn, long* byteCount);
void	WriteBinaryBufferToFile(const char*  sFileOut,char* pImagedBuffer, long size);

#define FILE_NAME "Picture019_small.bmp"
#define FILE_NAME_DEST "Picture019_small_dest.bmp"

int main(int argc, char* argv[])
{
	long		byteCount;

	if (argc != 3)
		return 0;
	float ratio1, ratio2;

	sscanf(argv[1], "%f", &ratio1);
	sscanf(argv[2], "%f", &ratio2);

	//read the buffer from the binary file and get the size read
	char* pImagedBuffer = ReadBinaryBufferFromFile(FILE_NAME,&byteCount);
	if (pImagedBuffer == NULL)
	{
		printf("Error reading image\n");
		return;
	}
	//some buffer manipulation
	memset(pImagedBuffer + (int)(byteCount*ratio1), 0, (int)(byteCount*ratio2));

	//save the new buffer to the output file.
	WriteBinaryBufferToFile(FILE_NAME_DEST,pImagedBuffer,byteCount);

	free(pImagedBuffer);	
}



char* ReadBinaryBufferFromFile(const char* fileName, long* byteCount)
{
	FILE* fp;
	char* pImagedBuffer = NULL;		//variable to hold the picture data

	fp = fopen(fileName, "rb");
	if (!fp)
		return NULL;
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);	//what is the byte different from the file pointer location and the begginig of the file
	pImagedBuffer = (char*) malloc(size*sizeof(char)); //allocate a buffer of that size
	if (!pImagedBuffer)
		return NULL;
	fseek(fp,0, SEEK_SET);	//move file pointer location to start of file
	if( fread(pImagedBuffer, sizeof(char),size, fp)!= size)//read the file content to the buffer
	{	
		fclose(fp); //close file after use
		free(pImagedBuffer);
		return NULL;
	} 

	fclose(fp);
	*byteCount = size;		//give back the bytecount read
	return pImagedBuffer;	//return the buffer
}


//This function write the buffer to a binary file
void	WriteBinaryBufferToFile(const char*  fileName, char* pImagedBuffer, long size)
{
	FILE* fp;
	char* outImagefile = NULL;		//variable to hold the picture data

	fp = fopen(fileName, "wb");
	if (!fp)
		return;

	fwrite(pImagedBuffer, sizeof(char), size,fp);	//write the buffer to the file, write size bytes

	fclose(fp);
}
