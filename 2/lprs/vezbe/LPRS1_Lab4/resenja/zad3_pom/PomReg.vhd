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
 
	signal sQ : std_logic_vector(7 downto 0) := "00000000";

begin
	process(iRST, iCLK) begin
		if (iRST = '1') then
			sQ <= "00000000";
      elsif (iCLK'event and iCLK = '1') then
			if(iLOAD = '1') then 					-- paralelni upis
				sQ <= iDATA;
			elsif (iSHR = '1' and iSHL = '0') then
				if (iARITH = '1') then
					sQ <= sQ(7) & sQ(7 downto 1);	-- aritmeticko pomeranje udesno
				else
					sQ <= '0' & sQ(7 downto 1);  	-- logicko pomeranje udesno
				end if;
			elsif (iSHL = '1' and iSHR = '0') then
				if (iARITH = '1') then
					sQ <= sQ(6 downto 0) & '0'; 	-- aritmeticko pomeranje ulevo
				else
					sQ <= sQ(6 downto 0) & '0';	-- logicko pomeranje ulevo
				end if;
			end if;
		end if;
				
	end process;
	
	oSHREG <= sQ;
end architecture;
