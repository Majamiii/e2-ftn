library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;

entity Signal_light is port ( 
	iCLK  	: in  std_logic;
	iRST  	: in  std_logic;
	iLEFT  	: in  std_logic;
	iRIGHT  	: in  std_logic;
	oLEFT		: out std_logic_vector(2 downto 0);
	oRIGHT	: out std_logic_vector(2 downto 0)
	);
end entity;

architecture Behavioral of Signal_light is
	
begin


end Behavioral;
