
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

library work;

entity lab4_counters is
	generic(
		-- Default frequency used in synthesis.
		constant CLK_FREQ         : positive := 12000000
	);
	port(
		-- On MAX1000.
		-- System signals.
		i_clk                      :  in std_logic; -- 12MHz clock.
		in_rst                     :  in std_logic; -- Active low reset.
		
		
		-- LEDs.
		o_led                      : out std_logic_vector(7 downto 0);
		
		
		
		-- On LPRS1_MAX1000_Shield.
		-- Semaphore.
		o_sem_r                    : out std_logic;
		o_sem_y                    : out std_logic;
		o_sem_g                    : out std_logic;
		
		
		-- RGB 8x8 LED matrix and 7-segm outputs.
		o_n_col_0_or_7segm_a       : out std_logic;
		o_n_col_1_or_7segm_b       : out std_logic;
		o_n_col_2_or_7segm_c       : out std_logic;
		o_n_col_3_or_7segm_d       : out std_logic;
		o_n_col_4_or_7segm_e       : out std_logic;
		o_n_col_5_or_7segm_f       : out std_logic;
		o_n_col_6_or_7segm_g       : out std_logic;
		o_n_col_7_or_7segm_dp      : out std_logic;
		
		o_mux_row_or_digit         : out std_logic_vector(2 downto 0);
		
		o_mux_sel_color_or_7segm   : out std_logic_vector(1 downto 0);
		
		
		-- Inputs.
		i_sw                       :  in std_logic_vector(7 downto 0);
		
		i_pb_up                    :  in std_logic;
		i_pb_center                :  in std_logic;
		i_pb_down                  :  in std_logic;
		i_pb_left                  :  in std_logic;
		i_pb_right                 :  in std_logic;
		i_pb_rst                   :  in std_logic
	);
end entity;

architecture lab4_counters_arch of lab4_counters is
	
	signal digit_sel    : std_logic_vector(1 downto 0);
	signal digit        : std_logic_vector(3 downto 0);
	signal digit_0      : std_logic_vector(3 downto 0);
	signal digit_1      : std_logic_vector(3 downto 0);
	signal digit_2      : std_logic_vector(3 downto 0);
	signal digit_3      : std_logic_vector(3 downto 0);
	
	signal segm_afbgecd : std_logic_vector(6 downto 0);
	signal segm_dp      : std_logic;
	
	
begin
	o_led <= i_sw;
	o_sem_r <= i_pb_up;
	o_sem_y <= i_pb_center;
	o_sem_g <= i_pb_down;

	digit_0 <= x"0";
	digit_1 <= x"1";
	digit_2 <= x"2";
	digit_3 <= x"3";
	
	
	digit_sel <= "00"; -- TODO Connect to lowest bits of counters.
	
	
	-- Mux for digits.
	with digit_sel select digit <=
		digit_0 when "00",
		digit_1 when "01",
		digit_2 when "10",
		digit_3 when others;
	
	-- 7-segm decoder.
	with digit select segm_afbgecd <=
		     '1'&
		'1'&      '1'&
		     '0'&
		'1'&      '1'&
		     '1'
				when x"0",
		     '0'&
		'0'&      '1'&
		     '0'&
		'0'&      '1'&
		     '0'
				when x"1",
		     '1'&
		'0'&      '1'&
		     '1'&
		'1'&      '0'&
		     '1'
				when x"2",
		     '1'&
		'0'&      '1'&
		     '1'&
		'0'&      '1'&
		     '1'
				when x"3",
		     '0'&
		'1'&      '1'&
		     '1'&
		'0'&      '1'&
		     '0'
				when x"4",
		     '1'&
		'1'&      '0'&
		     '1'&
		'0'&      '1'&
		     '1'
				when x"5",
		     '1'&
		'1'&      '0'&
		     '1'&
		'1'&      '1'&
		     '1'
				when x"6",
		     '1'&
		'0'&      '1'&
		     '0'&
		'0'&      '1'&
		     '0'
				when x"7",
		     '1'&
		'1'&      '1'&
		     '1'&
		'1'&      '1'&
		     '1'
				when x"8",
		     '1'&
		'1'&      '1'&
		     '1'&
		'0'&      '1'&
		     '1'
				when x"9",
		     '0'&
		'0'&      '0'&
		     '0'&
		'0'&      '0'&
		     '0'
				when others;
	
	-- Set point on odd numbers.
	segm_dp <= digit(0);
	
	o_n_col_0_or_7segm_a  <= not segm_afbgecd(6);
	o_n_col_1_or_7segm_b  <= not segm_afbgecd(4);
	o_n_col_2_or_7segm_c  <= not segm_afbgecd(1);
	o_n_col_3_or_7segm_d  <= not segm_afbgecd(0);
	o_n_col_4_or_7segm_e  <= not segm_afbgecd(2);
	o_n_col_5_or_7segm_f  <= not segm_afbgecd(5);
	o_n_col_6_or_7segm_g  <= not segm_afbgecd(3);
	o_n_col_7_or_7segm_dp <= not segm_dp;
	
	o_mux_row_or_digit <= '0' & digit_sel;
	
	o_mux_sel_color_or_7segm <= "11";
	
	
end architecture;
