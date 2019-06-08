library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity ffkj is
    Port ( j : in  STD_LOGIC;
           k : in  STD_LOGIC;
           Clk : in  STD_LOGIC;
           reset : in  STD_LOGIC;
           set : in  STD_LOGIC;
           Q : out  STD_LOGIC;
           Qn : out  STD_LOGIC);
end ffkj;

architecture Flip_flop of ffkj is
signal cuenta: natural range 0 to 25000001;
signal s1, Q1, Qn1: STD_LOGIC;
begin

process(clk)
begin
	if clk'event and clk = '1' then
		if cuenta = 25000000 then
			cuenta <= 0;
			s1 <= not s1; 
		else
			cuenta <= cuenta + 1;
		end if;
	end if;
end process;



process(j, k, s1, reset, set)
begin
	if reset = '1' then 
		Q1 <= '0';
		Qn1 <= '1';
	elsif (set = '1') then
		Q1 <= '1';
		Qn1 <= '0';
	else
		if(s1'event and s1 = '1') then
			if(j = '0' and k='0') then
				Q1 <= Q1;
				Qn1 <= Qn1;
			elsif (j = '0' and k='1') then
				Q1 <= '0';
				Qn1 <= '1';
			elsif (j = '1' and k = '0') then
				Q1 <= '1';
				Qn1 <= '0';
			else
				Q1 <= not Q1;
				Qn1 <= not Qn1;
			end if;
		end if;
	end if;
end process;
Q <= Q1;
Qn <= Qn1;

end Flip_flop;

