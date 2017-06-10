#ifndef __STREAMDOWNLOAD_H__
#define __STREAMDOWNLOAD_H__

#include <string>



namespace Shdl {

class CStreamDownload
{
public:
	CStreamDownload();
	~CStreamDownload();
	
	void FetchStream(std::string url);
};

} // end namespace

#endif