
library ieee;
use ieee.std_logic_1164.all;

library work;

entity lprs1_homework2_tb is
end entity;

architecture arch of lprs1_homework2_tb is
	
	constant i_clk_period : time := 20 ns; -- 50 MHz
	
	signal i_clk    : std_logic;
	signal i_rst    : std_logic;
	signal i_run    : std_logic;
	signal i_pause  : std_logic;
	
	signal o_digit0 : std_logic_vector(3 downto 0);
	signal o_digit1 : std_logic_vector(3 downto 0);
	signal o_digit2 : std_logic_vector(3 downto 0);
	signal o_digit3 : std_logic_vector(3 downto 0);
	
begin
	
	uut: entity work.lprs1_homework2
	port map(
		i_clk    => i_clk,
		i_rst    => i_rst,
		i_run    => i_run,
		i_pause  => i_pause,
		o_digit0 => o_digit0,
		o_digit1 => o_digit1,
		o_digit2 => o_digit2,
		o_digit3 => o_digit3
	);
	
	clk_p: process
	begin
		i_clk <= '1';
		wait for i_clk_period/2;
		i_clk <= '0';
		wait for i_clk_period/2;
	end process;
	
	stim_p: process
	begin
		-- Test cases:
		
		wait;
	end process;
	
	
end architecture;
