// bin2hex.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>

#include "orgfile.h"
#include "binfile.h"

//------------------------------------------------------------------------------
void helpText()
{
	printf("bin2hex - v1.0\n");
	printf("--------------\n");
	printf("Convert a collection of BIN files into an\n");
	printf("Intel HEX file\n");
	printf("\nbin2hex <ORG_File> <HEX_File>\n");

	exit(-1);
}

//------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	char* pInfilePath  = nullptr;
	char* pOutfilePath = nullptr;

	if (argc >= 2)
	{
		pInfilePath = argv[1];
	}
	if (argc >= 3)
	{
		pOutfilePath = argv[2];
	}

	if (pInfilePath)
	{
		// Load the ORG File
		ORGFile* org_file = new ORGFile( std::string(pInfilePath) );

		// Load the files in the .org file, into memory
		BINFile bin_file( *org_file );

		if (pOutfilePath)
		{
			bin_file.SaveAsHex( pOutfilePath );
		}

	}
	else
	{
		helpText();
	}


	return 0;
}

