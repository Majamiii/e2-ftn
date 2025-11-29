transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vcom -93 -work work {C:/Users/janko/FTN/Druga godina E2/LPRS 1/Test/Primeri testova/LPRS1_X_Y_Z_Grupa_A 2022/GrupaA.vhd}

vcom -93 -work work {C:/Users/janko/FTN/Druga godina E2/LPRS 1/Test/Primeri testova/LPRS1_X_Y_Z_Grupa_A 2022/GrupaA_tb.vhd}

vsim -t 1ps -L altera -L lpm -L sgate -L altera_mf -L altera_lnsim -L fiftyfivenm -L rtl_work -L work -voptargs="+acc"  GrupaA_tb

add wave *
view structure
view signals
run 1 us
