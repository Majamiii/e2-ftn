library IEEE;
use ieee.std_logic_1164.all;
use ieee. std_logic_signed.all;

entity zadatak is
    Port ( iCLK    : in  std_logic;
           iRST    : in  std_logic;
           iEN     : in  std_logic;
			  iA		 : in std_logic_vector(7 downto 0); -- ulazi u pomerac, comp2
			  iB		 : in std_logic_vector(4 downto 0); -- ulazi u blok F(x), comp2
			  iC		 : in std_logic_vector(6 downto 0); -- prvi sabirak, c2
			  iD		 : in std_logic_vector(6 downto 0); -- drugi sabirak, c2
			  oRESULT : out std_logic_vector(7 downto 0); -- izlaz iz MUX, c2
			  oCOMP   : out std_logic	-- izlaz iz komparatora
			  );
end zadatak;

architecture Behavioral of zadatak is
	
		signal sCOUNT : std_logic_vector(5 downto 0);
		signal sPOM : std_logic_vector(7 downto 0);
		signal sFX : std_logic_vector(7 downto 0);
		signal sBB : std_logic_vector(4 downto 0);
		signal sADD : std_logic_vector(7 downto 0);
		signal sCONST : std_logic_vector(7 downto 0);
		signal sRES : std_logic_vector(7 downto 0);
		signal sSEL : std_logic_vector(1 downto 0);
		signal sCOMP : std_logic;
		

begin

	process(iCLK, iRST) begin
		if(iRST='1')then
			sCOUNT <= (others => '0');
		elsif(rising_edge(iCLK)) then
			if(iEN='1') then
				if (sCOUNT = 24) then
					sCOUNT<=(others=>'0');
				else
					sCOUNT<= sCOUNT+1;
				end if;
			end if;
		end if;		
	end process;
	
	-- Pomerač pomera ulazni signal iA za 4 mesta udesno i to aritmetički.
	sPOM <= iA(7) & "000" & iA(7 downto 4);
	
	sBB <= iB + 7;
	sFX <= "000" & sBB;
	
	sADD <= (iD(6)&iD) + (iC(6)&iC);
	
	sCONST <= "00010010"; -- 18
	
	sSEL <= sCOUNT(1 downto 0);
	
	sRES <= sPOM when sSEL="00" else
			  sFX when sSEL="01" else
			  sADD when sSEL="10" else
			  sCONST;
			  
	oRESULT <= sRES;
	
	sCOMP <= '1' when sRES>0 else '0';
	oCOMP <= sCOMP;
	

end Behavioral;