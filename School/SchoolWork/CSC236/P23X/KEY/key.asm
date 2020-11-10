;--------------------------------------------------------------------
;   Program:  Key ( MASM version)
;
;   Function: Reads printable characters (20h-7Fh) from the Standard Input (keyboard or a
;             redirected ASCII text file) without echo(using ah=08h and int 21h). If the
;             character is an upper case letter or a space then write it to the standard output.
;             If the charater is a lower case letter then process it to an upper case letter then
;             write it to the standard output. If the character is a period then write it to the
;             standard output and exit out the program.
;
;   Owner:    Angela Ho
;
;   Date:     Changes
;   06/09/19  original version
;---------------------------------------
        .model      small              ; 64k code and 64k data
        .8086                          ; only allow 8086 instructions
        .stack      256                ; reserve 256 bytes for the stack
;---------------------------------------
        .code                          ;start the code segmen
;---------------------------------------
key:
;---------------------------------------
; while ( ch != '.' )
;---------------------------------------
while_:                                ;
;---------------------------------------
; ch = getchar()
;---------------------------------------
         mov        ah,8;              ; set up to read a character without echo
         int        21h                ; read the character
;---------------------------------------
; if ( ch == ' ' )
;---------------------------------------
         cmp        al, 20h            ; is the char a space
         je         display_           ; display the character
;---------------------------------------
; else if ( ch == '.' )
;---------------------------------------
         cmp        al, 2Eh            ; is the char a period
         je         display_           ; display the character
;---------------------------------------
; else if ( ch < 'A' )
;---------------------------------------
         cmp        al, 41h            ; is the char lower than 'A' in ASCII
         jl         while_             ; Lower then 'A' in ASCII, throw away
;---------------------------------------
; else if ( ch <= 'Z' )
;---------------------------------------
         cmp        al, 5Ah            ;
         jle        display_          ; display the character
;---------------------------------------
; else if ( ch < 'a' )
;---------------------------------------
         cmp        al, 61h            ; is the char lower than 'a' in ASCII
         jl         while_             ; Lower then 'a' in ASCII, throw away
;---------------------------------------
; else if ( ch <= 'z' )
;---------------------------------------
         cmp        al, 7Ah            ; is the char lower and equal to 'z' in ASCII
         jg         while_             ; everything else is gone
;---------------------------------------
; ch = ch - 32
;---------------------------------------
         sub        al, 20h            ; convert to upper case
;---------------------------------------
; putchar(ch)
;---------------------------------------
display_:
         mov        ah,2               ; set up to print a character
         mov        dl,al              ;
         int        21h                ; print the character
         cmp        al, 2Eh            ; is char a period
         jne        while_             ; no, repeat while
;---------------------------------------
; Terminate the Program
;---------------------------------------
exit:
         mov        ax,4c00h           ; set dos code to terminate program
         int        21h                ; return to dos
         end        key                ;end marks the end of the source code
                                       ;....and specifies where you want the
                                       ;....program to start execution
;---------------------------------------
