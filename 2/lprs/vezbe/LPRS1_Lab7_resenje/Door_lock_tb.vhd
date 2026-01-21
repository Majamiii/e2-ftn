library ieee;
use ieee.std_logic_1164.all;

entity Door_lock_tb is
end entity;
 
architecture Test of Door_lock_tb is
  
   signal sCLK			: std_logic := '0';
   signal sRST 		: std_logic := '0';
   signal sNEW_REQ 	: std_logic := '0';
	signal sCODE		: std_logic_vector(3 downto 0) := "0000";
   signal sSTATUS 	: std_logic;
	signal sWARNING	: std_logic;
	
	constant iCLK_period : time := 10 ns; 
   
	component Door_lock is port ( 
	iRST  	: in  std_logic;
	iCLK  	: in  std_logic;
	iNEW_REQ	: in  std_logic;
	iCODE		: in  std_logic_vector(3 downto 0);
	oSTATUS	: out std_logic;
	oWARNING	: out std_logic
	);
	end component;

begin

   uut: Door_lock port map (
      iRST  	=>	sRST,
		iCLK  	=> sCLK,
		iNEW_REQ	=> sNEW_REQ,
		iCODE  	=> sCODE,
		oSTATUS 	=> sSTATUS,
		oWARNING	=> sWARNING
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
		wait for 3.75 * iCLK_period;
		sRST <= '0';
		
		-- Pojavljuje se zahtev za otključavanje vrata (kada automat prepozna da je došao novi zahtev
		-- vrednost signala se postavlja na '0')
		sNEW_REQ <= '1';
		wait for 6 * iCLK_period;
		sNEW_REQ <= '0';
		
		--Stanar unosi dobru šifru karakter po karakter
		sCODE <= "0010";
		wait for 10 * iCLK_period;
		sCODE <= "0011";
		wait for 10 * iCLK_period;
		sCODE <= "0100";
		wait for 10 * iCLK_period;
		sCODE <= "0111";
		wait for 60* iCLK_period;
		
		-- Nova osoba se pojavljuje na vratima koja su zaključana (sačekati da prođe dovoljno vremena da
		-- se vrata zaključaju)
		sNEW_REQ <= '1';
		wait for 6 * iCLK_period;
		sNEW_REQ <= '0';
		
		
		-- Neko ko nije stanar zgrade unosi pogrešan kod
		sCODE <= "0010";
		wait for 10 * iCLK_period;
		sCODE <= "0111";
		wait for 10 * iCLK_period;
		sCODE <= "0100";
		wait for 10 * iCLK_period;
		sCODE <= "0111";
		wait for 60* iCLK_period;
		--VAŽNO: Obratite pažnju da novi karakter treba uneti dok je automat u stanju PAUSE jer će u
		-- suprotnom automat očitati 2 puta isti karakter što će rezultovati greškom.
		
		
		wait;
   end process;
end architecture;
