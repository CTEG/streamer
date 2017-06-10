#include <string>

#include "StreamDownload.h"



int main(int argc, char **argv)
{
	HttpDl::CStreamDownload dl;
	std::string url = "http://127.0.0.1:8080/?action=stream";

	dl.FetchStream(url);

	return 0;
}