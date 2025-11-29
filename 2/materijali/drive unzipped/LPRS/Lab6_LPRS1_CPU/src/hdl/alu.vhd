
----------------------------------------------------------------------------------
-- Logicko projektovanje racunarskih sistema 1
-- 2011/2012,2021-2022
--
-- Arithmetic-Logic Unit
--
-- authors:
-- Ivan Kastelan (ivan.kastelan@rt-rk.com)
-- Milos Subotic (milos.subotic@uns.ac.rs)
----------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity alu is
	port (
		iA     : in  std_logic_vector(15 downto 0);
		iB     : in  std_logic_vector(15 downto 0);
		iSEL   : in  std_logic_vector(3 downto 0);
		oC     : out std_logic_vector(15 downto 0);
		oSIGN  : out std_logic;
		oCARRY : out std_logic;
		oZERO  : out std_logic
	);
end entity alu;

architecture arch of alu is

	signal sA : std_logic_vector(16 downto 0);
	signal sB : std_logic_vector(16 downto 0);
	signal sC : std_logic_vector(16 downto 0);

begin
    -- Sign extensions.
    --TODO

    -- Mux with arithmetic-logical operations.
    --TODO
    
	 -- Flags.
    --TODO

end architecture;
