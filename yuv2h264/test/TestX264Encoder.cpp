#include <unistd.h>

#include "VideoCapture.h"


int main(int argc, char **argv)
{
	CVideoCapture capture;

	capture.Start();

	capture.EventHandleLoop();

	capture.Stop();

	return 0;
}


