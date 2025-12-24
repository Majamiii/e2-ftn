library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity lprs_hello is
port(
	iRST  : in  std_logic;
	iCLK  : in  std_logic;
	oDIS  : out std_logic_vector(1 downto 0);
	o7SEGM : out std_logic_vector(6 downto 0)
);
end entity;

-- Na sedmosegmentnim displejima prikazuju se slova LPRS. U zavisnosti od modula brojača
-- sDIS_CNT slova se prikazuju istovremeno ili se prikazuju jedno za drugim. Manji 
-- moduo rezultuje brzim izmjenama te ih oko ne registruje, pa djeluje 
-- kao da su sva 4 displeja aktivna u isto vrijeme.

architecture Behavior of lprs_hello is
signal sTC			: std_logic;
signal sDIS_SEL 	: std_logic_vector(1 downto 0);

--signal sDIS_CNT 	: std_logic_vector(14 downto 0); -- Sva slova se prikazuju "istovremeno"
signal sDIS_CNT 	: std_logic_vector(21 downto 0);


--constant cDIS_MAX	: std_logic_vector(14 downto 0) := "111111111111111"; -- Sva slova se prikazuju "istovremeno"
constant cDIS_MAX	: std_logic_vector(21 downto 0) := "1111111111111111111111";

begin

-- Određuje brzinu prikaza
process(iCLK, iRST)begin
		if(iRST='1')then
			sDIS_CNT<=(others=>'0');
		elsif(iCLK'event and iCLK='1')then
			if(sDIS_CNT=cDIS_MAX) then
				sDIS_CNT<=(others=>'0');
			else
				sDIS_CNT<=sDIS_CNT+1;
			end if;
		end if;
end process;

sTC<='1' when sDIS_CNT=cDIS_MAX else '0';

-- Određuje koji se displej (slovo) aktivira
process(iCLK, iRST)begin
		if(iRST='1')then
			sDIS_SEL<= "11";
		elsif(iCLK'event and iCLK='1')then
			if(sTC='1')then
				if(sDIS_SEL=0)then
					sDIS_SEL<= "11";
				else					
					sDIS_SEL<=sDIS_SEL-1;
				end if;	
			end if;
		end if;
end process;

oDIS <= sDIS_SEL;

process(sDIS_SEL) begin
		case sDIS_SEL is 
			when "11" => o7SEGM <= "1110001"; -- L
			when "10" => o7SEGM <= "0011000"; -- P
			when "01" => o7SEGM <= "0001000"; -- R
			when "00" => o7SEGM <= "0100100"; -- S 
			when others => o7SEGM <= "1111111";
		end case;
end process;

end architecture;