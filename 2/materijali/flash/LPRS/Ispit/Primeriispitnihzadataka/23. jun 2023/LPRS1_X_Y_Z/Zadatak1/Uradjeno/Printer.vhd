---------------------------------------------
-- Ime i prezime: 
-- Broj indeksa: 
---------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;

entity Printer is port ( 
	iCLK  			: in  std_logic;
	-- sinhorni 
	iRST  			: in  std_logic;
	-- signal za zahtjev za stampanje 
	iPRINT  			: in  std_logic;
	-- ubacivanje papira
	iADD_PAPER  	: in  std_logic;
	-- kolicina papira
	iAMOUNT			: in  std_logic_vector(7 downto 0);
	-- da li je stampanje zapocelo
	oPRINT			: out std_logic;
	-- greska, nedostaje papira
	oERROR			: out std_logic
	);
end entity;

architecture Behavioral of Printer is
  signal sEMPTY		 	: std_logic; 
  signal sPAPER_EN 	 	: std_logic;
  signal sSLEEP_EN		: std_logic;
  signal sSLEEP_TC		: std_logic;
  signal sPRINT_EN		: std_logic;
  signal sPRINT_TC		: std_logic;
  signal sSLEEP_CNT 		: std_logic_vector(5 downto 0); 
  signal sPRINT_CNT 		: std_logic_vector(3 downto 0); 
  signal sPAPER_CNT 		: std_logic_vector(7 downto 0);
  
  type tTYPE is (IDLE, SLEEP, CHECK_PAPER, PRINT, ERROR); 
  signal sSTATE, sNEXT_STATE : tTYPE;
  
	
begin
	
	-- brojac za neaktivno stanje 
		process(iCLK) begin
			if(iCLK' event and iCLK = '1') then
				if(iRST = '1') then
					sSLEEP_CNT <= "000000";
				else
					if(sSLEEP_EN = '1') then
						if(sSLEEP_CNT = "111011") then
							sSLEEP_CNT <= "000000";
						else
							sSLEEP_CNT <= sSLEEP_CNT + 1;
						end if;
					end if;
				end if;
			end if;
		end process;
		
		sSLEEP_TC <= '1' when sSLEEP_CNT = "111011" else '0';
		
	-- brojac za stampanje 
		process(iCLK) begin
			if(iCLK' event and iCLK = '1') then
				if(iRST = '1') then
					sPRINT_CNT <= "0000";
				else
					if(sPRINT_EN = '1') then
						if(sPRINT_CNT = "1110") then
							sPRINT_CNT <= "0000";
						else
							sPRINT_CNT <= sPRINT_CNT + 1;
						end if;
					end if;
				end if;
			end if;
		end process;
		
		sPRINT_TC <= '1' when sPRINT_CNT = "1110" else '0';
		
	-- brojac za papir
		process(iCLK) begin
			if(iCLK'event and iCLK = '1') then
				if(iRST = '1') then
					sPAPER_CNT <= "00000000";
				else
					if(iADD_PAPER = '1') then
						sPAPER_CNT <= iAMOUNT;
						if(sSTATE = CHECK_PAPER) then
							if(sEMPTY = '0') then
								sPAPER_CNT <= sPAPER_CNT - 1;
							else
								sPAPER_CNT <= (others => '0');
							end if;
						end if;
					end if;
				end if;
			end if;
		end process;
		
		sEMPTY <= '1' when sPAPER_CNT = "00000000" else '0';
	
	-- pocetno stanje automata
		process(iCLK) begin
			if(iCLK'event and iCLK = '1') then
				if(iRST = '1') then
					sSTATE <= IDLE;
				else 
					sSTATE <= sNEXT_STATE;
				end if;
			end if;
		end process;
		
	-- funkcija automata
		process(sSTATE, sSLEEP_TC, iPRINT, sEMPTY, sPRINT_TC) begin
			case(sSTATE) is
				when IDLE =>
					if(sSLEEP_TC = '1') then
						sNEXT_STATE <= SLEEP;
					elsif(iPRINT = '1') then
						sNEXT_STATE <= CHECK_PAPER;
					else 
						sNEXT_STATE <= IDLE;
					end if;
				when SLEEP =>
					if(iPRINT = '1') then
						sNEXT_STATE <= IDLE;
					else
						sNEXT_STATE <= SLEEP;
					end if;
				when CHECK_PAPER =>
					if(sEMPTY = '0') then
						sNEXT_STATE <= PRINT;
					elsif(sEMPTY = '1') then
						sNEXT_STATE <= ERROR;
					else
						sNEXT_STATE <= CHECK_PAPER;
					end if;
				when ERROR => 
					sNEXT_STATE <= IDLE;
				when PRINT =>
					if(sPRINT_TC = '1') then
						sNEXT_STATE <= IDLE;
					else
						sNEXT_STATE <= PRINT;
					end if;
				when others =>
					sNEXT_STATE <= IDLE;
			end case;
		end process;
		
	-- funkcije izlaza
		oPRINT <= '1' when sSTATE = PRINT else '0';
		oERROR <= '1' when sSTATE = ERROR else '0';
		sSLEEP_EN <= '1' when sSTATE = IDLE else '0';
		sPRINT_EN <= '1' when sSTATE = PRINT else '0';
		sPAPER_EN <= '1' when sSTATE = CHECK_PAPER else '0';
	
	
end Behavioral;
