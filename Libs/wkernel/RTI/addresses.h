#ifndef WKERNEL_RTI_ADDRESSES_H
#define WKERNEL_RTI_ADDRESSES_H
#include <j3dcore/j3d.h>
#include <wkernel/types.h>

// Function addresses

#define wkernel_Run_ADDR 0x004C41F0
#define wkernel_PeekProcessEvents_ADDR 0x004C42B0
#define wkernel_ProcessEvents_ADDR 0x004C4340
#define wkernel_SetWindowStyle_ADDR 0x004C43B0
#define wkernel_SetWindowSize_ADDR 0x004C4400
#define wkernel_SetWindowProc_ADDR 0x004C4430
#define wkernel_CreateWindow_ADDR 0x004C4440
#define wkernel_MainWndProc_ADDR 0x004C4580

// Variable addresses

#define wkernel_guid_ADDR 0x005099A8
#define wkernel_hwnd_ADDR 0x005E1030
#define wkernel_nShowCmd_ADDR 0x005E1034
#define wkernel_msg_1_ADDR 0x005E1038
#define wkernel_msg_2_ADDR 0x005E1058
#define wkernel_pfWndProc_ADDR 0x005E1074
#define wkernel_wndBorderWidth_ADDR 0x005E1078
#define wkernel_wndMenuBarHeight_ADDR 0x005E107C

#endif // WKERNEL_RTI_ADDRESSES_H
