transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vcom -93 -work work {D:/Work_from_home/LPRS1/2022_ispiti/1_Januar/Ostali/OSTALI/LPRS1_X_Y_Z_Q/LPRS1_Ispit_Zad1/Microwave.vhd}

vcom -93 -work work {D:/Work_from_home/LPRS1/2022_ispiti/1_Januar/Ostali/OSTALI/LPRS1_X_Y_Z_Q/LPRS1_Ispit_Zad1/simulation/modelsim/Microwave_tb.vhd}

vsim -t 1ps -L altera -L lpm -L sgate -L altera_mf -L altera_lnsim -L fiftyfivenm -L rtl_work -L work -voptargs="+acc"  Microwave_tb

add wave *
view structure
view signals
run 2500 ns
