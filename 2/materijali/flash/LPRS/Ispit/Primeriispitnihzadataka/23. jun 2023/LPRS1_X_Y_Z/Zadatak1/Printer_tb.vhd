---------------------------------------------
-- Ime i prezime:
-- Broj indeksa:
---------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

entity Printer_tb is
end entity;
 
architecture Test of Printer_tb is
  
   signal sCLK			: std_logic := '0';
   signal sRST 		: std_logic := '0';
   signal sPRINT 		: std_logic := '0';
	signal sADD_PAPER	: std_logic := '0';
	signal sAMOUNT		: std_logic_vector(7 downto 0) := "00000000";
	signal soPRINT		: std_logic;
	signal sERROR		: std_logic;
	
	constant iCLK_period : time := 10 ns; 
   
	component Printer is port ( 
	iCLK  		: in  std_logic;
	iRST  		: in  std_logic;
	iPRINT  		: in  std_logic;
	iADD_PAPER  : in  std_logic;
	iAMOUNT		: in  std_logic_vector(7 downto 0);
	oPRINT		: out std_logic;
	oERROR		: out std_logic
	);
	end component;

begin

   uut: Printer port map (
          iCLK 		=> sCLK,
          iRST 		=> sRST,
			 iPRINT		=> sPRINT,
			 iADD_PAPER	=> sADD_PAPER,
          iAMOUNT 	=> sAMOUNT,
          oPRINT 		=> soPRINT,
			 oERROR		=> sERROR
        );
		  
	iCLK_process: process
	begin
		sCLK <= '0';
		wait for iCLK_period / 2; -- iCLK_period je konstanta
		sCLK <= '1';
		wait for iCLK_period / 2;
	end process;

   stim_proc : process
   begin		
	
	sRST <= '1';
	wait for 5.25*iCLK_period;
	sRST <= '0';
	sADD_PAPER <= '1';
	sAMOUNT <= "00000011";
	wait for iCLK_period;
	sADD_PAPER <= '0';
	sAMOUNT <= (others=>('0'));
	
	sPrint <= '1';
	sPrint <= '1';
	wait for 27*iCLK_period;
	
	
	sPrint <= '1';
	sPrint <= '1';
	wait for 27*iCLK_period;
	
	sADD_PAPER <= '1';
	sAMOUNT <= "00001110"; -- 15 papira
	sPrint <= '1';
	sADD_PAPER <= '0';
	wait for iCLK_period;
	
	sRST <= '1';

		
		wait;
   end process;
end architecture;
