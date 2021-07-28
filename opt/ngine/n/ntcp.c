#include <ntcp.h>
#include <nutil.h>

static cntcp gtcp;


int32_t ntcp_Connected(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o)
{
  cntcp* p = (cntcp*)o;
  printf(" ntcp_Connected   ->   %08X %d\r\n", sz, p->conn_status);

  return 0;
}

int32_t ntcp_Disconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o)
{
  cntcp* p = (cntcp*)o;
  printf(" ntcp_Disconnected   ->   %08X \r\n", sz);

  return 0;
}


int32_t ntcp_Read(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o)
{
  cntcp* p = (cntcp*)o;
  printf(" ntcp_Read   ->   %08X \r\n"
          "================================================\r\n"
          "%s\r\n"
          "================================================\r\n", sz,b);

  return 0;
}

int32_t ntcp_get(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o)
{
  cntcp* p = (cntcp*)o;
  printf(" ntcp_get   ->   %08X \r\n"
          "================================================\r\n"
          "%s\r\n"
          "================================================\r\n", sz,b);

  return 0;
}
int32_t ntcp_post(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o)
{
  cntcp* p = (cntcp*)o;
  printf(" ntcp_post   ->   %08X \r\n"
          "================================================\r\n"
          "%s\r\n"
          "================================================\r\n", sz,b);

  return 0;
}

int32_t ntcp_Open(cntcp* p)
{
  int32_t e = 0;
  int8_t _json[1024] = {0};
  int8_t _argv[1024] = {0};

  p->icd.callback[ICODE_CALLBACK_CONNECTED] = ntcp_Connected;
  p->icd.callback[ICODE_CALLBACK_DISCONNECTED] = ntcp_Disconnected;
  p->icd.callback[ICODE_CALLBACK_READ] = ntcp_Read;

  readArgs(p->ind->argc, p->ind->argv, "--X", _argv);

  sprintf(_json, 
          "{"
            "\"SYSTEM_LIBRARY\":\"%s\","
            "\"SYNC\":\"DISABLE\","
            "\"BLOCK\":\"DISABLE\","
            "\"TIMEOUT\":\"4000\","
          "}",
          _argv
  );

  e = __socket_open(&p->icd.h, _json, p->icd.callback, p);
  return e;
}


int32_t ntcp_Close(cntcp* p)
{
  return __socket_close(&p->icd.h);
}


void ntcp(iNode* p)
{
  ntcp_Open(&gtcp);
}


void ntcp_Loop(iNode* p)
{

}
