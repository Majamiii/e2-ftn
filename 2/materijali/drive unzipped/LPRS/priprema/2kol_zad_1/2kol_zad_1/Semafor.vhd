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
	
	type stanje is (IDLE,GREEN,YELLOW,RED_0,RED_1);
	
	signal sstate,snextstate: stanje;
	
	signal sCNT: std_logic_vector(3 downto 0);
	
	signal sR: std_logic;
	signal sY: std_logic;
	signal sG: std_logic;
	signal iR: std_logic;
	signal iY: std_logic;
	signal iG: std_logic;
	signal sB: std_logic;
	signal oB: std_logic;
	signal sEN: std_logic;
	signal oCNT_EN: std_logic;
	signal iBLink: std_logic;
	
begin
 
 process(iclk,inrST) begin
	
	if(inrst='1') then
		sstate<=IDLE;
	elsif(rising_edge(iclk)) then
		sstate<=snextstate;
	end if;
 
 end process;

 process(sstate,snextstate,iG,iR,iY,sCNT) begin
	
	snextstate<=sstate;
	
	case(sstate) is
		
	when IDLE=>
		if(iG='1') then
			snextstate<=GREEN;
		elsif(iY='1') then
			snextstate<=YELLOW;
		elsif(ir='1') then
			snextstate<=RED_0;
		end if;
	when GREEN => 
		if (scnt="0101") then
			snextstate<=IDLE;
		end if;
	when YELLOW => 
			snextstate<=IDLE;
	when RED_0 =>
			snextstate<=RED_1;
	when RED_1 =>
		if(scnt="1010") then
			snextstate<=IDLE;
		else
			snextstate<=RED_0;
		end if;
	when others =>
			snextstate<=IDLE;
	end case;
 
 end process;
 
 oB<= '0' when sstate=GREEN else
		'1';
  --control block
 sY <= '1' when sCNT =6 else
		'0';

 sR<= '1' when sCNT =7 else
		'0'; 
sG<= '1' when scnT=13 else
		'0';
 
iR<=sR;
iY<=sY;
iG<=sG;
 
oCNT_EN<='0' when sstate=YELLOW or sstate=RED_0 else
			'1';
--brojac
sEn<=oCNT_EN;
process (iclk,inRST) begin
	
	if(inRst='1') then
		sCNT<=(others=>('0'));
	elsif (rising_edge(iclk) and sEN='1') then
			if (scnt<14-1) then
				scnt<=scnt+1;
			else
				scnt<=(others=>('0'));
			end if;
	end if;

end process;
sb<=oB;
iBLink<=sB;
o_Y<='1' when sCNT=6 or sCNT=11 or sCNT =12 else
	'0';
o_R<= '1' when scnt=7 or scnt=8 or scnt=9 or scnt=10 or scnt=11 or scnt=12 else
		'0';
o_G<= '1' when scnt=0 or scnt=1 or scnt=2 or scnt=3 or scnt=13 else
		'0';

end Behavioral;