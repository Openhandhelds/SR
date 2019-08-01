;;
;;  Copyright (C) 2016-2019 Roman Pauer
;;
;;  Permission is hereby granted, free of charge, to any person obtaining a copy of
;;  this software and associated documentation files (the "Software"), to deal in
;;  the Software without restriction, including without limitation the rights to
;;  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
;;  of the Software, and to permit persons to whom the Software is furnished to do
;;  so, subject to the following conditions:
;;
;;  The above copyright notice and this permission notice shall be included in all
;;  copies or substantial portions of the Software.
;;
;;  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
;;  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
;;  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
;;  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
;;  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
;;  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
;;  SOFTWARE.
;;

%include "misc.inc"

%ifidn __OUTPUT_FORMAT__, win32
    %define Game_errno _Game_errno
    %define Game_ReturnAddress _Game_ReturnAddress
    %define Game_Registers _Game_Registers
    %define Game_dlseek _Game_dlseek
    %define Game_dopen _Game_dopen
    %define Game_dread _Game_dread
    %define Game_dclose _Game_dclose
    %define Game_DigPlay _Game_DigPlay
    %define Game_AudioCapabilities _Game_AudioCapabilities
    %define Game_StopSound _Game_StopSound
    %define Game_PostAudioPending _Game_PostAudioPending
    %define Game_SetPlayMode _Game_SetPlayMode
    %define Game_PendingAddress _Game_PendingAddress
    %define Game_ReportSemaphoreAddress _Game_ReportSemaphoreAddress
    %define Game_SetBackFillMode _Game_SetBackFillMode
    %define Game_VerifyDMA _Game_VerifyDMA
    %define Game_SetDPMIMode _Game_SetDPMIMode
    %define Game_FillSoundCfg _Game_FillSoundCfg
    %define Game_RealPtr _Game_RealPtr

    %define Game_printf _Game_printf
    %define Game_WaitVerticalRetraceTicks _Game_WaitVerticalRetraceTicks

    %define Game_checkch _Game_checkch
    %define Game_getch _Game_getch

    %define fclose _fclose
    %define free _free
    %define Game_inp _Game_inp
    %define malloc _malloc
    %define strlen _strlen

    %define Game_fopen _Game_fopen
    %define Game_outp _Game_outp
    %define strcat _strcat
    %define strcpy _strcpy
    %define strcasecmp _strcasecmp

    %define Game_ReadSong _Game_ReadSong

    %define fread _fread
    %define Game_int386x _Game_int386x
%endif

extern Game_errno
extern Game_ReturnAddress
extern Game_Registers
extern Game_dlseek
extern Game_dopen
extern Game_dread
extern Game_dclose
extern Game_DigPlay
extern Game_AudioCapabilities
extern Game_StopSound
extern Game_PostAudioPending
extern Game_SetPlayMode
extern Game_PendingAddress
extern Game_ReportSemaphoreAddress
extern Game_SetBackFillMode
extern Game_VerifyDMA
extern Game_SetDPMIMode
extern Game_FillSoundCfg
extern Game_RealPtr



; stack params
extern Game_printf
extern Game_WaitVerticalRetraceTicks
; 0 params
extern Game_checkch
extern Game_getch
; 1 param
extern fclose
extern free
extern Game_inp
extern malloc
extern strlen
; 2 params
extern Game_fopen
extern Game_outp
extern strcat
extern strcpy
extern strcasecmp
; 3 params
extern Game_ReadSong
; 4 params
extern fread
extern Game_int386x
; 5 params

extern errno_val

; null procedures
global SR___CHK
; stack params
global SR_printf

global SR_dlseek
global SR_dopen
global SR_dread
global SR_dclose

global SR_DigPlay
global SR_AudioCapabilities
global SR_StopSound
global SR_PostAudioPending
global SR_SetPlayMode
global SR_PendingAddress
global SR_ReportSemaphoreAddress
global SR_SetBackFillMode
global SR_VerifyDMA
global SR_SetDPMIMode
global SR_FillSoundCfg
global SR_RealPtr
; 0 params
global SR_checkch
global SR_getch
; 1 param
global SR_fclose
global SR__nfree
global SR_inp
global SR__nmalloc
global SR_strlen
; 2 params
global SR_fopen
global SR_outp
global SR_strcat
global SR_strcpy
global SR_stricmp
; 3 params
global SR_ReadSong
; 4 params
global SR_fread
global SR_int386x
; 5 params

%include "SR-asm-calls.inc"

%ifidn __OUTPUT_FORMAT__, elf32
section .note.GNU-stack noalloc noexec nowrite progbits
section .text progbits alloc exec nowrite align=16
%else
section .text code align=16
%endif

align 16
Game_Set_errno_Asm:

        push eax
        push ecx
        push edx

        call Game_errno

        mov [errno_val], eax

        pop edx
        pop ecx
        pop eax

        retn

; end procedure Game_Set_errno_Asm

; null procedures
align 16
SR___CHK:

; [esp] = return address

        retn 4

; end procedure SR___CHK

; stack params
align 16
SR_printf:

; [esp + 2*4] = ...
; [esp +   4] = const char *format
; [esp      ] = return address

        ;Game_Call_Asm_Stack printf,'get_errno_val'
        Game_Call_Asm_Stack0 Game_printf,'get_errno_val'

; end procedure SR_printf

align 16
SR_dlseek:

; [esp + 3*4] = int whence
; [esp + 2*4] = int offset
; [esp +   4] = int fd
; [esp      ] = return address

        Game_Call_Asm_Stack0 Game_dlseek,-1

; end procedure SR_dlseek

align 16
SR_dopen:

; [esp + 2*4] = const char *mode
; [esp +   4] = const char *path
; [esp      ] = return address

        Game_Call_Asm_Stack0 Game_dopen,-1

; end procedure SR_dopen

align 16
SR_dread:

; [esp + 3*4] = int fd
; [esp + 2*4] = int count
; [esp +   4] = void *buf
; [esp      ] = return address

        Game_Call_Asm_Stack0 Game_dread,-1

; end procedure SR_dread

align 16
SR_dclose:

; [esp +   4] = int fd
; [esp      ] = return address

        Game_Call_Asm_Stack0 Game_dclose,-1

; end procedure SR_dclose

align 16
SR_DigPlay:

; [esp +   4] = SNDSTRUC *sndplay
; [esp      ] = return address

        Game_Call_Asm_Stack0 Game_DigPlay,-1

; end procedure SR_DigPlay

align 16
SR_AudioCapabilities:

        Game_Call_Asm_Reg0 Game_AudioCapabilities,-1

; end procedure SR_AudioCapabilities

align 16
SR_StopSound:

        Game_Call_Asm_Reg0 Game_StopSound,-1

; end procedure SR_StopSound

align 16
SR_PostAudioPending:

; [esp +   4] = SNDSTRUC *sndplay
; [esp      ] = return address

        Game_Call_Asm_Stack0 Game_PostAudioPending,-1

; end procedure SR_PostAudioPending

align 16
SR_SetPlayMode:

; [esp +   4] = short mode
; [esp      ] = return address

        Game_Call_Asm_Stack0 Game_SetPlayMode,-1

; end procedure SR_SetPlayMode

align 16
SR_PendingAddress:

        Game_Call_Asm_Reg0 Game_PendingAddress,-1

; end procedure SR_PendingAddress

align 16
SR_ReportSemaphoreAddress:

        Game_Call_Asm_Reg0 Game_ReportSemaphoreAddress,-1

; end procedure SR_ReportSemaphoreAddress

align 16
SR_SetBackFillMode:

; [esp +   4] = short mode
; [esp      ] = return address

        Game_Call_Asm_Stack0 Game_SetBackFillMode,-1

; end procedure SR_SetBackFillMode

align 16
SR_VerifyDMA:

; [esp +   8] = short length
; [esp +   4] = char *data
; [esp      ] = return address

        Game_Call_Asm_Stack0 Game_VerifyDMA,-1

; end procedure SR_VerifyDMA

align 16
SR_SetDPMIMode:

; [esp +   4] = short mode
; [esp      ] = return address

        Game_Call_Asm_Stack0 Game_SetDPMIMode,-1

; end procedure SR_SetDPMIMode

align 16
SR_FillSoundCfg:

; [esp +   8] = int count
; [esp +   4] = void *buf
; [esp      ] = return address

        Game_Call_Asm_Stack0 Game_FillSoundCfg,-1

; end procedure SR_FillSoundCfg

align 16
SR_RealPtr:

; [esp +   4] = char *real
; [esp      ] = return address

        Game_Call_Asm_Stack0 Game_RealPtr,-1

; end procedure SR_RealPtr


; 0 params
align 16
SR_checkch:

        Game_Call_Asm_Reg0 Game_checkch,-1

; end procedure SR_checkch

align 16
SR_getch:

        Game_Call_Asm_Reg0 Game_getch,-1

; end procedure SR_getch


; 1 param
align 16
SR_fclose:

; eax = FILE *fp

        Game_Call_Asm_Reg1 fclose,'get_errno_val'

; end procedure SR_fclose

align 16
SR__nfree:

; eax = void __near *ptr

        Game_Call_Asm_Reg1 free,-1

; end procedure SR__nfree

align 16
SR_inp:

; eax = int port

        Game_Call_Asm_Reg1 Game_inp,-1

; end procedure SR_inp

align 16
SR__nmalloc:

; eax = size_t size

        Game_Call_Asm_Reg1 malloc,-1

; end procedure SR__nmalloc

align 16
SR_strlen:

; eax = const char *s

        Game_Call_Asm_Reg1 strlen,-1

; end procedure SR_strlen


; 2 params
align 16
SR_fopen:

; eax = const char *filename
; edx = const char *mode

; errno_val is set inside Game_fopen

        Game_Call_Asm_Reg2 Game_fopen,-1

; end procedure SR_fopen

align 16
SR_outp:

; eax = int port
; edx = int value

        Game_Call_Asm_Reg2 Game_outp,-1

; end procedure SR_outp

align 16
SR_strcat:

; eax = char *dst
; edx = const char *src

        Game_Call_Asm_Reg2 strcat,-1

; end procedure SR_strcat

align 16
SR_strcpy:

; eax = char *dst
; edx = const char *src

        Game_Call_Asm_Reg2 strcpy,-1

; end procedure SR_strcpy

align 16
SR_stricmp:

; eax = const char *s1
; edx = const char *s2

        Game_Call_Asm_Reg2 strcasecmp,-1

; end procedure SR_stricmp


; 3 params
align 16
SR_ReadSong:

; eax = const char *catalog_name
; edx = int index
; ebx = uint8_t *buf

        Game_Call_Asm_Reg3 Game_ReadSong,-1

; end procedure SR_ReadSong

; 4 params
align 16
SR_fread:

; eax = void *buf
; edx = size_t elsize
; ebx = size_t nelem
; ecx = FILE *fp

        Game_Call_Asm_Reg4 fread,'get_errno_val'

; end procedure SR_fread

align 16
SR_int386x:

; eax = int inter_no
; edx = const union REGS *in_regs
; ebx = union REGS *out_regs
; ecx = struct SREGS *seg regs

        Game_Call_Asm_Reg4 Game_int386x,-1

; end procedure SR_int386x


; 5 params
