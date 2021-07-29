#ifndef __INODE_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __INODE_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#if defined XWIN32
#pragma pack(1)
#endif
typedef struct
#if defined LINUX
__attribute__((packed))
#endif
{
  uint8_t pth[128];
} iInfo;
#if defined XWIN32
#pragma pack()
#endif

#if defined XWIN32
#pragma pack(1)
#endif
typedef struct
#if defined LINUX
__attribute__((packed))
#endif
{
  void* log;
  void* obj;
  void* hdl;
  int32_t  argc;
  int8_t** argv;
  uint8_t  buf[1024];
} iNode;
#if defined XWIN32
#pragma pack()
#endif



int32_t inode_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);



#endif
