library ieee;
use ieee.std_logic_1164.all;

entity komparator is
	port(
		iA : in std_logic_vector(1 downto 0);
		iB : in std_logic_vector(1 downto 0);
		oLESS : out std_logic;
		oGREAT : out std_logic;
		oEQUAL : out std_logic
	);
end entity;

architecture UslovnaDodela of komparator is

begin

	oLESS <= '1' when (iA < iB) else '0';
	oGREAT <= '1' when (iA>iB) else '0';
	oEQUAL <= '1' when (iA=iB) else '0';

end architecture UslovnaDodela;
