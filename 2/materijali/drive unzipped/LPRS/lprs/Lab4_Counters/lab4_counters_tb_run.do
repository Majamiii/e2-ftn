
set wf lab4_counters_tb_wave.do

restart -force
delete wave *

# All is relative to simulation/modelsim/
if {[file exists wave.do]} {
	file delete ../../$wf
	file copy wave.do ../../$wf
}

do $wf

# Ignoring uninitialized signals warnings before reset activated.
set StdArithNoWarnings 1
set NumericStdNoWarnings 1
run 1ps
set StdArithNoWarnings 0
set NumericStdNoWarnings 0

run 1 us
