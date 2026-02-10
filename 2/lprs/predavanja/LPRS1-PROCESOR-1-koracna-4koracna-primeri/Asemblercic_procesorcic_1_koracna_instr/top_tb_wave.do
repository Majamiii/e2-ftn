onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /top_tb/uut/cpu_top_i/iCLK
add wave -noupdate /top_tb/uut/cpu_top_i/inRST
add wave -noupdate /top_tb/uut/cpu_top_i/iINSTR
add wave -noupdate /top_tb/uut/cpu_top_i/iDATA
add wave -noupdate /top_tb/uut/cpu_top_i/oPC
add wave -noupdate /top_tb/uut/cpu_top_i/oDATA
add wave -noupdate /top_tb/uut/cpu_top_i/oADDR
add wave -noupdate /top_tb/uut/cpu_top_i/oMEM_WE
add wave -noupdate /top_tb/uut/cpu_top_i/oLED
add wave -noupdate /top_tb/uut/cpu_top_i/sREG_WE
add wave -noupdate -radix decimal /top_tb/uut/cpu_top_i/sR0
add wave -noupdate -radix decimal /top_tb/uut/cpu_top_i/sR1
add wave -noupdate -radix decimal /top_tb/uut/cpu_top_i/sR2
add wave -noupdate -radix decimal /top_tb/uut/cpu_top_i/sR3
add wave -noupdate -radix decimal /top_tb/uut/cpu_top_i/sR4
add wave -noupdate -radix decimal /top_tb/uut/cpu_top_i/sR5
add wave -noupdate -radix decimal /top_tb/uut/cpu_top_i/sR6
add wave -noupdate -radix decimal /top_tb/uut/cpu_top_i/sR7
add wave -noupdate /top_tb/uut/cpu_top_i/sMUXA
add wave -noupdate /top_tb/uut/cpu_top_i/sMUXB
add wave -noupdate /top_tb/uut/cpu_top_i/sMUXA_SEL
add wave -noupdate /top_tb/uut/cpu_top_i/sMUXB_SEL
add wave -noupdate /top_tb/uut/cpu_top_i/sALU_SEL
add wave -noupdate /top_tb/uut/cpu_top_i/sC
add wave -noupdate /top_tb/uut/cpu_top_i/sPC
add wave -noupdate /top_tb/uut/cpu_top_i/sPC_IN
add wave -noupdate /top_tb/uut/cpu_top_i/sPC_LOAD
add wave -noupdate /top_tb/uut/cpu_top_i/sMEM_WE
add wave -noupdate /top_tb/uut/cpu_top_i/sSIGN_COMB
add wave -noupdate /top_tb/uut/cpu_top_i/sSIGN
add wave -noupdate /top_tb/uut/cpu_top_i/sZERO_COMB
add wave -noupdate /top_tb/uut/cpu_top_i/sZERO
add wave -noupdate /top_tb/uut/cpu_top_i/sCARRY_COMB
add wave -noupdate /top_tb/uut/cpu_top_i/sCARRY
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {0 ps} 0}
quietly wave cursor active 0
configure wave -namecolwidth 233
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ns
update
WaveRestoreZoom {0 ps} {933 ps}
