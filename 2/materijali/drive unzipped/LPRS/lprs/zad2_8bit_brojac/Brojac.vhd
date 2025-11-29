library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;

entity Brojac is port ( 
	iRST  : in  std_logic;
	iCLK  : in  std_logic;
	iEN   : in  std_logic;
	oCNT  : out std_logic_vector(7 downto 0)
	
	);
end entity;

architecture Behavioral of Brojac is

	signal scnt : std_logic_vector(7 downto 0);
	
	process(iCLK, IRST) BEGIN
		IF(iRST = '1') THEN
			SCNT <= (OTHERS => '0');
		ELSIF(rising_edge(iclk)) then
			if(ien = '1') then
				scnt <= scnt + 1;
			end if;
		end if;
	end process;
	
	sTC <= '1' WHEN SCNT = 225 ELSE
	'0'
	
	
	oCNT <= sCNT;
	
	
begin
	
end Behavioral;
