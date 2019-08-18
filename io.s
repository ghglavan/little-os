global outb  	; make outb visible
global inb      ; make inb visible

; outb - send a byte to an I/O port
; stack: [esp + 8] data byte
; 	 	 [esp + 4] I/O port
;	 	 [esp]	   retrun addr
outb:
	mov al, [esp + 8] 	; move data into al reg
	mov dx, [esp + 4] 	; move I/O port address into dx reg  
	out dx, al	  	  	; send data to the I/O port
	ret		  			; return to the caller

; inb - returns a byte from the given I/O port
; stack: [esp + 4] The address of the I/O port
;		 [esp]     The return address
inb:
	mov dx, [esp + 4]  	; move the address of the I/O in dx
	in al, dx 			; read a byte from the I/O port and store it in al
	ret					; return the read byte