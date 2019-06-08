library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- compuerta l�gica OR

entity OR_gate is
    Port ( a : in  STD_LOGIC;
           b : in  STD_LOGIC;
           s : out  STD_LOGIC);
end OR_gate;

architecture Compuerta of OR_gate is

begin

	s <= a OR b;

end Compuerta;

