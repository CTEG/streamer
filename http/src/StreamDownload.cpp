#include <string.h>
#include <stdio.h>

#include "Http.h"
#include "StreamDownload.h"



namespace HttpDl {


CStreamDownload::CStreamDownload()
{
}

CStreamDownload::~CStreamDownload()
{
}

static void Parser(void *context, void *contents, size_t size)
{
	printf("%lu\n", size);

    return;
}

void CStreamDownload::FetchStream(std::string url)
{
	CHttp *http = new CHttp(Parser, this);

	http->Request(url);
	
	delete http;
	http = NULL;

	return;
}

} // end namespace

