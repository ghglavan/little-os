global outb  	; make outb visible

; outb - send a byte to an I/O port
; stack: [esp + 8] data byte
; 	 	 [esp + 4] I/O port
;	 	 [esp]	   retrun addr
outb:
	mov al, [esp + 8] 	; move data into al reg
	mov dx, [esp + 4] 	; move I/O port address into dx reg  
	out dx, al	  	  	; send data to the I/O port
	ret		  			; return to the caller
