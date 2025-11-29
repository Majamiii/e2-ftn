library ieee;
use ieee.std_logic_1164.all;

------------------------------------------------------------------------------------------
-- OBAVEZNO UPIŠITE IME, PREZIME i BROJ INDEKSA!
-- Ime i prezime: 
-- Broj indeksa: 
-- Radim samo popravni (upisati DA ako je iskaz tačan): 
------------------------------------------------------------------------------------------

entity Microwave_tb is
end entity;
 
architecture Test of Microwave_tb is
  
	signal sCLK			: std_logic := '0';
	signal sRST 		: std_logic := '0';
	signal sREQ  		: std_logic := '0';
	signal sDOOR 		: std_logic := '0';
	signal s_i_TIME 	: std_logic_vector(5 downto 0) := "000000";
	signal sDONE   		: std_logic;
	signal sLAMP		: std_logic;
	signal s_o_TIME		: std_logic_vector(5 downto 0);
	
	constant iCLK_period : time := 10 ns; 
   
	component Microwave is port ( 
		iCLK  	: in  std_logic;
		iRST  	: in  std_logic;
		iREQ  	: in  std_logic;
		iDOOR  	: in  std_logic;
		iTIME		: in 	std_logic_vector(5 downto 0);
		oDONE   	: out std_logic;
		oLAMP		: out std_logic;
		oTIME		: out std_logic_vector(5 downto 0)
	);
	end component;

begin

   uut: Microwave port map (
          iCLK 	=> sCLK,
          iRST 	=> sRST,
          iREQ 	=> sREQ,
          iDOOR	=> sDOOR,
          iTIME	=> s_i_TIME,
          oDONE	=> sDONE,
          oLAMP	=> sLAMP,
          oTIME	=> s_o_TIME
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
	

		
		wait;
   end process;
end architecture;
