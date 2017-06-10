#include <string.h>
#include <stdio.h>

#include "Http.h"
#include "StreamDownload.h"



namespace Shdl {

IStreamDownload *IStreamDownload::Create()
{
	return new CStreamDownload();
}

static void Parser(void *context, void *contents, size_t size)
{
	CStreamDownload *thiz = (CStreamDownload *)context;

	if(thiz != NULL) {
		thiz->DataCbk(contents, size);
	}

    return;
}

CStreamDownload::CStreamDownload()
{
}

CStreamDownload::~CStreamDownload()
{
}

void CStreamDownload::Destroy()
{
	delete this;
}

void CStreamDownload::SetCallback(void *context, IDataCallback *pcbk)
{
	m_context = context;
	m_pcbk = pcbk;

	return;
}

void CStreamDownload::DataCbk(void *contents, size_t size)
{
	m_pcbk->HttpDlData(m_context, contents, size);

	return;
}

int CStreamDownload::FetchStream(std::string url)
{
	int res = -1;
	CHttp *http = new CHttp(Parser, this);

	res = http->Request(url);
	
	delete http;
	http = NULL;

	return res;
}

} // end namespace

