.include "xc.inc"

.bss

.text				;BP The following data is in ROM

.global _delay1u, _delay1m

_delay1u:
	;2 Cycle
	repeat #9		;1 Cycle
	nop				;9 + 1 Cycle
	
	return			;3 Cycle

_delay1m:
	;2 Cycle
	repeat #15993	;1 Cycle
	nop				;15994 Cycle
	
	return			;3 Cycle

.end
