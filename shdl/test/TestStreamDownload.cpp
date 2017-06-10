#include <string.h>
#include <stdio.h>
#include <string>

#include "shdl/IStreamDownload.h"



class CTestStreamDownload : public Shdl::IDataCallback
{
public:
	CTestStreamDownload();
	~CTestStreamDownload();

	virtual void HttpDlData(const void *context, const void *data, const size_t size);
};

CTestStreamDownload::CTestStreamDownload()
{
}

CTestStreamDownload::~CTestStreamDownload()
{
}

void CTestStreamDownload::HttpDlData(const void *context, const void *data, const size_t size)
{
	printf("%lu\n", size);

	return;
}

int main(int argc, char **argv)
{
	std::string url = "http://127.0.0.1:8080/?action=stream";
	Shdl::IStreamDownload *pdl = Shdl::IStreamDownload::Create();
	CTestStreamDownload testDl;

	pdl->SetCallback(&testDl, &testDl);
	pdl->FetchStream(url);

	pdl->Destroy();

	return 0;
}

