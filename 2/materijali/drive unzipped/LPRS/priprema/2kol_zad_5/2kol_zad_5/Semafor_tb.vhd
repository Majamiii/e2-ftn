library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all; 
 
entity Semafor_tb is
end Semafor_tb;
 
architecture Test of Semafor_tb is 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    component Semafor
    port(		iCLK    : in  std_logic;
					inRST    : in  std_logic;
					iCAR    : in  std_logic_vector (1 downto 0);
					
					oTOTAL    : out std_logic_vector(7 downto 0);
					oOPEN : out std_logic;
					oWARNING : out std_logic);
    end component;
    
   --Inputs
   signal sCLK : std_logic ;
   signal sRST : std_logic ;
   signal sCAR  : std_logic_vector(1 downto 0) ;
  
 	--Outputs
   signal sTOTAL    : std_logic_vector(7 downto 0);
   signal sOPEN: std_logic;
	signal sWARNING  : std_logic;

	
   -- Clock period definitions
   constant iCLK_period : time := 10 ns;
 
begin
 
	-- Instantiate the Unit Under Test (UUT)
   uut: Semafor port map (
          iCLK => sCLK,
          inRST => sRST,
          iCAR => scaR,
			 
          oTOTAL => sTOTAL,
			 oOPEN => sOPEN,
			 oWARNING => sWARNING);

   -- Clock process definitions
   iCLK_process :process
   begin
		sCLK <= '0';
		wait for iCLK_period/2;
		sCLK <= '1';
		wait for iCLK_period/2;
   end process;
 
 
	stim_proc: process
	begin
	
	sRST <= '1';
	wait for 5.24 * iCLK_period;
	sRST <= '0';
	
	--------------------------
	
	sCAR <= "01";
	wait for iCLK_period;
	sCAR <= "00";
	wait for 15 * iCLK_period;
	
	--------------------------
	
	sCAR <= "01";
	wait for 2 * iCLK_period;
	
	sCAR <= "10";
	wait for iCLK_period;
	sCAR <= "00";
	
	--------------------------
	wait for 5 * iCLK_period;
	--------------------------
	
	sCAR <= "01";
	wait for iCLK_period;
	wait for 22 * iCLK_period;
	
	sCAR <= "10";
	wait for iCLK_period;
	
	---------------------
	wait for 5 * iCLK_period;
	-----------------------------
	
	sCAR <= "10";
	wait for iCLK_period;
	sCAR <= "00";
	

  ---- Stimulus process
  --stim_proc: process
  --begin		
  --  
	--srst<='1';
	--scar<="00";
	--wait for 2.25*iclK_period;
	--srst<='0';
	--wait for iclK_period;
	--
	--scar<="01";
	--wait for iclK_period;
	--scar<="00";
	--wait for 5* iclK_period;
	--
	--scar<="01";
	--wait for iclK_period;
	--scar<="00";
	--wait for 2*iclK_period;
	--scar<="10";
	--wait for iclK_period;
	--scar<="00";
	--wait for 5* iclK_period;
	--
	--scar<="01";
	--wait for iclK_period;
	--scar<="00";
	--wait for 22*iclK_period;
	--scar<="10";
	--wait for iclK_period;
	--scar<="00";
	--wait for 5*iclK_period;
--
	--scar<="10";
	--wait for iclK_period;
	--scar<="00";
	--wait for 5*iclK_period;
	
	wait;
	end process;
end;