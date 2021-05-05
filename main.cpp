#include "Connection.h"

int main()
{
	Connection conn("localhost", "admin", "passwd");
	getchar();
	conn.init();
	return 0;
}
