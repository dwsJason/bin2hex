//
// BINFile Class
//

#ifndef BINFILE_H_
#define BINFILE_H_

#include <string>
#include <vector>

#include "bctypes.h"
#include "memstream.h"

// Forward references

class ORGFile;

//------------------------------------------------------------------------------

//class BINSection
//{
//	BINSection();
//	~BINSection() {}
//
//	i32 m_org;
//	i32 m_length;
//};

class BINFile
{
public:
	BINFile( ORGFile& org_file );
	~BINFile();

	void MapIntoMemory(ORGFile& org_file );

	// Serialize and apply relocation data, into the m_pRAM
	void LoadIntoMemory();

	void SaveAsHex(std::string filepath);

private:
	std::string m_filepath;
//	std::vector<BINSection> m_sections;

	u8* m_pRawData;

	// 16 megabytes of 65816 flat memory space
	u8* m_pRAM;

};

#endif // BINFILE_H_

