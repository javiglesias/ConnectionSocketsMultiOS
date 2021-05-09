#include "Connection.h"
#include "ServerConnection.h"

int main(int args, char** argv)
{
	if(args > 1) // TODO by default its gonna launch on client mode
	{
		ServerConnection serv_conn;
		serv_conn.init();
	}
	else
	{
		Connection conn("localhost", "admin", "passwd");
		conn.init();
	}
	return 0;
}
