transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vcom -93 -work work {D:/NASTAVA/LPRS1/Ispiti/2022-23/1_JANUAR/RA/Grupa_B/Zadatak1B/Signal_light.vhd}

vcom -93 -work work {D:/NASTAVA/LPRS1/Ispiti/2022-23/1_JANUAR/RA/Grupa_B/Zadatak1B/Signal_light_tb.vhd}

vsim -t 1ps -L altera -L lpm -L sgate -L altera_mf -L altera_lnsim -L fiftyfivenm -L rtl_work -L work -voptargs="+acc"  Signal_light_tb

add wave *
view structure
view signals
run 1 us
