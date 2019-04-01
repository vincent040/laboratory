#ifndef _ISO14443A_H
#define _ISO14443A_H

// ISO14443A命令：请求
static char REQUEST[7] = {0x07, // 帧长度
			  0x02, // 命令类型: ISO14443A
			  0x41, // 命令字'A'
			  0x01, // Length:1
			  0x52, // Info:ALL
			  0x00, // 校验和
			  0x03};// ETX

// ISO14443A命令：防碰撞
static char Anticol[7] = {0x08, // 帧长度
			  0x02, // 命令类型: ISO14443A
			  0x42, // 命令字'B'
			  0x02, // Length:2
			  0x93, // Info:ALL
			  0x00, // Info:ALL
			  0x00, // 校验和
			  0x03};// ETX

#endif
