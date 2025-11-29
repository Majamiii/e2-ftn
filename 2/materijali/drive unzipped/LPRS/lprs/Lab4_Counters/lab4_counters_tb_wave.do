onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /lab4_counters_tb/i_clk
add wave -noupdate /lab4_counters_tb/in_rst
add wave -noupdate /lab4_counters_tb/o_led
add wave -noupdate /lab4_counters_tb/uut/digit_sel
add wave -noupdate /lab4_counters_tb/uut/digit_0
add wave -noupdate /lab4_counters_tb/uut/digit_1
add wave -noupdate /lab4_counters_tb/uut/digit_2
add wave -noupdate /lab4_counters_tb/uut/digit_3
add wave -noupdate -radix unsigned /lab4_counters_tb/uut/digit_0
add wave -noupdate -radix unsigned /lab4_counters_tb/uut/digit_1
add wave -noupdate -radix unsigned /lab4_counters_tb/uut/digit_2
add wave -noupdate -radix unsigned /lab4_counters_tb/uut/digit_3
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {114409 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 407
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
WaveRestoreZoom {63448 ps} {1049293 ps}
