library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity Slozeni is port (
		iCLK   : in  std_logic;
      iRST   : in  std_logic;
      iEN    : in  std_logic;
		oCNT   : out std_logic_vector (7 downto 0);
      oSHREG : out  std_logic_vector (7 downto 0)
		);
end entity;

architecture Behavioral of Slozeni is

signal sCNT : std_logic_vector(7 downto 0);
signal sSHREG : std_logic_vector(7 downto 0);
signal sARITH : std_logic;
signal sLOAD : std_logic;

begin

	-- brojac
	process(iCLK, iRST) begin
	-- asinhroni proces
		if(iRST='1') then
			sCNT<=(others=>'0');
		elsif(rising_edge(iCLK)) then
			if(iEN='1') then
					sCNT <= sCNT+1;
			end if;
		end if;
	end process;


	-- shifter
	process(iCLK, iRST) begin
	-- asinhroni proces
		if(iRST='1') then
			sSHREG<=(others=>'0');
		elsif(rising_edge(iCLK)) then
			if(sLOAD = '1') then
				sSHREG <= sCNT;
			elsif (sARITH='1') then
				sSHREG <= sSHREG(7)&sSHREG(7 downto 1);
			else
				sSHREG <= sSHREG(6 downto 0)&'0';
			end if;
		end if;
	end process;



	--- LOAD
	sLOAD <= '1' when sCNT=8 else
				'1' when sCNT=128
				else '0';
				
	--- ARITH
	sARITH <= '1' when sCNT>128 else '0';

	oCNT <= sCNT;
	oSHREG <= sSHREG;

	
end architecture;
