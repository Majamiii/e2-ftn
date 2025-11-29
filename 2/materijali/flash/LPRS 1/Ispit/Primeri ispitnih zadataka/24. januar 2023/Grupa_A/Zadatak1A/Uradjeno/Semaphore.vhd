library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;

entity Semaphore is port ( 
	iCLK  	: in  std_logic;
	iRST  	: in  std_logic;
	-- pokrece rad sistema
	iSTART  	: in  std_logic;
	-- crveno svjetlo
	oRED   	: out std_logic;
	-- zeleno svjetlo
	oGREEN	: out std_logic;
	-- vrijeme do promjene stanja, vr nekog od brojaca
	oCNT		: out std_logic_vector(5 downto 0)
	);
end entity;

architecture Behavioral of Semaphore is
	
	signal sRED_CNT		: std_logic_vector(5 downto 0);
	signal sYELLOW_CNT	: std_logic_vector(3 downto 0);
	signal sGREEN_CNT		: std_logic_vector(4 downto 0);
	signal sR_EN			: std_logic;
	signal sG_EN			: std_logic;
	signal sY_EN			: std_logic;
	signal sR_TC			: std_logic;
	signal sG_TC			: std_logic;
	signal sY_TC			: std_logic;
	
		
	type tSTATE is (IDLE, RED, GREEN, YELLOW);
	signal sSTATE, sNEXT_STATE: tSTATE;
	
	
begin
	
	-- crveni brojac, 60
		process(iCLK) begin
			if(iCLK'event and iCLK = '1') then
				if(iRST = '1') then 
					sRED_CNT <= "000000";
				else
					if(sR_EN = '1') then
						if(sRED_CNT = "111011") then
							sRED_CNT <= "000000";
						else
							sRED_CNT <= sRED_CNT + 1;
						end if;
					end if;
				end if;
			end if;
		end process;
		
		sR_TC <= '1' when sRED_CNT = "111011" else '0';
		
		-- zeleni brojac, 20
		process(iCLK) begin
			if(iCLK'event and iCLK = '1') then
				if(iRST = '1') then 
					sGREEN_CNT <= "00000";
				else
					if(sG_EN = '1') then
						if(sGREEN_CNT = "10011") then
							sGREEN_CNT <= "00000";
						else
							sGREEN_CNT <= sGREEN_CNT + 1;
						end if;
					end if;
				end if;
			end if;
		end process;
		
		sG_TC <= '1' when sGREEN_CNT = "10011" else '0';
		
		-- zuti brojac, 10
		process(iCLK) begin
			if(iCLK'event and iCLK = '1') then
				if(iRST = '1') then 
					sYELLOW_CNT <= "0000";
				else
					if(sY_EN = '1') then
						if(sYELLOW_CNT = "1001") then
							sYELLOW_CNT <= "0000";
						else
							sYELLOW_CNT <= sYELLOW_CNT + 1;
						end if;
					end if;
				end if;
			end if;
		end process;
		
		sY_TC <= '1' when sYELLOW_CNT = "1001" else '0';
	
	-- registar prelaznog stanja
		process(iCLK) begin
			if(iCLK'event and iCLK = '1') then
				if(iRST = '1') then
					sSTATE <= IDLE;
				else
					sSTATE <= sNEXT_STATE;
				end if;
			end if;
		end process;
		
	-- prelazna funkcija
		process(sSTATE, iSTART, sR_TC, sG_TC, sY_TC) begin
			case(sSTATE) is
				when IDLE =>
					if(iSTART = '1') then
						sNEXT_STATE <= RED;
					else
						sNEXT_STATE <= IDLE;
					end if;
				when RED =>
					if(sR_TC = '1') then
						sNEXT_STATE <= GREEN;
					else
						sNEXT_STATE <= RED;
					end if;
				when GREEN =>
					if(sG_TC = '1') then
						sNEXT_STATE <= YELLOW;
					else 
						sNEXT_STATE <= GREEN;
					end if;
				when YELLOW =>
					if(sY_TC = '1') then
						sNEXT_STATE <= RED;
					else
						sNEXT_STATE <= YELLOW;
					end if;
				when others =>
					sNEXT_STATE <= IDLE;
			end case;
		end process;
		
		-- funkcije izlaza
		oRED <= '1' when (sSTATE = RED and sSTATE = YELLOW) else '0';
		oGREEN <= '1' when sSTATE = GREEN else '0';
		sR_EN <= '1' when sSTATE = RED else '0';
		sG_EN <= '1' when sSTATE = GREEN else '0';
		sY_EN <= '1' when sSTATE = YELLOW else '0';
		
		-- multiplekser
		oCNT <=  sRED_CNT when (sSTATE = RED) else
					'0' & sGREEN_CNT when (sSTATE = GREEN) else
					"00" & sYELLOW_CNT;

end Behavioral;
