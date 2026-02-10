---------------------------------------------------------------
-- LPRS dodatni zadatak
-- Naziv rada: Automat za upravljanje farmom
-- Zadatak je radjen u paru, sa kolegenicom Jovanom Vranjesevic
-- Ime i prezime: Maja Milovic
-- Broj indeksa: RA69/2024
-- Grupa na vežbama: 1
-- Asistent: Milica Tadic
---------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

entity farma_tb is
end entity;
 
architecture Test of farma_tb is
	--Inputs
   signal sCLK : std_logic := '0';
   signal sRST : std_logic := '0';
	signal sOK	: std_logic := '0';
   signal sTHIRSTY : std_logic := '0';
   signal sWARM : std_logic := '0';
	signal sCOLD	: std_logic := '0';
	signal sSEL		: std_logic_vector(1 downto 0) := "00";
	--Outputs
   signal sFEED  : std_logic;
   signal sWATER : std_logic;
	signal sRESULT  : std_logic_vector(5 downto 0);
	
	constant iCLK_PERIOD : time := 10 ns;
	
   component farma is  
		port (
				iCLK	  : in  std_logic;
				iRST    : in  std_logic;
				iOK	  : in std_logic;
				iTHIRSTY: in std_logic;
				iWARM	  : in std_logic;
				iCOLD	  : in std_logic;
				iSEL	  : in std_logic_vector(1 downto 0);
				oFEED	  : out std_logic;
				oWATER  : out std_logic;
				oRESULT: out std_logic_vector(5 downto 0)
		);
   end component;

begin

   uut: farma port map (
         iCLK => sCLK,
         iRST => sRST,
			iOK => sOK,
			iTHIRSTY => sTHIRSTY,
			iWARM => sWARM,
			iSEL => sSEL,
			iCOLD => sCOLD,
			oFEED => sFEED,
			oWATER => sWATER,
			oRESULT => sRESULT
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
	
        sRST <= '1';
        wait for iCLK_PERIOD * 2.25;
        sRST <= '0';
        
        sOK <= '1';
        wait for iCLK_PERIOD * 10;
        
        -- signal za zedj - prelazak u WATER stanje
        sSEL <= "10";
        sTHIRSTY <= '1';
        wait for iCLK_PERIOD*1;
        sTHIRSTY <= '0';
        
        -- signal da je toplo - prelazak u COOL stanje
        sWARM <= '1';
        sSEL <= "10"; -- prikaz temp
        wait for 5*iCLK_PERIOD;
        sWARM <= '0';
        
		  -- dalji prikaz spustanja temp
		  -- u medjuvremenu treba i da se automatski aktivira signal za hranu
        wait for 20*iCLK_PERIOD;
        
        -- signal da je hladno - prelazak u HEAT stanje
        sCOLD <= '1';
        sSEL <= "01";
        wait for 5*iCLK_PERIOD;
        sCOLD <= '0';
        
        -- cekanje da se temperatura digne do 30
        sSEL <= "10";
        wait for 25*iCLK_PERIOD;
        
        -- prelazak u ALARM
        sOK <= '0';
        sSEL <= "11";
        wait for 6*iCLK_PERIOD;
        
        -- izlazak iz ALARMa
        sOK <= '1';
        wait for 5*iCLK_PERIOD;
        
        -- signal za zedj
        sTHIRSTY <= '1';
        wait for iCLK_PERIOD;
        sTHIRSTY <= '0';
        wait for 5*iCLK_PERIOD;
        
        -- grejanje i hladjenje
        sCOLD <= '1';
		  sSEL <= "01";
        wait for 3*iCLK_PERIOD;
		  -- kako je temperatura vec visoko treba da da vraca u IDLE
        sOK <= '0';  -- alarm tokom grejanja
        wait for 5*iCLK_PERIOD;
        sOK <= '1';
        sCOLD <= '0';
        wait for 5*iCLK_PERIOD;
        
        -- provera svih SEL vrednosti
        sSEL <= "00";
        wait for 5*iCLK_PERIOD;
        sSEL <= "01";
        wait for 5*iCLK_PERIOD;
        sSEL <= "10";
        wait for 5*iCLK_PERIOD;
        sSEL <= "11";
        wait for 5*iCLK_PERIOD;
        
		  -- pustanje sistema da radi 20 taktova
        wait for 20*iCLK_PERIOD;
		  
		  -- iskljucivanje sistema
		  sRST <= '1';
		  
		  -- simulaciju treba pokrenuti oko 1500 ns kako bi se sve izvrsilo
		
	wait;
	
   end process;
end architecture;