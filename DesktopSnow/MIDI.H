/****************************************************************/
/*      MIDI静态联结库    HugeSoft工作室    1999年7月制作       */
/*                                作者:MMX                      */
/*      本库封装用于播放MIDI文件的windows API,可方便的          */
/*      播放MIDI文件.                                           */
/*      例如播放MIDI文件在WM_CREATE:中插入以下格式:             */
/*          打开MIDI文件：MID_Open(FileName);                   */
/*          播放MIDI文件：MID_Play();即可播放                   */
/*      需在Project的Setting的Link选项中加入midi.lib            */
/*      vfw32.lib winmm.lib 的联结                              */
/*      适用于Win95/Win98/WinNT4.0,VC 5.0或VC 6.0编程.          */
/*      如有问题，请e-mail:mmx_hugesoft@163.net                 */
/****************************************************************/

#include <windows.h>
#include <windowsx.h>
#include <vfw.h>

#ifdef __cplusplus
/* Assume C declarations for C++ */
extern "C" { 
#endif

/*    函数名：MID_GetDevices                        */
/*    作用：返回系统配置的支持MIDI的输出设置数目    */
/*    参数：无                                      */
/*    返值：系统配置的支持MIDI的输出设置数目        */
	extern int MID_GetDevices (void);
	
/*    函数名：MID_Open                              */
/*    作用：打开设备                                */
/*    参数：无                                      */
/*    返值：成功为TRUE，失败为FALSE                 */
	extern BOOL MID_Open (char *);
	
/*    函数名：MID_Close                             */
/*    作用：关闭文件并关闭MCI设备                   */
/*    参数：无                                      */
/*    返值：无                                      */
	extern void MID_Close (void);
	
/*    函数名：MID_Play                              */
/*    作用：从当前位置播放文件                      */
/*    参数：无                                      */
/*    返值：成功为TRUE，失败为FALSE                 */
	extern BOOL MID_Play (void);
	
/*    函数名：MID_Stop                              */
/*    作用：停止播放文件                            */
/*    参数：无                                      */
/*    返值：无                                      */
	extern void MID_Stop (void);
	
/*    函数名：MID_Pause                             */
/*    作用：暂停播放文件                            */
/*    参数：无                                      */
/*    返值：无                                      */
	extern void MID_Pause (void);
	
/*    函数名：MID_GetTotalLength                    */
/*    作用：指出MIDI文件的总长度                    */
/*    参数：int* pnMinutes,函数失败为-1             */
/*          int* pnSeconds,函数失败为-1             */
/*    返值：无                                      */
	extern void MID_GetTotalLength (int *, int*);
	
/*    函数名：MID_GetMinutes                        */
/*    作用：返回用分钟表示的MIDI文件当前位置        */
/*    参数：无                                      */
/*    返值：失败为-1                                */
	extern int MID_GetMinutes (void);
	
/*    函数名：MID_GetSeconds                        */
/*    作用：返回用秒表示的MIDI文件当前位置          */
/*    参数：无                                      */
/*    返值：失败为-1                                */
	extern int MID_GetSeconds (void);
	
/*    函数名：MID_IsPlaying                         */
/*    作用：返回所向播放状态并提供暂停状态          */
/*    文件暂停时IsPlaying()返回TRUE                 */
/*    参数：BOOl* bPaused                           */
/*	返值：文件暂停时IsPlaying()返回TRUE         */
/*            否则为FALSE                           */
	extern BOOL MID_IsPlaying (BOOL *);
	
/*    函数名：MID_SeekTo                            */
/*    作用：选择MIDI文件内的特定位置，              */
/*          如文件正在播放，将重置                  */
/*    参数：int nMinute,int nSecond                 */
/*    返值：成功为TRUE，失败为FALSE                 */
	extern BOOL MID_SeekTo (int, int);
	
/*    函数名：MID_SkipForWard                       */
/*    作用：使文件向前跳n秒，如文件正在             */
/*          播放，将重置                            */
/*    参数：int nSecond                             */
/*    返值：无                                      */
	extern void MID_SkipForward (int);
	
/*    函数名：MID_SKipBack                          */
/*    作用：使文件向后跳n秒，如文件正在             */
/*          播放，将重置                            */
/*    参数：int nSecond                             */
/*    返值：无                                      */
	extern void MID_SkipBack (int);
	
/*    函数名：MID_GetDivisionTpe                    */
/*    作用：判断MIDI文件的类型                      */
/*    参数：无                                      */
/*    返值：类型为MCI_SEQ_DIV_PPQN,返回0，          */
/*          否则为-1                                */
	extern int MID_GetDivisionType (void);
	
/*    函数名：MID_GetTempo                          */
/*    作用：返回MIDI文件的播放速度                  */
/*    参数：无                                      */
/*    返值：int nTempo                              */
	extern int MID_GetTempo (void);
	
/*    函数名：MID_GetTempo                          */
/*    作用：改变MIDI文件的播放速度                  */
/*    参数：int nTempo                              */
/*    返值：无                                      */
	extern void MID_SetTempo (int);
	
	extern BOOL m_bOpened, m_bPaused, m_bPlaying;
	extern WORD m_wDeviceID;
#ifdef __cplusplus
}
#endif
