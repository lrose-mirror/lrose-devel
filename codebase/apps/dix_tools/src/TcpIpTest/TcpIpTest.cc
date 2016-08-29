
// Testing program for TcpIp connections.
//   Note: Need to compile on a machine with 
//         pthread libraries in order to have
//         multiple clients for a server-type
//         socket.

// Comment this line out if your platform does not have pthreads libraries.
// 

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>

using namespace std;

void usage(ostream &out);
int readBuffer(int sd, char *buf);
int writeBuffer(int sd, char *buf);
int beClient(const char *host, int port);
int beServer(int port);
void setSocketOptions(int sd);

int main(int argc, char **argv)
{

  if (argc > 1 && !strcmp(argv[1], "-h")) {
    usage(cout);
    return 0;
  }

  if (argc != 3 && argc != 4) {
    usage(cerr);
    return -1;
  }
  
  if (!strcmp(argv[1], "server") && argc == 3) {
    
    // Get the port from argv[2]
    
    int port;
    if (sscanf(argv[2], "%d", &port) != 1) {
      cerr << "ERROR - bad port arg: " << argv[2] << endl;
      usage(cerr);
      return -1;
    }
    
    return beServer(port);
    
  } else if (!strcmp(argv[1], "client") && argc == 4) {
    
    // The host is argv[2].
    
    const char *host = argv[2];
    
    // Get the port from argv[3]

    int port;
    if (sscanf(argv[3], "%d", &port) != 1) {
      cerr << "ERROR - bad port arg: " << argv[3] << endl;
      usage(cerr);
      return -1;
    }
    
    // be a client
    
    return beClient(host, port);

  }

  usage(cerr);
  return -1;
  
}

void usage(ostream &out)
{
  out << "Usage: TcpIpTest [-h] "
      << "[server port | client host port ]"
      << endl;
}

int beClient(const char *host, int port)

{

  struct sockaddr_in rem_soc;
  struct hostent *hostport; // host port info
  hostport = gethostbyname(host); // get the remote host info
  if(!hostport) {
    cerr << "ERROR - beClient" << endl;
    cerr << "  gethostbyname() failed" << endl;
    return -1;
  }
  
  // copy the remote sockets internet address to local hostport struc
  
  rem_soc.sin_family = AF_INET;
  memcpy(&rem_soc.sin_addr, hostport->h_addr, sizeof(rem_soc.sin_addr));
  rem_soc.sin_port = port; // fill in port number */
  rem_soc.sin_port = htons(rem_soc.sin_port); 
  
  // get a file descriptor for the connection to the remote port
  
  int sd;
  if((sd = socket(AF_INET,SOCK_STREAM,0)) == -1) {
    cerr << "ERROR - beClient" << endl;
    cerr << "  socket() failed" << endl;
    return -1;
  }

  // Connect

  errno = 0;
  if(connect(sd, (struct sockaddr *) &rem_soc, sizeof(rem_soc)) < 0) {
    close(sd);
    cerr << "ERROR - beClient" << endl;
    cerr << "  connect() failed" << endl;
    return -1;
  }
  
  setSocketOptions(sd);

  // write a buffer of len nbytes, then read one
  
  char buf[BUFSIZ];
  sprintf(buf, "Test string\n");
  writeBuffer(sd, buf);
  readBuffer(sd, buf);

  // close

  close(sd);
  return 0;

}

int beServer(int port)

{

  // open the server

  int protoSd;

  if((protoSd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    cerr << "ERROR - beServer" << endl;
    cerr << "  socket() failed" << endl;
    return -1;
  }

  //  set socket options

  setSocketOptions(protoSd);
  
  // local sock info

  struct sockaddr_in loc_soc;
  loc_soc.sin_port = htons(port);
  loc_soc.sin_family = AF_INET;
  loc_soc.sin_addr.s_addr = htonl(INADDR_ANY);
  
  // bind to a local port

  errno = 0;
  if(bind(protoSd,
	  (struct sockaddr *) &loc_soc,
	  sizeof(loc_soc)) < 0) {
    cerr << "ERROR - beServer" << endl;
    cerr << "  bind() failed" << endl;
    close(protoSd);
    return -1;
  }
  
  // Wait for remote connection request

  errno = 0;
  if (listen(protoSd, 5) < 0) {
    cerr << "ERROR - beServer" << endl;
    cerr << "  listen() failed" << endl;
    close(protoSd);
    return -1;
  }
  
  while (true) {
    
    cerr << "==============================================" << endl;
    cerr << "Waiting for client" << endl;

    // accept a client

#if (defined (__linux))
    socklen_t name_len = sizeof(struct sockaddr_in);
#else
    int name_len = sizeof(struct sockaddr_in);
#endif
    errno = 0;
    union sunion {
      struct sockaddr_in sin;
      struct sockaddr_un sund;
    } sadd;
    
    int sd = -1;
    if((sd = accept(protoSd,
		    (struct sockaddr *) &sadd,
		    &name_len)) < 0) {
      cerr << "ERROR - beServer" << endl;
      cerr << "  accept() failed" << endl;
      close(protoSd);
      return -1;
    }
    
    setSocketOptions(sd);

    // read buffer then write it back to client
    
    char buf[BUFSIZ];
    readBuffer(sd, buf);
    writeBuffer(sd, buf);

    close (sd);
    
  }

  close (protoSd);
  return 0;

}

int writeBuffer(int sd, char *buf)

{

  char *writePtr = buf;
  
  while(*writePtr != '\0') {
    errno = 0;
    int bytesWritten = write(sd, writePtr, 1);
    if(bytesWritten <= 0) {
      if (errno != EINTR) { // system call was not interrupted
	cerr << "ERROR writing" << endl;
	sleep(1);
      }
    } else {
      writePtr += 1;
    }
  }
  
  cerr << "String written: " << buf << endl;

  return 0;

}

int readBuffer(int sd, char *buf)

{

  // read a buffer of nbytes
  
  char *readPtr = buf;
  char cc = 'a';
  
  while(cc != '\n') {
    
    errno = 0;
    int bytesRead = read(sd, &cc, 1);
    
    if (bytesRead <= 0) {
      if (errno != EINTR) { // system call was not interrupted
	cerr << "ERROR reading" << endl;
      }
    } else {
      *readPtr = cc;
      readPtr += 1;
    }

    if (cc == '\n') {
      // null terminate, done
      *readPtr = '\0';
      readPtr += 1;
    }

  }
  
  cerr << "String read: " << buf << endl;

  return 0;

}

  
void setSocketOptions(int sd)
{

  // reuse the socket

  int val = 1;
  int valen = sizeof(val);
  setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *) &val, valen);
  
}
