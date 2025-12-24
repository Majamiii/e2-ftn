library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity PomReg is port (
		iRST   : in  std_logic;
		iCLK   : in  std_logic;
		iLOAD  : in  std_logic;
		iARITH : in  std_logic;
		iSHL   : in  std_logic;
		iSHR   : in  std_logic;
		iDATA  : in  std_logic_vector(7 downto 0);
		oSHREG : out std_logic_vector(7 downto 0)
		);
end entity;

architecture Behavioral of PomReg is

signal sREG : std_logic_vector(7 downto 0);
    	 
begin

process(iCLK, iRST) begin

	if(iRST = '1') then
		sREG <= (others => '0');
	elsif(rising_edge(iCLK)) then
		if (iLOAD = '1') then
			sREG <= iDATA;
		elsif(iSHL='1' and iSHR='0') then
			sREG <= sREG(6 downto 0)&'0';
		elsif(iSHL='0' and iSHR='1') then
			if (iARITH='1') then
				sREG <= sREG(7)&sREG(7 downto 1);
			elsif (iARITH='0') then
				sREG <= '0' & sREG(7 downto 1);
			end if;
		end if;
	end if;
end process;

oSHREG <= sREG;

	
end architecture;
