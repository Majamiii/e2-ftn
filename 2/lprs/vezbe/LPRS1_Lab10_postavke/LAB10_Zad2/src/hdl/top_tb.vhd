
----------------------------------------------------------------------------------
-- Logicko projektovanje racunarskih sistema 1
-- 2011/2012, 2023
--
-- Computer system top level testbench
--
-- authors:
-- Ivan Kastelan (ivan.kastelan@rt-rk.com)
-- Teodora Novkovic (teodora.novkovic@uns.ac.rs)
----------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
 
entity top_tb is
end top_tb;
 
architecture behavior of top_tb is 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    component top
    port(
         iCLK  : in  std_logic;
         iRST  : in  std_logic;
         oLED  : out  STD_LOGIC_VECTOR (15 downto 0)
        );
    end component;
    

   --Inputs
   signal iCLK : std_logic := '0';
   signal iRST : std_logic := '0';
   signal oLED : std_logic_vector (15 downto 0);

   -- Clock period definitions
   constant iCLK_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: top port map (
          iCLK => iCLK,
          iRST => iRST,
          oLED => oLED
        );

   -- Clock process definitions
   iCLK_proc: process
   begin
		iCLK <= '0';
		wait for iCLK_period/2;
		iCLK <= '1';
		wait for iCLK_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin
   
      iRST <= '1';
      wait for 3.25*iCLK_period;
      iRST <= '0';

      wait;
   end process;

end;
