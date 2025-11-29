library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity Semafor is
    port ( 	
				iclk   : in std_logic;
				inRst  : in std_logic;
				istart : in std_logic;
				
				iA0    : in std_logic;
				iA1    : in std_logic;
				iA2    : in std_logic;
				iA3    : in std_logic;
				iA4    : in std_logic;
				iA5    : in std_logic;
				iA6    : in std_logic;
				iA7    : in std_logic;
				
				iB0    : in std_logic;
				iB1    : in std_logic;
				iB2    : in std_logic;
				iB3    : in std_logic;
				iB4    : in std_logic;
				iB5    : in std_logic;
				iB6    : in std_logic;
				iB7    : in std_logic;

				oDONE    : out std_logic;
				oE : out std_logic;
				oOUT : out std_logic_vector(2 DOWnto 0));
end Semafor;

architecture Behavioral of Semafor is
	type stanje is(IDLE,C,DE,DUE);
	signal sstate,snextstate: stanje;
	signal count: std_logic_vector(2 downto 0);
	signal sBPE : std_logic;
	signal count_en: std_logic;
	signal sAi: std_logic;
	signal sBi: std_logic;
begin

 process(iclk,inrst) begin
	
	if (inrst='1') then
		sstate<=IDLE;
	elsif(rising_edge(iclk)) then
		sstate<=snextstate;
	end if;
 
 end process;
 
 
 process(sstate,snextstate,count,istart,SBPE) begin
	 
	 snextstate<=sstate;
	 
	 case(sstate) is
		when IDLE => 
			if (istart='1') then
				snextstate<=C;
			end if;
		when C => 
			if (sBPE='0') then
				snextstate<=DUE;
			elsif(count=7) then
				snextstate<=DE;
			end if;
		when DE =>
			snextstate<=DE;
		when DUE =>
			snextstate<=DUE;
		when OTHers =>
			snextstate<=IDLE;
	end case;
	
 end process;
 
 count_en<= '1' when sstate=C else
				'0';
 
 process (iclk,inrst) begin
	
	if(inrst='1') then
		count<=(others=>('0'));
	elsif (rising_edge(iclk) and count_en='1') then
		if (count<7) then
			count<=count+1;
		
		end if;
	end if;
end process;

sAi <= iA0 when count="000" else
		iA1 when count="001" else 
		iA2 when count="010" else 
		iA3 when count="011" else 
		iA4 when count="100" else 
		iA5 when count="101" else 
		iA6 when count="110" else 
		iA7 ;

sBi <= iB0 when count="000" else
		iB1 when count="001" else 
		iB2 when count="010" else 
		iB3 when count="011" else 
		iB4 when count="100" else 
		iB5 when count="101" else 
		iB6 when count="110" else 
		iB7 ;
	
SBPE <= sAi xnor sBi; 
	
oDoNE<= '1' when sstate=DE or sstate=DUE else
		'0';
oE<= '1' when sstate=DE else
	'0';
oOuT<= COUnt;
end Behavioral;


