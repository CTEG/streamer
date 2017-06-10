#ifndef __STREAMDOWNLOAD_H__
#define __STREAMDOWNLOAD_H__

#include <string>

#include "shdl/IStreamDownload.h"


namespace Shdl {

class CStreamDownload : public IStreamDownload
{
public:
	virtual void Destroy();
	virtual void SetCallback(void *context, IDataCallback *pcbk);
	virtual int FetchStream(std::string url);

	void DataCbk(void *contents, size_t size);

	CStreamDownload();
	~CStreamDownload();

private:
	void*			m_context;
	IDataCallback*	m_pcbk;
};

} // end namespace

#endif