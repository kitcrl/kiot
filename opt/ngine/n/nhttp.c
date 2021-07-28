#include <nhttp.h>
#include <nutil.h>

#define STOCK_URL              "api.data.go.kr"
#define STOCK_PORT             "80"
#define STOCK_URI              "/openapi/tn_pubr_public_wrpp_qltwtr_inspct_api"



static cnhttp ghttpclnt;


int32_t nhttp_Connected(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o)
{
  cnhttp* p = (cnhttp*)o;
  printf(" nhttp_Connected   ->   %08X %d\r\n", sz, p->conn_status);

  p->conn_status = 1;
  return 0;
}

int32_t nhttp_Disconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o)
{
  cnhttp* p = (cnhttp*)o;
  printf(" nhttp_Disconnected   ->   %08X \r\n", sz);

  p->conn_status = -1;
  return 0;
}


int32_t nhttp_Read(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o)
{
  cnhttp* p = (cnhttp*)o;
  printf(" nhttp_Read   ->   %08X \r\n%s\r\n", sz, b);

  return 0;
}

int32_t nhttp_Open(cnhttp* p)
{
  int32_t e = 0;
  int8_t _json[1024] = {0};
  int32_t fd = 0;
  int8_t _argv[1024] = {0};

  p->icd.callback[ICODE_CALLBACK_CONNECTED] = nhttp_Connected;
  p->icd.callback[ICODE_CALLBACK_DISCONNECTED] = nhttp_Disconnected;
  p->icd.callback[ICODE_CALLBACK_READ] = nhttp_Read;

  readArgs(p->ind->argc, p->ind->argv, "--X", _argv);

  sprintf(_json, 
          "{"
            "\"SYSTEM_LIBRARY\":\"%s\","
            "\"SYNC\":\"ENABLE\","
            "\"TIMEOUT\":\"4000\","
            "\"URL\":\"%s\","
            "\"URI\":\"%s\","
            "\"PORT\":\"%s\","
          "}",
          _argv,
          STOCK_URL, STOCK_URI, STOCK_PORT
  );

  e = __http_open(&p->icd.h, _json, p->icd.callback, p);


  __http_fd(p->icd.h, 0, 0, 0, &fd, 0);


  return e;
}


int32_t nhttp_Close(cnhttp* p)
{
  return __http_close(&p->icd.h);
}


void nhttp(iNode* p)
{
  int32_t e= 0;
  e = nhttp_Open(&ghttpclnt);
}


void nhttp_Loop(iNode* p)
{
  int32_t e = 0;
  uint8_t b[2048] = {0};
  uint8_t hex = 0;

  {
    e = __http_read(ghttpclnt.icd.h, 0, b, 2048, 0, &ghttpclnt);
    if ( e > 0 ) printf("%s\r\n", b);
    delay(1000);


    //if ( ghttpclnt.conn_status == 1 )
    //{
    //  int32_t i = 0;
    //  delay(500);
    //  for ( i=0 ; i<16 ;i++ )
    //  {
    //    b[i] = hex%26 + 'A';
    //  }
    //  e = __http_write(ghttpclnt.icd.h, 0, b, 16, 0, &ghttpclnt);

    //  printf(" write (%d)-> %02X \r\n", e, b[0]);
    //  ghttpclnt.conn_status = -1;

    //  hex++;
    //}
  }


}
