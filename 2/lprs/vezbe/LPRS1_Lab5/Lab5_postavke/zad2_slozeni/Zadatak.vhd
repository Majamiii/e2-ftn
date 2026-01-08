library IEEE;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity Zadatak is
    Port ( iCLK    : in  std_logic;
           iRST    : in  std_logic;
           iEN     : in  std_logic;
           iSEL    : in  std_logic_vector(1 downto 0);
           iDATA   : in	 std_logic_vector(4 downto 0);
			  oRESULT : out std_logic_vector(4 downto 0));
end Zadatak;

architecture Behavioral of Zadatak is

	signal sCNT : std_logic_vector(4 downto 0);
	signal sEN : std_logic;
	
	signal sFX : std_logic_vector(4 downto 0);
	signal sSHREG : std_logic_vector(4 downto 0);
	signal sCOMP : std_logic_vector(4 downto 0);
	signal sCONST : std_logic_vector(4 downto 0);
	
	signal sMUX : std_logic_vector(4 downto 0);

begin

	process(iRST,iCLK)begin
		if(iRST='1') then
			sCNT <= (others=>'0');
		elsif(rising_edge(iCLK)) then
			if(iEN='1') then
				if(sCNT=31) then
					sCNT<=(others=>'0');
				else
					sCNT<=sCNT+1;
				end if;
			end if;
		end if;
	end process;
	
	process(iRST,iCLK)begin
		if(iRST='1')then
			sSHREG<="01010";
		elsif(rising_edge(iCLK)) then
			if(sEN='1') then
				sSHREG <= sSHREG(0)&sSHREG(4 downto 1);
			end if;
		end if;
	end process;
	
sEN <= not(sCNT(0));
sCOMP<=not(iDATA)+1;
sFX <= sCNT+3;
sCONST<="10001";

sMUX <= sFX when iSEL="00" else
		  sSHREG when iSEL="01" else
		  sCOMP when iSEL="10" else
		  sCONST;
		  
oRESULT<=sMUX;

end Behavioral;