#include <string.h>
#include <stdio.h>
#include <string>
// #include <iostream>
// #include <fstream>

#include "shdl/IStreamDownload.h"



class CTestStreamDownload : public Shdl::IDataCallback
{
public:
	CTestStreamDownload(std::string filename);
	~CTestStreamDownload();

	virtual void HttpDlData(const void *context, const void *data, const size_t size);

private:
	FILE* m_file;
};

CTestStreamDownload::CTestStreamDownload(std::string filename)
: m_file(NULL)
{
	if(filename.size() > 0) {
		printf("filename(%s)\n", filename.c_str());
		m_file = fopen(filename.c_str(), "w+");
		if(m_file == NULL) {
			printf("can not open file\n");
		}
	}
}

CTestStreamDownload::~CTestStreamDownload()
{
	fclose(m_file);
	m_file = NULL;
}

void CTestStreamDownload::HttpDlData(const void *context, const void *data, const size_t size)
{
	if(m_file != NULL) {
		size_t num = fwrite(data, 1, size, m_file);
		printf("get(%lu), write(%lu)\n", size, num);
	}

	return;
}

int main(int argc, char **argv)
{
	std::string url = "http://127.0.0.1:8080/?action=stream";
	Shdl::IStreamDownload *pdl = Shdl::IStreamDownload::Create();
	CTestStreamDownload testDl(argv[1]);

	pdl->SetCallback(&testDl, &testDl);
	pdl->FetchStream(url);

	pdl->Destroy();

	return 0;
}

