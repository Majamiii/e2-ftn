.data
   7 // vrednost 7, adresa 0
   0 // vrednost 0, adresa 1

.text
   sub R0, R0, R0  //R0 = 0 
   ld  R0, R0      //R0 <= M[0]
   mov R1, R0      //R1 <= R0
   sub R5, R5, R5  //R5 = 0
   inc R5, R5
   inc R5, R5      //R5 = 2   
   sub R6, R0, R5  //R6 <= R0-2 
   
Loop1:   
   sub R7, R7, R7  //R7 = 0
   add R6, R6, R7  //R6 <= R6 + 0  //azuriramo S, Z
   jmps Loop4  // if R0 < 2 goto Loop4
   jmpz Loop4  // if R0 = 2 goto Loop4
   sub R2, R0, R5  // R2 <= R0-2
   mov R3, R1      // R3 <= R1

Loop2:
   add R2, R2, R7  // R2 <= R2 + 0  //azuriramo S, Z
   jmps Loop3   // if R2 < 0 goto Loop3
   jmpz Loop3   // if R2 = 0 goto Loop3
   add R1, R1, R3  // R1 <= R1+R3   
   dec R2, R2      // R2--
   jmp Loop2
   
Loop3:
   dec R0, R0    // R0--
   mov R6, R0    // R6 <= R0
   jmp Loop1
   
Loop4:
   sub R7, R7, R7 // R7 = 0
   inc R7, R7     // R7 = 1
   st R1, R7      // M[R7] <= R1 

Loop5:
   jmp Loop5
   
