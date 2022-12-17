//
// ORGFile Class
//

#ifndef ORGFILE_H_
#define ORGFILE_H_

#include <string>
#include <vector>

#include "bctypes.h"
#include "memstream.h"

//------------------------------------------------------------------------------

class ORGFile
{
public:
	ORGFile( std::string filepath );
	~ORGFile();

	u32 GetAddress(std::string sectionName);

	u32 GetAddress(u32 index)
	{
		return m_orgs[index];
	}

	u32 NumSections() { return (u32)m_sections.size(); }

	const std::string& GetSectionName(u32 index)
	{
		return m_sections[index];
	}


private:
	std::string m_filepath;

	std::vector<std::string> m_sections;
	std::vector<u32> m_orgs;
};

#endif // ORGFILE_H_


