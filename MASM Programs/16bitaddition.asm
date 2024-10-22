CODE SEGMENT
ASSUME CS: CODE
START:     
    MOV SI, 3000H     
    MOV AX, [SI]     
    INC SI
    INC SI      
    MOV BX, [SI]       
    INC SI
    INC SI      
    ADD AX, BX                
    MOV [SI], AX       
    INT 3              
    CODE ENDS
    END START
