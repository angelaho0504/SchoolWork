;--------------------------------------------------------------------
;   Program:  nextval ( MASM version)
;
;   Function: Subroutine that will guide a mouse through a maze.
;             The maze is a 15 row by 30 column array that can be
;             traversed using left or right turning mouse.
;             You may only move one position at a time.
;             You may only move into a location in the maze if the
;             value of that location is blank (20h).
;             You may not move into a location that is blocked
;             (contains any value other than 20h).
;             You may only move left, right, up, down.
;             You may not move diagonally.
;             A position is given as y,x .
;             When your subroutine is called, you make 1 move in the maze
;             and then return.
;   Owner:    Angela Ho
;
;   Date:     Changes
;   06/25/19  original version
;---------------------------------------
        .model      small              ; 64k code and 64k data
        .8086                          ; only allow 8086 instructions
        public      nextval            ; all external program to call
;---------------------------------------

;---------------------------------------
        .data                          ;start the data segment
;---------------------------------------
col     db         30
;---------------------------------------
        .code                          ;start the code segment
;---------------------------------------
nextVal:
         push      bp                  ; save bp on stack
         push      ax                  ; save ax on stack
         push      cx                  ; save bx on stack
;---------------------------------------
; calculate the offset
; offset = (*y-1)*30 + (*x-1);
;---------------------------------------
getValue:
         mov       cl,[si]             ; load bl with the x value
         mov       al,[di]             ; load al with the y value
getOffset:
         dec       cl                  ; subtract 1 from x value
         dec       al                  ; subtract 1 from y value
         mul       [col]               ; multipy y by number of column (30)
         add       al, cl              ; al now contain the offset
         adc       ah, 0               ; add with carry to ensure the value wont overflow
         add       bp, ax              ; increment the pointer with offset to get current locatoion
;---------------------------------------
; get the current direction
; if (*direction == 1) goto testn;
; if (*direction == 2) goto teste;
; if (*direction == 3) goto tests;
; if (*direction == 4) goto testw;
;---------------------------------------
getDirection:
         cmp       byte ptr[bx],3;
         je        south;
         ja        west;
         cmp       byte ptr[bx],1;
         ja        east;
;---------------------------------------
; get the next direction and move
; north :
; if (maze[offset-30] == ' ')
; {
; *y = *y-1;
; *x = *x;
; *direction = 4;
; return; // return
; }
;---------------------------------------
north:
         cmp       byte ptr ds:[bp-30], 20h ; if the north direction is equal to space
         jne       east                ; if it is not a space, try east side
         mov       byte ptr[bx],4      ; change direction to north
         dec       byte ptr[di]        ; subtract y value by one to move the mouse
         jmp exit                      ; return
;---------------------------------------
; get the next direction and move
; east :
; if (maze[offset+1] == ' ')
; {
; *y = *y;
; *x = *x + 1;
; *direction = 1;
; return; // return
; }
;---------------------------------------
east:
         cmp       byte ptr ds:[bp+1],20h   ; if the east direction is equal to space
         jne       south               ; if it is not a space, try south side
         mov       byte ptr[bx],1      ; change direction to east
         add       byte ptr[si],1        ; increase the x value to move the mouse
         jmp       exit                ; return
;---------------------------------------
; get the next direction and move
; south :
; if (maze[offset+30] == ' ')
; {
; *y = *y+1;
; *x = *x;
; *direction = 2;
; return; // return
; }
;---------------------------------------
south:
         cmp       byte ptr ds:[bp+30],20h  ; if the south direction is equal to space
         jne       west                ; if it is not a space, try west side
         mov       byte ptr[bx],2      ; change direction to south
         inc       byte ptr[di]        ; increase y to move the mouse
         jmp       exit                ; return new x and y
;---------------------------------------
; get the next direction and move
; west :
; if (maze[offset-30] == ' ')
; {
; *y = *y;
; *x = *x-1;
; *direction = 3;
; return; // return
; }
;---------------------------------------
west:
         cmp       byte ptr ds:[bp-1],20h  ; if the west direction is equal to space
         jne       north               ; if it is not a space, try north side
         dec       byte ptr[si]        ; decrease x to move the mouse
         mov       byte ptr[bx],3      ; change direction to west
;---------------------------------------
; exit the program
;---------------------------------------
exit:
         pop       cx                  ; restore cx register
         pop       ax                  ; restore ax register
         pop       bp                  ; restore bp register
         ret                           ; return to function
         end
