library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity Semafor is
    port ( 	iCLK    : in  std_logic;
				inRST    : in  std_logic;
				
				o_R   : out std_logic;
				o_Y : out std_logic;
				o_G : out std_logic);
end Semafor;

architecture Behavioral of Semafor is
	
	signal sCNT: std_logic_vector(3 downto 0);
	signal sD: std_logic_vector(3 downto 0);
	signal sWR_EN: std_logic;
	signal sCTRL: std_logic;
	type stanje is(IDLE,GREEN,YELLOW,RED,WRITE_CNT);
	signal sSTATE,sNEXTSTATE: stanje;
begin
 --brojac
 
 process (iclk) begin
	if(rising_edge(iclk)) then
		if (inrST='0') then
			sCnT<=(others=>('0'));
		elsif(sWR_EN='1')then
			sCNT<=SD;
		elsif(sCNT<9-1) then
			sCnT<=ScnT+1;
		else
			sCNT<=(others=>('0'));
		end if;
	end if;
 end process;
	
process (iclk) begin
	if (rising_edge(iclk)) then
			if(inrST='0') then
				sstate<=IDLE;
			else
				sstate<=sneXTSTATE;
			end if;
	end if;
end process;

process(sstate,sneXTSTATE,scnt,sctRL) begin
	
	sneXTSTATE<=sstate;
	
	case (sstate) is
		
		when IDLE => 
			if(scnt ="0000") then 
				sneXTSTATE<=GREEN;
			elsif(scnt="0011") then
				sneXTSTATE<=Red;
			end if;
		when GrEEN =>
			if(sCNT="0111") then
				sneXTSTATE<=YELLOW;
			end if;
		when RED=> 
			if(scnt="0111") then
				sneXTSTATE<=YELLOW;
			end if;
		when YELLOW =>
			if(scnt ="1000" and sCTRL='1') then
				sneXTSTATE<=write_cnt;
			elsif(scnt="1000" and sCtRL='0') then
				sneXTSTATE<=IDLE;
			end if;
		when WRIte_cnt =>
			sneXTSTATE<=idle;
		when others=> 
			sneXTSTATE<=idle;
	end case;

end process;

swr_EN<='1' when sstate=write_cnt else
			'0';
sD <= "0010" when sstate=write_cnt else
		"0000";
		
process (iclk) begin
		
		if(rising_edge(iclk)) then
			if(sneXTSTATE=GreEN) then
				sCTRL<='1';
			elsif (sneXTSTATE=YELLOW) then
				sCTRL<=sCtRL;
			else 
				sctRL<='0';
			end if;
		end if;
end process;

o_Y<='1' when sCNT=8 else 
	'0';
	
o_R<='1' when sCNT=3 or sCNT=4 or sCNT=5 or sCNT=6 or sCNT=7 else
		'0';
		
o_G<='1' when sCNT=0 or sCNT=1 or sCNT=2 or sCNT=3 or sCNT=4 or sCNT=5 or sCNT=6 or sCNT=7 else
		'0';







end Behavioral;