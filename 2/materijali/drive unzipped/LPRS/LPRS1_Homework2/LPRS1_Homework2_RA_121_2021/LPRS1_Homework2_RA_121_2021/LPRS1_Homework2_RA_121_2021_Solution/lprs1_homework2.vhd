
library ieee;
use ieee.std_logic_1164.all;
-- Libraries.

entity lprs1_homework2 is
	port(
		i_clk    :  in std_logic;
		i_rst    :  in std_logic;
		i_run    :  in std_logic;
		i_pause  :  in std_logic;
		o_digit0 : out std_logic_vector(3 downto 0);
		o_digit1 : out std_logic_vector(3 downto 0);
		o_digit2 : out std_logic_vector(3 downto 0);
		o_digit3 : out std_logic_vector(3 downto 0)
	);
end entity;


architecture arch of lprs1_homework2 is
	-- Signals.
	
begin
	-- Body.
	
end architecture;
