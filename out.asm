	      INT   0, 32
	      SUP   0, main
	      RET   0, 0
main:
	      INT   0, 52
	     ADDR   0, i
	     LITI   0, 0
	      STX   0, 1
	     LDIB   0, 1
L2:
	     LITI   0, 0
	     LITI   0, 5
	     LSSI   0, 0
	      JPC   0, L3
	     LITI   0, 0
	     LITI   0, 2
	      MOD   0, 0
	      JPC   0, L4
	     LITI   0, 0
	     LITI   0, 0
	     LITI   0, 4
	     MULI   0, 0
	   OFFSET   0, 0
	     LITI   0, 0
	      STX   0, 1
	     LDIB   0, 1
L4:
	      INT   0, 12
	      LDA   0, 12
	     LITI   0, 0
	     LITI   0, 1431876528
	     LITI   0, 0
	     LITI   0, 4
	     MULI   0, 0
	     ADDI   0, 0
	      CHK   0, 1
	     LDIB   0, 6
	     ADDR   0, printf
	      CAL   0, 0
L1:
	     LITI   0, 0
	     ADDR   0, i
	      LDX   0, 1
	     INCI   0, 0
	      STO   0, 1
	     LDIB   0, 1
	      JMP   0, L2
L3:
	      RET   0, 0
.literal    12  "Element %d: %d\n"
