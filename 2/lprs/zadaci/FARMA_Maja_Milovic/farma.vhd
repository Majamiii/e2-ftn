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
use ieee.std_logic_unsigned.ALL;

entity farma is
	port (	
				iCLK	  : in  std_logic;
				iRST    : in  std_logic;	-- asinhroni reset aktivan na logickoj jedinici
				iOK	  : in std_logic;
				iTHIRSTY: in std_logic;
				iWARM	  : in std_logic;
				iCOLD	  : in std_logic;
				iSEL		: in std_logic_vector(1 downto 0);
				oFEED	  : out std_logic;
				oWATER  : out std_logic;
				oRESULT	: out std_logic_vector(5 downto 0)
		);
end entity;

architecture Behavioral of farma is

type tSTATE is (IDLE,FEED,WATER,HEAT,COOL,ALARM);
signal sSTATE, sNEXT_STATE : tSTATE;
signal sFEED, sDRINK, sTC_HEAT, sCOOL,sHEAT: std_logic;
signal sCNT_FEED : std_logic_vector(2 downto 0);
signal sTEMP : std_logic_vector(5 downto 0);
signal sCNT_HEAT : std_logic_vector(3 downto 0);
signal sCNT_COOL : std_logic_vector(3 downto 0);
signal sHEAT_NUM,sCOOL_NUM : std_logic_vector(3 downto 0);
signal sALARM : std_logic_vector(5  downto 0);


begin

	-- odredjivanje sledeceg stanja
	process (iCLK,iRST) begin
		if(iRST='1')then
			sSTATE <= IDLE;
		elsif(iCLK'event and iCLK='1')then
			sSTATE<=sNEXT_STATE;
		end if;
	end process;
	
	-- funkcija prelaza
	process (sSTATE, iOK, sFEED, sDRINK, iTHIRSTY, iCOLD, iWARM, sTEMP) begin
		case (sSTATE) is
			when IDLE =>
				if (iOK='1') then
					if (sFEED='1') then
						sNEXT_STATE <= FEED;
					elsif (sDRINK='1') then
						sNEXT_STATE <= WATER;
					elsif (iWARM='1') then
						sNEXT_STATE <= COOL;
					elsif (iCOLD='1') then
						sNEXT_STATE <= HEAT;
					else
						sNEXT_STATE <= IDLE;
					end if;
				else
					sNEXT_STATE <= ALARM;
				end if;
			when FEED =>
				if (sFEED ='0') then
					sNEXT_STATE <= WATER;
				elsif (iOK = '0') then
					sNEXT_STATE <= ALARM;
				else
					sNEXT_STATE <= FEED;
				end if;
			when WATER =>
				if (sDRINK ='0') then
					sNEXT_STATE <= IDLE;
				elsif (iOK = '0') then
					sNEXT_STATE <= ALARM;
				else
					sNEXT_STATE <= WATER;
				end if;
			when HEAT =>
				if (sTEMP >= 30) then
					sNEXT_STATE <= IDLE;
				elsif (iOK = '0') then
					sNEXT_STATE <= ALARM;
				else
					sNEXT_STATE <= HEAT;
				end if;
			when COOL =>
				if (sTEMP <= 10) then
					sNEXT_STATE <= IDLE;
				elsif (iOK = '0') then
					sNEXT_STATE <= ALARM;
				else
					sNEXT_STATE <= COOL;
				end if;
			when ALARM =>
				if (iOK='1') then
					sNEXT_STATE <= IDLE;
				else
					sNEXT_STATE <= ALARM;
				end if;
			when others =>
				sNEXT_STATE <= sSTATE;
		end case;
	end process;
	
	-- brojac po modulu 8 za hranu
	process (iCLK,iRST)begin
		if (iRST='1')then
			sCNT_FEED <= "000";
		elsif(iCLK'event and iCLK='1') then
			if (sCNT_FEED = 7) then
				sCNT_FEED <= "000";
			else
				sCNT_FEED <= sCNT_FEED + 1;
			end if;
		end if;
	end process;
	
	
	-- definisanje i mapiranje izlaznih signala za hranu i vodu
	
	sFEED <= '1' when (sCNT_FEED="111" and sSTATE=IDLE) else '0';
	oFEED <= '1' when sSTATE=FEED else '0';
	
	sDRINK <= '1' when iTHIRSTY='1'and (sSTATE=IDLE) else '0';
	oWATER <= '1' when sSTATE=WATER else '0';
	
	
	-- sekvencijalni proces za grejanje/hladjenje
	-- upotrebom Dzonsonovog brojaca
	process (iCLK,iRST)begin
		if (iRST='1')then
			sCNT_HEAT <= "0000";
			sCNT_COOL <= "1111";
		elsif(iCLK'event and iCLK='1') then
			case sSTATE is
				when HEAT =>	
					if(iCOLD = '1') then
						if(sCNT_HEAT = "1111") then
							sCNT_HEAT <= "0000";
						else
							sCNT_HEAT <= sCNT_HEAT(2 downto 0) & not(sCNT_HEAT(3));
						end if;
					end if;
					
				when COOL =>
					if(iWARM = '1') then
						if(sCNT_COOL = "0000") then
							sCNT_COOL <= "1111";
						else
							sCNT_COOL <= sCNT_COOL(2 downto 0) & not(sCNT_COOL(3));
						end if;

					end if;
				when others =>							
					sCNT_HEAT <= "0000";
					sCNT_COOL <= "1111";
				end case;
		end if;
	end process;
	
	-- sekvencijalni proces za odredjivanje stope promene temperature
	process(iCLK,iRST)begin
		if(iRST='1') then
			sTEMP <= "010100";
		elsif(iCLK'event and iCLK='1')then
			if (sSTATE=HEAT) then
			
				-- ako temperatura tezi da padne iznad 30, limitirati je tako da je maximum 30
				if (sTEMP + ("00" & sHEAT_NUM) >= 30) then
                sTEMP <= "011110";
            else
                sTEMP <= sTEMP + ("00" & sHEAT_NUM);
            end if;
			elsif (sSTATE=COOL)then
			
				-- ako temperatura tezi da padne ispod 10, limitirati je tako da je minimum 10
				if (sTEMP - ("00" & sCOOL_NUM) <= 10) then
					 sTEMP <= "001010";  -- 10
				else
					 sTEMP <= sTEMP - ("00" & sCOOL_NUM);
				end if;
			else
				sTEMP<=sTEMP;
			end if;
		end if;
	end process;
	
	-- prioritetni dekoderi viseg prioriteta za odredjivane promene temperature
	-- pri hladjenju, odnosno grejanju
	sHEAT_NUM <= "1000" when sCNT_HEAT(3) = '1' else
				 "0100" when sCNT_HEAT(2) = '1' else
				 "0010" when sCNT_HEAT(1) = '1' else
				 "0001" when sCNT_HEAT(0) = '1' else
				 "0000";
				 
	sCOOL_NUM <= "1000" when sCNT_COOL(3) = '0' else
				 "0100" when sCNT_COOL(2) = '0' else
				 "0010" when sCNT_COOL(1) = '0' else
				 "0001" when sCNT_COOL(0) = '0' else
				 "0000";
	
	-- definisanje internih signala koji ulaze u multiplekser
	sCOOL <= '1' when sSTATE=COOL else '0';
	sHEAT <= '1' when sSTATE=HEAT else '0';
	sALARM <= "111111" when sSTATE=ALARM else "000000";
	
	-- multiplekser koji na izlazu prikazuje adekvatan izlaz u zavisnosti od ulaznog iSEL
	oRESULT <= ("00000"&sCOOL) when iSEL="00" else		-- treba da bude aktivan kada je sistem u stanju COOL, kada smanjujemo temperaturu
				  ("00000"&sHEAT) when iSEL="01" else		-- treba da bude aktivan kada je sistem u stanju HEAT, kada povecavamo temperaturu
			   	sTEMP when iSEL="10" else
			   	sALARM;
	

end Behavioral;