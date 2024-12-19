	      INT   0, 48
	      SUP   0, main
	      RET   0, 0
main:
	      INT   0, 20
	     LITI   0, 0
	     LITI   0, 0
	     EQLI   0, 0
	      JPC   0, L1
	      INT   0, 12
	      LDA   0, 12
	     LDIB   0, 4
	     ADDR   0, printf
	      CAL   0, 0
	     ADDR   0, num
	     LITI   0, 0
	     LITI   0, 100
	     ADDI   0, 0
	      STX   0, 1
	     LDIB   0, 1
	      JMP   0, L2
L1:
	      INT   0, 12
	      LDA   0, 32
	     LDIB   0, 4
	     ADDR   0, printf
	      CAL   0, 0
L2:
	      RET   0, 0
.literal    12  "num은 0이다."
.literal    32  "num은 뭘까"
