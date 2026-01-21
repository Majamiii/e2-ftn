-------------------------------------------------------------
-- Ime i prezime: Maja Milovic
-- Broj indeksa: RA69/2024
-- Grupa na vežbama: 1
-- Asistent: Milica Tadic
-------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;

entity lprs1_zad3 is
	port (	
				iCLK	  : in  std_logic;
				iRST    : in  std_logic;
				iRUN    : in  std_logic;
				
				oRED    : out std_logic;
				oYELLOW : out std_logic;
				oGREEN  : out std_logic;
				
				oDIS    : out std_logic_vector(1 downto 0);
				o7SEGM  : out std_logic_vector(6 downto 0)
		);
end entity;

architecture Behavioral of lprs1_zad3 is

type tSTATE is (IDLE, RED,  YELLOW, GREEN, ERROR);
signal sSTATE, sNEXT_STATE : tSTATE;

signal sRED_UNITS_CNT	: std_logic_vector(3 downto 0);
signal sRED_TENS_CNT		: std_logic_vector(3 downto 0);
signal sRED_PREV_CNT		: std_logic_vector(3 downto 0);
signal sRED_TENS_EN		: std_logic;
signal sRED_DONE			: std_logic;

signal sGREEN_UNITS_CNT	: std_logic_vector(3 downto 0);
signal sGREEN_TENS_CNT	: std_logic_vector(3 downto 0);
signal sGREEN_PREV_CNT	: std_logic_vector(3 downto 0);
signal sGREEN_TENS_EN	: std_logic;
signal sGREEN_DONE		: std_logic;

--constant cSECOND			: std_logic_vector(23 downto 0):="101101110001101100000000"; --  --000000000000000000001100 101101110001101100000000
constant cSECOND			: std_logic_vector(23 downto 0):="000000000000000000000001";
signal sRED_TIMER			: std_logic_vector(23 downto 0);
signal sRED_COUNT_EN		: std_logic;

signal sGREEN_TIMER		: std_logic_vector(23 downto 0);
signal sGREEN_COUNT_EN	: std_logic;

signal sYELLOW_CNT		: std_logic_vector(23 downto 0);
signal sYELLOW_TC			: std_logic;
signal sHALF_SECOND		: std_logic_vector(1 downto 0);		-- dodat signal kako bi se omogucilo brojanje do 1,5 sekunde (3*0,5)

signal sRUN					: std_logic;
signal sCURRENT_STATE	: std_logic;
signal sPREV_STATE		: std_logic;

-- ==================== PRIKAZ NA DISPLAJU ====================
signal sTC					: std_logic;  -- dozvole za displej
signal sDIS_SEL 			: std_logic_vector(1 downto 0);
signal sDIS_CNT 			: std_logic_vector(14 downto 0);
-- constant cDIS_MAX			: std_logic_vector(14 downto 0) := "111111111111111";
constant cDIS_MAX			: std_logic_vector(14 downto 0) := "000000000000100";

signal sDISPLAY_0			: std_logic_vector(6 downto 0);
signal sDISPLAY_1			: std_logic_vector(6 downto 0);
signal sDISPLAY_2			: std_logic_vector(6 downto 0);
signal sDISPLAY_3			: std_logic_vector(6 downto 0);

-- ukoliko je brojač neaktivan da li se njegova vrijednost šalje na prikaz ili je displej isključen
signal sRED_TENS_DISPLAY	: std_logic_vector(3 downto 0); 
signal sRED_UNITS_DISPLAY	: std_logic_vector(3 downto 0); 
signal sGREEN_TENS_DISPLAY	: std_logic_vector(3 downto 0);
signal sGREEN_UNITS_DISPLAY	: std_logic_vector(3 downto 0);


begin


	-- odredjivanje sledeceg stanja i pokretanje semafora
	process (iCLK,iRST,iRUN) begin
		if(iRST='1')then
			sSTATE <= IDLE;
			sPREV_STATE <= '0';
		elsif(iCLK'event and iCLK='1')then
		-- registar sPREV_STATE cuva vrednost signala iRUN
			if (iRUN='1')then
				sPREV_STATE<='1';
			end if;
			
			if(sPREV_STATE='1')then
				sSTATE<=sNEXT_STATE;
			end if;
		end if;
	end process;
	
	-- signal sRUN
	sRUN <= '1' when (sPREV_STATE='0' and iRUN='1') else '0';
	
	-- registar CURRENT STATE
	process(iCLK,iRST)begin
		if(iRST='1')then
			sCURRENT_STATE <= '0';
		elsif(iCLK'event and iCLK='1')then
			if(sRUN='1')then
				sCURRENT_STATE <= sRUN;
			end if;
		end if;
	end process;
	
	
	-- odredjivanje sledeceg stanja automata
	process(sSTATE, sCURRENT_STATE, sRED_DONE, sYELLOW_TC, sGREEN_DONE)begin
		case (sSTATE) is
			when IDLE =>
				if (sCURRENT_STATE='1')then
					sNEXT_STATE <= RED;
				else
					sNEXT_STATE <= IDLE;
				end if;
				oRED <= '0';
				oYELLOW <= '0';
				oGREEN <= '0';
			when RED =>
				if (sRED_DONE='1')then
					sNEXT_STATE <= YELLOW;
				else
					sNEXT_STATE <= RED;
				end if;
				oRED <= '1';
				oYELLOW <= '0';
				oGREEN <= '0';
			when YELLOW =>
				if (sYELLOW_TC='1')then
					sNEXT_STATE <= GREEN;
				else
					sNEXT_STATE <= YELLOW;
				end if;
				oRED <= '0';
				oYELLOW <= '1';
				oGREEN <= '0';
			when GREEN => 
				if (sGREEN_DONE='1')then
					sNEXT_STATE <= IDLE;
				else
					sNEXT_STATE <= GREEN;
				end if;
				oRED <= '0';
				oYELLOW <= '0';
				oGREEN <= '1';
			when others => -- kada je u stanju ERROR
				sNEXT_STATE <= ERROR;
				
				oRED <= '1';
				oYELLOW <= '1';
				oGREEN <= '1';
		end case;
	end process;
	
	
	
	---------------------------
	-- 	CRVENO SVETLO 		 --
	---------------------------
	
	-- RED timer - registar koji se resetuje nakon svake sekunde
	process (iCLK,iRST)begin
		if(iRST='1')then
			sRED_TIMER<=(others => '0');
		elsif(iCLK'event and iCLK='1')then
			if (sRED_COUNT_EN = '1') then
				if (sRED_TIMER = cSECOND) then
					sRED_TIMER <= (others => '0');
				else
					sRED_TIMER <= sRED_TIMER + 1;
				end if;
			else
				sRED_TIMER <= (others=>'0');
			end if;
		end if;
	end process;
	
	sRED_COUNT_EN <= '1' when (sPREV_STATE='1' and sSTATE=RED) else '0';

	-- crveno svetlo za pesake traje 29 sekundi
	-- dakle jedinice krecu od 9
	process (iCLK,iRST)begin
		if(iRST='1')then
				sRED_UNITS_CNT <= "1001";
		elsif(iCLK'event and iCLK='1')then
			if (sRED_TIMER = cSECOND and sRED_COUNT_EN='1') then
				if (sRED_UNITS_CNT = "0000") then	
					sRED_UNITS_CNT <= "1001";
				else
					sRED_UNITS_CNT <= sRED_UNITS_CNT - 1;
				end if;
			end if;
			if(sRED_DONE='1') then
				sRED_UNITS_CNT <= "1001";
			end if;
		end if;
	end process;
	
	-- registar RED PREV CNT
	-- cuva sRED_UNITS
	process (iCLK,iRST)begin
		if(iRST='1')then
			sRED_PREV_CNT <= (others => '0');		
		elsif(iCLK'event and iCLK='1')then
			sRED_PREV_CNT <= sRED_UNITS_CNT;
		end if;
	end process;
	
	-- dozvolice se da se desetice smanje samo ako su jedinice dosle do 0
	--sRED_TENS_EN <= '1' when (sRED_PREV_CNT="0000" and sRED_UNITS_CNT="1001")
		--else '0';
	sRED_TENS_EN <= '1' when (sRED_PREV_CNT="0000" and sRED_COUNT_EN='1') else '0';
	
	-- crveno svetlo za pesake traje 29 sekundi
	-- dakle desetice krecu od 2
	process (iCLK,iRST)begin
		if(iRST='1')then
			sRED_TENS_CNT <= "0010";
		elsif(iCLK'event and iCLK='1')then
			if(sRED_TENS_EN='1' and sRED_TIMER=cSECOND) then
				sRED_TENS_CNT <= sRED_TENS_CNT - 1;
			elsif(sRED_DONE='1') then
				sRED_TENS_CNT <= "0010";
			end if;
		end if;
	end process;	

	-- signal da je crveno svetlo gotovo -> kada su i desetice i jedinice odbrojale
	sRED_DONE <= '1' when (sRED_TENS_CNT="0000" and sRED_UNITS_CNT="0000") else
			'0';
		
		
	
	---------------------------
	-- 		ZUTO SVETLO 	 --
	---------------------------
	process(iCLK,iRST)begin
		if(iRST='1')then
			sYELLOW_CNT <= (others => '0');
			sHALF_SECOND <= "00";
		elsif(iCLK'event and iCLK='1')then
			if (sSTATE=YELLOW) then
				if (sYELLOW_CNT = ('0' & cSECOND(23 downto 1)) ) then		-- ako je proslo pola sekunde
					sYELLOW_CNT <= (others => '0');
					sHALF_SECOND <= sHALF_SECOND+1;
				else
					sYELLOW_CNT <= sYELLOW_CNT+1;
				end if;
			else
				sYELLOW_CNT <= (others => '0');
				sHALF_SECOND <= "00";
			end if;
		end if;
	end process;
	
	sYELLOW_TC <= '1' when sHALF_SECOND="10" else '0';
	
	
	
	
	---------------------------
	-- 	ZELENO SVETLO 		 --
	---------------------------
	
	-- GREEN timer - registar koji se resetuje nakon svake sekunde
	process (iCLK,iRST)begin
		if(iRST='1')then
			sGREEN_TIMER<=(others => '0');
		elsif(iCLK'event and iCLK='1')then
			if (sGREEN_COUNT_EN = '1') then
				if (sGREEN_TIMER = cSECOND) then
					sGREEN_TIMER <= (others => '0');
				else
					sGREEN_TIMER <= sGREEN_TIMER + 1;
				end if;
			else
				sGREEN_TIMER <= (others=>'0');
			end if;
		end if;
	end process;
	
	sGREEN_COUNT_EN <= '1' when (sPREV_STATE='1' and sSTATE=GREEN) else '0';

	-- zeleno svetlo za pesake traje 19 sekundi
	-- dakle jedinice krecu od 9
	process (iCLK,iRST)begin
		if(iRST='1')then
				sGREEN_UNITS_CNT <= "1001";
		elsif(iCLK'event and iCLK='1')then
			if (sGREEN_TIMER = cSECOND and sGREEN_COUNT_EN='1') then
				if (sGREEN_UNITS_CNT = "0000") then	
					sGREEN_UNITS_CNT <= "1001";
				else
					sGREEN_UNITS_CNT <= sGREEN_UNITS_CNT -1;
				end if;
			end if;
			if(sGREEN_DONE='1') then
				sGREEN_UNITS_CNT <= "1001";
			end if;
		end if;
	end process;
	
	-- registar GREEN PREV CNT
	-- cuva sGREEN_UNITS
	process (iCLK,iRST)begin
		if(iRST='1')then
			sGREEN_PREV_CNT <= (others => '0');		
		elsif(iCLK'event and iCLK='1')then
			sGREEN_PREV_CNT <= sGREEN_UNITS_CNT;
		end if;
	end process;
	
	-- dozvolice se da se desetice smanje samo ako su jedinice dosle do 0
	sGREEN_TENS_EN <= '1' when (sGREEN_PREV_CNT="0000"and sGREEN_COUNT_EN='1') else '0';
	
	-- zeleno svetlo za pesake traje 19 sekundi
	-- dakle desetice krecu od 1
	process (iCLK,iRST)begin
		if(iRST='1')then
			sGREEN_TENS_CNT <= "0001";
		elsif(iCLK'event and iCLK='1')then
			if(sGREEN_TENS_EN='1' and sGREEN_TIMER=cSECOND) then
				sGREEN_TENS_CNT <= sGREEN_TENS_CNT - 1;
			elsif(sGREEN_DONE='1') then
				sGREEN_TENS_CNT <= "0001";
			end if;
		end if;
	end process;	

	-- signal da je zeleno svetlo gotovo -> kada su i desetice i jedinice odbrojale
	sGREEN_DONE <= '1' when (sGREEN_TENS_CNT="0000" and sGREEN_UNITS_CNT="0000") else
			'0';
			
		
		
	---------------------------
	-- 		DISPLEJ		 	 --
	---------------------------
	
	
	sDISPLAY_3 <= "0000001" when sGREEN_TENS_CNT="0000" else
					"1001111";
					
	sDISPLAY_2 <= "0000001" when sGREEN_UNITS_CNT="0000" else
					"1001111" when sGREEN_UNITS_CNT="0001" else
					"0010010" when sGREEN_UNITS_CNT="0010" else
					"0000110" when sGREEN_UNITS_CNT="0011" else
					"1001100" when sGREEN_UNITS_CNT="0100" else
					"0100100" when sGREEN_UNITS_CNT="0101" else
					"0100000" when sGREEN_UNITS_CNT="0110" else
					"0001111" when sGREEN_UNITS_CNT="0111" else
					"0000000" when sGREEN_UNITS_CNT="1000" else
					"0000100" when sGREEN_UNITS_CNT="1001" else
					"1111111";
					
	sDISPLAY_1 <= "0000001" when sRED_TENS_CNT="0000" else
					"1001111" when sRED_TENS_CNT="0001" else
					"0010010" when sRED_TENS_CNT="0010" else
					"0000110" when sRED_TENS_CNT="0011" else
					"1001100" when sRED_TENS_CNT="0100" else
					"0100100" when sRED_TENS_CNT="0101" else
					"0100000" when sRED_TENS_CNT="0110" else
					"0001111" when sRED_TENS_CNT="0111" else
					"0000000" when sRED_TENS_CNT="1000" else
					"0000100" when sRED_TENS_CNT="1001" else
					"1111111";
					
	sDISPLAY_0 <= "0000001" when sRED_UNITS_CNT="0000" else
					"1001111" when sRED_UNITS_CNT="0001" else
					"0010010";
	
	-- brojac za 7seg koji govori koliko brzo ce da treperi
	process (iCLK,iRST)begin
		if(iRST='1')then
			sDIS_CNT <= (others=>'0');
		elsif(iCLK'event and iCLK='1')then
			if (sDIS_CNT=cDIS_MAX) then
				sDIS_CNT <= (others =>'0');
			else
				sDIS_CNT <= sDIS_CNT+1;
			end if;
		end if;
	end process;
	
	
	sTC <= '1' when sDIS_CNT=cDIS_MAX else '0';
	
	-- menjanje selekcionog signala koji opisuje koji displej se prikazuje
	process (iCLK,iRST)begin
		if(iRST='1')then
			sDIS_SEL <= "00";
		elsif(iCLK'event and iCLK='1')then
			if (sTC='1') then
				sDIS_SEL <= sDIS_SEL+1;		-- promena displeja
			end if;
		end if;
	end process;
	
	
	-- izlazi
	
	oDIS <= sDIS_SEL;
	
	o7SEGM <= sDISPLAY_0 when sDIS_SEL="00" else
				 sDISPLAY_1 when sDIS_SEL="01" else
				 sDISPLAY_2 when sDIS_SEL="10" else
				 sDISPLAY_3;
	
	

end Behavioral;