
library ieee;
use ieee.std_logic_1164.all;

library work;

entity lab4_counters_tb is
end entity;

architecture lab4_counters_tb_arch
	of lab4_counters_tb is
	
	constant CLK_PERIOD : time := 83.333 ns; -- 12MHz
	
	
	-- On MAX1000.
	-- System signals.
	signal i_clk                      : std_logic := '0'; -- 12MHz clock.
	signal in_rst                     : std_logic := '0'; -- Active low reset.
		
		
		-- LEDs.
	signal o_led                      : std_logic_vector(7 downto 0);
		
		
		
	-- On LPRS1_MAX1000_Shield.
	-- Semaphore.
	signal o_sem_r                    : std_logic;
	signal o_sem_y                    : std_logic;
	signal o_sem_g                    : std_logic;
	
	
	-- RGB 8x8 LED matrix and 7-segm outputs.
	signal o_n_col_0_or_7segm_a       : std_logic;
	signal o_n_col_1_or_7segm_b       : std_logic;
	signal o_n_col_2_or_7segm_c       : std_logic;
	signal o_n_col_3_or_7segm_d       : std_logic;
	signal o_n_col_4_or_7segm_e       : std_logic;
	signal o_n_col_5_or_7segm_f       : std_logic;
	signal o_n_col_6_or_7segm_g       : std_logic;
	signal o_n_col_7_or_7segm_dp      : std_logic;
	
	signal o_mux_row_or_digit         : std_logic_vector(2 downto 0);
	
	signal o_mux_sel_color_or_7segm   : std_logic_vector(1 downto 0);
	
	
	-- Inputs.
	signal i_sw                       : std_logic_vector(7 downto 0)
		:= (others => '0');
	
	signal i_pb_up                    : std_logic := '0';
	signal i_pb_center                : std_logic := '0';
	signal i_pb_down                  : std_logic := '0';
	signal i_pb_left                  : std_logic := '0';
	signal i_pb_right                 : std_logic := '0';
	signal i_pb_rst                   : std_logic := '0';
	
	
	
begin
	
	uut: entity work.lab4_counters
	generic map(
		CLK_FREQ => 12000, -- Everything is 1000x faster.
	)
	port map(
		i_clk => i_clk,
		in_rst => in_rst,


		o_led => o_led,


		
		o_sem_r => o_sem_r,
		o_sem_y => o_sem_y,
		o_sem_g => o_sem_g,
	
	
		o_n_col_0_or_7segm_a => o_n_col_0_or_7segm_a,
		o_n_col_1_or_7segm_b => o_n_col_1_or_7segm_b,
		o_n_col_2_or_7segm_c => o_n_col_2_or_7segm_c,
		o_n_col_3_or_7segm_d => o_n_col_3_or_7segm_d,
		o_n_col_4_or_7segm_e => o_n_col_4_or_7segm_e,
		o_n_col_5_or_7segm_f => o_n_col_5_or_7segm_f,
		o_n_col_6_or_7segm_g => o_n_col_6_or_7segm_g,
		o_n_col_7_or_7segm_dp => o_n_col_7_or_7segm_dp,
	
		o_mux_row_or_digit => o_mux_row_or_digit,
	
		o_mux_sel_color_or_7segm => o_mux_sel_color_or_7segm,
	
	
		i_sw => i_sw,
	
		i_pb_up => i_pb_up,
		i_pb_center => i_pb_center,
		i_pb_down => i_pb_down,
		i_pb_left => i_pb_left,
		i_pb_right => i_pb_right,
		i_pb_rst => i_pb_rst
	);
	
	
	
	clk_gen_i: process
	begin
		wait for CLK_PERIOD/2;
		i_clk <= not i_clk;
	end process;
	
	stim_i: process
	begin
		wait for 3*CLK_PERIOD;
		in_rst <= '1';
		
	end process;


end architecture;
