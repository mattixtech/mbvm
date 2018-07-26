VM Details
===

Machine Layout
---
+ Program Counter: PC - DWORD
+ Stack Pointer: SP - DWORD
+ Registers: r0-r7 - DWORD
+ Data Register: dr - DWORD
+ Print Register: pr - DWORD
+ Status Register: sr - BYTE

Machine Instructions
---
+ EXIT
+ NOP
+ PUSH
+ POP
+ PEEK
+ LOAD
+ STORE
+ ADD
+ SUB
+ JMP
+ FCAL
+ FRET

Advanced Instructions
---
+ PRINT
+ SCAN

Machine Features
--
+ Hardware print-to-screen emulation

    Accessed by storing a character or string address in the print register and then issuing the PRINT instruction
