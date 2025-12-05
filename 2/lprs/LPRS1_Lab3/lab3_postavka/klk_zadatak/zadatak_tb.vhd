library ieee;
use ieee.std_logic_1164.all;

entity zadatak_tb is
end entity;

architecture Behavioral of zadatak_tb is
	
	signal sA : std_logic_vector(7 downto 0);
	signal sB : std_logic_vector(2 downto 0);
	signal sSEL : std_logic_vector(1 downto 0);
	signal sY : std_logic_vector(3 downto 0);
	signal sSEGM : std_logic_vector(6 downto 0);
	signal sZERO : std_logic;
	
	signal mA : std_logic_vector(1 downto 0);
	signal mB : std_logic_vector(3 downto 0);
	signal mY : std_logic_vector(3 downto 0);

	component zadatak is
		port(
			iA : in std_logic_vector(1 downto 0);
			iB : in std_logic_vector(3 downto 0);
			oY : out std_logic_vector(3 downto 0)
		);
	end component;

begin

	uut : zadatak port map(
		iA => mA,
		iB => mB,
		oY => mY
	);
	
	stimulus: process
	begin
		
		sB <= "1001";
		
		sA <= "00";
		wait for 100 ns;
		
		sA <= "01";
		wait for 100 ns;
		
		sA <= "10";
		wait for 100 ns;
		
		sa <= "11";
		wait;
		
	
	end process stimulus;

end architecture;