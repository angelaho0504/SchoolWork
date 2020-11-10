;--------------------------------------------------------------------
;   Program:  Tabs ( MASM version)
;
;   Function: Reads lines from an ASCII input text file which is redirected to the
;             standard input, performs some simple text editing on the lines,
;             and writes the updated lines to an ASCII output text
;             file which is redirected from the standard output. The specific
;             editing function is to expand tabs (replace tabs with  the
;             correct number of spaces) to create columns.
;
;   Owner:    Angela Ho
;
;   Date:     Changes
;   06/18/19  original version
;---------------------------------------
        .model      small              ; 64k code and 64k data
        .8086                          ; only allow 8086 instructions
        .stack      256                ; reserve 256 bytes for the stack
;---------------------------------------

;---------------------------------------
         .data                         ;start the data segment
;---------------------------------------
         .code                         ;start the code segment
;---------------------------------------
tabs:
;---------------------------------------
; test whether the a CLP was typed
;---------------------------------------
        mov         bl,0Ah             ; set the number of space to 10
        cmp         byte ptr es:[80h], 0 ; access the CLP count 80h bytes into the extra segment
        je          while_             ;  no parameter ... continue with the program
        mov         bl, byte ptr es:[82h] ; parameter entered ... load al with the CLP character
        sub         bl, 30h            ; convert the to hex value
set:
        mov        ch,0                ; set the counter to 0
;---------------------------------------
; while (1)
;---------------------------------------
while_:                                ;
;---------------------------------------
; ch = getchar()
;---------------------------------------
         mov        ah,8;              ; set up to read a character without echo
         int        21h                ; read the character
;---------------------------------------
; if (ch == 9 )
;---------------------------------------
         cmp        al, 09h            ; is the char a tab
         mov        cl, al             ; move data in al to t
         jne        put                ; if not tab just output the character
printtab:
         mov        al, 20h            ; move space character to al
         cmp        ch,bl              ; compare counter with user enter value
         jne        put                ; not equal go to put
         jmp        set                ; equal then reset
;---------------------------------------
; putchar(ch)
;---------------------------------------
put:
         mov        ah,2               ; set up to print a character
         mov        dl,al              ;
         int        21h                ; print the character
         add        ch, 1              ; count ++
         cmp        cl, 09h            ; if character is tab
         je         printtab           ;
;---------------------------------------
; if (ch == 10)
;---------------------------------------
         cmp        al, 1Ah            ; if the character is EOF
         je         exit               ; exit the program
         cmp        al, 0Ah            ; If LF then
         je         set                ; reset the counter and read the next char
         cmp        ch,bl              ; compare counter with with user enter value
         je         set                ;
         jmp        while_             ; repeat the loop
;---------------------------------------
; Terminate the Program
;---------------------------------------
exit:
         mov        ax,4c00h           ; set dos code to terminate program
         int        21h                ; return to dos
         end        tabs               ;end marks the end of the source code
                                       ;....and specifies where you want the
                                       ;....program to start execution
;---------------------------------------

