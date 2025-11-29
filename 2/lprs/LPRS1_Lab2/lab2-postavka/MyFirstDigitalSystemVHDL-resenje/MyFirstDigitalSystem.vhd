library ieee;

use ieee.std_logic_1164.all;

entity MyFirstDigitalSystem is
	port(
		iA : in std_logic;
		iB : in std_logic;
		oY : out std_logic
	);
end entity;

architecture Behavioral of MyFirstDigitalSystem is

	signal sS : std_logic;

begin

	sS <= iA and iB;
	oY <= not(sS);
	
end architecture;
