library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- compuerta lógica AND

entity and_gate is
    Port ( a : in  STD_LOGIC;
           b : in  STD_LOGIC;
           s : out  STD_LOGIC);
end and_gate;

architecture Compuerta of and_gate is

begin

	s <= a AND b;

end Compuerta;

