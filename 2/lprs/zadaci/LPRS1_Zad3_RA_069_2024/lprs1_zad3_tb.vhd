library ieee;
use ieee.std_logic_1164.all;

entity lprs1_zad3_tb is
end entity;
 
architecture Test of lprs1_zad3_tb is
	--Inputs
   signal sCLK : std_logic := '0';
   signal sRST : std_logic := '0';
   signal sRUN : std_logic := '1';
	signal sNIGHT : std_logic := '0';
  
 	--Outputs
   signal sRED    : std_logic;
   signal sYELLOW : std_logic;
	signal sGREEN  : std_logic;
	
	signal sDIS  : std_logic_vector(1 downto 0);
	signal s7SEGM : std_logic_vector(6 downto 0);
	
	constant iCLK_PERIOD : time := 10 ns;
	
   component lprs1_zad3 is  
		port (
			iCLK 		: in  std_logic;
			iRST 		: in  std_logic;
			iRUN     : in  std_logic;
			
			oRED    : out std_logic;
			oYELLOW : out std_logic;
			oGREEN  : out std_logic;
				
			oDIS  : out std_logic_vector(1 downto 0);
			o7SEGM : out std_logic_vector(6 downto 0)
		);
   end component;

begin

   uut: lprs1_zad3 port map (
         iCLK => sCLK,
         iRST => sRST,
         iRUN => sRUN,
         oRED => sRED,

         oYELLOW => sYELLOW,
         oGREEN => sGREEN,
			oDIS => sDIS,
			o7SEGM => s7SEGM
        );
	
	--takt process
	clk_proc : process
	begin
		sCLK <= '1';
		wait for iCLK_PERIOD / 2;
		sCLK <= '0';
		wait for iCLK_PERIOD / 2;
	end process;
	
   stimulus : process
   begin
	
		sRST <='1';
		wait for iCLK_PERIOD * 2.25;
		sRST <='0';
	
		sRUN <='1';
		-- IDLE - 1 iclk period
		-- RED - 29 sekundi
		-- YELLOW - 1.5 sekunde
		-- GREEN - 19 sekundi
		-- jedan ciklus -> 19+1.5+29=49.5 sekundi
		-- dva ciklusa -> sve to *2 => 99
		
		-- jedna sekunda = 12 000 000 clk perioda
		-- ali kod nas je zbog jednostavnosti i simulacije 1 sekunda 6 clk perioda
		
		wait for iCLK_PERIOD * 99 * 7;
		wait for iCLK_PERIOD *3; -- zbog IDLE stanja - 3 puta
		
		-- zbog toga sto je 1 sekunda = 6 taktova mnozimo sa 6+1=7 (broji 1 vise takt po sekundi nego sto je vrednost konstante)
		
		-- da bi se istestirao sistem u realnom vremenu odkomentarisati sledecu liniju:
		-- wait for iCLK_PERIOD * 50.5 * 12000000 * 2;
		
		sRST <= '1';

	
	wait;
	
   end process;
end architecture;