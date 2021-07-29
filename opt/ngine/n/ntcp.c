#include <ntcp.h>
#include <nutil.h>

static cntcp gtcp;
void* ntcp_request(cntcp* p)
{
  int32_t e = 0;
  uint8_t i = 0;
  uint8_t modbus_protocol[64] = { 0};
  uint8_t hbuf[8192] = {0};
  uint32_t hsz = 0;
  int16_t _addr = 0;
  int16_t _len  = 4;


  modbus_protocol[i++] = 0x00;
  modbus_protocol[i++] = 0;
  modbus_protocol[i++] = 0x00;
  modbus_protocol[i++] = 0x00;
  modbus_protocol[i++] = 0x00;
  modbus_protocol[i++] = 0x06;

  modbus_protocol[i++] = 0x01;

  modbus_protocol[i++] = 0x04;
  modbus_protocol[i++] = (_addr&0xFF00)>>8;
  modbus_protocol[i++] = (_addr&0x00FF);
  modbus_protocol[i++] = (_len &0xFF00)>>8;
  modbus_protocol[i++] = (_len &0x00FF);

  e = __socket_write(p->icd.h, 0, modbus_protocol, i, 0, p);
  to_raw(modbus_protocol, i, hbuf, &hsz);
  printf("XSOCKET  ->   %10s -> [%4d] %s\r\n", "request", hsz, hbuf);
  return 0;
}


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
  int32_t e = 0;
  uint8_t hb[1024] = {0};
  int32_t hbsz = 0;

  to_raw(b, sz, hb, &hbsz);

  printf(" ntcp_Read   ->   %08X \r\n"
          "================================================\r\n"
          "%s\r\n"
          "================================================\r\n", sz,hb);

  e = inode_write(h, fd, b, sz, moreinfo, &gtcp);

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
            "\"IP\":\"192.168.0.254\","
            "\"PORT\":\"502\","
            "\"CSTYPE\":\"CLIENT\","
            "\"PROTOCOL\":\"TCP\","
            "\"CASTTYPE\":\"UNICAST\","
            "\"SYNC\":\"DISABLE\","
            "\"TIMEOUT\":\"2000\","
          "}",
          _argv
  );
  e = __socket_open(&p->icd.h, _json, p->icd.callback, p);
  printf("__socket_open %08X %s\r\n", e, e>0?"READY":"FAIL");
  return e;
}


int32_t ntcp_Close(cntcp* p)
{
  return __socket_close(&p->icd.h);
}


void ntcp(iNode* p)
{
  gtcp.ind = p;
  ntcp_Open(&gtcp);
}


void ntcp_Loop(iNode* p)
{
  delay(1000);
  ntcp_request(&gtcp);
}
