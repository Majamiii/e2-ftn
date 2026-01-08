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

signal sTC : std_logic;
signal sREG : std_logic_vector(7 downto 0);
	
begin

process(iCLK,iRST) begin
	if(iRST='1')then
		sREG<=(others=>'0');
	elsif(rising_edge(iCLK)) then
		if(iEN = '1') then
			if (sREG = "11111111") then -- ili zameniti sa nekim drugim br ako hocemo moduo
				sTC<='1';
			else
				sTC<='0';
				sREG <= sREG + 1;
			end if;
		end if;
	end if;
end process;

-- sTC <= '1' when sCNT=255 else '0';

oCNT<=sREG;

	
end Behavioral;
