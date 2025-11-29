library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity Semafor is
    port ( 	iCLK    : in  std_logic;
				iRST    : in  std_logic;
				iSel     : in  std_logic_vector (1 downto 0);
				iduration  : in  std_logic_vector(7 downto 0);
				istart  : in  std_logic;
				o150w    : out std_logic;
				o300w : out std_logic;
				o650w : out std_logic;
				o800w : out std_logic;
				oWARN  : out std_logic);
end Semafor;

architecture Behavioral of Semafor is
	
	signal sHeat_cnt_en: std_logic;
	signal swarn_cnt_en: std_logic;
	signal sheat_en: std_logic;
	signal swarn_en: std_logic;
	signal warn_cnt: std_logic_vector(2 downto 0);
	signal swarn_cnt_tc: std_logic;
	signal heat_cnt: std_logic_vector(7 downto 0);
	signal sheat_cnt_tc: std_logic;
	type stanje is (IDLE,HEAT,WARNING);
	signal sstate,snextstate: stanje;
	

begin
 
 process (iclK,irsT) begin
	
	if (irsT='0') then
		sstate<=IDLE;
	elsif(rising_edge(iclK)) then
		sstate<=snextstate;
	end if;
	
 end process;

 process(sstate,snextstate,istart,sheat_cnt_tc,swarn_cnt_tc) begin
	
	snextstate<=sstate;
	
	case(sstate) is
	
	when IDLE=> 
		if(istart='1') then
			snextstate<=HEAT;
		end if;
	when HEAT =>
		if (sheat_cnt_tc='1') then
			snextstate<=warNING;
		end if;
	when WarNING=> 
		if(swarn_cnt_tc='1') then
			snextstate<=IDLE;
		end if;
		
	when others =>
		snextstate<=IDLE;
	end case;
 
 end process;
 
 
 process(sstate) begin
	
	case(sstate) is
	
		when HEAT=>
			sheat_cnt_en<='1';
			swarn_cnt_en<='0';
			sheat_en<= '1';
			swarn_en<='0';
		when WarNING=>
			sheat_cnt_en<='0';
			swarn_cnt_en<='1';
			sheat_en<= '0';
			swarn_en<='1';
		when others =>
			sheat_cnt_en<='0';
			swarn_cnt_en<='0';
			sheat_en<= '0';
			swarn_en<='0';
	end case;
	
 end process;

 process(iclK,irsT) begin
	
	if(irsT='0') then
		heat_cnt<=(others=>('0'));
	elsif(rising_edge(iclk) and sheat_cnt_en='1') then
		
		if(heat_cnt<iduration) then
			heat_cnt<=heat_cnt+1;
		else 
			heat_cnt<=(others=>('0'));
		end if;
	
	end if;
 
 end process;

sheat_cnt_tc<='1' when heat_cnt=iduration-1 else
				'0';

process (iclk,irst) begin
	
	if(irsT='0') then
		warn_cnt<=(others=>'0');
	elsif(rising_edge(iclk) and swarn_cnt_en='1') then
		
		if(warn_cnt<8-1) then
			warn_cnt<=warn_cnt+1;
		else
			warn_cnt<=(others=>('0'));
			
		end if;
		
	end if;

end process;

swarn_cnt_tc<= '1' when warn_cnt=7 else
					'0';

o150w<= sheat_en when isel="00" else
		'0';
o300w<= sheat_en when isel="01" else
		'0';
o650w<= sheat_en when isel="10" else
		'0';
o800w<= sheat_en when isel="11" else
		'0';
	
owaRN<=swarn_en;
end Behavioral;