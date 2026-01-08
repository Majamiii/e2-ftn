-- zadatak grupe pre moje sa klk
-- uslovni shifter koji logicki pomera za onoliko mesta koliko kaze jedan ulaz
-- i na kraju sabirac i izlaz se prenosi na dva izlaza

-- ??? ja cu implementirati da se sabira tipa stara vrednost iB sa ovom shiftovanom
-- i onda to na demultiplekser u zavisnosti od nekog iSEL
-- idk dobro je za vezbu svakako


library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity zadatak is
	port(
		iA : in std_logic_vector(1 downto 0);
		iB : in std_logic_vector(3 downto 0);
		iSEL : in std_logic;
		oY : out std_logic_vector(4 downto 0);
		oZ : out std_logic_vector(4 downto 0)
	);
end entity;

architecture Behavioral of zadatak is

	signal sCSHR : std_logic_vector(3 downto 0);
	signal sADD : std_logic_vector(4 downto 0);
	
begin
	--uslovni pomerac udesno
	sCSHR <= '0'&iB(3 downto 1) when iA="00" else
			"00"&iB(3 downto 2) when iA="01" else
			"000"&iB(3) when iA="10" else
			"0000";
			
	-- sabirac
	sADD <= ('0' & iB) + ('0' & sCSHR);
	
	-- demultiplekser
	oY <= sADD(4 downto 0) when iSEL='0' else "00000";
	oZ <= sADD(4 downto 0) when iSEL='1' else "00000";
	
	
end architecture;