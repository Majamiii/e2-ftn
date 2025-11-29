
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;
use ieee.numeric_std.all;

entity lprs1_homework1 is
	port(
		i_x   :  in std_logic_vector(3 downto 0);
		i_y   :  in std_logic_vector(3 downto 0);
		i_z   :  in std_logic_vector(1 downto 0);
		i_sel :  in std_logic_vector(1 downto 0);
		o_res : out std_logic_vector(3 downto 0);
		o_cmp : out std_logic_vector(1 downto 0);
		o_enc : out std_logic_vector(1 downto 0)
	);
end entity;


architecture arch of lprs1_homework1 is
		signal s_shl, s_shr, s_dec, s_const0, s_const1, s_sub, s_add, s_mux: std_logic_vector(3 downto 0);
	
begin
		--Design.
		
      --logicki shift u levo za 3 mesta
		--logicki shift u desno za 1 mesto
		s_shr <= "0" & i_y(3 downto 1);
		s_shl <= i_x(0) & "000";
		
		--dekoder
		s_dec   <=  "0001" when i_z = "00" else
					"0010" when i_Z = "01" else
					"0100" when i_z = "10" else
					"1000" when i_z = "11" else 
					"0000";
		--sabirac
		s_add <= s_shl + s_shr;
		
		--oduzimanje:
		s_sub <= s_dec - i_x;
		
	-----------------------------------------------
	

		--dodela za konstantne signale:
		
		s_const0 <= "0011";
		s_const1 <= "1101";
		
		--multiplekser:
		
		s_mux <= s_const0 when i_sel = "11" else
					s_const1 when i_sel = "10" else
					s_add when i_sel = "01" else
					s_sub;
		
		--dodela vrednosti za o_res:
		
		o_res <= s_mux;
		
		--komparator koji postavlja bite izlaznog signala
		
		
		o_cmp(0) <= '1' when s_mux = 0 else
						'0';
		o_cmp(1) <= '1' when s_mux < 6 else
						'0';
		
		--enkoder o_enc izlaznog signala:
		
		o_enc <= "00" when s_mux(0) = '1' else
					"01" when s_mux(1) = '1' else
					"10" when s_mux(2) = '1' else
					"11";
	
end architecture;
