#ifndef __NHTTP_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __NHTTP_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <icode.x.h>
#include <inode.h>

#if defined XWIN32
#pragma pack(1)
#endif
typedef struct
#if defined LINUX
__attribute__((packed))
#endif
{
  iCode icd;
  iNode* ind;

  int8_t  conn_status;
} cnhttp;
#if defined XWIN32
#pragma pack()
#endif

int32_t nhttp_Open(cnhttp* p);
int32_t nhttp_Close(cnhttp* p);
void nhttp(iNode* p);
void nhttp_Loop(iNode* p);


#endif
