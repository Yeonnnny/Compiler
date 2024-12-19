	      INT   0, 32
	      SUP   0, main
	      RET   0, 0
main:
	      INT   0, 20
	     LITI   0, 0
	     LITI   0, 0
	     EQLI   0, 0
	      JPC   0, L1
	     ADDR   0, num
	     LITI   0, 0
	     LITI   0, 3
	     ADDI   0, 0
	      STX   0, 1
	     LDIB   0, 1
L1:
L4:
	      INT   0, 12
	      LDA   0, 12
	     LITI   0, 0
	     LDIB   0, 5
	     ADDR   0, printf
	      CAL   0, 0
	     LITI   0, 0
	     ADDR   0, num
	      LDX   0, 1
	     DECI   0, 0
	      STO   0, 1
	     LDIB   0, 1
L3:
	      JPT   0, L4
L2:
	      RET   0, 0
.literal    12  "현재 값: %d\n"
