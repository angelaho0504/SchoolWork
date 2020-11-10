;----------------------------------
;Program:  MOV
;
;Function: Read and echo 3 ASCII characters x y z
;              x will be an ASCII uppercase letter ‘A’ - ‘Z’ or digit ‘0’ - ‘9’
;              y will be an ASCII digit ‘0’ - ‘9’
;              z will be an ASCII plus sign ‘+’ or other ASCII character
;          Using only the mov instruction:
;              convert y from ASCII ‘0’ to ‘9’to hex 0 to 9
;              calculate … if (z == '+') then x = x + y
;          Output x
;          Terminate
;
;Owner:    Angela Ho
;
;Version:  Date      Reason
;          07/17/19  Original code
;
;
;----------------------------------
         .model    small          ;4 64KB segments
         .8086                    ;only 8086 instructions
         .stack    256            ;256 byte stack
;----------------------------------
.data                    ;data
;----------------------------------
x        db        0              ;variable x
dum_x    db        0              ;dummy variable z at memory offset z + 1
y        db        0              ;variable y
z        db        0              ;variable z
                                  ;
                                  ; ------------------------
cvt      db         0h,1h,2h,3h,4h,5h,6h,7h,8h,9h ;
                                                           ;
inctbl   db        000,001,002,003,004,005,006,007,008,009 ;
         db        010,011,012,013,014,015,016,017,018,019 ;
         db        020,021,022,023,024,025,026,027,028,029 ;
         db        030,031,032,033,034,035,036,037,038,039 ;
         db        040,041,042,043,044,045,046,047,048,049 ;
         db        050,051,052,053,054,055,056,057,058,059 ;
         db        060,061,062,063,064,065,066,067,068,069 ;
         db        070,071,072,073,074,075,076,077,078,079 ;
         db        080,081,082,083,084,085,086,087,088,089 ;
         db        090,091,092,093,094,095,096,097,098,099 ;
         db        100,101,102,103,104,105,106,107,108,109 ;
         db        110,111,112,113,114,115,116,117,118,119 ;
         db        120,121,122,123,124,125,126,127,128     ;

;-----------------------------------------------------------

;----------------------------------
         .fardata                 ;256 bytes of work memory for selection code
;----------------------------------
         db        256 dup(0)     ;byte vars need 256 bytes of work memory
;----------------------------------

;----------------------------------
         .code                    ;Program
;----------------------------------
; Establish addressability to data and extra segment
; Clear bx, to be used as a word pointer.
;----------------------------------
start:
         mov       ax,@data       ;initialize
         mov       ds,ax          ; the ds register
         mov       ax,@fardata    ; initialize
         mov       es,ax          ; the es register
         mov       bx,0           ;clear bx as a pointer to zero
         mov       cx,0           ;clear cx as a pointer to zero
;----------------------------------
; Read and echo x
;----------------------------------
         mov       ah,8           ;read code
         int       21h            ;read interrupt
         mov       [x],al         ;save x
         mov       dl,al          ;ready to echo x
         mov       ah,2           ;write code
         int       21h            ;write interrupt
;----------------------------------
; Read and echo y
;----------------------------------
         mov       ah,8           ;read code
         int       21h            ;read interrupt
         mov       [y],al         ;save y
         mov       dl,al          ;ready to echo y
         mov       ah,2           ;write code
         int       21h            ;write interrupt
;----------------------------------
; Read and echo z
;----------------------------------
         mov       ah,8           ;read code
         int       21h            ;read interrupt
         mov       [z],al         ;save y
         mov       dl,al          ;ready to echo y
         mov       ah,2           ;write code
         int       21h            ;write interrupt

;----------------------------------
; Convert the ASCII value of y '0' to '9' into a hex 0 to 9
; save the hex value in to si for double index
;----------------------------------
         mov     bl,[y]           ;Load y into bl
         mov     cl,[cvt + bx - 48] ; use bx as index in to covert table
         mov     si,cx            ;Save the hex value in si

;----------------------------------
; Calculate x + y in the al register
;----------------------------------
         mov     bl,[x]           ; load x into bl
         mov     al,[inctbl + bx + si]; use si and bx to index into convert table
;----------------------------------
; test if z is '+'
;----------------------------------
         mov       bl,'+'          ;bx pts to es memory addr=value_of_+
         mov  byte ptr es:[bx],1   ;es memory at memory addr=value_of_+ set to 1
         mov       bl,[z]          ;bx pts to es memory addr=value_of_z
         mov  byte ptr es:[bx],0   ;es memory at addr=value_of_z set to 0
         mov       bl,'+'          ;bx pts to es memory addr=value_of_+
         mov       bl,es:[bx]      ;bx=0 if (z==+)  bx=1 if (z!=+)
         mov  byte ptr[x+bx],al    ;x=x+y if (z==+)  dum_x=al if (z!=+)

;----------------------------------
; Output x
;----------------------------------
         mov       ah,2           ;write code
         mov       dl,[x]         ;write x
         int       21h            ;write interrupt
;----------------------------------
; Terminate
;----------------------------------
         mov       ax,4c00h       ;get the termination code
         int       21h            ;terminate
                                  ;
         end       start          ;end program
;----------------------------------

