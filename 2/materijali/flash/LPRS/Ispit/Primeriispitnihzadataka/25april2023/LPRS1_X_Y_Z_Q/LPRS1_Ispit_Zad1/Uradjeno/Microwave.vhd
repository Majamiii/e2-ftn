library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;

------------------------------------------------------------------------------------------
-- OBAVEZNO UPIŠITE IME, PREZIME i BROJ INDEKSA!
-- Ime i prezime: 
-- Broj indeksa: 
-- Radim samo popravni (upisati DA ako je iskaz tačan): 
------------------------------------------------------------------------------------------

entity Microwave is port ( 
	iCLK  	: in  std_logic;
	iRST  	: in  std_logic;	--sinhron
	-- zahtjev za podgrijavanje 
	iREQ  	: in  std_logic;
	-- da li su otvorena vrata
	iDOOR  	: in  std_logic;
	-- koliko dugo traje zagrijavanje hrane
	iTIME	: in  std_logic_vector(5 downto 0);
	-- aktivan kad mikrot zavrsi s radom
	oDONE   : out std_logic;
	-- mikrot grije hranu
	oLAMP	: out std_logic;
	-- vrijeme preostalo do kraja rada mikrot
	oTIME	: out std_logic_vector(5 downto 0)
	);
end entity;

architecture Behavioral of Microwave is

	signal sREQ		: std_logic;
	signal sCLEAR	: std_logic;
	signal sTC		: std_logic;
	signal sEN1		: std_logic;
	signal sEN2		: std_logic;
	signal sTIME	: std_logic_vector(5 downto 0);

--dodatan signal za brojac od 60 do 0
	signal sCNT		: std_logic_vector(5 downto 0);
	
	type tSTATE is (IDLE, CLOSE_DOOR, COOK, PAUSE, DONE);
	signal sSTATE, sNEXT_STATE: tSTATE;
	
	
begin

	-- registar za prihvatanje zahtjeva
		process(iCLK) begin
			if(iCLK'event and iCLK = '1') then
				if(sCLEAR = '1') then
					sREQ <= '0';
				else
					sREQ <= iREQ;
				end if;
			end if;
		end process;
		
				
	-- registar za pamcenje stanja, sinhrono
		process(iCLK) begin
			if(iCLK'event and iCLK = '1') then
				if(iRST = '1') then
					sSTATE <= IDLE;
				else
					sSTATE <= sNEXT_STATE;
				end if;
			end if;
		end process;
		
	-- tajmer za rad
		process(iCLK) begin
			if(iCLK'event and iCLK = '1') then
				if(iRST = '1') then
					sTIME <= "000000";
				else
					if(sEN1 = '1' and iDOOR = '0') then
						sTIME <= sTIME - 1;
					elsif(sSTATE = CLOSE_DOOR) then
						sTIME <= iTIME;
					else
						sTIME <= sTIME;
					end if;
				end if;
			end if;
		end process;
		
		-- tajmer za promjenu neaktivnog stanja, broji od 60 do 0 
		process(iCLK) begin
			if(iCLK'event and iCLK = '1') then
				if(sEN2 = '0') then
					sCNT <= "111100"; --60
				else 
					sCNT <= sCNT - 1;
				end if;
			end if;
		end process;
		
		sTC <= '1' when sCNT = "000000" else '0';
		
		-- funkcija automata
		process(sSTATE, iREQ, iDOOR, sTIME, sTC) begin
			case(sSTATE) is
				when IDLE =>
					if(iREQ = '1') then
						sNEXT_STATE <= CLOSE_DOOR;
					else
						sNEXT_STATE <= IDLE;
					end if;
				when CLOSE_DOOR =>
					if(iDOOR = '0' and sTIME /= 0) then
						sNEXT_STATE <= COOK;
					else
						sNEXT_STATE <= CLOSE_DOOR;
					end if;
				when COOK =>
					if(iDOOR = '1') then
						sNEXT_STATE <= PAUSE;
					elsif(sTIME = 0) then
						sNEXT_STATE <= DONE;
					else
						sNEXT_STATE <= COOK;
					end if;
				when PAUSE =>
					if(iDOOR = '0') then
						sNEXT_STATE <= COOK;
					elsif(sTC = '1') then
						sNEXT_STATE <= DONE;
					else
						sNEXT_STATE <= PAUSE;
					end if;
				when others =>
					sNEXT_STATE <= IDLE;
			end case;
		end process;
		
		-- funkcije izlaza
		oDONE <= '1' when sSTATE = DONE else '0';
		oLAMP <= '1' when sSTATE = COOK else '0';
		sEN1 <= '1' when sSTATE = COOK else '0';
		sEN2 <= '1' when sSTATE = PAUSE else '0';
		sCLEAR <= '1' when sSTATE = DONE else '0';
		
		oTIME <= sTIME;

end Behavioral;
