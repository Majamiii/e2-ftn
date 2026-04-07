library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;

entity Signal_light is port ( 
	iCLK  	: in  std_logic;
	iRST  	: in  std_logic;
	iLEFT  	: in  std_logic;
	iRIGHT  	: in  std_logic;
	oLEFT		: out std_logic_vector(2 downto 0);
	oRIGHT	: out std_logic_vector(2 downto 0)
	);
end entity;

architecture Behavioral of Signal_light is
	
	signal sLEFT_CNT 		:	std_logic_vector(3 downto 0);
	signal sRIGHT_CNT		:	std_logic_vector(3 downto 0);
	signal sL_EN			:	std_logic;
	signal sR_EN			:	std_logic;
	signal sRST_L			:	std_logic;
	signal sRST_R			:	std_logic;
	signal sL_TC			:	std_logic;
	signal sR_TC			:	std_logic;
	
	type tTYPE is (IDLE, L1, L2, L3, R1, R2, R3);
	signal sSTATE			:	tTYPE;
	signal sNEXT_STATE	:	tTYPE;
	
begin

		--brojac lijevi, 10
		process(iCLK, iRST) begin
			if(iRST = '1') then
				sLEFT_CNT <= "0000";
			elsif(iCLK'event and iCLK = '1') then
				if(sRST_L = '1') then
					sLEFT_CNT <= "0000";
				else
					if(sL_EN = '1') then
						if(sLEFT_CNT = "1001") then
							sLEFT_CNT <= "0000";
						else
							sLEFT_CNT <= sLEFT_CNT + 1;		
						end if;
					end if;
				end if;
			end if;
		end process;
		
		sL_TC <= '1' when sLEFT_CNT = "1001" else '0';
		
		--brojac desni, 10
		process(iCLK, iRST) begin
			if(iRST = '1') then
				sRIGHT_CNT <= "0000";
			elsif(iCLK'event and iCLK = '1') then
				if(sRST_R = '1') then
					sRIGHT_CNT <= "0000";
				else
					if(sR_EN = '1') then
						if(sRIGHT_CNT = "1001") then
							sRIGHT_CNT <= "0000";
						else
							sRIGHT_CNT <= sRIGHT_CNT + 1;		
						end if;
					end if;
				end if;
			end if;
		end process;
		
		sR_TC <= '1' when sRIGHT_CNT = "1001" else '0';

		-- registar
		process(iCLK, iRST) begin
			if(iRST = '1') then
				sSTATE <= IDLE;
			elsif(iCLK'event and iCLK = '1') then
				sSTATE <= sNEXT_STATE;
			end if;
		end process;
		
		-- prelazna funkcija automata
		process(sSTATE, sL_TC, iLEFT, iRIGHT, sR_TC) begin
			case(sSTATE) is
				when IDLE =>
					if(iLEFT = '1') then
						sNEXT_STATE <= L1;
					elsif(iRIGHT = '1') then
						sNEXT_STATE <= R1;
					else 
						sNEXT_STATE <= IDLE;
					end if;
				when L1 =>
					if(iLEFT = '0') then
						sNEXT_STATE <= IDLE;
					elsif(sL_TC = '1' and iLEFT = '1') then
						sNEXT_STATE <= L2;
					else
						sNEXT_STATE <= L1;
					end if;
				when L2 =>
					if(iLEFT = '0') then
						sNEXT_STATE <= IDLE;
					elsif(sL_TC = '1' and iLEFT = '1') then
						sNEXT_STATE <= L3;
					else
						sNEXT_STATE <= L2;
					end if;
				when L3 =>
					if(iLEFT = '0' or sL_TC = '1') then
						sNEXT_STATE <= IDLE;
					else
						sNEXT_STATE <= L3;
					end if;
				when R1 =>
					if(iRIGHT = '0') then
						sNEXT_STATE <= IDLE;
					elsif(sR_TC = '1' and iRIGHT = '1') then
						sNEXT_STATE <= R2;
					else
						sNEXT_STATE <= R1;
					end if;
				when R2 =>
					if(iRIGHT = '0') then
						sNEXT_STATE <= IDLE;
					elsif(sR_TC = '1' and iRIGHT = '1') then
						sNEXT_STATE <= R3;
					else
						sNEXT_STATE <= R2;
					end if;
				when R3 =>
					if(iRIGHT = '0' or sR_TC = '1') then
						sNEXT_STATE <= IDLE;
					else
						sNEXT_STATE <= R3;
					end if;
				when others =>
					sNEXT_STATE <= IDLE;
			end case;
		end process;
		
		-- funkcija izlaza, oLEFT
		process(sSTATE) begin
			if(sSTATE = L1) then
				oLEFT <= "001";
			elsif(sSTATE = L2) then
				oLEFT <= "011";
			elsif(sSTATE = L3) then
				oLEFT <= "111";
			else
				oLEFT <= "000";
			end if;
		end process;
		
		-- funkcija izlaza, oRIGHT
		process(sSTATE) begin
			if(sSTATE = R1) then
				oRIGHT <= "001";
			elsif(sSTATE = R2) then
				oRIGHT <= "011";
			elsif(sSTATE = R3) then
				oRIGHT <= "111";
			else
				oRIGHT <= "000";
			end if;
		end process;
		
		sL_EN <= '1' when (sSTATE = L1 or sSTATE = L2 or sSTATE = L3) else '0';
		sR_EN <= '1' when (sSTATE = R1 or sSTATE = R2 or sSTATE = R3) else '0';
		sRST_L <= '1' when (sSTATE = R1 or sSTATE = R2 or sSTATE = R3 or sSTATE = IDLE) else '0';
		sRST_R <= '1' when (sSTATE = L1 or sSTATE = L2 or sSTATE = L3 or sSTATE = IDLE) else '0';
		
		
end Behavioral;
