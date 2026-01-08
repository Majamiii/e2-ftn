library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity Slozeni is port (
		iCLK   : in  std_logic;
      iRST   : in  std_logic;
      iEN    : in  std_logic;
		oCNT   : out std_logic_vector (7 downto 0);
      oSHREG : out  std_logic_vector (7 downto 0)
		);
end entity;

architecture Behavioral of Slozeni is

	signal sCNT   : std_logic_vector (7 downto 0);
	signal sSHREG : std_logic_vector (7 downto 0);
	signal sLOAD  : std_logic;
	signal sARITH : std_logic;

begin
 -- Counter 8bit --
    process (iCLK, iRST) begin
        if (iRST = '1') then
            sCNT <= "00000000";
        elsif (iCLK'event and iCLK = '1') then
            if (iEN = '1') then
                sCNT <= sCNT + 1;
            end if;
        end if;
    end process;
	 
	 -- Shift register 8bit --
	 process (iCLK, iRST) begin
        if (iRST = '1') then
            sSHREG <= "00000000";
        elsif (iCLK'event and iCLK = '1') then
            if (sLOAD = '1') then
                sSHREG <= sCNT;   -- if sCNT = 8 or sCNT = 128 -> load
				else
					if (sARITH = '1') then 
                   sSHREG <= sSHREG(7) & sSHREG(7 downto 1); -- shift right arith
					else                   
						 sSHREG <= sSHREG(6 downto 0) & '0';  		 -- shift left logic
					end if;
            end if;
        end if;
    end process;
	 
	 
	 
	 -- Shifter and counter rules --
	 
	 sLOAD <= '1' when (sCNT = 8 or sCNT = 128) else  -- load if counter = 8 or counter = 128
				 '0';
	 
	 sARITH <= '1' when sCNT > 128 else  	-- shift arith right
				  '0';                      	-- shift logic left
				  
	 oSHREG <= sSHREG;
	 oCNT <= sCNT;

end architecture;
