library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

-- Libraries.

entity lprs1_homework3 is
    port ( 
		 
		 iCLK: in  std_logic;
		 iNRST    : in  std_logic;
		 iSel     : in  std_logic_vector (1 downto 0);
		 iduration  : in  std_logic_vector(7 downto 0);
		 istart  : in  std_logic;
		 o150w    : out std_logic;
		 o300w : out std_logic;
		 o650w : out std_logic;
		 o800w : out std_logic;
		 oWARN  : out std_logic);
end entity;


architecture arch of lprs1_homework3 is
	signal sWARN_CNT_EN, sWARN_CNT_TC, sheat_cnt_en, sheat_cnt_tc, sWARN_EN, sHEAT_EN: std_logic;
	type stanje is (IDLE, HEAT, WARNING);
	signal sstate, snext_state: stanje;
	signal warn_cnt: std_logic_vector(2 downto 0);
	signal heat_cnt: std_logic_vector(7 downto 0);
	
begin
	--idle setter 
	
	process(iCLK, inRST) begin
		if(iNRST = '1') then
			sSTATE <= IDLE;
		elsif(rising_edge(iCLK)) then 
			sSTATE <= snext_state;
		end if;
	end process;

	
	--prelazi stanja
	
	process(sstate, snext_state, istart, sheat_cnt_tc, swarn_Cnt_tc) begin
		sstate <= snext_state;
		
		
		case (sstate) is
			when HEAT =>
				if(sheat_cnt_tc = '1') then
					snext_state <= WARNING;
				end if;
			when WARNING =>
				if(sWARN_cnt_tc = '1') then 
					snext_State <= IDLE;
				end if;
			when IDLE =>
				if(iSTART = '1') then
					snext_State <= HEAT;
				end if;
			when others => 
				snext_state <= IDLE;
		end case;
	end process;
	
	
	--promene u stanjima 
	
	process (sstate) begin
	
		case (sstate) is
			when HEAT => 
				sHeat_cnt_en <= '1';
				swarn_cnt_en <= '0';
				swarn_en     <= '0';
				sHEat_cnt_en <= '1';
			When WARNING =>
				sHeat_cnt_en <= '0';
				swarn_cnt_en <= '1';
				swarn_en     <= '1';
				sHEat_cnt_en <= '0';
			When others =>
				sHeat_cnt_en <= '0';
				swarn_cnt_en <= '0';
				swarn_en     <= '0';
				sHEat_cnt_en <= '0';
		end case;
	end process;
	
	
	--heating counter
	
	process(iCLK, inRST) begin
		if (iNRST = '1') then
			heat_cnt <= "00000000";
		else
			if(sHeat_CNT_En = '1') then
				if(rising_edge(iclk)) then
					if(heat_cnt<iduration) then
						heat_cnt<=heat_cnt+1;
					else 
						heat_cnt<=(others=>('0'));
					end if;
				end if;
			else
				heat_cnt <= (others => '0');
			end if;
		end if;
	end process;
	
sHeat_cnt_tc <= '1' when heat_cnt = iDURATION - 1 else
					 '0';

	--warn counter 
	
	process(inRST, iCLK) begin 
		if (iNRST = '0') then
			warn_cnt <= (others => ('0'));
		elsif (swarn_cnt_en = '1' and rising_edge(iclk)) then
				if(warn_cnt < 8-1) then
					warn_Cnt <= warn_cnt + 1;
				else 
					warn_cnt <= (others => '0');
				end if;
		else 
			warn_cnt <= (others => '0');
		end if;
	end process;
	
swarn_cnt_tc <= '1' when warn_cnt = 7 else
					 '0';

	----------      demux        ----------
	
o150w<= sheat_en when isel="00" else
		'0';
o300w<= sheat_en when isel="01" else
		'0';
o650w<= sheat_en when isel="10" else
		'0';
o800w<= sheat_en when isel="11" else
		'0';
	
	
	
end architecture;