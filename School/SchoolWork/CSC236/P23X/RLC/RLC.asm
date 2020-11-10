;---------------------------------------------------------------------
;  Program:      Run Length Coding
;
;  Function:     Decompresses 1 dimensional run lengths
;                This subroutine links with a C main program
;
;                Add your additional functional comments
;
;  Owner:        Angela Ho
;
;  Changes:
;  Date          Reason
;  ----          ------
;  07/07/2019    Original version
;---------------------------------------------------------------------
.model    small
.8086
public    _rlc
;---------------------------------------
.data                         ;start the data segment
;---------------------------------------
run      db        2 dup (?)           ; declare 2 uninitialized bytes to hold two runs
len      db        ?                   ; number of pels in the current run
i        db        ?                   ; for loop counter
cur      db        ?
;---------------------------------------
.code                         ;start the code segnment
;---------------------------------------
; Save the registers ... 'C' requires (bp,si,di)
; Access the input and output lists
;---------------------------------------
_rlc:                                  ;
         push      bp                  ;save 'C' register
         mov       bp,sp               ;set bp to point to stack
         push      si                  ;save 'C' register
         push      di                  ;save 'C' register
         mov       si,[bp+4]           ;si points to the input compressed data
         mov       di,[bp+6]           ;di points to the empty output buffer
;---------------------------------------
; pels_left = 80;
; cur = wh;
;---------------------------------------
         mov       al, 80              ; al store pels on a line, 80 al == pl
         mov       ah, 32             ; dl store first color to output, white
         mov       cl, 4               ; cl store the amount of shift
;---------------------------------------
; while(1) {
; code = *comp;
; comp++;
;---------------------------------------
while_:
         mov       bl,byte ptr [si]    ; mov the input compressed data into current  input bl == code
         add       si, 1               ; advance the pointer to next element
;---------------------------------------
; if ( code == 0 ) return(0);
;---------------------------------------
         cmp       bl, 0               ; if ( code == 0 )
         je        exit                ; a byte of 00h signals end of data
;---------------------------------------
; run[0] = (unsigned char)(code >> 4)
; run[1] = (unsigned char)(code << 4)
;---------------------------------------
         mov       bh, bl               ; mov input into run[1]
         shr       bl, cl               ; left 4 bits of input
         and       bh, 0fh              ; right 4 bits of input
;---------------------------------------
; for ( i = 0; i < 2; i++ )
;---------------------------------------
for_:
         mov       [i], 0              ; initialize for loop couter
;---------------------------------------
; if i = 0   dl = [run+0]
; if i = 1   dl = [run+1]
;---------------------------------------
testRun_:
         mov       dl,bl               ;
         cmp       [i], 1              ; if the i = 0 then dl = [run+0]
         jg        while_              ;
         jne       do_                 ; else dl = [run+1]
second_:
         mov       dl,bh               ;
;---------------------------------------
; if ( pels_left == 0 ) {
; pels_left = 80;
; cur = wh;
; }
;---------------------------------------
do_:
         cmp       al, 0               ; if at the end of a line then
         jne       testEnd_            ; if not equal jmp to testRun
         mov       al,80               ; 80 pels to fill on that new line
         mov       ah,32               ; first color is white
;---------------------------------------
; if ( run[i] == 15) len = pels_left;
; else len = run[i];
;---------------------------------------
testEnd_:
         mov       [len], al           ; len = pl
         cmp       dl, 15              ; a run of 15 means go to end of line
         je        reducePel_             ;
else_:
         mov       [len], dl           ; else we has a length 0-14
;---------------------------------------
; while ( len > 0 )
; *dcomp = cur;
; dcomp ++;
; len--;
; pels_left--;
;---------------------------------------
reducePel_:
        sub        al,[len]            ;
        mov        cl,[len]            ;
while1_:
         jcxz      swap_;
         mov       byte ptr [di], ah   ; *dcomp = cur
         add       di, 1               ; advance the pointer to next element
         loop      while1_;
;---------------------------------------
; if ( cur == wh ) cur = bl;
; else cur = wh;
;---------------------------------------
swap_:
         cmp       ah, 32              ; cmp == wh
         jne       else2_              ; if not equal
         mov       ah, 219             ;
         jmp       next_               ; jump to test
else2_:
         mov       ah, 32         ; swap the output pel color
next_:
         inc       [i]                 ;
         jmp       testRun_            ;
;---------------------------------------
; Restore registers and return
;---------------------------------------
exit:                                  ;
         pop       di                  ;restore 'C' register
         pop       si                  ;restore 'C' register
         pop       bp                  ;restore 'C' register
         ret                           ;return
;---------------------------------------
end


