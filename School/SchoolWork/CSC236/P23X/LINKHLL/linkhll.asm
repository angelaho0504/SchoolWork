;-----------------------------------------------------------
;
; Program: Linkhll
;
; Function: The linkhll subroutine is a C/C++ subroutine
;          and will be linked with a C/C++ main program.
;          The linkhll subroutine will be
;          passed four unsigned words on the stack
;          (these are passed by value).
;          Linkhll is to find the two largest unsigned values and
;          multiply them creating a 32 bit unsigned product.
;
; Owner: Angela Ho
;
; Date:
; 07/03/2016   Original Version
;
;
;---------------------------------------
.model    small               ;
.8086                         ;
public    _linkhll            ;
;---------------------------------------
.data
;---------------------------------------
.code
;---------------------------------------
;
; Code Segment
;
;---------------------------------------
_linkhll:                              ;
         push      bp                  ; save caller's bp
         mov       bp,sp               ; init bp so we can get the arguments
         mov       ax,[bp+4]           ; set the first val to max
         mov       bx,[bp+6]           ; set the second val to 2max
         cmp       bx,ax               ; test if the first and second need to swap
         jbe       loadThird_          ; if not just load the third
         xchg      ax,bx               ; else swap
;---------------------------------------
; Ｔry to load the third value;
;---------------------------------------
loadThird_:
         cmp       [bp+8],bx           ; compare third to second max
         jbe       loadForth_          ; if third is lower than dont change
;---------------------------------------
; update the maximums
;---------------------------------------
update_:
         mov       bx,[bp+8]           ; update max
         cmp       bx,ax               ; compare the max and second max
         jbe       loadForth_          ; if not, test if there is next val
         xchg      ax,bx               ; exchange the maxs
;---------------------------------------
; Ｔry to load the forth value;
;---------------------------------------
loadForth_:
         cmp       [bp+10],bx          ; compare forth to second max
         jbe       getVal_             ; if forth value is lower, dont change
;---------------------------------------
; update the maximums
;---------------------------------------
update1_:
         mov       bx,[bp+10]          ; update max
;---------------------------------------
;
; get the multiple and return it then exit
;---------------------------------------
getVal_:
         mul       bx                  ;
         pop       bp                  ;
         ret                           ; return
         end                           ; end source code
;---------------------------------------
