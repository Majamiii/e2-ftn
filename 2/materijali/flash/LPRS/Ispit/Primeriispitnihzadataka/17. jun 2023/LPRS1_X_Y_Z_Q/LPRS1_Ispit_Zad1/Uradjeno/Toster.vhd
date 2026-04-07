library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;

entity Toster is port ( 
	iCLK  	: in  std_logic;
	-- sinhroni
	iRST  	: in  std_logic;
	-- zahtjev za tostiranje
	-- kad krene zagrijavanje postaviti ga na 0
	iTOAST  	: in  std_logic;
	-- aktivan kad zavrsi sa tostiranjem
	oDONE   	: out std_logic;
	-- temp unutar postera
	oTEMP		: out std_logic_vector(7 downto 0);
	-- vrijeme preostalo do kraja
	oTIME		: out std_logic_vector(5 downto 0)
	);
end entity;

architecture Behavioral of Toster is

	signal sTC1		: std_logic;
	signal sHEAT	: std_logic;
	signal sEN		: std_logic;
	signal sTC2		: std_logic;
	signal sTEMP	: std_logic_vector(7 downto 0);
	signal sCNT		: std_logic_vector(2 downto 0);
	signal sCNT2	: std_logic_vector(5 downto 0);
	
	type tSTATE is (IDLE, WARM_UP, TOAST, COOL_DOWN);
	signal sSTATE, sNEXT_STATE: tSTATE;
	
	
begin
	
	-- brojac po modulu 5
		process(iCLK) begin
			if(iCLK' event and iCLK = '1') then	
				if(iRST = '1') then
					sCNT <= "000";
				else 
					if(sCNT = "100") then
						sCNT <= "000";
					else 
						sCNT <= sCNT + 1;
					end if;
				end if;
			end if;
		end process;
		
		sTC1 <= '1' when sCNT = "100" else '0';
		
	-- senzor za temperaturu
		process(iCLK) begin
			if(iCLK'event and iCLK = '1') then
				if(iRST = '1') then
					if(sHEAT = '1') then
						if(sTC1 = '1') then
							if(sTEMP <= 240) then
								sTEMP <= sTEMP + 10;
							end if;
						end if;
					else 
						if(sTC1 = '1') then
							if(sTEMP >= 30) then
								sTEMP <= sTEMP - 10;
							end if;
						end if;
					end if;
				end if;
			end if;
		end process;
		
	-- tajmer za tostiranje, od 60 do 0
		process(iCLK) begin
			if(iCLK' event and iCLK = '1') then
				if(iRST = '1') then
					sCNT2 <= "111100"; --60
				else
					if(sEN = '1') then
						if(sCNT2 = 0) then
							sCNT2 <= "111100";
						else 	
							sCNT2 <= sCNT2 - 1;
						end if;
					end if;
				end if;
			end if;
		end process;
		
		sTC2 <= '1' when sCNT2 = 0 else '0';
		
	-- registar pamcenja stanja
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
		process(sSTATE, iTOAST, sTEMP, sTC2) begin
			case(sSTATE) is
				when IDLE =>
					if(iTOAST = '1') then
						sNEXT_STATE <= WARM_UP;
					else
						sNEXT_STATE <= IDLE;
					end if;
				when WARM_UP =>
					if(sTEMP > 100) then
						sNEXT_STATE <= TOAST;
					else 
						sNEXT_STATE <= WARM_UP;
					end if;
				when TOAST =>
					if(sTC2 = '1') then
						sNEXT_STATE <= COOL_DOWN;
					else 
						sNEXT_STATE <= TOAST;
					end if;
				when COOL_DOWN =>
					if(iTOAST = '0' and sTEMP = 20) then
						sNEXT_STATE <= IDLE;
					elsif(iTOAST = '1' and sTEMP < 100) then
						sNEXT_STATE <= WARM_UP;
					elsif(iTOAST = '1' and sTEMP < 200) then
						sNEXT_STATE <= TOAST;
					else 
						sNEXT_STATE <= COOL_DOWN;
					end if;
				when others =>
					sNEXT_STATE <= IDLE;
			end case;
		end process;
		
	-- funkcija izlaza
		oDONE <= '1' when sSTATE = COOL_DOWN else '0';
		sHEAT <= '1' when (sSTATE = WARM_UP and sSTATE = TOAST) else '0';
		sEN <= '1' when sSTATE = TOAST else '0';
		
					

end Behavioral;
