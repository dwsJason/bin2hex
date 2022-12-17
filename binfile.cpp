//
// omffile.cpp
//
#include "binfile.h"
#include "hexfile.h"
#include "orgfile.h"

#include "bctypes.h"
#include "memstream.h"  // Jason's memory stream thing
#include "minialloc.h"

#include <stdio.h>


// -----------------------------------------------------------------------------

// Static Local Helper functions
//
// Fixed Label, probably doesn't have a zero termination
//
static std::string FixedLabelToString( u8* pLabel, size_t numBytes )
{
	std::string result;
	result.insert(0, (char*)pLabel, numBytes);
	return result;
}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
BINFile::BINFile( ORGFile& org_file )
{

	for (u32 index = 0; index < org_file.NumSections(); ++index)
	{
		BINSection* pBINSection = new BINSection(org_file.GetSectionName(index),org_file.GetAddress(index));

		m_sections.push_back(pBINSection);

	}
}

//------------------------------------------------------------------------------

BINFile::~BINFile()
{
}

//------------------------------------------------------------------------------

void BINFile::SaveAsHex(std::string filepath)
{
	// Step 1, build a memory address sorted list of the segments, to make
	// the output as small as possible

	std::vector<BINSection*> sections;

	for (int idx = 0; idx < m_sections.size(); ++idx)
	{
		BINSection* pSection = m_sections[ idx ];

		int insert_index = 0;

		for (;insert_index < sections.size(); ++insert_index)
		{
			if (sections[ insert_index ]->m_org > pSection->m_org)
				break;
		}

		sections.insert(sections.begin()+insert_index, pSection);
	}

	#if 0
	{
		for (int idx = 0; idx < sections.size(); ++idx)
		{
			printf("%2d %06x\n", idx, sections[idx]->m_org);
		}
	}
	#endif

	// Step 2, create hex file object

	HexFile hex( filepath );

	// Step 3, serialize

	for (int idx = 0; idx < sections.size(); ++idx)
	{
		BINSection* pSection = sections[ idx ];
		hex.SaveBytes(pSection->m_data, pSection->m_org, pSection->m_length);
	}

	hex.EndOfFile();
}

//------------------------------------------------------------------------------

BINSection::BINSection(const std::string& filename, i32 org)
	: m_name(filename)
	, m_org(org)
	, m_data(nullptr)
{
	FILE* pFile = nullptr;
	errno_t err = fopen_s(&pFile, filename.c_str(), "rb");

	if (0==err)
	{
		fseek(pFile, 0, SEEK_END);
		size_t length = ftell(pFile);
		fseek(pFile, 0, SEEK_SET);

		printf("Reading %s - %lld bytes\n", filename.c_str(), length);

		m_length = (i32)length;

		m_data = new u8[ length ];

		fread(m_data, sizeof(u8), length / sizeof(u8), pFile);

		fclose(pFile);
	}
	else
	{
		printf("BINFile could not open %s\n", filename.c_str());
		printf("This file will be missing from the export\n");
	}

}

//------------------------------------------------------------------------------

