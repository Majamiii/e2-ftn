library ieee;
use ieee.std_logic_1164.all;
entity Comparator_tb is
end Comparator_tb;
architecture Test_tb of Comparator_tb is
signal sA : std_logic_vector(1 downto 0);
signal sB : std_logic_vector(1 downto 0);
signal sLESS : std_logic;
signal sGREAT : std_logic;
signal sEQUAL : std_logic;
component komparator is
port(
iA : in std_logic_vector(1 downto 0);
iB : in std_logic_vector(1 downto 0);
oLESS : out std_logic;
oGREAT : out std_logic;
oEQUAL : out std_logic
);
end component;
begin
	-- mapiranje komponente koja ima više različitih arhitektura
	uut : entity work.komparator port map (
	iA => sA,
	iB => sB,
	oLESS => sLESS,
	oGREAT => sGREAT,
	oEQUAL => sEQUAL
	);
	-- zadavanje svih kombinacija ULAZNIH signala
	stimulus: process
	begin
		sA <= "00";
		sB <= "00";
		wait for 100 ns;
		
		sA <= "11";
		sB <= "00";
		wait for 100 ns;
		
		sA <= "00";
		sB <= "11";
		wait for 100 ns;
	
	end process stimulus;
end architecture;