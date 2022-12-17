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

class BINSection
{
public:
	BINSection(const std::string& filename, i32 org);
	~BINSection()
	{
		if (m_data)
		{
			delete m_data;
			m_data = nullptr;
		}
	}

	std::string m_name;
	i32 m_org;
	i32 m_length;
	u8* m_data;

};

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
	std::vector<BINSection*> m_sections;
};

#endif // BINFILE_H_

