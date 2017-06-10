#include "Http.h"



int main(int argc, char **argv)
{
	Shdl::CHttp *http = new Shdl::CHttp();

	// http->Request("http://127.0.0.1:8080/test.m3u8"); // test local http server
	http->Request("www.baidu.com");
	http->Request("http://live.hkstv.hk.lxdns.com/live/hks/playlist.m3u8");
	http->Request("http://dlhls.cdn.zhanqi.tv/zqlive/34338_PVMT5.m3u8");
	
	delete http;
	http = NULL;

	return 0;
}