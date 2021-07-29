#include <nwsc.h>
#include <nutil.h>

static cnwsc gwsc;

int32_t nwsc_Write(uint8_t* b, int32_t sz)
{
  int32_t e = 0;

  e = __ws_write(gwsc.icd.h, 0, b, sz, 0, &gwsc);

  return e;
}

int32_t nwsc_Connected(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o)
{
  cnwsc* p = (cnwsc*)o;
  printf(" nwsd_Connected   ->   %08X %08X %d\r\n", fd, sz, p->conn_status);

  p->conn_status = 1;
  return 0;
}

int32_t nwsc_Disconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o)
{
  cnwsc* p = (cnwsc*)o;
  printf(" nwsd_Disconnected   ->   %08X %08X \r\n", fd, sz);

  p->conn_status = -1;
  return 0;
}


int32_t nwsc_Read(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o)
{
  cnwsc* p = (cnwsc*)o;
  printf(" nwsd_Read   ->   %08X %08X %s\r\n", fd, sz, b);

  return 0;
}

int32_t nwsc_Open(cnwsc* p)
{
  int32_t e = 0;
  int8_t _json[1024] = {0};
  int8_t _argv[1024] = {0};

  p->icd.callback[ICODE_CALLBACK_CONNECTED] = nwsc_Connected;
  p->icd.callback[ICODE_CALLBACK_DISCONNECTED] = nwsc_Disconnected;
  p->icd.callback[ICODE_CALLBACK_READ] = nwsc_Read;

  readArgs(p->ind->argc, p->ind->argv, "--X", _argv);

  sprintf(_json,
          "{"
            "\"SYSTEM_LIBRARY\":\"%s\","
            "\"IP\":\"127.0.0.1\","
            "\"PORT\":\"7811\","
            "\"CSTYPE\":\"CLIENT\","
            "\"TIMEOUT\":\"4000\","
          "}",
          _argv
          );
  e = __ws_open(&p->icd.h, _json, p->icd.callback, p);
  printf("__ws_open %08X %s\r\n", e, e>0?"READY":"FAIL");
  return e;
}


int32_t nwsc_Close(cnwsc* p)
{
  return __ws_close(&p->icd.h);
}


void nwsc(iNode* p)
{
  gwsc.ind = p;
  nwsc_Open(&gwsc);
}


void nwsc_Loop(iNode* p)
{
  //int32_t e = 0;
  //delay(2000);
  //e = __ws_write(gwsc.icd.h, 0, "Hello", 5, 0, &gwsc);
  //printf("__ws_write : %08X \r\n", e);
}
