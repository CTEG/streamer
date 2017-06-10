#ifndef __ISTREAMDOWNLOAD_H__
#define __ISTREAMDOWNLOAD_H__

#include <string>


namespace Shdl {

class IDataCallback
{
public:
	// virtual ~IDataCallback() {};

	virtual void HttpDlData(const void *context, const void *data, const size_t size) = 0;
};

class IStreamDownload
{
public:
	static IStreamDownload *Create();

	// virtual ~IStreamDownload() {};

	virtual void Destroy() = 0;

	virtual void SetCallback(void *context, IDataCallback *pcbk) = 0;

	virtual int FetchStream(std::string url) = 0;
};

} // end namespace

#endif