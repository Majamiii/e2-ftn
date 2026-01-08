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


architecture Behavior of lprs_hello is
	signal sTC			: std_logic;
	signal sDIS_SEL 	: std_logic_vector(1 downto 0);

	--signal sDIS_CNT 	: std_logic_vector(14 downto 0); -- Sva slova se prikazuju "istovremeno"
	signal sDIS_CNT 	: std_logic_vector(21 downto 0);
	
	
	signal sDIS_7 : std_logic_vector(6 downto 0);
	
	--constant cDIS_MAX	: std_logic_vector(14 downto 0) := "111111111111111"; -- Sva slova se prikazuju "istovremeno"
	constant cDIS_MAX	: std_logic_vector(21 downto 0) := "1111111111111111111111";
	
begin
	-- brojac po modulu cDIS_MAX
	process (iCLK,iRST) begin
		if(iRST='1')then
			sDIS_CNT <= (others=>'0');
		elsif(rising_edge(iCLK)) then
			if (sDIS_CNT = cDIS_MAX) then
				sTC <= '1';
				sDIS_CNT <= (others => '0');
			else
				sTC <= '0';
				sDIS_CNT <= sDIS_CNT+1;
			end if;
		end if;
	end process;
	
	
	-- brojac po modulu 4 unazad
	
	process (iCLK,iRST) begin
		if(iRST='1')then
			sDIS_SEL <= "11";
		elsif(rising_edge(iCLK)) then
			if sTC='1' then
				if (sDIS_SEL = "00") then
					sDIS_SEL <= "11";
				else
					sDIS_SEL <= sDIS_SEL - 1;
				end if;
			end if;
		end if;
	end process;
	
	oDIS <= sDIS_SEL;
	
	
	-- MUX
	sDIS_7 <= "1110001" when sDIS_SEL="11" else
				 "0011000" when sDIS_SEL="10" else
				 "0001000" when sDIS_SEL="01" else
				 "0100100" when sDIS_SEL="00" else
				 "1111111";
				 
	o7SEGM <= sDIS_7;
	


end architecture;