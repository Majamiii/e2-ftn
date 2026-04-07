#!/usr/bin/env tcl
###############################################################################
# LPRS1 assembler script.
# Author: Milos Subotic <milos.subotic@uns.ac.rs>
###############################################################################

set asm_file "src/asm/stepen.asm.txt"

###############################################################################

set OS [lindex $tcl_platform(os) 0]
set result  [
	catch {
		if { $OS == "Windows" } {
			exec ./bin/lprsasm.exe $asm_file src/hdl/
		} elseif { $OS == "Linux" } {
			exec ./bin/lprsasm.linux $asm_file src/hdl/
		} else {
			error "Non supported OS: $OS"
		}
	} result_text
]

puts $result_text

if {$result} {
	puts "exit code: $result"
	puts "****\nError in LPRS1 assembling!"
} else {
	puts "****\nLPRS1 assembling OK."
}

###############################################################################
