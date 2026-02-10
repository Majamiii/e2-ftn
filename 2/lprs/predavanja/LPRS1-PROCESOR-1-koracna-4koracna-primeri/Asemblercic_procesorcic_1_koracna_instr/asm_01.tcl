
###############################################################################

set asm_file  "Primer_01/asm/p01.asm"

###############################################################################

set assembler_dir "lprs1_assembler/"


set ir_vhd_beg "-- ubaciti sadrzaj *.txt datoteke generisane pomocu lprsasm ------"
set ir_vhd_end "------------------------------------------------------------------"
set dr_vhd_beg "-- ubaciti sadrzaj *.dat datoteke generisane pomocu lprsasm ------"
set dr_vhd_end "------------------------------------------------------------------"


# Assembling to "binary".
set prj_dir [pwd]
set OS [lindex $tcl_platform(os) 0]
cd $prj_dir/$assembler_dir
set result  [
	catch {
		if { $OS == "Windows" } {
			exec lprsasm.exe $prj_dir/$asm_file
		} elseif { $OS == "Linux" } {
			exec wine ./lprsasm.exe $prj_dir/$asm_file
		} else {
			error "Non supported OS: $OS"
		}
	} result_text
]
cd $prj_dir
puts $result_text

# Inserting "binary" to VHDL.
proc insert_to_vhd {insert_fn vhd_fn beg_str end_str} {
	file copy -force $vhd_fn $vhd_fn.bak
	
	set fp [open $insert_fn r]
	set insert [read $fp]
	close $fp
	
	set fp [open $vhd_fn r]
	set vhd [read $fp]
	close $fp
	
	set beg [string first $beg_str $vhd]
	set beg [expr $beg + [string length $beg_str] + 1]
	#puts [string index $vhd $beg]
	
	set end [string first $end_str $vhd]
	set end [expr $end - 1]
	#puts [string index $vhd $end]
	
	set vhd [string replace $vhd $beg $end $insert]
	
	set fp [open $vhd_fn w]
	puts $fp $vhd
	close $fp
}

if {$result} {
	puts "Error in assembling!"
} else {
	set asm_bare [file rootname $asm_file]
	insert_to_vhd $asm_bare.o.txt Primer_01/hdl/instr_rom.vhd \
		$ir_vhd_beg $ir_vhd_end
	insert_to_vhd $asm_bare.o.dat Primer_01/hdl/data_ram.vhd \
		$dr_vhd_beg $dr_vhd_end
	
	puts "LPRS1 assembling OK."
}

###############################################################################
