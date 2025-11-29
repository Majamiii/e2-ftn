
library ieee;
use ieee.std_logic_1164.all;

library work;

entity lprs1_homework2_tb is
end entity;

architecture arch of lprs1_homework2_tb is
	
	constant i_clk_period : time := 5 ns; -- 200 MHz
	
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
	
		i_run   <= '0';
		i_pause <= '0';
		
		--1. 
		i_rst <= '1';
		wait for 1us - i_clk_period; --995ns 
		i_rst <= '0';
		wait for 1us;
		--2.
		i_run <= '1';			  --1995ns
		wait for i_clk_period; --2000ns
		i_run <= '0';
		
		--3.
		wait for 200*i_clk_period; --3000ns
		
		--4.
		i_pause <= '1';
		wait for i_clk_period; --3005ns 
		i_pause <= '0';
		
		--5.
		i_run <= '1';
		
		--6.
		wait for 400*i_clk_period; --5005ns
		i_rst <= '1';
		
		wait for 199*i_clk_period; --6000ns
		i_rst <= '0';
		
		--7. 
		wait for 5201*i_clk_period;	--32005 ns (5 je produzetak od takta)    
		wait for i_clk_period;			--32010 ns
		i_rst <= '1';
		i_run <= '0';
		wait for 1 * i_clk_period; 	--33015 ns
		i_rst <= '0';						--33015 ns
		i_run <= '1';
		
		--8. 
		wait for 6599* i_clk_period;  --66010ns
		wait for 3 * i_clk_period;	   --66020ns
		i_rst <= '1';
		wait for i_clk_period;
		i_rst <= '0';
		wait;
	end process;
	
	
end architecture;